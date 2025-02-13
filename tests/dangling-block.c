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

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <exceptions4c-pthreads.h>

static void *foobar(void *arg);

/**
 * Leaks exception block intentionally by exiting TRY block improperly.
 */
int main(void) {
    int error;
    pthread_t thread;

    e4c_set_context_supplier(e4c_pthreads_context_supplier);

    error = pthread_create(&thread, NULL, foobar, NULL);
    if (error) {
        errno = error;
        perror("pthread_create");
        return EXIT_FAILURE;
    }

    error = pthread_join(thread, NULL);
    if (error) {
        errno = error;
        perror("pthread_join");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static void *foobar(void *arg) { /* NOSONAR */
    TRY {
        goto oops;
    }
oops:
    return NULL;
}
