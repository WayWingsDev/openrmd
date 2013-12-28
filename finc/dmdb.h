#ifndef _DMDB_H_
#define _DMDB_H_

/* data type */
#define DM_DATA_CHAR		0	/* CHAR     */
#define DM_DATA_VARCHAR2	1	/* VARCHAR  */
#define DM_DATA_VARCHAR		2	/* VARCHAR  */
#define DM_DATA_BIT		3	/* BIT STRING */
#define DM_DATA_VARBIT		4	/* VAR BIT STRING */
#define DM_DATA_TINYINT		5	/* SMALL INTEGER, 2 bytes */
#define DM_DATA_SMALLINT	6	/* SMALL INTEGER, 2 bytes */
#define DM_DATA_INT		7	/* INTEGER 4 bytes */
#define DM_DATA_INT64		8	/* INTEGER 8 bytes */
#define DM_DATA_DEC		9	/* DECIMAL */
#define DM_DATA_FLOAT		10	/* FLOAT, SINGLE */
#define DM_DATA_DOUBLE		11	/* DOUBLE */
#define DM_DATA_BLOB		12	/* BINARY LARGE OBJECT */

/* fetch deriction */
#define DM_FETCH_NEXT       1
#define DM_FETCH_FIRST      2
#define DM_FETCH_LAST       3
#define DM_FETCH_PRIOR      4
#define DM_FETCH_ABSOLUTE   5
#define DM_FETCH_RELATIVE   6

typedef struct dmdb_conn_t dmdb_conn_t;
typedef struct dmdb_query_t dmdb_query_t;

int dmdb_init(void);
dmdb_conn_t *dmdb_open(char *host, char *user, char *pwd, int port);
dmdb_query_t *dmdb_query(dmdb_conn_t *conn, const char *sql);
unsigned long dmdb_query_get_rows(dmdb_query_t *query);
int dmdb_query_get_cols(dmdb_query_t *query);
int dmdb_query_fetch_scroll(dmdb_query_t *query, int move_type, int offset);
int dmdb_query_get_value(dmdb_query_t *query, int column, int data_type,
		void *value, int len);
int dmdb_query_free(dmdb_query_t *query);
int dmdb_exec(dmdb_conn_t *conn, const char *sql);
unsigned long dmdb_get_count(dmdb_conn_t *conn, const char *sql);
int dmdb_get_value(dmdb_conn_t *conn, char *sql, int data_type, 
		void *value, int len);
int dmdb_close(dmdb_conn_t *conn);
int dmdb_cleanup(void);

#endif	/* _DMDB_H_ */
