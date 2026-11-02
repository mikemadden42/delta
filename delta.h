#ifndef DELTA_H
#define DELTA_H

#include <charconv>
#include <chrono>
#include <ctime>
#include <optional>
#include <string_view>

// Parses an ISO 8601 date (YYYY-MM-DD), rejecting malformed or impossible dates.
inline std::optional<std::chrono::year_month_day> parseDate(std::string_view s) {
    using namespace std::chrono;
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

inline std::chrono::year_month_day today() {
    using namespace std::chrono;
    std::time_t t = std::time(nullptr);
    std::tm tm{};
    localtime_r(&t, &tm);
    return year{tm.tm_year + 1900} / (tm.tm_mon + 1) / tm.tm_mday;
}

// Returns the number of days from `from` to `to` (negative if `to` is earlier).
inline long diffDays(std::chrono::year_month_day from, std::chrono::year_month_day to) {
    using namespace std::chrono;
    return (sys_days{to} - sys_days{from}).count();
}

#endif
