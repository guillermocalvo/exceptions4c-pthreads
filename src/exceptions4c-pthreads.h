/*
 * Copyright 2025 Guillermo Calvo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Thread-safe extension for exceptions4c.
 *
 * This library allows you to safely and concurrently use
 * [**exceptions4c**](https://github.com/guillermocalvo/exceptions4c/) on
 * multithreaded programs that are based on
 * [**POSIX threads**](https://man7.org/linux/man-pages/man7/pthreads.7.html).
 *
 * <a href="https://exceptions4c-pthreads.guillermo.dev/">
 * <img src="exceptions4c-pthreads.svg">
 * </a>
 *
 * This library consists of two files:
 *
 * - `exceptions4c-pthreads.h`
 * - `exceptions4c-pthreads.c`
 *
 * To use it in your project, include the header file in your source code files.
 *
 * ```c
 * #include <exceptions4c-pthreads.h>
 * ```
 *
 * And then link your program against the library code.
 *
 * @important
 * Remember to also link your program against libraries
 * [**exceptions4c**](https://github.com/guillermocalvo/exceptions4c/) and
 * [**pthreads**](https://man7.org/linux/man-pages/man7/pthreads.7.html).
 *
 *
 * @file        exceptions4c-pthreads.h
 * @version     0.1.0
 * @author      [Guillermo Calvo]
 * @copyright   Licensed under [Apache 2.0]
 * @see         For more information, visit the [project on GitHub]
 *
 * [Guillermo Calvo]: https://guillermo.dev
 * [Apache 2.0]: http://www.apache.org/licenses/LICENSE-2.0
 * [project on GitHub]: https://github.com/guillermocalvo/exceptions4c-pthreads
 */

#ifndef EXCEPTIONS4C_PTHREADS

/**
 * Returns the major version number of this library.
 */
#define EXCEPTIONS4C_PTHREADS 0

#include <exceptions4c.h>

/**
 * Supplies a thread-safe exception context.
 *
 * @note
 * This function MUST be passed to <tt>e4c_set_context_supplier</tt> so each
 * thread will get its own exception context.
 *
 * @return The thread-safe exception context.
 */
struct e4c_context *e4c_pthreads_context_supplier(void);

#endif
