#pragma once

#include <array>
#include <string>
#include <string_view>

namespace euler_spelling {

const std::array<std::string_view, 20> ones = {
    "one",     "two",     "three",     "four",     "five",     "six",      "seven",
    "eight",   "nine",    "ten",       "eleven",   "twelve",   "thirteen", "fourteen",
    "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", "twenty"};

const std::array<std::string_view, 10> tens_names = {
    "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

std::string to_number(int n) {
  if (n == 1000) {
    return "one thousand";
  }
  if (n <= 20) {
    return std::string{ones[n - 1]};
  }
  if (n < 100) {
    int t = n / 10;
    int r = n % 10;
    std::string result{tens_names[t]};
    if (r > 0) {
      result += '-';
      result += ones[r - 1];
    }
    return result;
  }
  std::string result{ones[n / 100 - 1]};
  result += " hundred";
  if (n % 100 > 0) {
    result += " and ";
    result += to_number(n % 100);
  }
  return result;
}

} // namespace euler_spelling
