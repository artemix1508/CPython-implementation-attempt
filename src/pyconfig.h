#ifndef PYCONFIG_H
#define PYCONFIG_H

/* Platform */
#define PLATFORM "boredos"

/* Inline types needed before any headers load */
typedef int pthread_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int sig_atomic_t;
typedef unsigned long dev_t;
typedef unsigned long ino_t;
typedef unsigned int  mode_t;
typedef long          off_t;

/* stdint extras the SDK is missing */
#ifndef SIZE_MAX
#define SIZE_MAX (~(size_t)0)
#endif
#ifndef INTPTR_MAX
#define INTPTR_MAX 9223372036854775807L
#endif
#ifndef INTPTR_MIN
#define INTPTR_MIN (-9223372036854775807L - 1)
#endif
#ifndef UINT32_MAX
#define UINT32_MAX 0xffffffffU
#endif
#ifndef UINT64_MAX
#define UINT64_MAX 0xffffffffffffffffULL
#endif
#ifndef INT64_MAX
#define INT64_MAX 0x7fffffffffffffffLL
#endif
#ifndef INT64_MIN
#define INT64_MIN (-INT64_MAX - 1)
#endif

#define HAVE_DIRENT_H 1
#define NAMLEN(dirent) strlen((dirent)->d_name)

static inline void tzset(void) {}

#define HAVE_CLOCK 1


#ifndef isinf
#define isinf(x) __builtin_isinf(x)
#endif
#ifndef isnan
#define isnan(x) __builtin_isnan(x)
#endif
#ifndef isfinite
#define isfinite(x) __builtin_isfinite(x)
#endif

/* Missing errno codes */
#ifndef ENXIO
#define ENXIO 6
#endif
#ifndef ENODEV
#define ENODEV 19
#endif
#ifndef EACCES
#define EACCES 13
#endif
#ifndef ENOTDIR
#define ENOTDIR 20
#endif
#ifndef EISDIR
#define EISDIR 21
#endif
#ifndef ENOEXEC
#define ENOEXEC 8
#endif
#ifndef ELOOP
#define ELOOP 40
#endif
#ifndef ETIMEDOUT
#define ETIMEDOUT 110
#endif
#ifndef EOVERFLOW
#define EOVERFLOW 75
#endif
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT 97
#endif

#ifndef INT32_MAX
#define INT32_MAX 0x7fffffff
#endif
#ifndef INT32_MIN
#define INT32_MIN (-INT32_MAX - 1)
#endif
#ifndef UINT32_MAX
#define UINT32_MAX 0xffffffffU
#endif

/* fcntl flags */
#define F_GETFD 1
#define F_SETFD 2
#define F_GETFL 3
#define F_SETFL 4
#define FD_CLOEXEC 1
#define O_NONBLOCK 2048

#ifndef CHAR_MAX
#define CHAR_MAX 127
#endif
#ifndef CHAR_MIN
#define CHAR_MIN (-128)
#endif


#ifndef setbuf
#define setbuf(f, b) setvbuf(f, b, (b) ? _IOFBF : _IONBF, BUFSIZ)
#endif

#ifndef UINT8_MAX
#define UINT8_MAX 0xff
#endif
#ifndef UINT16_MAX
#define UINT16_MAX 0xffff
#endif
#ifndef INT8_MAX
#define INT8_MAX 0x7f
#endif
#ifndef INT16_MAX
#define INT16_MAX 0x7fff
#endif
#ifndef INT8_MIN
#define INT8_MIN (-INT8_MAX - 1)
#endif
#ifndef INT16_MIN
#define INT16_MIN (-INT16_MAX - 1)
#endif

#ifndef rewind
#define rewind(f) fseek(f, 0, 0)
#endif

#define HAVE_CLOCK_GETTIME 1
static inline void pause(void) { }
#define _PYTHONFRAMEWORK ""

#define ALIGNOF_SIZE_T 8
#define ALIGNOF_LONG   8
#define ALIGNOF_INT    4

#ifndef EALREADY
#define EALREADY 114
#endif
#ifndef EINPROGRESS
#define EINPROGRESS 115
#endif
#ifndef ECONNABORTED
#define ECONNABORTED 103
#endif
#ifndef ECONNREFUSED
#define ECONNREFUSED 111
#endif
#ifndef ECONNRESET
#define ECONNRESET 104
#endif
#ifndef EPERM
#define EPERM 1
#endif
#ifndef ESRCH
#define ESRCH 3
#endif
#ifndef ECHILD
#define ECHILD 10
#endif
#ifndef EDEADLK
#define EDEADLK 35
#endif
#ifndef ENOLCK
#define ENOLCK 37
#endif
#ifndef ENOSYS
#define ENOSYS 38
#endif
#ifndef ENOTEMPTY
#define ENOTEMPTY 39
#endif
#ifndef EWOULDBLOCK
#define EWOULDBLOCK EAGAIN
#endif
#ifndef EHOSTUNREACH
#define EHOSTUNREACH 113
#endif
#ifndef ENETUNREACH
#define ENETUNREACH 101
#endif

struct timespec {
    long long tv_sec;
    long tv_nsec;
};

struct timeval {
    long long tv_sec;
    long tv_usec;
};

struct timezone {
    int tz_minuteswest;
    int tz_dsttime;
};

