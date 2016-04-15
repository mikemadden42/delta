// Build with cmake, make, ninja:
// rm -rf release/; mkdir release; cd release/; cmake -GNinja ..; ninja
// rm -rf release/; mkdir release; cd release/; cmake ..; make

// Build without cmake:
// g++ -Wall -O2 -mtune=native -o delta delta.cc -lboost_date_time
// clang++ -Wall -O2 -mtune=native -o delta delta.cc -lboost_date_time

#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

int main() {
  using namespace boost::gregorian;
  std::string s = "2016-03-30";
  try {
    date start(from_simple_string(s));
    date today = day_clock::local_day();
    days diff = today - start;
    std::cout << "now: " << today << std::endl;
    std::cout << "then: " << start << std::endl;
    std::cout << "diff: " << diff.days() << " days" << std::endl;
  }
  catch (...) {
    std::cout << "bad date: " << s << std::endl;
  }
  return 0;
}
