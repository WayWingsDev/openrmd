#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <oci.h>
#include "device_cfg.h"
#include "evenbits_compl.h"
#include "getcfg.h"
#include "localip.h"

#define BCD_TYPE	2

#define OCISTMTPREPARE(sql) OCIStmtPrepare(stmthp, errhp, sql, \
		strlen((char *)sql), OCI_NTV_SYNTAX, OCI_DEFAULT)
#define OCIDEFINEBYPOS(no, val, len, val_type) OCIDefineByPos(stmthp, \
		&define[no], errhp, (no+1), val, len, val_type, 0, 0, 0, \
		OCI_DEFAULT)
#define OCI_ERR do { \
	OCIErrorGet((dvoid *)errhp, (ub4)1, NULL, &oci_ecode, oci_ebuff, \
			(ub4)sizeof(oci_ebuff), OCI_HTYPE_ERROR); \
	printf("%d %s\n", oci_ecode, oci_ebuff); \
} while (0)

static OCIEnv    *envhp;
static OCIServer *srvhp;
static OCIError  *errhp;
static OCISvcCtx *svchp;
static OCIStmt   *stmthp;
static sb4       oci_ecode;
static text      oci_ebuff[512];
static OCIDefine *define[20] = {(OCIDefine *)0};  /* Max define items */

/* initialize OCI environment */
static int ora_init()
{
	if (OCIEnvCreate(&envhp, OCI_DEFAULT, 0, 0, 0, 0, 0, 0)) {
		printf("Init OCI environment error\n");
		return -1;
	}

	OCIAttrSet(svchp, OCI_HTYPE_SVCCTX, srvhp, 0, OCI_ATTR_SERVER, errhp);
	OCIServerAttach(srvhp, errhp, 0, 0, OCI_DEFAULT);
	OCIHandleAlloc(envhp, (dvoid *)&errhp, OCI_HTYPE_ERROR,  0, 0);
	OCIHandleAlloc(envhp, (dvoid *)&srvhp, OCI_HTYPE_SERVER, 0, 0);
	OCIHandleAlloc(envhp, (dvoid *)&svchp, OCI_HTYPE_SVCCTX, 0, 0);
	OCIHandleAlloc(envhp, (dvoid *)&stmthp, OCI_HTYPE_STMT,  0, 0);
	return 0;
}

/* release all OCI handle */
static void ora_release()
{
	OCIServerDetach(srvhp, errhp, OCI_DEFAULT);
	OCIHandleFree(stmthp,  OCI_HTYPE_STMT);
	OCIHandleFree(errhp,   OCI_HTYPE_ERROR);
	OCIHandleFree(srvhp,   OCI_HTYPE_SERVER);
	OCIHandleFree(svchp,   OCI_HTYPE_SVCCTX);
}

/* logon database */
static int ora_login()
{
	char user[256], pwd[64], db[64];

	if (getcfg(cfg_file, "db_ora_user", user, GETCFG_STR) != 0 ||
			getcfg(cfg_file, "db_ora_pwd", pwd, GETCFG_STR) != 0 ||
			getcfg(cfg_file, "db_ora_tns", db, GETCFG_STR) != 0) {
		printf("get database info error\n");
		return -1;
	}

	if (OCILogon(envhp, errhp, &svchp, (text *)user, strlen(user), 
				(text *)pwd, strlen(pwd), (text *)db, 
				strlen(db)) != 0) {
		printf("connect oracle error\n");
		return -1;
	}
	//printf("connect oracle seccess\n");
	return 0;
}

/*  logout from database */
static void ora_logout()
{
	/* FIXME: In this program, open this sentence, when use CTRL+C the
	 * terminated this process, it will crash. */
	OCILogoff(svchp, errhp);
}

int device_cfg_init()
{
	return ora_init();
}

