# delta

[![CI](https://github.com/mikemadden42/delta/actions/workflows/ci.yml/badge.svg)](https://github.com/mikemadden42/delta/actions/workflows/ci.yml)

Find the difference between various dates

## Build

Requires a C++20 compiler (GCC 11+, a recent Clang, or MSVC 2019 16.10+). No other dependencies.
Builds on Linux, macOS, and Windows.

```sh
make
# or
cmake -S . -B build && cmake --build build
```

On Windows, use CMake (the Makefile assumes a Unix-like environment).

Run the tests with `make test`, or `ctest --test-dir build` after a CMake build
(add `-C Release` or `-C Debug` with multi-config generators such as Visual Studio).

## Usage

```sh
delta <date> [date]
```

Dates are in `YYYY-MM-DD` format.

```sh
$ delta 2020-07-06              # compared with today
2310 days ago
$ delta 2024-02-28 2024-03-01   # days from the first date to the second
2 days
$ delta 2024-03-01 2024-02-28
-2 days
```
