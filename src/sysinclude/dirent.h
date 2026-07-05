#ifndef STUB_DIRENT_H
#define STUB_DIRENT_H
#define direct dirent

struct dirent {
    unsigned long  d_ino;
    unsigned short d_reclen;
    unsigned char  d_type;
    char           d_name[256];
};

typedef struct { int fd; } DIR;

static inline DIR *opendir(const char *p) { (void)p; return NULL; }
static inline struct dirent *readdir(DIR *d) { (void)d; return NULL; }
static inline int closedir(DIR *d) { (void)d; return 0; }
static inline int mkdir(const char *p, int m) { (void)p;(void)m; return -1; }
static inline int rmdir(const char *p) { (void)p; return -1; }
static inline int lstat(const char *p, struct stat *s) { return stat(p, s); }
static inline int utime(const char *p, void *t) { (void)p;(void)t; return 0; }
static inline int setenv(const char *n, const char *v, int o) { (void)n;(void)v;(void)o; return 0; }
static inline int unsetenv(const char *n) { (void)n; return 0; }

#endif