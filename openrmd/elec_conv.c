#include <mysql.h>
#include "elec_conv.h"
#include "rmd.h"
#include "hash.h"
#include "getcfg.h"

#define ELEC_DRIVER_TYPE_ID	13	/* should equal with librmd_elec.so */
#define CODE_FIXED_BITS		12 	/* the first 12 bit is fixed */

static hash_table_t *conv_table = NULL;

typedef struct {
	unsigned int code;
	char	plat[32];
	int	device_type;
	int	device_id;
	int	device_sub_id;
	int	channel_id;
} conv_channel_info_t;

static inline unsigned int hash_func_channel(const int table_size, void *data)
{
	conv_channel_info_t *ptr = (conv_channel_info_t *)data;
	return (unsigned int)(ptr->code % table_size);
}

static inline int cmp_func_channel(void *data, void *param)
{
	conv_channel_info_t *info = (conv_channel_info_t *)data;
	return (info->code == (unsigned int)param ? 0 : -1);
}

static int get_devices()
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	my_bool reconn = 1;
	char sql[512];
	char ip[32], user[256], pwd[64], db[64];

	if (getcfg(cfg_file, "db_mysql_ip", ip, GETCFG_STR) != 0 ||
			getcfg(cfg_file, "db_mysql_user", user, 
				GETCFG_STR) != 0 ||
			getcfg(cfg_file, "db_mysql_pwd", pwd, 
				GETCFG_STR) != 0 ||
			getcfg(cfg_file, "db_mysql", db, GETCFG_STR) != 0) {
		syslog(LOG_DEBUG, "Can't get database info from config file.");
		return -1;
	}

	mysql_init(&mysql);

	/* NOTE: MYSQL_OPT_RECONNECT support from MySQL 5.0.13. */
	if (mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk") ||
			mysql_options(&mysql, MYSQL_OPT_RECONNECT, &reconn)) {
		syslog(LOG_ERR, "Error:mysql_options().");
		return -1;
	}

	while (mysql_real_connect(&mysql, ip, user, pwd, db, 0, NULL, 0) == 
			NULL) {
		mysql_close(&mysql);
		sleep(10);
	}
	syslog(LOG_DEBUG, "connect mysql seccess");

	/* get devices */
	snprintf(sql, sizeof(sql), "SELECT A.ObjectAddr, A.Code, B.ProduceID,"
			" A.DevID, B.SubID, A.ChanIndx FROM "
			"Device_DVR_Channel_Display_Info A, "
			"Device_Para_Man_Info B WHERE A.DevID = B.ID"
			" ORDER BY A.DevID, A.ChanIndx, A.ObjectAddr");
	if (mysql_query(&mysql, sql) != 0) {
		syslog(LOG_DEBUG, "Error:mysql_query() when get devices.");
		return -1;
	}
	if ((res = mysql_store_result(&mysql)) == NULL) {
		syslog(LOG_DEBUG, "Error:mysql_store_result() at get devices");
		return -1;
	}

	if (mysql_num_rows(res) <= 0)
		return -1;

	int count = 0;
	conv_channel_info_t *ptr;
	while ((row = mysql_fetch_row(res)) != NULL) {
		if (strlen(row[0]) != 18)	/* code's length is fixed */
			continue;
		ptr = malloc(sizeof(conv_channel_info_t));
		if (ptr == NULL) {
			syslog(LOG_DEBUG, "malloc() error");
			return -1;
		}

		ptr->code = (unsigned int)atoi(&row[0][CODE_FIXED_BITS]);
		snprintf(ptr->plat, sizeof(ptr->plat), row[1]);
		ptr->device_type = atoi(row[2]);
		ptr->device_id = atoi(row[3]);
		ptr->device_sub_id = atoi(row[4]);
		ptr->channel_id = atoi(row[5]);

		if (hash_add(conv_table, (void *)ptr) == 0)
			count++;
	}

	/* cleanup */
	mysql_free_result(res);
	mysql_close(&mysql);

	return (count <= 0) ? -1 : 0;
}

int elec_conv_init()
{
	conv_table = hash_init(1000, hash_func_channel);
	if (conv_table == NULL)
		return -1;

	if (get_devices() != 0)
		return -1;

	return 0;
}

int elec_conv_channel(const char *code, rmd_session_t *sess)
{
	int i_code = atoi(&code[CODE_FIXED_BITS]);
	conv_channel_info_t node = {i_code};
	conv_channel_info_t *info;

	if (hash_entry(conv_table, (void *)&node, cmp_func_channel, 
			(void *)i_code, (void **)&info) == -1)
		return -1;

	sess->driver_type   = ELEC_DRIVER_TYPE_ID;
	sess->device_id     = info->device_id;
	sess->channel_id    = info->channel_id;

	snprintf(sess->plat, sizeof(sess->plat), info->plat);
	sess->device_type   = info->device_type;
	sess->device_sub_id = info->device_sub_id;
	return 0;
}

int elec_conv_cleanup()
{
	hash_clear(conv_table, ds_free_callback, NULL);
	hash_destory(conv_table);
	return 0;
}
