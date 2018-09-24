/*
 * include/qd_real.h
 *
 * This work was supported by the Director, Office of Science, Division
 * of Mathematical, Information, and Computational Sciences of the
 * U.S. Department of Energy under contract number DE-AC03-76SF00098.
 *
 * Copyright (c) 2000-2007
 *
 * Quad-double precision (>= 212-bit significand) floating point arithmetic
 * package, written in ANSI C++, taking full advantage of operator overloading.
 * Uses similar techniques as that of David Bailey's double-double package 
 * and that of Jonathan Shewchuk's adaptive precision floating point 
 * arithmetic package.  See
 *
 *   http://www.nersc.gov/~dhbailey/mpdist/mpdist.html
 *   http://www.cs.cmu.edu/~quake/robust.html
 *
 * for more details.
 *
 * Yozo Hida
 */
#ifndef _QD_QD_REAL_H
#define _QD_QD_REAL_H

#include <cstdint>
#include <iostream>
#include <string>
#include <limits>
#include <type_traits>
#include <qd/qd_config.h>
#include <qd/dd_real.h>

struct QD_API qd_real {
  double x[4];    /* The Components. */

  /* Eliminates any zeros in the middle component(s). */
  void zero_elim();
  void zero_elim(double &e);

  void renorm();
  void renorm(double &e);

  void quick_accum(double d, double &e);
  void quick_prod_accum(double a, double b, double &e);

  qd_real(double x0, double x1, double x2, double x3);
  explicit qd_real(const double *xx);

  static const qd_real & _2pi();
  static const qd_real & _pi();
  static const qd_real & _3pi4();
  static const qd_real & _pi2();
  static const qd_real & _pi4();
  static const qd_real & _e();
  static const qd_real & _log2();
  static const qd_real & _log10();
  static const qd_real & _nan();
  static const qd_real & _inf();

  static double _eps();
  static double _min_normalized();
  static const qd_real & _max();
  static const qd_real & _safe_max();
  static int _ndigits();

  qd_real();
  qd_real(const char *s);
  qd_real(const dd_real &dd);
  qd_real(double d);
  qd_real(int i);
  qd_real(int64_t i);

  double operator[](int i) const;
  double &operator[](int i);

  static void error(const char *msg);

  bool isnormal() const;
  bool isnan() const;
  bool isfinite() const { return QD_ISFINITE(x[0]); }
  bool isinf() const { return QD_ISINF(x[0]); }

  static qd_real ieee_add(const qd_real &a, const qd_real &b);
  static qd_real sloppy_add(const qd_real &a, const qd_real &b);

  qd_real &operator+=(int a);
  qd_real &operator+=(int64_t a);
  qd_real &operator+=(double a);
  qd_real &operator+=(const dd_real &a);
  qd_real &operator+=(const qd_real &a);

  qd_real &operator-=(int a);
  qd_real &operator-=(int64_t a);
  qd_real &operator-=(double a);
  qd_real &operator-=(const dd_real &a);
  qd_real &operator-=(const qd_real &a);

  static qd_real sloppy_mul(const qd_real &a, const qd_real &b);
  static qd_real accurate_mul(const qd_real &a, const qd_real &b);

  qd_real &operator*=(int a);
  qd_real &operator*=(int64_t a);
  qd_real &operator*=(double a);
  qd_real &operator*=(const dd_real &a);
  qd_real &operator*=(const qd_real &a);

  static qd_real sloppy_div(const qd_real &a, const dd_real &b);
  static qd_real accurate_div(const qd_real &a, const dd_real &b);
  static qd_real sloppy_div(const qd_real &a, const qd_real &b);
  static qd_real accurate_div(const qd_real &a, const qd_real &b);

  qd_real &operator/=(int a);
  qd_real &operator/=(int64_t a);
  qd_real &operator/=(double a);
  qd_real &operator/=(const dd_real &a);
  qd_real &operator/=(const qd_real &a);

  qd_real operator^(int n) const;

  qd_real operator-() const;

  qd_real &operator=(int a);
  qd_real &operator=(int64_t a);
  qd_real &operator=(double a);
  qd_real &operator=(const dd_real &a);
  qd_real &operator=(const char *s);

  bool is_zero() const;
  bool is_one() const;
  bool is_positive() const;
  bool is_negative() const;

  static qd_real rand(void);

