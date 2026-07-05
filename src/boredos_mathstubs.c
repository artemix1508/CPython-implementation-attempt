/* Math function stubs for BoredOS CPython port */
double modf(double x, double *iptr) {
    return __builtin_modf(x, iptr);
}
double round(double x) {
    return __builtin_round(x);
}
double fma(double x, double y, double z) {
    return __builtin_fma(x, y, z);
}
double log1p(double x) {
    return __builtin_log1p(x);
}
double acosh(double x) {
    return __builtin_acosh(x);
}
double asinh(double x) {
    return __builtin_asinh(x);
}
double atan(double x) {
    return __builtin_atan(x);
}
double atanh(double x) {
    return __builtin_atanh(x);
}
double cbrt(double x) {
    return __builtin_cbrt(x);
}
double copysign(double x, double y) {
    return __builtin_copysign(x, y);
}
double erf(double x) {
    return __builtin_erf(x);
}
double erfc(double x) {
    return __builtin_erfc(x);
}
double exp2(double x) {
    return __builtin_exp2(x);
}
double expm1(double x) {
    return __builtin_expm1(x);
}
double lgamma(double x) {
    return __builtin_lgamma(x);
}
double tgamma(double x) {
    return __builtin_tgamma(x);
}
double trunc(double x) {
    return __builtin_trunc(x);
}
double remainder(double x, double y) {
    return __builtin_remainder(x, y);
}
double nextafter(double x, double y) {
    return __builtin_nextafter(x, y);
}