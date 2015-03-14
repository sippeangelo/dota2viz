/**
 * @file config.hpp
 * @author Robin Dietrich <me (at) invokr (dot) org>
 * @version 1.1
 *
 * @par License
 *    Alice Replay Parser
 *    Copyright 2014 Robin Dietrich
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0

 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef _DOTA_CONFIG_HPP_
#define _DOTA_CONFIG_HPP_

#define DOTA_VERSION ""          // sha1 hash of repository version
#define DOTA_PYTHON          // whether to build python binding
#define DOTA_EXTRA   OFF         // whether to rely on addon functionallity
#define DOTA_64BIT   0          // target architecture
#define DOTA_DEBUG   OFF               // whether to enable debugging
#define DOTA_EMSCRIPTEN OFF // whether alice is being build for emscripten
#define DOTA_BZIP2   OFF               // whether bzip2 uncompression is enabled

#include <cstring>
#define D_FILE (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if DOTA_DEBUG > 0
  #define D_(x, y) if( DOTA_DEBUG >= y ) { x }
#else
  #define D_(x, y)
#endif

#endif /* _DOTA_CONFIG_HPP_ */