  void to_digits(char *s, int &expn, int precision = _ndigits()) const;
  void write(char *s, int len, int precision = _ndigits(), 
      bool showpos = false, bool uppercase = false) const;
  std::string to_string(int precision = _ndigits(), int width = 0, 
      std::ios_base::fmtflags fmt = static_cast<std::ios_base::fmtflags>(0), 
      bool showpos = false, bool uppercase = false, char fill = ' ') const;
  static int read(const char *s, qd_real &a);

  /* Debugging methods */
  void dump(const std::string &name = "", std::ostream &os = std::cerr) const;
  void dump_bits(const std::string &name = "", 
                 std::ostream &os = std::cerr) const;

  static qd_real debug_rand();

};

namespace std {
  template <>
  class numeric_limits<qd_real> : public numeric_limits<double> {
  public:
    inline static double epsilon() { return qd_real::_eps(); }
    inline static double (min)() { return qd_real::_min_normalized(); }
    inline static qd_real (max)() { return qd_real::_max(); }
    inline static qd_real safe_max() { return qd_real::_safe_max(); }
    inline static qd_real infinity() { return qd_real::_inf(); }
    static const bool has_infinity = true;
    static const int digits = 209;
    static const int digits10 = 62;
  };

  // integration with type traits
  template <>
  struct is_floating_point<qd_real> : true_type
  {
  };

  template <>
  struct is_signed<qd_real> : true_type
  {
  };

  template <>
  struct is_unsigned<qd_real> : false_type
  {
  };

  template <>
  struct is_integral<qd_real> : false_type
  {
  };
}

QD_API qd_real polyeval(const qd_real *c, int n, const qd_real &x);
QD_API qd_real polyroot(const qd_real *c, int n, 
    const qd_real &x0, int max_iter = 64, double thresh = 0.0);

QD_API qd_real qdrand(void);

namespace std {
    QD_API qd_real sqrt(const qd_real &a);

    QD_API inline bool isnormal(const qd_real &a) { return a.isnormal(); }
    QD_API inline bool isnan(const qd_real &a) { return a.isnan(); }
    QD_API inline bool isfinite(const qd_real &a) { return a.isfinite(); }
    QD_API inline bool isinf(const qd_real &a) { return a.isinf(); }

    QD_API inline bool issubnormal(const qd_real &a) {
        return (fpclassify(a.x[3]) == FP_SUBNORMAL || fpclassify(a.x[2]) == FP_SUBNORMAL ||
            fpclassify(a.x[1]) == FP_SUBNORMAL || fpclassify(a.x[0]) == FP_SUBNORMAL);
    }
}

/* Computes  qd * d  where d is known to be a power of 2.
   This can be done component wise.                      */
QD_API qd_real mul_pwr2(const qd_real &qd, double d);

QD_API qd_real operator+(const qd_real &a, const qd_real &b);
QD_API qd_real operator+(const dd_real &a, const qd_real &b);
QD_API qd_real operator+(const qd_real &a, const dd_real &b);
QD_API qd_real operator+(const qd_real &a, double b);
QD_API qd_real operator+(double a, const qd_real &b);

QD_API qd_real operator+(const qd_real &a, int64_t b);
QD_API qd_real operator+(int64_t a, const qd_real &b);

QD_API qd_real operator+(const qd_real &a, int b);
QD_API qd_real operator+(int a, const qd_real &b);

QD_API qd_real operator-(const qd_real &a, const qd_real &b);
QD_API qd_real operator-(const dd_real &a, const qd_real &b);
QD_API qd_real operator-(const qd_real &a, const dd_real &b);
QD_API qd_real operator-(const qd_real &a, double b);
QD_API qd_real operator-(double a, const qd_real &b);

QD_API qd_real operator-(const qd_real &a, int64_t b);
QD_API qd_real operator-(int64_t a, const qd_real &b);

QD_API qd_real operator-(const qd_real &a, int b);
QD_API qd_real operator-(int a, const qd_real &b);

QD_API qd_real operator*(const qd_real &a, const qd_real &b);
QD_API qd_real operator*(const dd_real &a, const qd_real &b);
QD_API qd_real operator*(const qd_real &a, const dd_real &b);
QD_API qd_real operator*(const qd_real &a, double b);
QD_API qd_real operator*(double a, const qd_real &b);

QD_API qd_real operator*(const qd_real &a, int64_t b);
QD_API qd_real operator*(int64_t a, const qd_real &b);

QD_API qd_real operator*(const qd_real &a, int b);
QD_API qd_real operator*(int a, const qd_real &b);

