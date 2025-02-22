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
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <exceptions4c-pthreads.h>

const struct e4c_exception_type MY_EXCEPTION = {NULL, "My exception."};

static void foobar(const char *thread_name);

static void *success(void *arg);

static void *failure(void *arg);

#define THREADS 100

/**
 * Integration test.
 */
int main(void) {
    pthread_t thread[THREADS];
    int result[THREADS];
    bool failed = false;

    e4c_set_context_supplier(e4c_pthreads_context_supplier);

    int index;
    for (index = 0; index < THREADS; index++) {
        /* assume error */
        result[index] = 1;
        errno = pthread_create(&thread[index], NULL, index % 2 ? &success : &failure, &result[index]);
        perror("pthread_join");
    }

    for (index = 0; index < THREADS; index++) {
        errno = pthread_join(thread[index], NULL);
        perror("pthread_join");
        if (result[index]) {
            failed = true;
        }
    }

    return failed;
}

static void foobar(const char *thread_name) {
    THROW(MY_EXCEPTION, "Exception thrown by: %s", thread_name);
}


static void *success(void *arg) {
    int *result = arg;
    const pthread_t self = pthread_self();

    printf("Starting thread %.4lx\n", self);
    fflush(stdout);

    TRY {
        foobar("SUCCESS");
    } CATCH(MY_EXCEPTION) {
        const struct e4c_exception *thrown = e4c_get_exception();

        printf("Thread %.4lx: Caught %s: %s\n", self, thrown->name, thrown->message);
        fflush(stdout);

        /* if the exception is caught and the message matches, then there was no error */
        *result = strcmp(thrown->message, "Exception thrown by: SUCCESS");
    }

    return NULL;
}

static void *failure(void *arg) {
    int *result = arg;
    const pthread_t self = pthread_self();

    printf("Starting thread %.4lx\n", self);
    fflush(stdout);

    /* assume no error */
    *result = 0;

    TRY {
        foobar("FAILURE");
    } FINALLY {
        const struct e4c_exception *thrown = e4c_get_exception();

        /* if the exception is caught, there was an error */
        *result = !e4c_is_uncaught();

        printf("Thread %.4lx: Uncaught %s: %s\n", self, thrown->name, thrown->message);
        fflush(stdout);
    }

    /* if this thread is still running, there was an error */
    *result = 1;

    return NULL;
}
