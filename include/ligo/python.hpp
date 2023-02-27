#ifndef INCLUDE_LIGO_PYTHON_HPP_
#define INCLUDE_LIGO_PYTHON_HPP_
// use this file instead of including <Python.h>

#include <Python.h>

// undefine the python overloads:
#if defined(isalnum)
#undef isalnum
#endif

#if defined(isalpha)
#undef isalpha
#endif

#if defined(islower)
#undef islower
#endif

#if defined(isspace)
#undef isspace
#endif

#if defined(isupper)
#undef isupper
#endif

#if defined(tolower)
#undef tolower
#endif

#if defined(toupper)
#undef toupper
#endif

#if defined(copysign)
#undef copysign
#endif

#if defined(setter)
#undef setter
#endif

#if defined(getter)
#undef getter
#endif

#endif  // INCLUDE_LIGO_PYTHON_HPP_
