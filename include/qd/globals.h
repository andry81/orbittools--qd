#ifndef _QD_GLOBALS_H
#define _QD_GLOBALS_H

#include <qd/qd_real.h>
#include <qd/dd_real.h>


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
}

#endif
