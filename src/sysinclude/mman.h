#ifndef STUB_MMAN_H
#define STUB_MMAN_H
#define PROT_READ  0x1
#define PROT_WRITE 0x2
#define MAP_SHARED  0x1
#define MAP_PRIVATE 0x2
#define MAP_FAILED  ((void*)-1)
static inline void* mmap(void *a, unsigned long l, int p, int f, int fd, long o)
{ (void)a;(void)l;(void)p;(void)f;(void)fd;(void)o; return MAP_FAILED; }
static inline int munmap(void *a, unsigned long l) { (void)a;(void)l; return -1; }
#endif