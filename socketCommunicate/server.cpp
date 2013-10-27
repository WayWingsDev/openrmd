#include <iostream>
#include <pthread.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <netinet/tcp.h>
#include <signal.h>

//using namespace std;

#define PORT		 	5566		//port num of sock
#define BACKLOG			2048		//max connections of sock, 2nd arg of listen
#define MAXCLIENTS		100			//max client num 
#define EVENTS			1024		//max events of epoll_wait()
#define KEEPALIVE_IDEL	60			//start keepalives after period(seconds)
#define KEEPALIVE_CNT	6			//number of keepalives before death
#define KEEPALIVE_INTV	10			//interval of keepalives
#ifndef BUFSIZE
#define BUFSIZE			100
#endif

struct fd_t
{
	int sockfd;
	int epfd;
};

int g_epfd;
int g_sockfd;
static int SockClient[MAXCLIENTS] = {0};
static int icount = 0;
int client_in(int, int);
int client_out(int, int);
void data_in(int, int);
void del_invalid_client(int);

#ifndef PATH_MAX
#define PATH_MAX 512
#endif
/* value type */
typedef enum {
	GETCFG_INT32,	/* int */
	GETCFG_UINT32,	/* unsigned int */
	GETCFG_UINT64,	/* unsigned long long */
	GETCFG_STR	/* string */
} getcfg_val_t;

int getcfg(char *file, char *key, void *val, getcfg_val_t t)
{
	FILE *fp;
	char line[PATH_MAX], pkey[PATH_MAX], pval[PATH_MAX];

	char buff[PATH_MAX];
	char *p;
	if (readlink("/proc/self/exe", buff, PATH_MAX) <= 0)
		return -1;
	printf("working path: %s\n", buff);
	if((p = strrchr(buff, '/')) == NULL)
		return -1;
	char abs_path[PATH_MAX];
	snprintf(abs_path, PATH_MAX, "%s%c%s", buff, '/', file);
	printf("absolute path: %s\n", abs_path);

	if ((fp = fopen(file, "r")) == NULL)
		return -1;

	while (fgets(line, sizeof(line), fp) != NULL) {
		if (sscanf(line, "%[^=]=%s", pkey, pval) != 2 ||
				strcmp(pkey, key) != 0)
			continue;

		if (t == GETCFG_INT32)
			*(int *)val = atol(pval);
		else if (t == GETCFG_UINT32)
			*(uint32_t *)val = strtoul(pval, NULL, 0);
		else if (t == GETCFG_UINT64)
			*(uint64_t *)val = strtoull(pval, NULL, 0);
		else
			snprintf((char*)val, strlen(pval) + 1, pval);

		fclose(fp);
		return 0;
	}

	fclose(fp);
	return -1;
}

void *loop_thread(void *fdall)
{
	fd_t fd = *((fd_t *)fdall);
	int sockfd = fd.sockfd;
	int epfd = fd.epfd;
	printf("sockfd: %d, epfd: %d\n", sockfd, epfd);
	struct epoll_event ev, events[EVENTS];
	while(1)
	{
		int epoll_events = epoll_wait(epfd, events, EVENTS, -1);
		if (epoll_events == -1 && errno != EINTR)
		{
			printf("epoll_wait(): %s", strerror(errno));
			break;
		}
		for(int i = 0; i < epoll_events; i++)
		{
			if( (events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP)
					|| (!(events[i].events & EPOLLIN)) )
			{
				client_out(events[i].data.fd, epfd);	
				continue;
			}
			if(events[i].data.fd == sockfd)
				client_in(sockfd, epfd);
			else
				data_in(events[i].data.fd, epfd);
		}
	}
}

int set_nonblock(int sockfd)
{
	return fcntl(sockfd, F_SETFL, O_NONBLOCK | fcntl(sockfd, F_GETFL));
}

int set_keepalive(int sockfd ,int idel, int count, int interval)
{
	int k = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &k, sizeof(int));
	setsockopt(sockfd, SOL_TCP, TCP_KEEPIDLE, &idel, sizeof(int));
	setsockopt(sockfd, SOL_TCP, TCP_KEEPCNT, &count, sizeof(int));
	setsockopt(sockfd, SOL_TCP, TCP_KEEPINTVL, &interval, sizeof(int));

	return 0;
}

char *getcliip(const int sock)
{
	char *cliip = NULL;
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);

	if(getpeername(sock, (struct sockaddr *)&addr, &len) == 0)
		cliip = inet_ntoa(addr.sin_addr);
	return cliip;
}

void uninit(int sig)
{
	close(g_sockfd);
	printf("close sock\n");
	close(g_epfd);
	printf("close epoll\n");
	exit(0);
}

