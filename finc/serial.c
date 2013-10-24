#include "serial.h"
#include "syshdr.h"

typedef struct {
	int fd;
	serial_data_callback_t cbk;
	void *cbk_param;
	int stop;
} serial_handle_t;

static int set_baudrate(int fd, int baud)
{
#if defined(_LINUX_)
	static int a[] = {
		50, 75, 110, 134, 150, 
		200, 300, 600, 1200, 1800, 
		2400, 4800, 9600, 19200, 38400, 
		57600, 115200
	};
	static int b[] = {
		B50, B75, B110, B134, B150, 
		B200, B300, B600, B1200, B1800, 
		B2400, B4800, B9600, B19200, B38400, 
		B57600, B115200
	};

	struct termios opt;
	int i;

	for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
		if (baud == a[i])
			break;
	}
	if (i == sizeof(a) / sizeof(a[0]))
		return -1;

	tcgetattr(fd, &opt);

	cfsetispeed(&opt, b[i]);
	cfsetospeed(&opt, b[i]);
	opt.c_cflag |= (CLOCAL | CREAD);

	opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	opt.c_oflag &= ~OPOST;
	opt.c_oflag &= ~(ONLCR | OCRNL);
	opt.c_iflag &= ~(ICRNL | INLCR);
	opt.c_iflag &= ~(IXON | IXOFF | IXANY);
	opt.c_cc[VTIME] = 150;	/* timeout: 15 seconds */
	opt.c_cc[VMIN] = 0;

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &opt);

#elif defined(_WIN32_)
	static int a[] = {
		110, 300, 600, 1200, 2400, 
		4800, 9600, 14400, 19200, 38400, 
		56000, 57600, 115200, 128000, 256000
	};

	DCB opt;
	int i;
	COMMTIMEOUTS to;

	for (i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
		if (baud == a[i])
			break;
	}
	if (i == sizeof(a) / sizeof(a[0]))
		return -1;

	if (GetCommState(fd, &opt) == 0)
		return -1;
	opt.BaudRate = baud;

	if (SetCommState(fd, &opt) == 0)
		return -1;

	to.ReadIntervalTimeout = 20;
	to.ReadTotalTimeoutMultiplier = 10;
	to.ReadTotalTimeoutConstant = 100; 
	to.WriteTotalTimeoutMultiplier = 10;
	to.WriteTotalTimeoutConstant = 100;
	SetCommTimeouts(fd, &to);
#endif

	return 0;
}

static int set_parity(int fd, int data_bits, int parity, int stop_bits)
{
#if defined(_LINUX_)
	struct termios opt;

	tcgetattr(fd, &opt);

	/* 8N1 (data bits:8 parity:none stop bits:1) */
	if (data_bits == 8 && parity == 'N' && stop_bits == 1) {
		opt.c_cflag &= ~PARENB;
		opt.c_cflag &= ~CSTOPB;
		opt.c_cflag &= ~CSIZE;;
		opt.c_cflag |= CS8;
	}
	
	/* 7E1 (data bits:7 parity:even stop bits:1) */
	else if (data_bits == 7 && parity == 'E' && stop_bits == 1) {
		opt.c_cflag |= PARENB;
		opt.c_cflag &= ~PARODD;
		opt.c_cflag &= ~CSTOPB;
		opt.c_cflag &= ~CSIZE;
		opt.c_cflag |= CS7;
	}
	
	/* 7O1 (data bits:7 parity:odd  stop bits:1) */
	else if (data_bits == 7 && parity == 'O' && stop_bits == 1) {
		opt.c_cflag |= PARENB;
		opt.c_cflag |= PARODD;
		opt.c_cflag &= ~CSTOPB;
		opt.c_cflag &= ~CSIZE;
		opt.c_cflag |= CS7;
	}
	
	/* 7S1 (data bits:7 parity:space stop bits:1) */
	else if (data_bits == 7 && parity == 'S' && stop_bits == 1) {
		opt.c_cflag &= ~PARENB;
		opt.c_cflag &= ~CSTOPB;
		opt.c_cflag &= ~CSIZE;
		opt.c_cflag |= CS7;
	} else {
		return -1;
	}

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &opt);
	
