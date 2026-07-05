#ifndef STUB_STAT_H
#define STUB_STAT_H

typedef unsigned long dev_t;
typedef unsigned long ino_t;
typedef unsigned int  mode_t;
typedef unsigned long nlink_t;
typedef unsigned int  uid_t;
typedef unsigned int  gid_t;
typedef long          off_t;
typedef long          blksize_t;
typedef long          blkcnt_t;

#define S_IFMT   0170000
#define S_IFDIR  0040000
#define S_IFREG  0100000
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define S_IFCHR  0020000
#define S_IFBLK  0060000
#define S_IFIFO  0010000
#define S_IFLNK  0120000
#define S_IFSOCK 0140000
#define S_ISCHR(m)  (((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m)  (((m) & S_IFMT) == S_IFBLK)
#define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
#define S_ISLNK(m)  (((m) & S_IFMT) == S_IFLNK)


struct stat {
    dev_t     st_dev;
    ino_t     st_ino;
    mode_t    st_mode;
    nlink_t   st_nlink;
    uid_t     st_uid;
    gid_t     st_gid;
    dev_t     st_rdev;
    off_t     st_size;
    blksize_t st_blksize;
    blkcnt_t  st_blocks;
    long long st_atime;
    long long st_mtime;
    long long st_ctime;
};

static inline int stat(const char *p, struct stat *s) { (void)p;(void)s; return -1; }
static inline int fstat(int fd, struct stat *s) { (void)fd;(void)s; return -1; }

#endif