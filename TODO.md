# TODO

## Code (`delta.cc`)

- [ ] **Accept dates from the command line.** The start date `2020-07-06` is hard-coded, but the README promises "various dates". Read dates from `argv` (e.g. `delta 2020-07-06 [2021-01-01]`, using today when the second date is left out).
- [ ] **Handle bad input.** `from_simple_string` throws on invalid dates and nothing catches it. Add a `try`/`catch`, print a usage message, and return a non-zero exit code.
- [ ] **Remove the date → string → date round trip.** `day_clock::local_day()` is converted to a string and parsed back. Make `diffDays` take `date` values and parse strings only for user input.
- [ ] **Small fixes:**
  - [ ] Add `#include <string>` and `#include <cstdlib>`; don't rely on Boost including them indirectly.
  - [ ] Take strings as `const std::string&` instead of by value.
  - [ ] Stop narrowing `diff.days()` (a `long`) to `int`.
  - [ ] Consider showing direction ("N days ago" / "in N days") instead of hiding it with `std::abs`.

## CMake (`CMakeLists.txt`)

- [ ] **Fail when Boost is missing.** The `if(Boost_FOUND)` guard means configure succeeds but no target is built. Use `find_package(Boost REQUIRED ...)`.
- [ ] **Don't overwrite user flags.** `set(CMAKE_CXX_FLAGS ...)` discards any flags the user passes. Use `target_compile_options(delta PRIVATE -Wall -Wextra -pedantic)`.
- [ ] **Modernize the Boost setup.** Replace `include_directories`/`link_directories`/`${Boost_LIBRARIES}` with `target_link_libraries(delta PRIVATE Boost::headers)` (Boost.DateTime is header-only since ~1.73). Use `find_package(Boost CONFIG REQUIRED)` to avoid the FindBoost deprecation warning (CMP0167) on CMake ≥ 3.30. Remove the comment linking to the CMake 3.0 docs.

## Makefile

- [ ] Rename `CC`/`CFLAGS` to `CXX`/`CXXFLAGS` (the C++ conventions, so users can override them in the usual way).
- [ ] Match the CMake warnings (`-Wextra -pedantic`) and drop `-lboost_date_time`, which isn't needed for a header-only library and can fail where the stub library isn't shipped.
- [ ] Support Homebrew on Apple silicon (`/opt/homebrew` isn't on the default compiler search path), e.g. via `-I$(shell brew --prefix)/include`.
- [ ] Make `clean` use `rm -f` and mark `all`/`clean` as `.PHONY`.

## Repo

- [ ] Add the in-tree `delta` binary to `.gitignore`.
- [ ] Add a small test of `diffDays` against known dates (including leap years).
- [ ] Add CI.
- [ ] Add a usage example to the README.

## Priority

1. Command-line dates and error handling (without these the tool only answers one question).
2. CMake fixes, so the build fails loudly and uses modern Boost targets.
3. Everything else is quick cleanup.