QD_API qd_real operator/(const qd_real &a, const qd_real &b);
QD_API qd_real operator/(const dd_real &a, const qd_real &b);
QD_API qd_real operator/(const qd_real &a, const dd_real &b);
QD_API qd_real operator/(const qd_real &a, double b);
QD_API qd_real operator/(double a, const qd_real &b);

QD_API qd_real operator/(const qd_real &a, int64_t b);
QD_API qd_real operator/(int64_t a, const qd_real &b);

QD_API qd_real operator/(const qd_real &a, int b);
QD_API qd_real operator/(int a, const qd_real &b);


QD_API qd_real sqr(const qd_real &a);

namespace std {
    QD_API qd_real sqrt(const qd_real &a);
    QD_API qd_real pow(const qd_real &a, int n);
    QD_API qd_real pow(const qd_real &a, int64_t n);
    QD_API qd_real pow(const qd_real &a, double b);
    QD_API qd_real pow(const qd_real &a, const qd_real &b);
}

QD_API qd_real npwr(const qd_real &a, int n);
QD_API qd_real npwr(const qd_real &a, int64_t n);

QD_API qd_real nroot(const qd_real &a, int n);

QD_API qd_real rem(const qd_real &a, const qd_real &b);
QD_API qd_real drem(const qd_real &a, const qd_real &b);
QD_API qd_real divrem(const qd_real &a, const qd_real &b, qd_real &r);

dd_real to_dd_real(const qd_real &a);
double  to_double(const qd_real &a);
int     to_int(const qd_real &a);

QD_API bool operator==(const qd_real &a, const qd_real &b);
QD_API bool operator==(const qd_real &a, const dd_real &b);
QD_API bool operator==(const dd_real &a, const qd_real &b);
QD_API bool operator==(double a, const qd_real &b);
QD_API bool operator==(const qd_real &a, double b);

QD_API bool operator<(const qd_real &a, const qd_real &b);
QD_API bool operator<(const qd_real &a, const dd_real &b);
QD_API bool operator<(const dd_real &a, const qd_real &b);
QD_API bool operator<(double a, const qd_real &b);
QD_API bool operator<(const qd_real &a, double b);

QD_API bool operator>(const qd_real &a, const qd_real &b);
QD_API bool operator>(const qd_real &a, const dd_real &b);
QD_API bool operator>(const dd_real &a, const qd_real &b);
QD_API bool operator>(double a, const qd_real &b);
QD_API bool operator>(const qd_real &a, double b);

QD_API bool operator<=(const qd_real &a, const qd_real &b);
QD_API bool operator<=(const qd_real &a, const dd_real &b);
QD_API bool operator<=(const dd_real &a, const qd_real &b);
QD_API bool operator<=(double a, const qd_real &b);
QD_API bool operator<=(const qd_real &a, double b);

QD_API bool operator>=(const qd_real &a, const qd_real &b);
QD_API bool operator>=(const qd_real &a, const dd_real &b);
QD_API bool operator>=(const dd_real &a, const qd_real &b);
QD_API bool operator>=(double a, const qd_real &b);
QD_API bool operator>=(const qd_real &a, double b);

QD_API bool operator!=(const qd_real &a, const qd_real &b);
QD_API bool operator!=(const qd_real &a, const dd_real &b);
QD_API bool operator!=(const dd_real &a, const qd_real &b);
QD_API bool operator!=(double a, const qd_real &b);
QD_API bool operator!=(const qd_real &a, double b);

namespace std {
    QD_API qd_real fabs(const qd_real &a);
    QD_API qd_real abs(const qd_real &a);    /* same as fabs */

    QD_API qd_real ldexp(const qd_real &a, int n);
}

QD_API qd_real nint(const qd_real &a);
QD_API qd_real quick_nint(const qd_real &a);

namespace std {
    QD_API qd_real floor(const qd_real &a);
    QD_API qd_real ceil(const qd_real &a);
}

QD_API qd_real aint(const qd_real &a);

namespace std {
    QD_API qd_real sin(const qd_real &a);
    QD_API qd_real cos(const qd_real &a);
    QD_API qd_real tan(const qd_real &a);
}

QD_API void sincos(const qd_real &a, qd_real &s, qd_real &c);

namespace std {
    QD_API qd_real asin(const qd_real &a);
    QD_API qd_real acos(const qd_real &a);
    QD_API qd_real atan(const qd_real &a);
    QD_API qd_real atan2(const qd_real &y, const qd_real &x);

    QD_API qd_real exp(const qd_real &a);
    QD_API qd_real log(const qd_real &a);
    QD_API qd_real log10(const qd_real &a);

