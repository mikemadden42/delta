# delta

[![CI](https://github.com/mikemadden42/delta/actions/workflows/ci.yml/badge.svg)](https://github.com/mikemadden42/delta/actions/workflows/ci.yml)

Find the difference between various dates

## Build

Requires a C++20 compiler (GCC 11+ or a recent Clang). No other dependencies.

```sh
make
# or
cmake -S . -B build && cmake --build build
```

Run the tests with `make test`, or `ctest --test-dir build` after a CMake build.

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
