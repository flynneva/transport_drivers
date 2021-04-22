#ifndef IO_CONTEXT__VISIBILITY_CONTROL_HPP_
#define IO_CONTEXT__VISIBILITY_CONTROL_HPP_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define IO_CONTEXT_EXPORT __attribute__ ((dllexport))
    #define IO_CONTEXT_IMPORT __attribute__ ((dllimport))
  #else
    #define IO_CONTEXT_EXPORT __declspec(dllexport)
    #define IO_CONTEXT_IMPORT __declspec(dllimport)
  #endif
  #ifdef IO_CONTEXT_BUILDING_DLL
    #define IO_CONTEXT_PUBLIC IO_CONTEXT_EXPORT
  #else
    #define IO_CONTEXT_PUBLIC IO_CONTEXT_IMPORT
  #endif
  #define IO_CONTEXT_PUBLIC_TYPE IO_CONTEXT_PUBLIC
  #define IO_CONTEXT_LOCAL
#else
  #define IO_CONTEXT_EXPORT __attribute__ ((visibility("default")))
  #define IO_CONTEXT_IMPORT
  #if __GNUC__ >= 4
    #define IO_CONTEXT_PUBLIC __attribute__ ((visibility("default")))
    #define IO_CONTEXT_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define IO_CONTEXT_PUBLIC
    #define IO_CONTEXT_LOCAL
  #endif
  #define IO_CONTEXT_PUBLIC_TYPE
#endif

#endif  // IO_CONTEXT__VISIBILITY_CONTROL_HPP_