    QD_API qd_real sinh(const qd_real &a);
    QD_API qd_real cosh(const qd_real &a);
    QD_API qd_real tanh(const qd_real &a);
}

QD_API void sincosh(const qd_real &a, qd_real &sin_qd, qd_real &cos_qd);

namespace std {
    QD_API qd_real asinh(const qd_real &a);
    QD_API qd_real acosh(const qd_real &a);
    QD_API qd_real atanh(const qd_real &a);
}

QD_API qd_real qdrand(void);

namespace std {
    QD_API qd_real(max)(const qd_real &a, const qd_real &b);
    QD_API qd_real(max)(const qd_real &a, const qd_real &b, const qd_real &c);
    QD_API qd_real(min)(const qd_real &a, const qd_real &b);
    QD_API qd_real(min)(const qd_real &a, const qd_real &b, const qd_real &c);

    QD_API qd_real fmod(const qd_real &a, const qd_real &b);
    QD_API qd_real fmod(const qd_real &a, double b);
    QD_API qd_real fmod(const qd_real &a, int64_t b);
    QD_API qd_real fmod(const qd_real &a, int b);
}

QD_API std::ostream &operator<<(std::ostream &s, const qd_real &a);
QD_API std::istream &operator>>(std::istream &s, qd_real &a);
#ifdef QD_INLINE
#include <qd/qd_inline.h>
#endif

namespace std {
    QD_API inline qd_real nextafter(const qd_real & from, const qd_real & to) {
        if (from.isnan() || to.isnan()) {
            const double quite_NaN = numeric_limits<double>::quiet_NaN();
            return qd_real(quite_NaN, quite_NaN, quite_NaN, quite_NaN);
        }

        if (from < to) {
            const double pos_infinity = numeric_limits<double>::infinity();

            const double next_x0 = nextafter(from.x[0], pos_infinity);
            if (isinf(next_x0)) {
                return qd_real::_inf();
            }

            if (fpclassify(next_x0) != FP_SUBNORMAL && !next_x0) {
                const double x0_max = next_x0 - from.x[0];

                const double next_x1 = nextafter(from.x[1], pos_infinity);
                if (next_x1 <= x0_max) {
                    if (from.x[1]) {
                        const double x1_max = next_x1 - from.x[1];

                        const double next_x2 = nextafter(from.x[2], pos_infinity);
                        if (next_x2 <= x1_max) {
                            if (from.x[2]) {
                                const double x2_max = next_x2 - from.x[2];

                                const double next_x3 = nextafter(from.x[3], pos_infinity);
                                if (next_x3 < x2_max) {
                                    return qd_real(from.x[0], from.x[1], from.x[2], next_x3);
                                }
                            }

                            if (next_x2 != x1_max) {
                                return qd_real(from.x[0], from.x[1], next_x2, 0);
                            }
                        }
                    }

                    if (next_x1 != x0_max) {
                        return qd_real(from.x[0], next_x1, 0, 0);
                    }
                }
            }

            return qd_real(next_x0, 0, 0, 0);
        }
        else if (from > to) {
            const double neg_infinity = -numeric_limits<double>::infinity();

            const double next_x0 = nextafter(from.x[0], neg_infinity);
            if (isinf(next_x0)) {
                return -qd_real::_inf();
            }

            if (fpclassify(next_x0) != FP_SUBNORMAL && !next_x0) {
                const double x0_min = next_x0 - from.x[0];

                const double next_x1 = nextafter(from.x[1], neg_infinity);
                if (next_x1 >= x0_min) {
                    if (from.x[1]) {
                        const double x1_min = next_x1 - from.x[1];

                        const double next_x2 = nextafter(from.x[2], neg_infinity);
                        if (next_x2 >= x1_min) {
                            if (from.x[2]) {
                                const double x2_min = next_x2 - from.x[2];

                                const double next_x3 = nextafter(from.x[3], neg_infinity);
                                if (next_x3 > x2_min) {
                                    return qd_real(from.x[0], from.x[1], from.x[2], next_x3);
                                }
                            }

                            if (next_x2 != x1_min) {
                                return qd_real(from.x[0], from.x[1], next_x2, 0);
                            }
                        }
                    }

                    if (next_x1 != x0_min) {
                        return qd_real(from.x[0], next_x1, 0, 0);
                    }
                }
            }

            return qd_real(next_x0, 0, 0, 0);
        }

        return to;
    }
}

#endif /* _QD_QD_REAL_H */