int main(int argc, char *argv[])
{
	signal(SIGTERM, uninit);
	signal(SIGINT, uninit);
	signal(SIGPIPE, SIG_IGN);
	int sockfd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	struct sockaddr_in clients[MAXCLIENTS];
	int sin_size, port;
	int reuse = 1;
	pthread_t tidsend, tidrecv;
	sin_size = sizeof(struct sockaddr_in);

/*	if(argc != 2)
	{
		printf("%s paramete error! try again with port num\a\n", argv[0]);
		exit(1);
	}
	if((port = atoi(argv[1])) < 0)
	{
		printf("Usage: %s port\n", argv[0]);
		exit(1);
	}
	*/
	if(getcfg("sockcfg", "port", &port, GETCFG_INT32) != 0)
	{
		printf("cannot get cfg info \n");
		exit(1);
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("Socket error: %s\n", strerror(errno));
		exit(1);
	}
	g_sockfd = sockfd;

	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(port);

	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1)
	{
		printf("Setsocketopt error: %s\n", strerror(errno));
		exit(1);
	}


	if(bind(sockfd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr)) == -1)
	{
		printf("Bind error:%s\n", strerror(errno));
		exit(1);
	}
	printf("Bind server: %s %d\n", inet_ntoa(server_addr.sin_addr), port);
	if(listen(sockfd, BACKLOG) == -1)
	{
		printf("Listen error:%s\n", strerror(errno));
		exit(1);
	}

	struct epoll_event ev, events[EVENTS];
	int epfd = epoll_create(MAXCLIENTS);
	if(epfd == -1)
	{
		fprintf(stderr, "epoll_create error: %s\n\a", strerror(errno));
		exit(1);
	}
	g_epfd = epfd;
	printf("Socket: %d\n", sockfd);
	printf("Epoll create: %d \n", epfd);

	ev.data.fd = sockfd;
	ev.events = EPOLLIN;

	if(epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev) == -1)
	{
		fprintf(stderr, "epoll_ctl: %s\n\a", strerror(errno));
		close(sockfd);
		exit(1);
	}

	pthread_t thread;
	struct fd_t fd;
	fd.sockfd = sockfd;
	fd.epfd = epfd;
	/*
	if(pthread_create(&thread, NULL, loop_thread, &fd) != 0)
	{
		printf("pthread_create error: %s\n", strerror(errno));
	}
	else
		pthread_detach(thread);
	printf("thread create \n");	
	*/
	while (1)
	{
		loop_thread(&fd);
	}
	//close(sockfd);
//	exit(0);
}	

void data_in(int sockfd, int epfd)
{
	int i, byte = 0;
	char char_recv[100];
//	while(1)
	{
		if((byte = recv(sockfd, char_recv, BUFSIZE, 0)) < 0)
		{
			printf("recv error: %s\n", strerror(errno));
			client_out(sockfd, epfd);
		}
		else if(byte > 0)
		{
			char_recv[byte] = '\0';
			printf("recv : %s\n", char_recv);

			for(i = 0; i < icount; i++)
			{
				printf("client %d is %d\n", i, SockClient[i]);
//				if(sockfd != SockClient[i])
				{
					int size = 0;
					if((size = send(SockClient[i], char_recv, byte, 0)) < 0)
					{
						printf("send error: %s\n", strerror(errno));
						del_invalid_client(SockClient[i]);
					}
					else
						printf("send ok, size is %d\n", size);
				}
			}
		}
	}
}

int client_in(int sockfd, int epfd)
{
	while(1)
	{
		struct epoll_event ev;
		struct sockaddr_in client_addr;
		int sin_size = 0;
		sin_size = sizeof(struct sockaddr_in);
		int newsockfd = accept(sockfd, (struct sockaddr *)(&client_addr), (socklen_t *)&sin_size);
		if(newsockfd == -1)
		{
			printf("accept error:%s\n\a", strerror(errno));
			exit(1);
		}

		ev.events = EPOLLIN;
		ev.data.fd = newsockfd;
		if(epoll_ctl(epfd, EPOLL_CTL_ADD, newsockfd, &ev) == -1)
		{
			fprintf(stderr, "epoll_ctl error: %s\n\a", strerror(errno));
			close(newsockfd);
			exit(1);
		}

	//	char buf[] = "you are connected to server";
	//	send(newsockfd, buf, sizeof(buf), 0);
		printf("[Client in %s, fd is %d]\n", inet_ntoa(client_addr.sin_addr), newsockfd);
		SockClient[icount++] = newsockfd;
		set_keepalive(newsockfd, KEEPALIVE_IDEL, KEEPALIVE_CNT, KEEPALIVE_INTV);
		printf("Now Count is %d\n", icount);
		return newsockfd;	
	}
}

int client_out(int sockfd, int epfd)
{
	printf("[Client out %s, fd is %d]\n", getcliip(sockfd), sockfd);

	if(epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL) != 0)
		printf("remove client error: %s[fd=%d]", strerror(errno), sockfd);

	close(sockfd);

	del_invalid_client(sockfd);

	return 1;
}

void del_invalid_client(int sockfd)
{
	for(int i = 0; i < icount; i++)
	{
		if(sockfd == SockClient[i])
		{
			for(int j = i; j < icount - 1; j++)
				SockClient[j] = SockClient[j+1];
			icount--;
		}
	}
	printf("Now Count is %d\n", icount);
}
