// Copyright 2018 Apex.AI, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Co-developed by Tier IV, Inc. and Apex.AI, Inc.

#ifndef SERIAL_DRIVER__VISIBILITY_CONTROL_HPP_
#define SERIAL_DRIVER__VISIBILITY_CONTROL_HPP_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define SERIAL_DRIVER_EXPORT __attribute__ ((dllexport))
    #define SERIAL_DRIVER_IMPORT __attribute__ ((dllimport))
  #else
    #define SERIAL_DRIVER_EXPORT __declspec(dllexport)
    #define SERIAL_DRIVER_IMPORT __declspec(dllimport)
  #endif
  #ifdef SERIAL_DRIVER_BUILDING_DLL
    #define SERIAL_DRIVER_PUBLIC SERIAL_DRIVER_EXPORT
  #else
    #define SERIAL_DRIVER_PUBLIC SERIAL_DRIVER_IMPORT
  #endif
  #define SERIAL_DRIVER_PUBLIC_TYPE SERIAL_DRIVER_PUBLIC
  #define SERIAL_DRIVER_LOCAL
#else
  #define SERIAL_DRIVER_EXPORT __attribute__ ((visibility("default")))
  #define SERIAL_DRIVER_IMPORT
  #if __GNUC__ >= 4
    #define SERIAL_DRIVER_PUBLIC __attribute__ ((visibility("default")))
    #define SERIAL_DRIVER_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define SERIAL_DRIVER_PUBLIC
    #define SERIAL_DRIVER_LOCAL
  #endif
  #define SERIAL_DRIVER_PUBLIC_TYPE
#endif

#endif  // SERIAL_DRIVER__VISIBILITY_CONTROL_HPP_
