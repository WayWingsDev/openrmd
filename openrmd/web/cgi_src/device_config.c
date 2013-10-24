#include <stdio.h>
#include <string.h>

/* device configure info */
typedef struct {
	int  type;
	int  id;
	char ip[32];
	int  port;
	char user[20];
	char pwd[20];
	int  channel_num;
	char rec[128];
	int  storage_device_type;
	char storage_ip[32];
	int  storage_port;
	char storage_user[20];
	char storage_pwd[20];
	int  storage_disk;
	int  baud_rate;
} device_cfg_t;

void cameras()
{
	FILE *fp;
	char line[512];
	device_cfg_t device;

	fp = fopen("/programs/openrmd/device.conf", "r");
	if (fp == NULL) {
		printf("open device configure file error!<br>");
		return;
	}

	printf("<p><H3>CAMERAS INFO:</H3>");
	while (fgets(line, sizeof(line), fp) != NULL) {
		if (line[0] == '#' || line[0] == '/' || strlen(line) == 1)
			continue;

		if (sscanf(line, "%d;%d;%[^;];%d;%[^;];%[^;];%d;%[^;];"
				"%d;%[^;];%d;%[^;];%[^;];%d;%d;",
				&device.type,
				&device.id,
				device.ip,
				&device.port,
				device.user,
				device.pwd,
				&device.channel_num,
				device.rec,
				&device.storage_device_type,
				device.storage_ip,
				&device.storage_port,
				device.storage_user,
				device.storage_pwd,
				&device.storage_disk,
				&device.baud_rate) != 15)
			continue;
		printf("%2d %3d %15s %5d %2d %15s:%2d<br>", 
				device.type,
				device.id,
				device.ip,
				device.port,
				device.storage_device_type,
				device.storage_ip,
				device.storage_disk);
	}

	fclose(fp);
}

int main(int argc, char **argv)
{
	printf("Content-type: text/html\n\n");
	cameras();
	return 0;
}
