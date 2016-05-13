#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

using namespace boost::gregorian;

int diffDays(std::string s1, std::string s2) {
  date start(from_simple_string(s1));
  date end(from_simple_string(s2));
  days diff = start - end;
  return std::abs(diff.days());
}

int main() {
  std::string s1 = "2016-03-30";
  std::string s2 = "2016-05-13";
  std::cout << "diff: " << diffDays(s1, s2) << " days" << std::endl;
  return 0;
}
