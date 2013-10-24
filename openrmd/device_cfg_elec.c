#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include "device_cfg.h"
#include "getcfg.h"

#define TYPE_ELEC	13

static MYSQL mysql;
static MYSQL_RES *res = NULL;
static MYSQL_ROW row;

int get_sys_param(char *param, char *val, size_t max_len)
{
	char sql[512];
	snprintf(sql, sizeof(sql), "SELECT Con FROM Sys_Man_Info"
			" WHERE Para = '%s'", param);
	if (mysql_query(&mysql, sql) != 0)
		return -1;
	if ((res = mysql_store_result(&mysql)) == NULL || 
			mysql_num_rows(res) <= 0) {
		mysql_free_result(res);
		return -1;
	}

	while ((row = mysql_fetch_row(res)) != NULL) {
		snprintf(val, max_len, "%s", row[0]);
		break;
	}
	mysql_free_result(res);
	return 0;
}

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

	/* get elec platform's ip and port */
	char plat_ip[32], plat_port[16];
	if (get_sys_param("ISDServerIP", plat_ip, sizeof(plat_ip)) != 0) {
		printf("get platform's IP error\n");
		goto err;
	}
	if (get_sys_param("RealTransferPort", plat_port, sizeof(plat_port)) 
			!= 0) {
		printf("get platform's port error\n");
		goto err;
	}

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
	channel_cfg_t cfg;
	snprintf((char *)sql, sizeof(sql), "select DevID,"
	  "if((MaxIPChans > 0), (MaxIPChans + 32), VideoInNum) AS VideoInNum"
	  " from Device_DVR_Basic_Info order by DevID");

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

	cfg.type = TYPE_ELEC;
	snprintf(cfg.ip, sizeof(cfg.ip), plat_ip);
	cfg.port = atoi(plat_port);
	snprintf(cfg.user, sizeof(cfg.user), "xx");
	snprintf(cfg.pwd, sizeof(cfg.pwd), "xx");
	snprintf(cfg.rec, sizeof(cfg.rec), "xx");
	cfg.storage_device_type = 0;
	snprintf(cfg.storage_ip, sizeof(cfg.storage_ip), "xx");
	cfg.storage_port = 0;
	snprintf(cfg.storage_user, sizeof(cfg.storage_user), "xx");
	snprintf(cfg.storage_pwd, sizeof(cfg.storage_pwd), "xx");
	cfg.storage_disk = 0;
	cfg.baud_rate = 0;
	while ((row = mysql_fetch_row(res)) != NULL) {
		cfg.id = atoi(row[0]);
		cfg.channel_num = atoi(row[1]);

		snprintf(line, sizeof(line),
			"%d;%d;%s;%d;%s;%s;%d;%s;%d;%s;%d;%s;%s;%d;%d;\n", 
			cfg.type,
			cfg.id,
			cfg.ip,
			cfg.port, 
			cfg.user,
			cfg.pwd,
			cfg.channel_num,
			cfg.rec,
			cfg.storage_device_type,
			cfg.storage_ip,
			cfg.storage_port,
			cfg.storage_user,
			cfg.storage_pwd,
			cfg.storage_disk,
			cfg.baud_rate);
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