struct tms {
    long tms_utime;
    long tms_stime;
    long tms_cutime;
    long tms_cstime;
};
static inline long times(struct tms *t) { (void)t; return 0; }

/* time extras */
typedef int clockid_t;
#define CLOCK_MONOTONIC 1
#define CLOCK_REALTIME  0

static inline int clock_gettime(clockid_t id, struct timespec *ts) {
    (void)id; ts->tv_sec = 0; ts->tv_nsec = 0; return 0;
}
static inline int clock_getres(clockid_t id, struct timespec *ts) {
    (void)id; ts->tv_sec = 0; ts->tv_nsec = 1000000; return 0;
}
static inline int gettimeofday(struct timeval *tv, void *tz) {
    (void)tz; tv->tv_sec = 0; tv->tv_usec = 0; return 0;
}
static inline struct tm *localtime_r(const time_t *t, struct tm *tm) {
    (void)t; return tm;
}
static inline struct tm *gmtime_r(const time_t *t, struct tm *tm) {
    (void)t; return tm;
}
/* select/fd_set stub */
typedef struct { unsigned long fds_bits[16]; } fd_set;
static inline int select(int n, fd_set *r, fd_set *w, fd_set *e, struct timeval *t) {
    (void)n;(void)r;(void)w;(void)e;(void)t; return 0;
}

static inline int __boredos_fileno(void *f) { (void)f; return 0; }

static inline int __popcountdi2(long long x) {
    x = x - ((x >> 1) & 0x5555555555555555LL);
    x = (x & 0x3333333333333333LL) + ((x >> 2) & 0x3333333333333333LL);
    return (((x + (x >> 4)) & 0x0f0f0f0f0f0f0f0fLL) * 0x0101010101010101LL) >> 56;
}

/* Math constants */
#ifndef INFINITY
#define INFINITY __builtin_inff()
#endif
#ifndef NAN
#define NAN __builtin_nanf("")
#endif

/* Thread support */
#define HAVE_PTHREAD_H 1
#define _POSIX_THREADS 1
#define Py_HAVE_PTHREAD_MUTEX_T 1
#define HAVE_PTHREAD_MUTEX_T 1
#define NATIVE_TSS_KEY_T pthread_key_t

/* Sizes */
#define SIZEOF_WCHAR_T 4
#define SIZEOF_INT 4
#define SIZEOF_LONG 8
#define SIZEOF_LONG_LONG 8
#define SIZEOF_SIZE_T 8
#define SIZEOF_VOID_P 8
#define SIZEOF_SHORT 2
#define SIZEOF_FLOAT 4
#define SIZEOF_DOUBLE 8
#define SIZEOF_FPOS_T 8
#define SIZEOF_OFF_T 8
#define SIZEOF_PID_T 4
#define SIZEOF_TIME_T 8
#define SIZEOF_UINTPTR_T 8
#define SIZEOF_PTHREAD_T 8

/* Available headers */
#define HAVE_ERRNO_H 1
#define HAVE_SIGNAL_H 1
#define HAVE_STDARG_H 1
#define HAVE_STDDEF_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_TIME_H 1
#define HAVE_MATH_H 1
#define HAVE_SETJMP_H 1
#define HAVE_LOCALE_H 1
#define HAVE_LIMITS_H 1
#define HAVE_CTYPE_H 1
#define HAVE_STDIO_H 1
#define HAVE_WCHAR_H 1
#define HAVE_FILENO 1
#define HAVE_ISATTY 1

/* Unavailable */
#undef HAVE_DLFCN_H
#undef HAVE_SYS_MMAN_H
#undef HAVE_MMAP
#undef HAVE_FORK
#undef HAVE_EXECV
#undef HAVE_PIPE
#undef HAVE_DYNAMIC_LOADING
#undef HAVE_DLOPEN
#undef WITH_CYCLE_GC
#undef HAVE_SIGACTION
#undef HAVE_SIGALTSTACK

/* Disable pyc cache */
#define Py_DISABLE_IMPORTLIB_CACHE 1

/* Math functions */
#define HAVE_ROUND 1
#define HAVE_HYPOT 1
#define HAVE_FINITE 1
#define HAVE_FMOD 1
#define HAVE_FREXP 1
#define HAVE_MODF 1
#define HAVE_SQRT 1
#define HAVE_FLOOR 1
#define HAVE_CEIL 1
#define HAVE_INFINITY 1

/* Filesystem */
#define HAVE_STAT 1
#define HAVE_FSTAT 1
#define HAVE_OPEN 1
#define HAVE_READ 1
#define HAVE_WRITE 1
#define HAVE_CLOSE 1

/* String/misc */
#define HAVE_SNPRINTF 1
#define HAVE_VSNPRINTF 1
#define HAVE_STRCHR 1
#define HAVE_STRDUP 1
#define HAVE_STRTOL 1
#define HAVE_STRTOD 1
#define HAVE_MEMCPY 1
#define HAVE_MEMMOVE 1
#define HAVE_MEMSET 1

/* Python build */
#define Py_BUILD_CORE 1
#define PREFIX "/usr"
#define EXEC_PREFIX "/usr"
#define VERSION "3.14"
#define VPATH ""
#define PY_FORMAT_LONG_LONG "ll"
#define DOUBLE_IS_LITTLE_ENDIAN_IEEE754 1

#endif /* PYCONFIG_H */