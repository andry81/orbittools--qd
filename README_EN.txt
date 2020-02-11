* README_EN.txt
* 2020.02.10
* qd

1. DESCRIPTION
2. LICENSE
3. REPOSITORIES
4. INSTALLATION
5. KNOWN ISSUES
6. AUTHOR

-------------------------------------------------------------------------------
1. DESCRIPTION
-------------------------------------------------------------------------------
QD patched sources fork from:
https://www.davidhbailey.com/dhbsoftware/

Other references:
http://crd-legacy.lbl.gov/~dhbailey/mpdist/
http://crd.lbl.gov/software/applied-mathematics-software/

From authors:

  QD (A C++/Fortran-90 double-double and quad-double package) 
  Unix-based systems (including Apple Macintosh systems)
  Before downloading or installing this software, please read
  LBNL-BSD-License.doc (which contains license information) and the README
  file. 

  This package supports both a double-double datatype (approx. 32 decimal
  digits) and a quad-double datatype (approx. 64 decimal digits). The
  computational library is written in C++. Both C++ and Fortran-90 high-level
  language interfaces are provided to permit one to use convert an existing C++
  or Fortran-90 program to use the library with only minor changes to the
  source code. In most cases only a few type statements and (for Fortran-90
  programs) read/write statements need to be changed. PSLQ and numerical
  quadrature programs are included. 

The original library patched to fix these issues:

1. Missed overloading for constructors, operators and functions.

2. Fix trigonometric range before call and after call to triginometric
   functions because of sloppy QD arithmetic outside and inside a function
   call.

Cmake scripts uses the cmake modules from the tacklelib library:

https://svn.code.sf.net/p/tacklelib/cmake/trunk

-------------------------------------------------------------------------------
2. LICENSE
-------------------------------------------------------------------------------
modified BSD license
(see included text file "COPYING" and "BSD-LBNL-License.doc")

-------------------------------------------------------------------------------
3. REPOSITORIES
-------------------------------------------------------------------------------
Primary:
  * https://sf.net/p/orbittools/qd_/HEAD/tree/trunk
    https://svn.code.sf.net/p/orbittools/qd_/trunk
First mirror:
  * https://github.com/andry81/orbittools--qd/tree/trunk
    https://github.com/andry81/orbittools--qd.git
Second mirror:
  * https://bitbucket.org/andry81/orbittools-qd/src/trunk
    https://bitbucket.org/andry81/orbittools-qd.git

-------------------------------------------------------------------------------
4. INSTALLATION
-------------------------------------------------------------------------------
N/A

-------------------------------------------------------------------------------
5. KNOWN ISSUES
-------------------------------------------------------------------------------

1. Construction from the int64_t utilizes conversion into the double type
   directly or as is, which means a big value greater than the length of the
   double type mantissa will be truncated to fit the mantissa.

-------------------------------------------------------------------------------
6. AUTHOR
-------------------------------------------------------------------------------
Andrey Dibrov (andry at inbox dot ru)