#elif defined(_WIN32_)
	DCB opt;

	if (GetCommState(fd, &opt) == 0)
		return -1;

	opt.ByteSize = 8;

	if (parity == 'N')
		opt.Parity = NOPARITY;
	else if (parity == 'E')
		opt.Parity = EVENPARITY;
	else if (parity == 'O')
		opt.Parity = ODDPARITY;
	else if (parity == 'S')
		opt.Parity = SPACEPARITY;

	if (stop_bits == 1)
		opt.StopBits = ONESTOPBIT;
	else if (stop_bits == 2)
		opt.StopBits = TWOSTOPBITS;

	if (SetCommState(fd, &opt) == 0)
		return -1;
#endif

	return 0;
}

static void close_serial(int fd)
{
	if (fd == -1)
		return;

#if defined(_LINUX_)
	close(fd);
#elif defined(_WIN32_)
	//PurgeComm(fd, PURGE_RXCLEAR | PURGE_TXCLEAR);
	CloseHandle(fd);
#endif
}

#if defined(_LINUX_)
static void *read_data_thread(void *arg)
#elif defined(_WIN32_)
static DWORD WINAPI read_data_thread(LPVOID arg)
#endif
{
	serial_handle_t *p = (serial_handle_t *)arg;
	unsigned char buff[1024];
	int bytes;

	while (p->stop == 0) {
#if defined(_LINUX_)
		bytes = read(p->fd, buff, sizeof(buff));
#elif defined(_WIN32_)
		ReadFile(p->fd, buff, sizeof(buff), &bytes, NULL);
#endif

		if (bytes > 0)
			p->cbk((unsigned long)p, buff, bytes, p->cbk_param);
	}

	free(arg);
	return NULL;
}

unsigned long serial_open(char *name, int baud_rate, int data_bits, int parity, 
		int stop_bits, serial_data_callback_t cbk, void *param)
{
	serial_handle_t *handle;
	int fd = -1;

#if defined(_LINUX_)
	pthread_t tid;
#elif defined(_WIN32_)
	HANDLE thdl;
#endif

	handle = malloc(sizeof(serial_handle_t));
	if (handle == NULL)
		goto err;

	/* open serial port */
#if defined(_LINUX_)
	fd = open(name, O_RDWR | O_NOCTTY);
#elif defined(_WIN32_)
	fd = CreateFile(name, GENERIC_READ | GENERIC_WRITE, 0, NULL,  
		OPEN_EXISTING, 0, NULL);
#endif
	if (fd == -1)
		goto err;

	/* set options */
	if (set_baudrate(fd, baud_rate) != 0)
		goto err;
	if (set_parity(fd, data_bits, parity, stop_bits) != 0)
		goto err;

	handle->fd = fd;
	handle->cbk = cbk;
	handle->cbk_param = param;
	handle->stop = 0;

#if defined(_LINUX_)
	if (pthread_create(&tid, NULL, read_data_thread, handle) != 0)
		goto err;
	pthread_detach(tid);
#elif defined(_WIN32_)
	thdl = CreateThread(NULL, 0, read_data_thread, handle, 0, 0);
	if (thdl == NULL)
		goto err;
	CloseHandle(thdl);
#endif

	return (unsigned long)handle;

err:
	if (fd != -1)
		close_serial(fd);
	if (handle)
		free(handle);
	return -1;
}

int serial_send_data(unsigned long handle, unsigned char *buff, int bytes)
{
	int fd = ((serial_handle_t *)handle)->fd;
#if defined(_WIN32_)
	int n;
#endif

	if (handle == -1 || handle == 0)
		return -1;

#if defined(_LINUX_)
	write(fd, buff, bytes);
#elif defined(_WIN32_)
	if (WriteFile(fd, buff, bytes, &n, NULL) == 0)
		return -1;
#endif
	return 0;
}

int serial_close(unsigned long handle)
{
	serial_handle_t *p = (serial_handle_t *)handle;
	if (handle == -1 || handle == 0)
		return -1;

	close_serial(p->fd);
	p->stop = 1;

	return 0;
}
