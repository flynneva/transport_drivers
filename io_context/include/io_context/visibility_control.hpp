// Copyright 2021 Evan Flynn
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
