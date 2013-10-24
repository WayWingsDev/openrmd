#ifndef _HTTP_H_
#define _HTTP_H_

/* rfc2616 */

#define HTTP_VER		"HTTP/1.1"
#define HTTP_VER10		"HTTP/1.0"
#define HTTP_CRLF		"\r\n"			/* line flag */
#define HTTP_CRLF_LEN		strlen(HTTP_CRLF)
#define STATUS_LINE_LEN		512
#define FLD_LEN			32
#define FLD_CON_LEN		512

static char http_fld[][FLD_LEN] = {
	"Accept",
	"Accept-Charset",
	"Accept-Encoding",
	"Accept-Language",
	"Accept-Ranges",
	"Age",
	"Allow",
	"Authorization",
	"Cache-Control",
	"Connection",
	"Content-Encoding",
	"Content-Language",
	"Content-Length",
	"Content-Location",
	"Content-MD5",
	"Content-Range",
	"Content-Type",
	"Date",
	"ETag",
	"Expect",
	"Expires",
	"From",
	"Host",
	"If-Match",
	"If-Modified-Since",
	"If-None-Match",
	"If-Range",
	"If-Unmodified-Since",
	"Last-Modified",
	"Location",
	"Max-Forwards",
	"Pragma",
	"Proxy-Authenticate",
	"Proxy-Authorization",
	"Range",
	"Referer",
	"Retry-After",
	"Server",
	"TE",
	"Trailer",
	"Transfer-Encoding",
	"Upgrade",
	"User-Agent",
	"Vary",
	"Via",
	"Warning",
	"WWW-Authenticate"
};

/* header fields count */
#define HDR_FLD_COUNT (sizeof(http_fld) / FLD_LEN)

/* header field index */
typedef enum {
	ACCEPT,
	ACCEPT_CHARSET,
	ACCEPT_ENCODING,
	ACCEPT_LANGUAGE,
	ACCEPT_RANGES,
	AGE,
	ALLOW,
	AUTHORIZATION,
	CACHE_CONTROL,
	CONNECTION,
	CONTENT_ENCODING,
	CONTENT_LANGUAGE,
	CONTENT_LENGTH,
	CONTENT_LOCATION,
	CONTENT_MD5,
	CONTENT_RANGE,
	CONTENT_TYPE,
	DATE,
	ETAG,
	EXPECT,
	EXPIRES,
	FROM,
	HOST,
	IF_MATCH,
	IF_MODIFIED_SINCE,
	IF_NONE_MATCH,
	IF_RANGE,
	IF_UNMODIFIED_SINCE,
	LAST_MODIFIED,
	LOCATION,
	MAX_FORWARDS,
	PRAGMA,
	PROXY_AUTHENTICATE,
	PROXY_AUTHORIZATION,
	RANGE,
	REFERER,
	RETRY_AFTER,
	SERVER,
	TE,
	TRAILER,
	TRANSFER_ENCODING,
	UPGRADE,
	USER_AGENT,
	VARY,
	VIA,
	WARNING,
	WWW_AUTHENTICATE,
} http_hdr_fld_index_t;

/* Status Code Definitions */
/* Informational 1xx */
#define HTTP_SC_100		"100 Continue"
#define HTTP_SC_101		"101 Switching Protocols"

/* Successful 2xx */
#define HTTP_SC_200		"200 OK"
#define HTTP_SC_201		"201 Created"
#define HTTP_SC_202		"202 Accepted"
#define HTTP_SC_203		"203 Non-Authoritative Information"
#define HTTP_SC_204		"204 No Content"
#define HTTP_SC_205		"205 Reset Content"
#define HTTP_SC_206		"206 Partial Content"

/* Redirection 3xx */
#define HTTP_SC_300		"300 Multiple Choices"
#define HTTP_SC_301		"301 Moved Permanently"
#define HTTP_SC_302		"302 Found"
#define HTTP_SC_303		"303 See Other"
#define HTTP_SC_304		"304 Not Modified"
#define HTTP_SC_305		"305 Use Proxy"
#define HTTP_SC_306		"306 (Unused)"
#define HTTP_SC_307		"307 Temporary Redirect"

/* Client Error 4xx */
#define HTTP_SC_400		"400 Bad Request"
#define HTTP_SC_401		"401 Unauthorized"
#define HTTP_SC_402		"402 Payment Required"
#define HTTP_SC_403		"403 Forbidden"
#define HTTP_SC_404		"404 Not Found"
#define HTTP_SC_405		"405 Method Not Allowed"
#define HTTP_SC_406		"406 Not Acceptable"
#define HTTP_SC_407		"407 Proxy Authentication Required"
#define HTTP_SC_408		"408 Request Timeout"
#define HTTP_SC_409		"409 Conflict"
#define HTTP_SC_410		"410 Gone"
#define HTTP_SC_411		"411 Length Required"
#define HTTP_SC_412		"412 Precondition Failed"
#define HTTP_SC_413		"413 Request Entity Too Large"
#define HTTP_SC_414		"414 Request-URI Too Long"
#define HTTP_SC_415		"415 Unsupported Media Type"
#define HTTP_SC_416		"416 Requested Range Not Satisfiable"
#define HTTP_SC_417		"417 Expectation Failed"

/* Server Error 5xx */
#define HTTP_SC_500		"500 Internal Server Error"
#define HTTP_SC_501		"501 Not Implemented"
#define HTTP_SC_502		"502 Bad Gateway"
#define HTTP_SC_503		"503 Service Unavailable"
#define HTTP_SC_504		"504 Gateway Timeout"
#define HTTP_SC_505		"505 HTTP Version Not Supported"

/* header field info */
typedef struct {
	char status_line[STATUS_LINE_LEN];
	char fld[HDR_FLD_COUNT][FLD_CON_LEN];
} http_hdr_t;

int http_recv(int fd, http_hdr_t *hdr, char **body, int *body_len);
int http_send(int fd, char *buff, int len);
int http_reply(int fd, char *status);

#endif	/* _HTTP_H_ */
