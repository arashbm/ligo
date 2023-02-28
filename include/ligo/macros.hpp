#ifndef INCLUDE_LIGO_MACROS_HPP_
#define INCLUDE_LIGO_MACROS_HPP_

#define LIGO_STRINGIFY(x) #x
#define LIGO_TOSTRING(x) LIGO_STRINGIFY(x)
#define LIGO_CONCAT(first, second) first##second
#if defined(_WIN32)
#define LIGO_EXPORT        __declspec(dllexport)
#else
#define LIGO_EXPORT        __attribute__ ((visibility("default")))
#endif

#define LIGO_MODULE(name, docs, variable)                                     \
  extern "C" [[maybe_unused]] LIGO_EXPORT PyObject* PyInit_##name();          \
  static ::ligo::python_module LIGO_CONCAT(ligo_module_, name)(               \
    LIGO_TOSTRING(name), LIGO_TOSTRING(docs));                                \
  [[maybe_unused]] static void LIGO_CONCAT(                                   \
    ligo_init_, name)(::ligo::python_module &);                               \
  extern "C" LIGO_EXPORT PyObject* PyInit_##name() {                          \
      try {                                                                   \
          LIGO_CONCAT(ligo_init_, name)(LIGO_CONCAT(ligo_module_, name));     \
          return LIGO_CONCAT(ligo_module_, name).init();                      \
      } catch (const std::exception &e) {                                     \
          PyErr_SetString(PyExc_ImportError, e.what());                       \
          return nullptr;                                                     \
      }                                                                       \
  }                                                                           \
  void LIGO_CONCAT(ligo_init_, name)(::ligo::python_module& (variable))

#endif  // INCLUDE_LIGO_MACROS_HPP_
