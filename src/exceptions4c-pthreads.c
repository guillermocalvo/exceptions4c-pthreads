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
 * Implementation of the thread-safe extension for exceptions4c.
 *
 * <a href="https://exceptions4c-pthreads.guillermo.dev/">
 * <img src="exceptions4c-pthreads.svg">
 * </a>
 *
 * @file        exceptions4c-pthreads.c
 * @version     0.1.0
 * @author      [Guillermo Calvo]
 * @copyright   Licensed under [Apache 2.0]
 * @see         For more information, visit the [project on GitHub]
 *
 * [Guillermo Calvo]: https://guillermo.dev
 * [Apache 2.0]: http://www.apache.org/licenses/LICENSE-2.0
 * [project on GitHub]: https://github.com/guillermocalvo/exceptions4c-pthreads
 */

#include <stdio.h> /* fflush, fprintf, stderr */
#include <errno.h> /* errno */
#include <pthread.h>
#include <exceptions4c-pthreads.h>

/**
 * Invokes a function and terminates the program on error.
 *
 * @param message The message to print to standard error output.
 * @param function The function to call.
 * @param ... The arguments to pass to the function.
 */
#define ASSERT_PTHREAD(message, function, ...)                              \
  do {                                                                      \
    const int error_code = function(__VA_ARGS__);                           \
    if (error_code != 0) {                                                  \
        print_error(message);                                               \
        errno = error_code;                                                 \
        perror(#function);                                                  \
        abort();                                                            \
    }                                                                       \
  } while (false)

/**
 * Causes abnormal program termination depending on assertion.
 *
 * @param assertion The condition that must be true to avoid termination.
 * @param cause The cause of the problem.
 * @param message The message to print to standard error output.
 */
#define ASSERT_THAT(cause, message, assertion)                              \
  do {                                                                      \
    if (!(assertion)) {                                                     \
      print_error(message);                                                 \
      if (errno != 0) {                                                     \
        perror(cause);                                                      \
      }                                                                     \
      abort();                                                              \
    }                                                                       \
  } while (false)

/* Key for the thread-specific exception context */
static pthread_key_t context_key;

/* Once-only initialization of the key */
static pthread_once_t context_key_once = PTHREAD_ONCE_INIT;

/* Once-only control variable to register the cleanup function */
static pthread_once_t cleanup_once = PTHREAD_ONCE_INIT;

/* Allocates and initializes the thread-specific context */
static struct e4c_context *create_context(void);

/* Allocates the context key */
static void create_context_key(void);

/* Deallocates the context key */
static void delete_context_key(void);

/* Registers function delete_context_key to be called on normal program termination */
static void cleanup(void);

/* Deallocates the thread-specific context */
static void delete_context(void *context);

/* Terminates the current thread */
static void termination_handler(void);

/* Prints a library error message to the standard error stream */
static void print_error(const char *error_message);

/**
 * Prints a library error message to the standard error stream.
 *
 * @param error_message The message to print to standard error output.
 */
static void print_error(const char *error_message) {
    (void) fprintf(stderr, "\n[exceptions4c-pthreads] Thread %.4lx: %s\n",
                   pthread_self(), error_message);
    (void) fflush(stderr);
}

/**
 * Allocates the context key.
 */
static void create_context_key(void) {
    ASSERT_PTHREAD("Could not create context key.", pthread_key_create, &context_key, delete_context);
}

/**
 * Deallocates the context key.
 */
static void delete_context_key(void) {
    ASSERT_PTHREAD("Could not delete context key.", pthread_key_delete, context_key);
}

/**
 * Registers function delete_context_key to be called on normal program termination.
 */
static void cleanup(void) {
    ASSERT_PTHREAD("Could not register cleanup function.", atexit, delete_context_key);
}

/**
 * Terminates the current thread.
 *
 * This termination handler cancels the current thread, rather than
 * terminating the entire program.
 */
static void termination_handler(void) {
    print_error("Terminating due to uncaught exceptions.");
    pthread_exit(PTHREAD_CANCELED);
}

/**
 * Allocates and initializes the thread-specific context.
 */
static struct e4c_context *create_context(void) {
    ASSERT_PTHREAD("Could not initialize context key.", pthread_once, &context_key_once, create_context_key);
    ASSERT_PTHREAD("Could not initialize cleanup function.", pthread_once, &cleanup_once, cleanup);
    struct e4c_context *context = calloc(1, sizeof(*context));
    ASSERT_THAT("calloc", "Could not allocate exception context.", context != NULL);
    context->termination_handler = &termination_handler;
    ASSERT_PTHREAD("Could not save thread-specific context.", pthread_setspecific, context_key, context);
    return context;
}

/**
 * Deallocates the thread-specific context.
 *
 * @param context the context to deallocate.
 */
static void delete_context(void *context) {
    const void *block = ((struct e4c_context *) context)->_innermost_block;
    free(context);
    if (block != NULL) {
        print_error("Dangling exception block detected.\n"
            "    Some TRY block may have been exited improperly (via goto, break, continue, or return).");
    }
}

struct e4c_context *e4c_pthreads_context_supplier(void) {
    struct e4c_context *context = pthread_getspecific(context_key);
    return context ? context : create_context();
}
