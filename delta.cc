#include <cstdlib>
#include <iostream>

#include "delta.h"

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
