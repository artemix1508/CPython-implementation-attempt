#ifndef STUB_PTHREAD_H
#define STUB_PTHREAD_H

typedef int pthread_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_attr_t;

static inline int pthread_mutex_init(pthread_mutex_t *m, const pthread_mutexattr_t *a) { (void)m;(void)a; return 0; }
static inline int pthread_mutex_destroy(pthread_mutex_t *m) { (void)m; return 0; }
static inline int pthread_mutex_lock(pthread_mutex_t *m) { (void)m; return 0; }
static inline int pthread_mutex_unlock(pthread_mutex_t *m) { (void)m; return 0; }
static inline int pthread_cond_init(pthread_cond_t *c, const pthread_condattr_t *a) { (void)c;(void)a; return 0; }
static inline int pthread_cond_destroy(pthread_cond_t *c) { (void)c; return 0; }
static inline int pthread_cond_signal(pthread_cond_t *c) { (void)c; return 0; }
static inline int pthread_cond_broadcast(pthread_cond_t *c) { (void)c; return 0; }
static inline int pthread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m) { (void)c;(void)m; return 0; }
static inline int pthread_key_create(pthread_key_t *k, void (*d)(void*)) { (void)k;(void)d; return 0; }
static inline int pthread_key_delete(pthread_key_t k) { (void)k; return 0; }
static inline void* pthread_getspecific(pthread_key_t k) { (void)k; return 0; }
static inline int pthread_setspecific(pthread_key_t k, const void *v) { (void)k;(void)v; return 0; }
static inline pthread_t pthread_self(void) { return 0; }
static inline int pthread_once(pthread_once_t *o, void (*f)(void)) { (void)o;(void)f; return 0; }
static inline int pthread_create(pthread_t *t, const void *a, void*(*f)(void*), void *arg) { (void)t;(void)a;(void)f;(void)arg; return 0; }
static inline int pthread_join(pthread_t t, void **r) { (void)t;(void)r; return 0; }
static inline int pthread_cond_timedwait(pthread_cond_t *c, pthread_mutex_t *m, const struct timespec *t) { (void)c;(void)m;(void)t; return 0; }
static inline int pthread_attr_init(pthread_attr_t *a) { (void)a; return 0; }
static inline int pthread_attr_destroy(pthread_attr_t *a) { (void)a; return 0; }
static inline int pthread_attr_setstacksize(pthread_attr_t *a, size_t s) { (void)a;(void)s; return 0; }
static inline int pthread_attr_setdetachstate(pthread_attr_t *a, int s) { (void)a;(void)s; return 0; }
static inline int pthread_detach(pthread_t t) { (void)t; return 0; }
static inline void pthread_exit(void *v) { (void)v; }
static inline int pthread_mutex_trylock(pthread_mutex_t *m) { (void)m; return 0; }
static inline int pthread_equal(pthread_t a, pthread_t b) { return a == b; }

#endif