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
