#include "syshdr.h"
#include "dmdb.h"

#ifdef _WIN32_
#include "dmapi.h"		/* Dameng database API header file */

struct dmdb_conn_t {
	dm_hdbc dbc;
//	char host[32];
//	char user[64];
//	char pwd[32];
//	int port;
};

struct dmdb_query_t {
	dm_hstmt stmt;
};

static dm_henv env;

static void *login_thread(void *arg)
{
	return NULL;
}

int dmdb_init(void)
{
	int ret;

	dm_api_init();
	ret = dm_alloc_env(&env);
	if (ret == DM_FALSE)
		return -1;
	return 0;
}

dmdb_conn_t *dmdb_open(char *host, char *user, char *pwd, int port)
{
	dmdb_conn_t *conn = NULL;
	dm_bool ret;
	
	conn = (dmdb_conn_t *)calloc(1, sizeof(dmdb_conn_t));
	if (conn == NULL)
		goto err;

	ret = dm_alloc_connect(env, &conn->dbc);
	if (ret == DM_FALSE)
		goto err;

	ret = dm_login_port(conn->dbc, host, user, pwd, port);
	if (ret == DM_FALSE)
		goto err;

	return conn;

err:
	dmdb_close(conn);
	return NULL;
}

dmdb_query_t *dmdb_query(dmdb_conn_t *conn, const char *sql)
{
	dmdb_query_t *query = NULL;
	dm_bool ret;

	query = (dmdb_query_t *)calloc(1, sizeof(dmdb_query_t));
	if (query == NULL)
		goto err;

	ret = dm_alloc_stmt(conn->dbc, &query->stmt);
	if (ret == DM_FALSE)
		goto err;

	ret = dm_direct_exec(query->stmt, (char *)sql);
	if (ret == DM_FALSE)
		goto err;

	return query;

err:
	dmdb_query_free(query);
	return NULL;
}

unsigned long dmdb_query_get_rows(dmdb_query_t *query)
{
	__int64 rows;
	dm_bool ret;

	ret = dm_describe_row_num(query->stmt, &rows);
	if (ret == DM_FALSE)
		return 0;

	return (unsigned long)rows;
}

int dmdb_query_get_cols(dmdb_query_t *query)
{
	unsigned short cols;
	dm_bool ret;

	ret = dm_describe_col_num(query->stmt, &cols);
	if (ret == DM_FALSE)
		return 0;

	return (int)cols;
}

int dmdb_query_fetch_scroll(dmdb_query_t *query, int move_type, int offset)
{
	dm_bool ret;

	ret = dm_fetch_scroll(query->stmt, move_type, offset);
	return (ret == DM_FALSE) ? -1 : 0;
}

int dmdb_query_get_value(dmdb_query_t *query, int column, int data_type,
		   void *value, int len)
{
	dm_bool ret;
	int c_type;
	long ind;

	if (data_type == DM_DATA_INT)
		c_type = TYPE_INTEGER;
	else if (data_type == DM_DATA_INT64)
		c_type = TYPE_ULONG;
	else if (data_type == DM_DATA_SMALLINT)
		c_type = TYPE_USHORT;
	else if (data_type == DM_DATA_FLOAT)
		c_type = TYPE_FLOAT;
	else if (data_type == DM_DATA_DOUBLE)
		c_type = TYPE_DOUBLE;
	else if (data_type == DM_DATA_CHAR)
		c_type = TYPE_CHAR;
	else if (data_type == DM_DATA_VARCHAR)
		c_type = TYPE_CHAR;
	else if (data_type == DM_DATA_VARCHAR2)
		c_type = TYPE_CHAR;
	else
		return -1;

	ret = dm_get_data(query->stmt, column, data_type, c_type, 
		value, len, &ind);
	if (ret == DM_FALSE)
		return -1;
	if (ind == -1)
		memset(value, 0, len);
	return 0;
}

int dmdb_query_free(dmdb_query_t *query)
{
	if (query == NULL)
		return -1;

	if (query->stmt != NULL)
		dm_free_stmt(query->stmt);

	free(query);

	return 0;
}

int dmdb_exec(dmdb_conn_t *conn, const char *sql)
{
	dm_hstmt stmt;
	dm_bool ret;

	ret = dm_alloc_stmt(conn->dbc, &stmt);
	if (ret == DM_FALSE)
		return -1;

	ret = dm_direct_exec(stmt, (char *)sql);
	dm_free_stmt(stmt);

	return (ret == DM_FALSE) ? -1 : 0;
}

unsigned long dmdb_get_count(dmdb_conn_t *conn, const char *sql)
{
	dmdb_query_t *query;
	unsigned long rows;

	query = dmdb_query(conn, sql);
	if (query == NULL)
		return -1;

	rows = dmdb_query_get_rows(query);
	dmdb_query_free(query);
	return rows;
}

int dmdb_get_value(dmdb_conn_t *conn, char *sql, int data_type, 
		void *value, int len)
{
	dmdb_query_t *query;
	int ret;

	query = dmdb_query(conn, sql);
	if (query == NULL)
		return -1;

	if (dmdb_query_get_rows(query) == 0) {
		dmdb_query_free(query);
		return -1;
	}

	if (dmdb_query_fetch_scroll(query, DM_FETCH_NEXT, 0) != 0) {
		dmdb_query_free(query);
		return -1;
	}

	ret = dmdb_query_get_value(query, 1, data_type, value, len);
	dmdb_query_free(query);
	return ret;
}

int dmdb_close(dmdb_conn_t *conn)
{
	if (conn == NULL)
		return -1;

	if (conn->dbc != NULL) {
		dm_logout(conn->dbc);
		dm_free_connect(conn->dbc);
	}

	free(conn);

	return 0;
}

int dmdb_cleanup(void)
{
	dm_free_env(env);
	return 0;
}
#endif

#ifdef _LINUX_

struct dmdb_conn_t {
	void *dbc;
};

struct dmdb_query_t {
	void *stmt;
};

int dmdb_init(void)
{
	return -1;
}

dmdb_conn_t *dmdb_open(char *host, char *user, char *pwd, int port)
{
	return NULL;
}

dmdb_query_t *dmdb_query(dmdb_conn_t *conn, const char *sql)
{
	return NULL;
}

unsigned long dmdb_query_get_rows(dmdb_query_t *query)
{
	return 0;
}

int dmdb_query_get_cols(dmdb_query_t *query)
{
	return 0;
}

int dmdb_query_fetch_scroll(dmdb_query_t *query, int move_type, int offset)
{
	return -1;
}

int dmdb_query_get_value(dmdb_query_t *query, int column, int data_type,
		void *value, int len)
{
	return -1;
}

int dmdb_query_free(dmdb_query_t *query)
{
	return -1;
}

int dmdb_exec(dmdb_conn_t *conn, const char *sql)
{
	return -1;
}

unsigned long dmdb_get_count(dmdb_conn_t *conn, const char *sql)
{
	return -1;
}

int dmdb_get_value(dmdb_conn_t *conn, char *sql, int data_type, 
		void *value, int len)
{
	return -1;
}

int dmdb_close(dmdb_conn_t *conn)
{
	return -1;
}

int dmdb_cleanup(void)
{
	return -1;
}
#endif
