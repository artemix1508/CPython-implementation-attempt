#ifndef STUB_WCHAR_H
#define STUB_WCHAR_H

#include <stddef.h>
#include <stdarg.h>

typedef int wint_t;
typedef unsigned int wctype_t;

#ifndef WCHAR_MIN
#define WCHAR_MIN 0
#endif
#ifndef WCHAR_MAX
#define WCHAR_MAX 0x10ffff
#endif
#ifndef WEOF
#define WEOF ((wint_t)-1)
#endif

static inline size_t wcstombs(char *d, const wchar_t *s, size_t n) { (void)d;(void)s;(void)n; return 0; }
static inline size_t mbstowcs(wchar_t *d, const char *s, size_t n) { (void)d;(void)s;(void)n; return 0; }
static inline wchar_t *wcsncpy(wchar_t *d, const wchar_t *s, size_t n) { (void)d;(void)s;(void)n; return d; }
static inline long wcstol(const wchar_t *s, wchar_t **e, int b) { (void)s;(void)e;(void)b; return 0; }
static inline wchar_t *wcstok(wchar_t *s, const wchar_t *d, wchar_t **p) { (void)s;(void)d;(void)p; return NULL; }

/* Basic wchar functions CPython needs */
static inline size_t wcslen(const wchar_t *s) {
    const wchar_t *p = s;
    while (*p) p++;
    return p - s;
}

static inline wchar_t *wcsrchr(const wchar_t *s, wchar_t c) {
    const wchar_t *last = NULL;
    while (*s) { if (*s == c) last = s; s++; }
    return (wchar_t *)last;
}

static inline int wcsncmp(const wchar_t *a, const wchar_t *b, size_t n) {
    while (n && *a && *a == *b) { a++; b++; n--; }
    return n ? (*a - *b) : 0;
}

static inline wchar_t *wmemchr(const wchar_t *s, wchar_t c, size_t n) {
    while (n--) { if (*s == c) return (wchar_t *)s; s++; }
    return NULL;
}

static inline wchar_t *wcschr(const wchar_t *s, wchar_t c) {
    while (*s && *s != c) s++;
    return (*s == c) ? (wchar_t *)s : NULL;
}

static inline wchar_t *wcscpy(wchar_t *d, const wchar_t *s) {
    wchar_t *r = d;
    while ((*d++ = *s++));
    return r;
}
static inline int wcscmp(const wchar_t *a, const wchar_t *b) {
    while (*a && *a == *b) { a++; b++; }
    return *a - *b;
}
static inline wchar_t *wcscat(wchar_t *d, const wchar_t *s) {
    wchar_t *r = d;
    while (*d) d++;
    while ((*d++ = *s++));
    return r;
}

#endif