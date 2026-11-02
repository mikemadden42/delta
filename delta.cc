#include <charconv>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <optional>
#include <string_view>

using namespace std::chrono;

// Parses an ISO 8601 date (YYYY-MM-DD), rejecting malformed or impossible dates.
std::optional<year_month_day> parseDate(std::string_view s) {
    if (s.size() != 10 || s[4] != '-' || s[7] != '-') {
        return std::nullopt;
    }
    auto field = [&](size_t pos, size_t len, auto& out) {
        const char* first = s.data() + pos;
        const char* last = first + len;
        auto [ptr, ec] = std::from_chars(first, last, out);
        return ec == std::errc{} && ptr == last;
    };
    int y;
    unsigned m, d;
    if (!field(0, 4, y) || !field(5, 2, m) || !field(8, 2, d)) {
        return std::nullopt;
    }
    year_month_day ymd{year{y}, month{m}, day{d}};
    if (!ymd.ok()) {
        return std::nullopt;
    }
    return ymd;
}

year_month_day today() {
    std::time_t t = std::time(nullptr);
    std::tm tm{};
    localtime_r(&t, &tm);
    return year{tm.tm_year + 1900} / (tm.tm_mon + 1) / tm.tm_mday;
}

// Returns the number of days from `from` to `to` (negative if `to` is earlier).
long diffDays(year_month_day from, year_month_day to) {
    return (sys_days{to} - sys_days{from}).count();
}

int usage(const char* prog) {
    std::cerr << "usage: " << prog << " <date> [date]\n"
              << "  Prints the number of days between two dates (YYYY-MM-DD).\n"
              << "  If only one date is given, it is compared with today.\n";
    return EXIT_FAILURE;
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        return usage(argv[0]);
    }

    auto from = parseDate(argv[1]);
    if (!from) {
        std::cerr << argv[0] << ": invalid date: " << argv[1] << '\n';
        return usage(argv[0]);
    }

    if (argc == 2) {
        long n = diffDays(*from, today());
        if (n > 0) {
            std::cout << n << (n == 1 ? " day ago\n" : " days ago\n");
        } else if (n < 0) {
            std::cout << "in " << -n << (n == -1 ? " day\n" : " days\n");
        } else {
            std::cout << "today\n";
        }
        return EXIT_SUCCESS;
    }

    auto to = parseDate(argv[2]);
    if (!to) {
        std::cerr << argv[0] << ": invalid date: " << argv[2] << '\n';
        return usage(argv[0]);
    }
    long n = diffDays(*from, *to);
    std::cout << n << (n == 1 || n == -1 ? " day\n" : " days\n");
    return EXIT_SUCCESS;
}
