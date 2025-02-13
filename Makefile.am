#
# exceptions4c-pthreads
#
# Copyright (c) 2025 Guillermo Calvo
# Licensed under the Apache License, Version 2.0
#

AUTOMAKE_OPTIONS = foreign subdir-objects

AM_CFLAGS = -Wall -Werror --pedantic -Wno-missing-braces -Wno-dangling-else -coverage -O0 -I$(EXCEPTIONS4C_PTHREADS_PATH) -Ideps/exceptions4c


# Library

EXCEPTIONS4C_PTHREADS_PATH      = src
EXCEPTIONS4C_PTHREADS_LIBRARY   = lib/libexceptions4c-pthreads.a


# Install

lib_LIBRARIES = $(EXCEPTIONS4C_PTHREADS_LIBRARY)

include_HEADERS = src/exceptions4c-pthreads.h


# Documentation

docsdir = $(datadir)/docs/exceptions4c-pthreads
docs_DATA = docs/*


# Cleanup

CLEANFILES =                                \
    *.log                                   \
    *.gcda                                  \
    *.gcno                                  \
    *.gcov                                  \
    *.stackdump                             \
    src/*.gcda                              \
    src/*.gcno                              \
    src/*.gcov                              \
    tests/*.gcda                            \
    tests/*.gcno                            \
    tests/*.gcov


# Check

check_PROGRAMS =                            \
    bin/check/dangling-block                \
    bin/check/integration-test              \
    bin/check/examples/pthreads

TESTS =                                     \
    bin/check/dangling-block                \
    bin/check/integration-test              \
    bin/check/examples/pthreads


tests: check


# Dependencies

dependencies: deps/exceptions4c/exceptions4c.h deps/exceptions4c/exceptions4c.c

deps/exceptions4c/exceptions4c.h:
	mkdir -p deps/exceptions4c
	wget --verbose --output-document deps/exceptions4c/exceptions4c.h https://github.com/guillermocalvo/exceptions4c/raw/refs/tags/4.0.0/src/exceptions4c.h

deps/exceptions4c/exceptions4c.c:
	mkdir -p deps/exceptions4c
	wget --verbose --output-document deps/exceptions4c/exceptions4c.c https://github.com/guillermocalvo/exceptions4c/raw/refs/tags/4.0.0/src/exceptions4c.c


# Library

lib_libexceptions4c_pthreads_a_CFLAGS       = -Wall -Werror --pedantic -Wno-missing-braces -I$(EXCEPTIONS4C_PTHREADS_PATH) -Ideps/exceptions4c
lib_libexceptions4c_pthreads_a_SOURCES      = src/exceptions4c-pthreads.c


# Tests

bin_check_dangling_block_SOURCES            = src/exceptions4c-pthreads.c deps/exceptions4c/exceptions4c.c tests/dangling-block.c
bin_check_integration_test_SOURCES          = src/exceptions4c-pthreads.c deps/exceptions4c/exceptions4c.c tests/integration-test.c


# Examples

bin_check_examples_pthreads_SOURCES         = src/exceptions4c-pthreads.c deps/exceptions4c/exceptions4c.c examples/pthreads.c


# Coverage

coverage: exceptions4c-pthreads.c.gcov

coverage-report: docs/html/coverage/index.html

docs/html/coverage/index.html: coverage.info
	genhtml coverage.info --output-directory docs/html/coverage

coverage.info: exceptions4c-pthreads.c.gcov
	lcov --capture --directory . --output-file coverage.info

exceptions4c-pthreads.c.gcov: src/exceptions4c-pthreads.gcda
	gcov --verbose src/exceptions4c-pthreads.c

src/exceptions4c-pthreads.gcda: check
