#ifndef _FINC_WIN32_H_
#define _FINC_WIN32_H_

/* system header files */
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <process.h>	/* _getpid() */
#include <io.h>		/* _close() */
#include <direct.h>	/* _mkdir() */

/* private header files */
#include "syslog.h"
#include "win32/getopt.h"
#include "win32/daemon.h"
#include "win32/pause.h"
#include "win32/stdint.h"
#include "win32/wsa_startup.h"
#include "win32/pthreads/pthread.h"
#include "win32/pthreads/sched.h"
#include "win32/pthreads/semaphore.h"
#include "win32/open_console.h"
#include "win32/basename.h"

/* type define */
#define uint32_t	unsigned int
#define uint64_t	unsigned long long
#define socklen_t	unsigned int

//#define inline		__inline
#define inline

#define FINC_SLASH	'\\'

#ifndef PATH_MAX
#define PATH_MAX	512
#endif

#define snprintf	_snprintf
#define getpid		_getpid
#define strtoull	_strtoui64
#define strtok_r	strtok_s

#define bzero(str, len) memset(str, 0, len)
#define sleep(x)	Sleep((x) * 1000)

/* From MSDN:
 * Bool CloseHandle(HANDLE hObject);
 * This function closes to the following objects:
 *  [*] Access token
 *  [*] Communications device
 *  [*] Console input
 *  [*] Console screen buffer
 *  [*] Event
 *  [*] File
 *  [*] File mapping
 *  [*] Job
 *  [*] Mailslot
 *  [*] Memory resource notification
 *  [*] Mutex
 *  [*] Named pipe
 *  [*] Pipe
 *  [*] Process
 *  [*] Semaphore
 *  [*] Socket
 *  [*] Thread
 *  [*] Waitable timer
 */
#define close(fd)	CloseHandle((HANDLE)fd)

#define readlink(x, buff, buff_size) \
	GetModuleFileName(NULL, buff, buff_size)

#define dlopen(filename, flag) LoadLibrary(filename)
#define dlsym(handle, symbol)  GetProcAddress(handle, symbol)
#define dlclose(handle)        FreeLibrary(handle)

/* signal */
typedef void __signalfn_t(int);
typedef __signalfn_t *__sighandler_t;

#ifndef SIG_DFL
#define SIG_DFL	((__sighandler_t)0)	/* default signal handling */
#endif

#ifndef SIG_IGN
#define SIG_IGN	((__sighandler_t)1)	/* ignore signal */
#endif

#ifndef SIG_ERR
#define SIG_ERR	((__sighandler_t)-1)	/* error return from signal */
#endif

#define SIGPIPE		SIGABRT

#define S_IRWXU 00700
#define S_IRUSR 00400
#define S_IWUSR 00200
#define S_IXUSR 00100

#define S_IRWXG 00070
#define S_IRGRP 00040
#define S_IWGRP 00020
#define S_IXGRP 00010

#define S_IRWXO 00007
#define S_IROTH 00004
#define S_IWOTH 00002
#define S_IXOTH 00001

/* Value returned if `sem_open' failed.  */
#define SEM_FAILED      ((sem_t *) 0)

#define SHUT_RD		SD_RECEIVE
#define SHUT_WR		SD_SEND
#define SHUT_RDWR	SD_BOTH

#endif	/* _FINC_WIN32_H_ */
