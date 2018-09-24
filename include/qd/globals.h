#ifndef _QD_GLOBALS_H
#define _QD_GLOBALS_H

#include <qd/qd_real.h>
#include <qd/dd_real.h>

#include <cfloat>
#include <cmath>
#include <type_traits>
#include <functional>


#ifndef USER_STD_HAS_IDENTITY
#define USER_STD_HAS_IDENTITY

namespace _std
{
  template <typename T>
  struct identity
  {
    typedef T type;
  };
}

#endif

// cast functions

#ifndef QD_INTEGRATION_ENABLED
#ifdef ENABLE_QD_QD_INTEGRATION
namespace qd
{
  inline qd_real to_real(int i) { return i; }
  inline qd_real to_real(long i) { return int64_t(i); }
  inline qd_real to_real(int64_t i) { return i; }
  inline qd_real to_real(double d) { return d; }
}

#define QD_INTEGRATION_ENABLED 1

#elif defined(ENABLE_QD_DD_INTEGRATION)
namespace qd
{
  inline dd_real to_real(int i) { return i; }
  inline dd_real to_real(long i) { return int64_t(i); }
  inline dd_real to_real(int64_t i) { return i; }
  inline dd_real to_real(double d) { return d; }
}

#define QD_INTEGRATION_ENABLED 1

#else

inline int to_double(int i) { return i; }
inline long to_double(long i) { return i; }
inline int64_t to_double(int64_t i) { return i; }
inline double to_double(double d) { return d; }

namespace qd
{
  inline double to_real(int i) { return double(i); }
  inline double to_real(long i) { return double(i); }
  inline double to_real(int64_t i) { return double(i); }
  inline double to_real(double d) { return d; }
}

#define QD_INTEGRATION_ENABLED 0

#endif

template <typename T>
inline double as_double(T d) { return double(d); }

#endif

namespace qd
{
  inline qd_real cast_to(const qd_real & qd, _std::identity<qd_real>)
  {
    return qd;
  }

  inline dd_real cast_to(const dd_real & dd, _std::identity<dd_real>)
  {
    return dd;
  }

  inline dd_real cast_to(const qd_real & qd, _std::identity<dd_real>)
  {
    return dd_real(qd.x[0], qd.x[1]);
  }

  inline qd_real cast_to(const dd_real & dd, _std::identity<qd_real>)
  {
    return qd_real(dd.x[0], dd.x[1], 0, 0);
  }

  inline double cast_to(const qd_real & qd, _std::identity<double>)
  {
    return to_double(qd);
  }

  inline double cast_to(const dd_real & dd, _std::identity<double>)
  {
    return to_double(dd);
  }

  inline double cast_to(double d, _std::identity<double>)
  {
    return d;
  }

  inline int cast_to(double d, _std::identity<int>)
  {
      return int(d);
  }

  inline int cast_to(int i, _std::identity<int>)
  {
    return i;
  }

  template <typename T>
  inline bool is_valid_float(const T & v)
  {
    static_assert(std::is_floating_point<T>::value, "type T must be float");

    return (std::isnormal(v) && (std::numeric_limits<T>::max)() != v && -(std::numeric_limits<T>::max)() != v || v == 0.0);
  }

  template <typename T>
  inline bool is_valid_not_zero_float(const T & v)
  {
    static_assert(std::is_floating_point<T>::value, "type T must be float");

    return (is_valid_float(v) && (v != 0));
  }

  template <typename T>
  extern inline T truncate_float_to_minmax(const T & value, const T & min_value, const T & max_value)
  {
    static_assert(std::is_floating_point<T>::value, "type T must be float");

    //assert(max_value, min_value);

    if (max_value < value) {
      return max_value;
    }

    if (value < min_value) {
      return min_value;
    }

    return value;
  }

  template <typename T>
  extern inline T fix_float_trigonometric_range_factor(const T & value)
  {
    static_assert(std::is_floating_point<T>::value, "type T must be float");

    // avoid fix in special case
    if (is_valid_not_zero_float(value)) {
      return truncate_float_to_minmax(value, T(-1.0), T(+1.0));
    }

    return value;
  }

  template <typename T>
  extern inline T fix_float_trigonometric_range_asin(const T & value, const std::function<T()> & pi_getter)
  {
    static_assert(std::is_floating_point<T>::value, "type T must be float");

    // avoid fix in special case
    if (is_valid_not_zero_float(value)) {
      const T pi = pi_getter();
      const T min_value_included = -pi / 2;
      const T max_value_included = pi / 2;
      return truncate_float_to_minmax(value, min_value_included, max_value_included);
    }

    return value;
  }

  template <typename T>
  extern inline T fix_float_trigonometric_range_acos(const T & value, const std::function<T()> & pi_getter)
  {
    static_assert(std::is_floating_point<T>::value, "type T must be float");

    // avoid fix in special case
    if (is_valid_not_zero_float(value)) {
      const T pi = pi_getter();
      const T min_value_included = 0;
      const T max_value_included = pi;
      return truncate_float_to_minmax(value, min_value_included, max_value_included);
    }

    return value;
  }

  template <typename T>
  extern inline T fix_float_trigonometric_range_atan(const T & value, const std::function<T()> & pi_getter)
  {
    static_assert(std::is_floating_point<T>::value, "type T must be float");

    return fix_float_trigonometric_range_asin(value, pi_getter);
  }

  template <typename T>
  extern inline T fix_float_trigonometric_range_atan2(const T & value, const std::function<T()> & pi_getter)
  {
    static_assert(std::is_floating_point<T>::value, "type T must be float");

    // avoid fix in special case
    if (is_valid_not_zero_float(value)) {
      const T pi = pi_getter();
      const T min_value_exluded = std::nextafter(-pi, std::numeric_limits<T>::infinity());
      const T max_value_included = pi;
      return truncate_float_to_minmax(value, min_value_exluded, max_value_included);
    }

    return value;
  }
}

#endif
