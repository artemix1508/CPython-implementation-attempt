#ifndef STUB_FCNTL_H
#define STUB_FCNTL_H
#define F_GETFD 1
#define F_SETFD 2
#define F_GETFL 3
#define F_SETFL 4
#define FD_CLOEXEC 1
#define O_NONBLOCK 2048
#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR   2
#define O_CREAT  64
#define O_TRUNC  512
#define O_APPEND 1024
#define O_NOFOLLOW 131072
#define O_EXCL   128
static inline int fcntl(int fd, int cmd, ...) { (void)fd;(void)cmd; return 0; }
static inline int open(const char *p, int f, ...) { (void)p;(void)f; return -1; }
#endif