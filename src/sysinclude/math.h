#ifndef STUB_MATH_H
#define STUB_MATH_H
#include_next <math.h>

#ifndef INFINITY
#define INFINITY __builtin_inff()
#endif
#ifndef NAN
#define NAN __builtin_nanf("")
#endif
#ifndef HUGE_VALF
#define HUGE_VALF __builtin_huge_valf()
#endif

/* Declarations for functions in boredos_mathstubs.c */
double log1p(double x);
double fma(double x, double y, double z);
double acosh(double x);
double asinh(double x);
double atan(double x);
double atanh(double x);
double cbrt(double x);
double copysign(double x, double y);
double erf(double x);
double erfc(double x);
double exp2(double x);
double expm1(double x);
double lgamma(double x);
double tgamma(double x);
double trunc(double x);
double remainder(double x, double y);
double round(double x);
double modf(double x, double *iptr);
double nextafter(double x, double y);

#endif