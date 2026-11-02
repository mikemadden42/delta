#include <cstdlib>
#include <iostream>

#include "delta.h"

using namespace std::chrono;

// Unlike assert, CHECK still runs under NDEBUG and reports every failure.
static int failures = 0;

#define CHECK(expr)                                                     \
    do {                                                                \
        if (!(expr)) {                                                  \
            std::cerr << __FILE__ << ':' << __LINE__ << ": FAILED: "    \
                      << #expr << '\n';                                 \
            ++failures;                                                 \
        }                                                               \
    } while (0)

static long diff(const char* from, const char* to) {
    return diffDays(*parseDate(from), *parseDate(to));
}

static void testParseValid() {
    CHECK(parseDate("2020-07-06") == year{2020} / July / 6);
    CHECK(parseDate("0001-01-01") == year{1} / January / 1);
    CHECK(parseDate("9999-12-31") == year{9999} / December / 31);
    CHECK(parseDate("2024-02-29") == year{2024} / February / 29);  // leap year
    CHECK(parseDate("2000-02-29") == year{2000} / February / 29);  // divisible by 400
}

static void testParseInvalid() {
    // Impossible dates.
    CHECK(!parseDate("2023-02-29"));  // not a leap year
    CHECK(!parseDate("1900-02-29"));  // divisible by 100 but not 400
    CHECK(!parseDate("2020-04-31"));
    CHECK(!parseDate("2020-13-01"));
    CHECK(!parseDate("2020-00-01"));
    CHECK(!parseDate("2020-01-00"));
    CHECK(!parseDate("2020-01-32"));

    // Malformed input.
    CHECK(!parseDate(""));
    CHECK(!parseDate("2020-7-6"));
    CHECK(!parseDate("2020-07-6"));
    CHECK(!parseDate("20200706"));
    CHECK(!parseDate("2020/07/06"));
    CHECK(!parseDate("2020-07-06 "));
    CHECK(!parseDate(" 2020-07-06"));
    CHECK(!parseDate("2020-07-06x"));
    CHECK(!parseDate("abcd-ef-gh"));
    CHECK(!parseDate("+020-07-06"));
    CHECK(!parseDate("2020-+7-06"));
    CHECK(!parseDate("2020--7-06"));
    CHECK(!parseDate("2020-07--6"));
}

static void testDiff() {
    CHECK(diff("2020-07-06", "2020-07-06") == 0);
    CHECK(diff("2020-07-06", "2020-07-07") == 1);
    CHECK(diff("2020-07-07", "2020-07-06") == -1);

    // Month and year boundaries.
    CHECK(diff("2020-01-31", "2020-02-01") == 1);
    CHECK(diff("2019-12-31", "2020-01-01") == 1);

    // Leap years.
    CHECK(diff("2024-02-28", "2024-03-01") == 2);
    CHECK(diff("2023-02-28", "2023-03-01") == 1);
    CHECK(diff("2000-02-28", "2000-03-01") == 2);
    CHECK(diff("1900-02-28", "1900-03-01") == 1);
    CHECK(diff("2024-01-01", "2025-01-01") == 366);
    CHECK(diff("2023-01-01", "2024-01-01") == 365);

    // Long spans (checked against Python's datetime).
    CHECK(diff("1970-01-01", "2026-11-02") == 20759);
    CHECK(diff("2026-11-02", "1970-01-01") == -20759);
    CHECK(diff("0001-01-01", "9999-12-31") == 3652058);
}

int main() {
    testParseValid();
    testParseInvalid();
    testDiff();
    if (failures) {
        std::cerr << failures << " check(s) failed\n";
        return EXIT_FAILURE;
    }
    std::cout << "all tests passed\n";
    return EXIT_SUCCESS;
}