int device_cfg_get(int old_ver, char **buff, int *length)
{
	text sql[512];

	char line[256];
	*buff = NULL;
	*length = 0;

	/* get local IP address */
	char interface[64], local_ip[32];
	if (getcfg(cfg_file, "interface", interface, GETCFG_STR) != 0) {
		printf("can't get network interface, use eth0\n");
		snprintf(interface, sizeof(interface), "eth0");
	}
	if (localip(interface, local_ip, sizeof(local_ip)) != 0) {
		printf("get %s ip address error\n", interface);
		return -1;
	}

	if (ora_login() != 0)
		return -1;

	/* get BCD ID */
	int bcd_id;
	snprintf((char *)sql, sizeof(sql),
			"SELECT ID FROM DEVICE_PARA_MAN_INFO WHERE TYPEID=6"
			"AND IP='%s' ORDER BY ID", local_ip);
	OCISTMTPREPARE(sql);
	OCIDEFINEBYPOS(0, &bcd_id, sizeof(int), SQLT_INT);
	if (OCIStmtExecute(svchp, stmthp, errhp, 1, 0, 0, 0, 0)) {
		printf("get BCD ID error\n");
		goto err;
	}
	printf("BCD_ID: %d\n", bcd_id);

	/* get BCD configure version */
	int new_ver;
	snprintf((char *)sql, sizeof(sql),
			"SELECT CONFIGVERSION FROM DEVICE_SERVER_BCD_INFO "
			"WHERE ID = %d", bcd_id);
	OCISTMTPREPARE(sql);
	OCIDEFINEBYPOS(0, &new_ver, sizeof(int), SQLT_INT);
	if (OCIStmtExecute(svchp, stmthp, errhp, 1, 0, 0, 0, 0)) {
		printf("get version number error\n");
		goto err;
	}
	printf("NER_VER: %d\n", new_ver);
	if (new_ver <= old_ver) {
		printf("not need update\n");
		goto succ;	/* not need update */
	}

	/* get IPC configure info */
	channel_cfg_t cfg;
	snprintf((char *)sql, sizeof(sql),
			"select B.PROID, A.ID, B.IP,"
			"decode(B.PROID, 4, 5000, 6, 554) as PORT,"
			"A.USERCODE, A.PASS, 2 as CHANNELS, '11' as REC,"
			"(select PROID from DEVICE_PARA_MAN_INFO where IP ="
			"to_char(substr(A.STOREIP,0,instr(A.STOREIP,':')-1)))"
			"as STORAGE_TYPE,"
			"to_char(substr(A.STOREIP,0,instr(A.STOREIP,':')-1)) "
			"as STORAGE_IP,"
			"substr(A.STOREIP, instr(A.STOREIP,':')+1) as "
			"STORAGE_DISK from DEVICE_CAMERA_INFO A,"
			"DEVICE_PARA_MAN_INFO B "
			"where A.BLADEID=%d and A.ID = B.ID",
//			"where A.BLADEID=%d and A.TYPEID = 1 and A.ID = B.ID",
			bcd_id);
	//printf("%s\n", sql);

	OCISTMTPREPARE(sql);
	OCIDEFINEBYPOS(0, &cfg.type, sizeof(int),      SQLT_INT);
	OCIDEFINEBYPOS(1, &cfg.id,   sizeof(int),      SQLT_INT);
	OCIDEFINEBYPOS(2, cfg.ip,    sizeof(cfg.ip),   SQLT_STR);
	OCIDEFINEBYPOS(3, &cfg.port, sizeof(int),      SQLT_INT);
	OCIDEFINEBYPOS(4, cfg.user,  sizeof(cfg.user), SQLT_STR);
	OCIDEFINEBYPOS(5, cfg.pwd,   sizeof(cfg.pwd),  SQLT_STR);
	OCIDEFINEBYPOS(6, &cfg.channel_num, sizeof(int), SQLT_INT);
	OCIDEFINEBYPOS(7, cfg.rec,   sizeof(cfg.rec),  SQLT_STR);
	OCIDEFINEBYPOS(8, &cfg.storage_device_type, sizeof(int), SQLT_INT);
	OCIDEFINEBYPOS(9, cfg.storage_ip,  sizeof(cfg.storage_ip), SQLT_STR);
	OCIDEFINEBYPOS(10,&cfg.storage_disk, sizeof(int), SQLT_INT);
	if (OCIStmtExecute(svchp, stmthp, errhp, 0, 0, 0, 0, 
				OCI_STMT_SCROLLABLE_READONLY)) {
		printf("get IPC configure error\n");
		goto err;
	}

	snprintf(line, sizeof(line), "version=%d\n\n", new_ver);
	if (add_line(buff, length, line) != 0)
		goto err;

	if (add_line(buff, length, "#driver_type;dev_id;ip;port;user;pwd;"
				"channels;rec;type;ip;port;user;pwd;disk;"
				"baud_rate\n\n") != 0)
		goto err;

	while (OCIStmtFetch2(stmthp, errhp, 1, OCI_FETCH_NEXT, 1, 
				OCI_DEFAULT) != OCI_NO_DATA) {
		if (cfg.storage_device_type == 10) {	/* bnnvr */
			sprintf(cfg.storage_user, "web_admin");
			sprintf(cfg.storage_pwd, "123");
			cfg.storage_port = 8008;
		} else {
			sprintf(cfg.storage_user, "admin");
			sprintf(cfg.storage_pwd, "password");
			cfg.storage_port = 100;
		}

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
			2400);
		if (add_line(buff, length, line) != 0)
			goto err;
	}

succ:
	ora_logout();
	return 0;

err:
	OCI_ERR;
	ora_logout();
	return -1;
}

int device_cfg_cleanup()
{
	ora_release();
	return 0;
}
