#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define BUFFER_SIZE 	100

int sockfd = -1;

void uninit(int sig)
{
	close(sockfd);
	printf("close sock\n");
	exit(0);
}

int main(int argc, char *argv[])
{
	signal(SIGTERM, uninit);
	signal(SIGINT, uninit);
	signal(SIGPIPE, SIG_IGN);
//	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	int i, byte;
	char char_send[100] = { 0 };
	if(argc != 3)
	{
		printf("usage: client <address> <port> \n");
		return 1;
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &address.sin_addr);
	len = sizeof(address);

	if((result = connect(sockfd, (struct sockaddr *)&address, len)) < 0)
	{
		printf("connect %s error %s\n", inet_ntoa(address.sin_addr), strerror(errno));
		exit(1);
	}
	while(1)
	{
		char buf[BUFFER_SIZE] = {0};
		bzero(buf, BUFFER_SIZE);
//		recv(sockfd, buf, BUFFER_SIZE, 0);
//		printf("%s\n", buf);
		scanf("%s", char_send);
		fflush(stdin);

		if(strcmp(char_send, "exit") == 0)
		{
			if((byte = send(sockfd, char_send, sizeof(char_send), 0)) < 0)
			{
				printf("send error\n");
				exit(1);
			}
			break;
		}
		if((byte = send(sockfd, char_send, sizeof(char_send), 0)) <= 0)
		{
			printf("send error\n");
			exit(1);
		}
		printf("send size: %d\n", byte);
	}
	close(sockfd);
	return 0;
}
