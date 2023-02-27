#ifndef INCLUDE_LIGO_PYTHON_HPP_
#define INCLUDE_LIGO_PYTHON_HPP_
// use this file instead of including <Python.h>

// disable linking to python*_d.lib on MSVC
#if defined(_MSC_VER)
#pragma warning(push)
#if defined(_DEBUG) && !defined(Py_DEBUG)
#define LIGO_DEBUG_MARKER
#undef _DEBUG
#endif
#endif

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

// turn _DEBUG back to whatever it was
#if defined(_MSC_VER)
#if defined(NB_DEBUG_MARKER)
#define _DEBUG
#undef LIGO_DEBUG_MARKER
#endif
#pragma warning(pop)
#endif

#endif  // INCLUDE_LIGO_PYTHON_HPP_
