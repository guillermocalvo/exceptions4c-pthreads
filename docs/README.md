
<div style="justify-items: center">
<img style="display: block" src="exceptions4c-pthreads.svg">
</div>

# Introduction

This library allows you to safely and concurrently use [**exceptions4c**][EXCEPTIONS4C] on multithreaded programs that
are based on [**POSIX threads**][PTHREADS].


# Getting Started

## Adding This Extension to Your Project

This library consists of two files:

- `exceptions4c-pthreads.h`
- `exceptions4c-pthreads.c`

To use it in your project, include the header file in your source code files.

```c
#include <exceptions4c-pthreads.h>
```

And then link your program against the library code.

> [!IMPORTANT]
> Remember to also link your program against [**exceptions4c**][EXCEPTIONS4C] and [**pthreads**][PTHREADS] libraries.


# Usage

All you have to do is call `e4c_set_context_supplier` with the
[exception context supplier](#e4c_pthreads_context_supplier) provided by this library so each thread will get its own
exception context.

@snippet pthreads.c setup

In the event of an uncaught exception, instead of terminating the program, only the current thread will be canceled.

> [!NOTE]
> [Read the docs][EXCEPTIONS4C_DOCS] for more information about [**exceptions4c**][EXCEPTIONS4C] usage.


# Additional Info

## Compatibility

This library should compile in any modern C compiler.

## Releases

This library adheres to [Semantic Versioning][SEMVER]. All notable changes for each version are documented in a
[change log][CHANGELOG].

Head over to GitHub for the [latest release][LATEST_RELEASE].

[![Latest Release][BADGE_LATEST_RELEASE]][LATEST_RELEASE]

## Source Code

The source code is [available on GitHub][SOURCE_CODE].

[![Fork me on GitHub][BADGE_GITHUB]][SOURCE_CODE]


[BADGE_GITHUB]:                 https://img.shields.io/badge/Fork_me_on_GitHub-black?logo=github
[BADGE_LATEST_RELEASE]:         https://img.shields.io/github/v/release/guillermocalvo/exceptions4c-pthreads
[CHANGELOG]:                    https://github.com/guillermocalvo/exceptions4c-pthreads/blob/main/CHANGELOG.md
[EXCEPTIONS4C]:                 https://github.com/guillermocalvo/exceptions4c/
[EXCEPTIONS4C_DOCS]:            https://exceptions4c.guillermo.dev/
[LATEST_RELEASE]:               https://github.com/guillermocalvo/exceptions4c-pthreads/releases/latest
[PTHREADS]:                     https://man7.org/linux/man-pages/man7/pthreads.7.html
[RESULT_LIBRARY]:               https://result.guillermo.dev/
[SEMVER]:                       https://semver.org/
[SOURCE_CODE]:                  https://github.com/guillermocalvo/exceptions4c-pthreads/
