# TODO

## Done

- [x] Replace Boost.DateTime with C++20 `<chrono>`; the project now has no dependencies beyond the standard library.
- [x] Accept dates from the command line (`delta <date> [date]`, comparing with today when one date is given).
- [x] Handle bad input: invalid dates or argument counts print usage and exit non-zero.
- [x] Remove the date → string → date round trip for today's date.
- [x] Add missing includes, avoid narrowing the day count, and show direction ("N days ago" / "in N days").
- [x] CMake: use `target_compile_options` instead of overwriting `CMAKE_CXX_FLAGS`; drop the Boost setup.
- [x] Makefile: use `CXX`/`CXXFLAGS`, match the CMake warnings, `rm -f` in `clean`, mark targets `.PHONY`.
- [x] Ignore the in-tree `delta` binary.
- [x] Add a usage example to the README.
- [x] Add tests for `parseDate` and `diffDays` (`make test` or `ctest`).

## Remaining

- [ ] Add CI (build and run tests with GCC and Clang).
- [ ] Windows support: `localtime_r` is POSIX; MSVC needs `localtime_s`.
