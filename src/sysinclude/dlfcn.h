#ifndef STUB_DLFCN_H
#define STUB_DLFCN_H
#define RTLD_LAZY   0
#define RTLD_NOW    0
#define RTLD_GLOBAL 0
static inline void* dlopen(const char *f, int m) { (void)f; (void)m; return 0; }
static inline void* dlsym(void *h, const char *s) { (void)h; (void)s; return 0; }
static inline int   dlclose(void *h) { (void)h; return 0; }
static inline char* dlerror(void) { return "unsupported"; }
#endif