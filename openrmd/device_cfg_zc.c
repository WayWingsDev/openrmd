#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include "device_cfg.h"
#include "getcfg.h"
#include "localip.h"

#define TYPE_ELEC	13

static MYSQL mysql;
static MYSQL_RES *res = NULL;
static MYSQL_ROW row;

int device_cfg_init()
{
	return 0;
}

int device_cfg_get(int old_ver, char **buff, int *length)
{
	my_bool reconn = 1;
	char sql[512];
	char ip[32], user[256], pwd[64], db[64];
	char line[256];
	*buff = NULL;
	*length = 0;

	/* get local IP address */
	int rmd_id;
	char interface[64], local_ip[32];
	if (getcfg(cfg_file, "interface", interface, GETCFG_STR) != 0) {
		printf("can't get network interface, use eth0\n");
		snprintf(interface, sizeof(interface), "eth0");
	}
	if (localip(interface, local_ip, sizeof(local_ip)) != 0) {
		printf("get %s ip address error\n", interface);
		return -1;
	}

	if (getcfg(cfg_file, "db_mysql_ip", ip, GETCFG_STR) != 0 ||
			getcfg(cfg_file, "db_mysql_user", user, 
				GETCFG_STR) != 0 ||
			getcfg(cfg_file, "db_mysql_pwd", pwd, 
				GETCFG_STR) != 0 ||
			getcfg(cfg_file, "db_mysql", db, GETCFG_STR) != 0) {
		printf("can't get database info from config file\n");
		return -1;
	}

	mysql_init(&mysql);

	/* NOTE: MYSQL_OPT_RECONNECT support from MySQL 5.0.13. */
	if (mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk") ||
			mysql_options(&mysql, MYSQL_OPT_RECONNECT, &reconn)) {
		printf("Error:mysql_options()\n");
		return -1;
	}
	if (mysql_real_connect(&mysql, ip, user, pwd, db, 0, NULL, 0) 
			== NULL) {
		goto err;
	}

	snprintf((char *)sql, sizeof(sql), "select A.ID "
	  "from Server_Software_Info As A, Device_Server_Basic_Info As B "
	  "where A.ServerType='1' and A.DeviceID=B.ID and B.IP='%s'", local_ip);
	if (mysql_query(&mysql, sql) != 0) {
		printf("get rmd_id error\n");
		goto err;
	}
	if ((res = mysql_store_result(&mysql)) == NULL || 
			mysql_num_rows(res) <= 0)
		goto err;
	row = mysql_fetch_row(res);
	if (row == NULL)
		goto err;
	rmd_id = atoi(row[0]);
	printf("rmd_id: %d\n", rmd_id);
	mysql_free_result(res);

	snprintf(line, sizeof(line), "version=%d\n\n", old_ver);
	if (add_line(buff, length, line) != 0) {
		printf("[%s]\n", line);
		goto err;
	}
	if (add_line(buff, length, "#driver_type;dev_id;ip;port;user;pwd;"
				"channels;rec;type;ip;port;user;pwd;disk;"
				"baud_rate\n\n") != 0)
		goto err;

	/* get devices */
	snprintf((char *)sql, sizeof(sql), "select ProID, ID, IP, Port, "
	  "UserName, Password, ChanQuans, storageType, storageIP, storagePort,"
	  "storageUser, storagePwd, disk, baud from v_device_info where "
	  "RS_ID = %d", rmd_id);
	if (mysql_query(&mysql, sql) != 0) {
		printf("Error:mysql_query() when get devices\n");
		goto err;
	}
	if ((res = mysql_store_result(&mysql)) == NULL) {
		printf("Error:mysql_store_result() at get devices\n");
		goto err;
	}
	if (mysql_num_rows(res) <= 0)
		goto err;

	while ((row = mysql_fetch_row(res)) != NULL) {
		int channel_num = atoi(row[6]);
		char rec[256];
		if (channel_num <= 0 || channel_num > (sizeof(rec) - 1))
			continue;
		memset(rec, '1', channel_num);
		rec[channel_num] = '\0';

		snprintf(line, sizeof(line),
			"%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", 
			row[0], row[1],  row[2],  row[3],  row[4], 
			row[5], row[6],  rec,     row[7],  row[8], 
			row[9], row[10], row[11], row[12], row[13]);
		if (add_line(buff, length, line) != 0)
			goto err;
	}

	mysql_free_result(res);
	mysql_close(&mysql);
	return 0;

err:
	mysql_close(&mysql);
	return -1;
}

int device_cfg_cleanup()
{
	return 0;
}
