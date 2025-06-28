// Compile with:
// g++-14 -std=c++23 -march=native -O3 -Wall first.cc -o first -ltbb -lgmpxx -lgmp

#include <gmpxx.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <execution>
#include <generator>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

#include "euler.hh"
#include "first_input.hh"

class Solution {
 public:
  virtual std::string solve() = 0;
};

class P001 : public Solution {
 public:
  std::string solve() override {
    int ans = 0;
    for (int i = 0; i < 1000; i++) {
      if (i % 3 == 0 || i % 5 == 0) {
        ans += i;
      }
    }
    return std::to_string(ans);
  }
};

class P002 : public Solution {
 public:
  std::string solve() override {
    int ans = 0;
    for (int f : euler::fibonacci_generator()) {
      if (f >= 4'000'000) {
        break;
      }
      if (f % 2 == 0) {
        ans += f;
      }
    }
    return std::to_string(ans);
  }
};

class P003 : public Solution {
 public:
  std::string solve() override {
    return std::to_string(std::ranges::max(euler::factor_integer(600851475143LL)));
  }
};

class P004 : public Solution {
 public:
  std::string solve() override {
    int best = 0;
    for (int i = 100; i <= 999; i++) {
      for (int j = i; j <= 999; j++) {
        int product = i * j;
        if (euler::is_palindrome(product)) {
          best = std::max(best, product);
        }
      }
    }
    return std::to_string(best);
  }
};

class P005 : public Solution {
 public:
  std::string solve() override {
    auto range = std::views::iota(2, 21);
    int ans = std::accumulate(range.begin(), range.end(), 1, euler::lcm<int>);
    return std::to_string(ans);
  }
};

class P006 : public Solution {
 public:
  std::string solve() override {
    int squares = 0;
    int acc = 0;
    for (int i = 1; i <= 100; i++) {
      squares += i * i;
      acc += i;
    }
    return std::to_string(acc * acc - squares);
  }
};

class P007 : public Solution {
 public:
  P007(const std::vector<int>& primes) : primes(primes) {}

  std::string solve() override { return std::to_string(primes[10000]); }

 private:
  const std::vector<int>& primes;
};

class P008 : public Solution {
 public:
  std::string solve() override {
    long long best = 0LL;
    for (auto window : euler::window_generator<int, 13>(euler::digit_generator(p008_input))) {
      long long product =
          std::accumulate(window.begin(), window.end(), 1LL, std::multiplies<long long>());
      best = std::max(best, product);
    }
    return std::to_string(best);
  }
};

class P009 : public Solution {
 public:
  std::string solve() override {
    for (int a = 1; a < 1000; a++) {
      for (int b = a + 1; b < 1000 - a; b++) {
        int c = 1000 - a - b;
        if (a * a + b * b == c * c) {
          return std::to_string(a * b * c);
        }
      }
    }
    std::unreachable();
  }
};

class P010 : public Solution {
 public:
  P010(const std::vector<int>& primes) : primes(primes) {}
  std::string solve() override {
    auto valid_primes = primes | std::views::take_while([](int p) { return p < 2'000'000; });
    auto sum = std::ranges::fold_left(valid_primes, 0LL, std::plus<long long>());
    return std::to_string(sum);
  }

 private:
  const std::vector<int>& primes;
};

class P011 : public Solution {
 public:
  std::string solve() override {
    std::vector<int> numbers = euler::fill_vector(euler::parse_numbers<int>(p011_input));
    int best = 0;
    for (auto [dy, dx] : directions) {
      for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
          int product = 1;
          for (int i = 0; i < 4; i++) {
            int ny = y + dy * i;
            int nx = x + dx * i;
            product *= grid(numbers, ny, nx);
          }
          best = std::max(best, product);
        }
      }
    }
    return std::to_string(best);
  }

 private:
  int grid(std::vector<int>& numbers, int y, int x) {
    if (y < 0 || y >= 20 || x < 0 || x >= 20) {
      return 0;
    }
    return numbers[y * 20 + x];
  }

  std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
};

class P012 : public Solution {
 public:
  std::string solve() override {
    for (int t : euler::triangular_generator()) {
      if (euler::num_of_divisors(t) > 500) {
        return std::to_string(t);
      }
    }
    std::unreachable();
  }
};

class P013 : public Solution {
 public:
  std::string solve() override {
    auto numbers = euler::fill_vector<mpz_class>(euler::parse_numbers<mpz_class>(p013_input));
    mpz_class sum = std::accumulate(numbers.begin(), numbers.end(), mpz_class(0));
    std::ostringstream oss;
    oss << sum;
    return oss.str().substr(0, 10);
  }
};

class P014 : public Solution {
 public:
  std::string solve() override {
    int best_length = 0, best_index = 0;
    const int size = 1'000'000;
    std::vector<int> collatz_lengths(size, 0);
    for (int i = 1; i < size; i++) {
      if (collatz_lengths[i] > 0) {
        continue;
      }
      int length = 0;
      for (long long value : euler::collatz_generator(i)) {
        if (value < size) {
          if (collatz_lengths[value] > 0) {
            length += collatz_lengths[value];
            break;
          }
        }
        length++;
      }
      if (length > best_length) {
        best_length = length;
        best_index = i;
      }
      for (long long value : euler::collatz_generator(i)) {
        if (value < size) {
          if (collatz_lengths[value] > 0) {
            break;
          }
          collatz_lengths[value] = length;
        }
        length--;
      }
    }
    return std::to_string(best_index);
  }
};

class P015 : public Solution {
 public:
  std::string solve() override {
    long long paths = euler::binomial<long long>(40, 20);
    return std::to_string(paths);
  }
};

class P016 : public Solution {
 public:
  std::string solve() override {
    mpz_class power = mpz_class{1} << 1000;
    auto digits = euler::fill_vector(euler::digit_generator(power.get_str()));
    int sum = std::accumulate(digits.begin(), digits.end(), 0);
    return std::to_string(sum);
  }
};

class P017 : public Solution {
 public:
  std::string solve() override {
    int ans = 0;
    for (int i = 1; i <= 1000; i++) {
      ans += count_letters(to_number(i));
    }
    return std::to_string(ans);
  }

 private:
  int count_letters(std::string number) {
    return std::count_if(number.begin(), number.end(), [](char c) { return std::isalpha(c); });
  }
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

  const std::array<std::string_view, 20> ones = {
      "one",     "two",     "three",     "four",     "five",     "six",      "seven",
      "eight",   "nine",    "ten",       "eleven",   "twelve",   "thirteen", "fourteen",
      "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", "twenty"};

  const std::array<std::string_view, 10> tens_names = {
      "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
};

class P018 : public Solution {
 public:
  std::string solve() override {
    auto grid = parse_triangle(p018_input);
    std::vector<std::vector<int>> ans(grid.size(), std::vector<int>(grid.size(), 0));
    int n = grid.size();
    for (int i = 0; i < n; i++) {
      ans[n - 1][i] = grid[n - 1][i];
    }
    for (int j = n - 2; j >= 0; j--) {
      for (int i = 0; i <= j; i++) {
        ans[j][i] = grid[j][i] + std::max(ans[j + 1][i], ans[j + 1][i + 1]);
      }
    }
    return std::to_string(ans[0][0]);
  }

 private:
  std::vector<std::vector<int>> parse_triangle(const std::string& source) {
    std::vector<std::vector<int>> triangle;
    for (size_t line = 0, i = 0; auto value : euler::parse_numbers<int>(source)) {
      if (line >= triangle.size()) {
        triangle.emplace_back();
      }
      triangle[line].push_back(value);
      i++;
      if (i == line + 1) {
        line++;
        i = 0;
      }
    }
    return triangle;
  }
};

class P019 : public Solution {
 public:
  std::string solve() override {
    int count = 0;
    for (int y = 1901; y <= 2000; ++y) {
      for (unsigned m = 1; m <= 12; ++m) {
        auto ymd = std::chrono::year{y} / std::chrono::month{m} / std::chrono::day{1};
        auto sd = std::chrono::sys_days{ymd};
        if (std::chrono::weekday{sd} == std::chrono::Sunday) {
          count++;
        }
      }
    }
    return std::to_string(count);
  }
};

class P020 : public Solution {
 public:
  std::string solve() override {
    mpz_class factorial = 1;
    for (int i = 1; i <= 100; i++) {
      factorial *= i;
    }
    auto digits = euler::fill_vector(euler::digit_generator(factorial.get_str()));
    int sum = std::accumulate(digits.begin(), digits.end(), 0);
    return std::to_string(sum);
  }
};

class P021 : public Solution {
 public:
  P021(const std::vector<int>& divisor_sums) : divisor_sums(divisor_sums) {}
  std::string solve() override {
    int ans = 0;
    for (int i = 1; i < 10'000; i++) {
      int sum = divisor_sums[i] - i;
      if (sum > i && sum < 10'000 && divisor_sums[sum] - sum == i) {
        ans += i + sum;
      }
    }
    return std::to_string(ans);
  }

 private:
  const std::vector<int>& divisor_sums;
};

class P022 : public Solution {
 public:
  std::string solve() override {
    auto names = p022_input;
    std::sort(names.begin(), names.end());
    long long ans = 0;
    for (size_t i = 0; i < names.size(); i++) {
      ans += (i + 1) * name_score(names[i]);
    }
    return std::to_string(ans);
  }

 private:
  int name_score(const std::string& name) {
    return std::accumulate(name.begin(), name.end(), 0,
                           [](int acc, char c) { return acc + (std::toupper(c) - 'A' + 1); });
  }
};

class P023 : public Solution {
 public:
  P023(const std::vector<int>& divisor_sums) : divisor_sums(divisor_sums) {}
  std::string solve() override {
    const int limit = 28123;
    std::vector<int> abundants;
    for (int i = 1; i <= limit; i++) {
      if (divisor_sums[i] - i > i) {
        abundants.push_back(i);
      }
    }

    std::vector<bool> non_abundant_sum(2 * limit + 1, true);
    for (size_t i = 0; i < abundants.size(); i++) {
      for (size_t j = i; j < abundants.size(); j++) {
        if (abundants[i] + abundants[j] > limit) {
          break;
        }
        non_abundant_sum[abundants[i] + abundants[j]] = false;
      }
    }
    int ans = 0;
    for (size_t i = 0; i < non_abundant_sum.size(); i++) {
      if (non_abundant_sum[i]) {
        ans += i;
      }
    }
    return std::to_string(ans);
  }

 private:
  const std::vector<int>& divisor_sums;
};

class P024 : public Solution {
 public:
  std::string solve() override {
    std::string digits = "0123456789";
    std::sort(digits.begin(), digits.end());
    for (int i = 0; i < 1'000'000 - 1; i++) {
      std::next_permutation(digits.begin(), digits.end());
    }
    return digits;
  }
};

class P025 : public Solution {
 public:
  std::string solve() override {
    float phi = (1 + sqrt(5)) / 2;
    return std::to_string(static_cast<int>(ceil((999 + log10(sqrt(5))) / log10(phi))));
  }
};

class P026 : public Solution {
 public:
  std::string solve() override {
    std::vector<int> remainder(1000, -1);
    int best_period = 0, best_index = 0;
    for (int i = 2; i < 1000; i++) {
      int rem = period(i, remainder);
      if (rem > best_period) {
        best_period = rem;
        best_index = i;
      }
    }
    return std::to_string(best_index);
  }

 private:
  int period(int n, std::vector<int>& remainders) {
    int pos = 0, a = 1;
    fill(remainders.begin(), remainders.end(), -1);
    remainders[1] = 0;
    while (true) {
      pos++;
      if (a == 0) {
        return 0;
      }
      int rem = a * 10 % n;
      if (remainders[rem] >= 0) {
        return pos - remainders[rem];
      }
      remainders[rem] = pos;
      a = rem;
    }
  }
};

class P027 : public Solution {
 public:
  P027(const std::vector<int>& primes)
      : primes(primes | std::ranges::views::filter([](int p) { return p < 1000; }) |
               std::ranges::to<std::unordered_set<int>>()) {}
  std::string solve() override {
    int best_a = 0, best_b = 0, best_count = 0;
    for (int a = -999; a <= 999; a++) {
      for (int b : primes) {
        int n = 0;
        while (true) {
          int value = n * n + a * n + b;
          if (value < 0 || primes.find(value) == primes.end()) {
            break;
          }
          n++;
        }
        if (n > best_count) {
          best_count = n;
          best_a = a;
          best_b = b;
        }
      }
    }
    return std::to_string(best_a * best_b);
  }

 private:
  const std::unordered_set<int> primes;
};

class P028 : public Solution {
 public:
  std::string solve() override {
    int sum = 1, current = 1;
    ;
    for (int i = 2; i <= 1001; i += 2) {
      for (int j = 0; j < 4; j++) {
        current += i;
        sum += current;
      }
    }
    return std::to_string(sum);
  }
};

class P029 : public Solution {
 public:
  std::string solve() override {
    std::set<mpz_class> unique_terms;
    for (mpz_class a = 2; a <= 100; a++) {
      mpz_class value = a;
      for (long long b = 2; b <= 100; b++) {
        value *= a;
        unique_terms.insert(value);
      }
    }
    return std::to_string(unique_terms.size());
  }
};

class P030 : public Solution {
 public:
  std::string solve() override {
    int sum = 0;
    for (int i = 10; i < 1'000'000; i++) {
      int digit_sum = 0, value = i;
      while (value > 0) {
        digit_sum += euler::ipow(value % 10, 5);
        value /= 10;
      }
      if (digit_sum == i) {
        sum += i;
      }
    }
    return std::to_string(sum);
  }
};

class P031 : public Solution {
 public:
  std::string solve() override { return std::to_string(count(200, 0)); }

 private:
  int count(int n, size_t index) {
    if (n == 0) {
      return 1;
    }
    if (index >= coins.size()) {
      return 0;
    }
    int ans = 0;
    for (int i = 0; i <= n; i += coins[index]) {
      ans += count(n - i, index + 1);
    }
    return ans;
  }
  const std::vector<int> coins = {200, 100, 50, 20, 10, 5, 2, 1};
};

class P032 : public Solution {
 public:
  std::string solve() override {
    std::set<int> seen;
    do {
      for (int product = 1; product < 7; product++) {
        for (int equals = product + 1; equals < 8; equals++) {
          int result = value(equals, 9);
          if (value(0, product) * value(product, equals) == result) {
            seen.insert(result);
          }
        }
      }
    } while (std::next_permutation(digits.begin(), digits.end()));
    return std::to_string(std::accumulate(seen.begin(), seen.end(), 0));
  }

 private:
  int value(int start, int end) {
    int ans = 0;
    for (int i = start; i < end; i++) {
      ans = ans * 10 + digits[i];
    }
    return ans;
  }
  std::vector<int> digits = {1, 2, 3, 4, 5, 6, 7, 8, 9};
};

class P033 : public Solution {
 public:
  std::string solve() override {
    int num_prod = 1;
    int den_prod = 1;

    for (int num = 10; num < 100; ++num) {
      for (int den = num + 1; den < 100; ++den) {
        int a = num / 10;
        int b = num % 10;
        int c = den / 10;
        int d = den % 10;

        if (b == 0 && d == 0) continue;

        if (b == c && d != 0 && a * den == num * d) {
          num_prod *= a;
          den_prod *= d;
        } else if (a == d && c != 0 && b * den == num * c) {
          num_prod *= b;
          den_prod *= c;
        } else if (a == c && d != 0 && b * den == num * d) {
          num_prod *= b;
          den_prod *= d;
        } else if (b == d && c != 0 && a * den == num * c) {
          num_prod *= a;
          den_prod *= c;
        }

        int g = std::gcd(num_prod, den_prod);
        num_prod /= g;
        den_prod /= g;
      }
    }
    return std::to_string(den_prod);
  }
};

class P034 : public Solution {
 public:
  std::string solve() override {
    int ans = 0;
    for (int i = 3; i <= 100000; i++) {
      int sum = 0, value = i;
      while (value > 0) {
        sum += euler::factorial(value % 10);
        value /= 10;
      }
      if (sum == i) {
        ans += i;
      }
    }
    return std::to_string(ans);
  }
};

class P035 : public Solution {
 public:
  P035(const std::vector<int>& primes, const std::unordered_set<int>& prime_set)
      : primes(primes), prime_set(prime_set) {}
  std::string solve() override {
    int ans = 0;
    for (int prime : primes) {
      if (prime >= 1'000'000) {
        break;
      }
      int d = euler::digits(prime);
      if (is_circular_prime(prime, d)) {
        ans++;
      }
    }
    return std::to_string(ans);
  }

 private:
  bool is_circular_prime(int n, int digits) {
    int value = n;
    for (int i = 0; i < digits; i++) {
      if (prime_set.find(value) == prime_set.end()) {
        return false;
      }
      value = (value % 10) * euler::powers10[digits - 1] + value / 10;
    }
    return true;
  }
  const std::vector<int>& primes;
  const std::unordered_set<int>& prime_set;
};

class P036 : public Solution {
 public:
  std::string solve() override {
    int ans = 0;
    for (int i = 1; i < 1'000'000; i++) {
      if (euler::is_palindrome(i) && euler::is_palindrome(euler::to_binary_string(i))) {
        ans += i;
      }
    }
    return std::to_string(ans);
  }

 private:
};

class P037 : public Solution {
 public:
  P037(const std::vector<int>& primes, const std::unordered_set<int>& prime_set)
      : primes(primes), prime_set(prime_set) {}
  std::string solve() override {
    int ans = 0;
    for (int prime :
         primes | std::ranges::views::take_while([](int p) { return p <= 1'000'000; })) {
      if (prime > 10 && is_truncatable_prime(prime)) {
        ans += prime;
      }
    }
    return std::to_string(ans);
  }

 private:
  bool is_truncatable_prime(int original) {
    int n = original, top = 0, power = 1;
    while (n) {
      if (prime_set.find(n) == prime_set.end()) {
        return false;
      }
      top = top + n % 10 * power;
      if (prime_set.find(top) == prime_set.end()) {
        return false;
      }
      n /= 10;
      power *= 10;
    }
    return true;
  }
  std::vector<int> primes;
  std::unordered_set<int> prime_set;
};

class P038 : public Solution {
 public:
  std::string solve() override {
    int ans = 0;
    for (int i = 2; i < 10; i++) {
      ans = std::max(ans, search(i));
    }
    return std::to_string(ans);
  }

 private:
  int search(int n) {
    std::vector<int> solutions;
    std::string goal = "123456789";
    for (int i = 1;; i++) {
      int d = euler::digits(i);
      if (d * n > 9) {
        if (!solutions.empty()) {
          return *std::max_element(solutions.begin(), solutions.end());
        }
        return 0;
      }
      std::string s;
      for (int j = 1; j <= n; j++) {
        s += std::to_string(i * j);
      }
      std::string check = s;
      std::sort(check.begin(), check.end());
      if (check == goal) {
        solutions.push_back(std::stoi(s));
      }
    }
  }
};

class P039 : public Solution {
 public:
  std::string solve() override {
    int ans = 0, best = 0;
    for (int i = 1; i <= 1000; i++) {
      int candidate = count(i);
      if (candidate > best) {
        best = candidate;
        ans = i;
      }
    }
    return std::to_string(ans);
  }

 private:
  int count(int n) {
    int ans = 0;
    for (int a = 1; a <= n / 3; a++) {
      for (int b = a + 1; b < n - a; b++) {
        if (a * a + b * b == (n - a - b) * (n - a - b)) {
          ans++;
        }
      }
    }
    return ans;
  }
};

class P040 : public Solution {
 public:
  std::string solve() override {
    std::string s;
    for (int i = 1; s.size() < 1'000'000; i++) {
      s += std::to_string(i);
    }
    int ans = 1;
    for (int i = 1; i <= 7; i++) {
      int digit = static_cast<int>(euler::ipow(10, i - 1));
      ans *= s[digit - 1] - '0';
    }
    return std::to_string(ans);
  }
};

class P041 : public Solution {
 public:
  std::string solve() override {
    long long best = 0;
    for (int n = 2; n < 10; n++) {
      for (long long value : euler::pandigital_generator<long long>(n, 1)) {
        if (euler::prime_test(value)) {
          best = std::max(best, value);
        }
      }
    }
    return std::to_string(best);
  }
};

class P042 : public Solution {
 public:
  std::string solve() override {
    int ans = 0;
    for (const auto& word : p042_input) {
      int score = std::accumulate(word.begin(), word.end(), 0,
                                  [](int acc, char c) { return acc + c - 'A' + 1; });
      if (euler::is_triangular(score)) {
        ans++;
      }
    }
    return std::to_string(ans);
  }
};

class P043 : public Solution {
 public:
  P043(const std::vector<int>& primes) : primes(primes) {}
  std::string solve() override {
    long long ans = 0;
    for (long long n : euler::pandigital_generator<long long>(10, 0)) {
      if (is_substring_divisible(n)) {
        ans += n;
      }
    }
    return std::to_string(ans);
  }

 private:
  bool is_substring_divisible(long long n) {
    for (int i = 6; i >= 0; i--) {
      if (n % 1000 % primes[i] != 0) {
        return false;
      }
      n /= 10;
    }
    return true;
  }
  std::vector<int> primes;
};

class P044 : public Solution {
 public:
  std::string solve() override {
    long long best = 1e12;
    for (int i = 1; i < 5000; i++) {
      long long pi = euler::pentagonal(i);
      for (int j = i + 1; j < 5000; j++) {
        long long pj = euler::pentagonal(j);
        if (euler::is_pentagonal(pj - pi) && euler::is_pentagonal(pi + pj)) {
          best = std::min(best, pj - pi);
        }
      }
    }
    return std::to_string(best);
  }
};

class P045 : public Solution {
 public:
  std::string solve() override {
    long long t = 285, p = 165, h = 143;
    t++;
    while (true) {
      long long tn = euler::triangular(t);
      long long pn = euler::pentagonal(p);
      long long hn = euler::hexagonal(h);
      if (tn == pn && pn == hn) {
        return std::to_string(tn);
      }
      if (tn <= pn && tn <= hn) {
        t++;
      } else if (pn <= tn && pn <= hn) {
        p++;
      } else {
        h++;
      }
    }
    std::unreachable();
  }
};

class P046 : public Solution {
 public:
  P046(const std::unordered_set<int>& prime_set) : prime_set(prime_set) {}
  std::string solve() override {
    for (int n = 9;; n += 2) {
      if (prime_set.contains(n)) {
        continue;
      }
      if (!is_twice_square(n)) {
        return std::to_string(n);
      }
    }
    std::unreachable();
  }

 private:
  bool is_twice_square(int n) {
    for (int i = 1; i * i * 2 < n; i++) {
      int candidate = n - 2 * i * i;
      if (candidate > 0 && prime_set.contains(candidate)) {
        return true;
      }
    }
    return false;
  }
  const std::unordered_set<int>& prime_set;
};

class P047 : public Solution {
 public:
  std::string solve() override {
    int consecutive = 0;
    for (int n = 1; n < 1000000; n++) {
      int len = std::ranges::distance(euler::group_factor_integer(n));
      if (len == 4) {
        consecutive++;
        if (consecutive == 4) {
          return std::to_string(n - 3);
        }
      } else {
        consecutive = 0;
      }
    }
    std::unreachable();
  }
};

class P048 : public Solution {
 public:
  std::string solve() override {
    mpz_class ans = 0;
    mpz_class digits = euler::ipow(mpz_class(10), mpz_class(10));
    for (mpz_class i = 1; i <= 1000; i++) {
      ans += euler::modpow(i, i, digits);
    }
    std::ostringstream oss;
    oss << ans % digits;
    return oss.str();
  }
};

class P049 : public Solution {
 public:
  P049(const std::vector<int>& primes, const std::unordered_set<int>& prime_set)
      : primes(primes), prime_set(prime_set) {}
  std::string solve() override {
    std::string ans;
    for (int i = 0; primes[i] < 10000; i++) {
      if (primes[i] <= 1487) {
        continue;
      }
      for (int j = i + 1; primes[j] < 10000; j++) {
        int k = primes[i] + 2 * (primes[j] - primes[i]);
        if (k < 10000 && prime_set.contains(k) && is_anagram(primes[i], primes[j], k)) {
          return std::to_string(primes[i]) + std::to_string(primes[j]) + std::to_string(k);
        }
      }
    }
    std::unreachable();
  }

 private:
  const std::vector<int>& primes;
  const std::unordered_set<int>& prime_set;
  bool is_anagram(int a, int b, int c) {
    return std::ranges::is_permutation(std::to_string(a), std::to_string(b)) &&
           std::ranges::is_permutation(std::to_string(a), std::to_string(c));
  }
};

class P050 : public Solution {
 public:
  P050(const std::vector<int>& primes, const std::unordered_set<int>& prime_set)
      : primes(primes), prime_set(prime_set) {}
  std::string solve() override {
    int best = 0, stride = 0;
    for (int i = 0; primes[i] < 1'000'000; i++) {
      int total = primes[i];
      for (int j = 1; primes[i + j] < 1'000'000; j++) {
        total += primes[i + j];
        if (total >= 1'000'000) {
          break;
        }
        if (j > stride && prime_set.contains(total)) {
          best = total;
          stride = j;
        }
      }
    }
    return std::to_string(best);
  }

 private:
  const std::vector<int>& primes;
  const std::unordered_set<int>& prime_set;
};

class P051 : public Solution {
 public:
  P051(const std::vector<int>& primes, const std::unordered_set<int>& prime_set)
      : primes(primes), prime_set(prime_set) {}
  std::string solve() override {
    for (size_t idx = 0; idx < primes.size(); ++idx) {
      int p = primes[idx];
      if (p < 10) {
        continue;
      }
      std::string s = std::to_string(p);
      int d = s.size();
      int limit = euler::powers10[d - 1];
      int max_mask = (1 << d) - 1;
      // iterate all non-empty, non-full masks
      for (int mask = 1; mask < max_mask; ++mask) {
        if (mask == max_mask) break;
        // build base by zeroing masked digits
        int base = 0;
        for (int i = 0; i < d; ++i) {
          char c = ((mask >> (d - 1 - i)) & 1) ? '0' : s[i];
          base = base * 10 + (c - '0');
        }
        int imask = compute_imask(mask, d);
        int candidate = search_candidate(base, imask, limit);
        if (candidate > 0) {
          return std::to_string(candidate);
        }
      }
    }
    std::unreachable();
  }

 private:
  const std::vector<int>& primes;
  const std::unordered_set<int>& prime_set;

  int compute_imask(int mask, int d) {
    int imask = 0;
    for (int i = 0; i < d; ++i) {
      int bit = (mask >> (d - 1 - i)) & 1;
      imask = imask * 10 + bit;
    }
    return imask;
  }

  int search_candidate(int base, int imask, int limit) {
    int count = 0;
    for (int digit = 0; digit < 10; ++digit) {
      int candidate = base + digit * imask;
      if (candidate >= limit && candidate < limit * 10 && prime_set.contains(candidate)) {
        ++count;
      }
      if (count >= 8) {
        for (int digit = 0; digit < 10; ++digit) {
          int candidate = base + digit * imask;
          if (prime_set.contains(candidate)) {
            return candidate;
          }
        }
      }
    }
    return -1;
  }
};

class P052 : public Solution {
 public:
  std::string solve() override {
    auto it = std::ranges::find_if(std::views::iota(1), [&](int n) { return works(n); });
    return std::to_string(*it);
  }

 private:
  bool works(int n) {
    std::string s = std::to_string(n);
    for (int i = 2; i <= 6; i++) {
      std::string s2 = std::to_string(n * i);
      if (!std::ranges::is_permutation(s, s2)) {
        return false;
      }
    }
    return true;
  }
};

class P053 : public Solution {
 public:
  std::string solve() override {
    int count = 0;
    for (int n = 1; n <= 100; n++) {
      for (int r = 0; r <= n; r++) {
        if (euler::binomial<mpz_class>(n, r) > 1'000'000) {
          count++;
        }
      }
    }
    return std::to_string(count);
  }
};

class P054 : public Solution {
 public:
  std::string solve() override {
    std::vector<std::pair<Hand, Hand>> hands;
    std::istringstream infile(p054_input);
    std::string line;
    while (std::getline(infile, line)) {
      std::istringstream iss(line);
      std::vector<std::string> s;
      std::string token;
      while (iss >> token) s.push_back(token);
      if (s.size() != 10) continue;
      hands.emplace_back(parse_hand({s[0], s[1], s[2], s[3], s[4]}),
                         parse_hand({s[5], s[6], s[7], s[8], s[9]}));
    }
    int p1wins = 0;
    for (const auto& [p1, p2] : hands) {
      if (winner(p1, p2) == 1) ++p1wins;
    }
    return std::to_string(p1wins);
  }

 private:
  using Card = std::pair<int, char>;
  using Hand = std::vector<Card>;
  using ScoreResult = std::pair<bool, std::vector<int>>;
  using ScoreFunc = std::function<ScoreResult(const Hand&)>;
  using ScorePair = std::pair<std::string, ScoreFunc>;
  using ScoreInfo = std::tuple<int, std::string, std::vector<int>>;

  const std::map<char, int> values = {{'2', 2},  {'3', 3},  {'4', 4}, {'5', 5},  {'6', 6},
                                      {'7', 7},  {'8', 8},  {'9', 9}, {'T', 10}, {'J', 11},
                                      {'Q', 12}, {'K', 13}, {'A', 14}};

  Hand parse_hand(const std::vector<std::string>& cards) {
    Hand hand;
    for (const auto& cs : cards) {
      char rank = cs[0];
      char suit = cs[1];
      hand.emplace_back(values.at(rank), suit);
    }
    std::sort(hand.begin(), hand.end());
    return hand;
  }

  std::vector<int> discarded(const Hand& hand, const std::vector<int>& skips) {
    std::vector<int> result = skips;
    for (auto it = hand.rbegin(); it != hand.rend(); ++it) {
      int rank = it->first;
      if (std::find(skips.begin(), skips.end(), rank) == skips.end()) {
        result.push_back(rank);
      }
    }
    return result;
  }

  ScoreResult high_card(const Hand& hand) { return {true, discarded(hand, {})}; }

  std::map<int, int> count_ranks(const Hand& hand) {
    std::map<int, int> c;
    for (const auto& [rank, suit] : hand) {
      c[rank]++;
    }
    return c;
  }

  std::map<char, int> count_suits(const Hand& hand) {
    std::map<char, int> c;
    for (const auto& [rank, suit] : hand) {
      c[suit]++;
    }
    return c;
  }

  template <typename T>
  int max_rank(const T& c) {
    return std::max_element(c.begin(), c.end(),
                            [](auto& a, auto& b) { return a.second < b.second; })
        ->second;
  }

  ScoreResult one_pair(const Hand& hand) {
    auto c = count_ranks(hand);
    if (max_rank(c) != 2) {
      return {false, {}};
    }
    std::vector<int> ranks;
    for (auto& [k, v] : c) {
      if (v == 2) {
        ranks.push_back(k);
      }
    }
    if (ranks.size() > 1) {
      return {false, {}};
    }
    return {true, discarded(hand, {ranks[0]})};
  }

  ScoreResult two_pairs(const Hand& hand) {
    auto c = count_ranks(hand);
    if (max_rank(c) != 2) return {false, {}};
    std::vector<int> ranks;
    for (auto& [k, v] : c)
      if (v == 2) ranks.push_back(k);
    if (ranks.size() != 2) return {false, {}};
    int r1 = std::max(ranks[0], ranks[1]);
    int r2 = std::min(ranks[0], ranks[1]);
    return {true, discarded(hand, {r1, r2})};
  }

  ScoreResult three_of_a_kind(const Hand& hand) {
    auto c = count_ranks(hand);
    if (max_rank(c) != 3) return {false, {}};
    if (std::any_of(c.begin(), c.end(), [](auto& p) { return p.second == 2; })) return {false, {}};
    std::vector<int> ranks;
    for (auto& [k, v] : c)
      if (v == 3) ranks.push_back(k);
    return {true, discarded(hand, ranks)};
  }

  ScoreResult full_house(const Hand& hand) {
    auto c = count_ranks(hand);
    bool has3 = std::any_of(c.begin(), c.end(), [](auto& p) { return p.second == 3; });
    bool has2 = std::any_of(c.begin(), c.end(), [](auto& p) { return p.second == 2; });
    if (!has3 || !has2) return {false, {}};
    int big = 0, small = 0;
    for (auto& [k, v] : c)
      if (v == 3) big = k;
    for (auto& [k, v] : c)
      if (v == 2) small = k;
    return {true, discarded(hand, {big, small})};
  }

  bool consecutive(const Hand& hand) {
    for (size_t i = 1; i < hand.size(); ++i)
      if (hand[i].first != hand[i - 1].first + 1) return false;
    return true;
  }

  ScoreResult straight(const Hand& hand) {
    if (!consecutive(hand)) return {false, {}};
    std::vector<int> r;
    for (auto it = hand.rbegin(); it != hand.rend(); ++it) r.push_back(it->first);
    return {true, r};
  }

  ScoreResult flush(const Hand& hand) {
    auto c = count_suits(hand);
    if (max_rank(c) != 5) return {false, {}};
    std::vector<int> r;
    for (auto it = hand.rbegin(); it != hand.rend(); ++it) r.push_back(it->first);
    return {true, r};
  }

  ScoreResult straight_flush(const Hand& hand) {
    auto s = straight(hand);
    if (!s.first) return {false, {}};
    auto f = flush(hand);
    if (!f.first) return {false, {}};
    return s;
  }

  ScoreResult royal_flush(const Hand& hand) {
    if (!consecutive(hand)) return {false, {}};
    auto c_suit = count_suits(hand);
    if (max_rank(c_suit) != 5) return {false, {}};
    if (hand[0].first != 10) return {false, {}};
    std::vector<int> r;
    for (auto it = hand.rbegin(); it != hand.rend(); ++it) r.push_back(it->first);
    return {true, r};
  }

  ScoreResult four_of_a_kind(const Hand& hand) {
    auto c = count_ranks(hand);
    if (max_rank(c) != 4) return {false, {}};
    std::vector<int> ranks;
    for (auto& [k, v] : c)
      if (v == 4) ranks.push_back(k);
    return {true, discarded(hand, ranks)};
  }

  const std::vector<ScorePair> scores = {
      {"royal_flush", [&](const Hand& hand) { return royal_flush(hand); }},
      {"straight_flush", [&](const Hand& hand) { return straight_flush(hand); }},
      {"four_of_a_kind", [&](const Hand& hand) { return four_of_a_kind(hand); }},
      {"full_house", [&](const Hand& hand) { return full_house(hand); }},
      {"flush", [&](const Hand& hand) { return flush(hand); }},
      {"straight", [&](const Hand& hand) { return straight(hand); }},
      {"three_of_a_kind", [&](const Hand& hand) { return three_of_a_kind(hand); }},
      {"two_pairs", [&](const Hand& hand) { return two_pairs(hand); }},
      {"one_pair", [&](const Hand& hand) { return one_pair(hand); }},
      {"high_card", [&](const Hand& hand) { return high_card(hand); }},
  };

  ScoreInfo best_score(const Hand& hand) {
    for (size_t i = 0; i < scores.size(); ++i) {
      const auto& [name, func] = scores[i];
      auto [res, val] = func(hand);
      if (res) {
        return {static_cast<int>(scores.size() - i), name, val};
      }
    }
    return {0, "none", {}};
  }

  int winner(const Hand& p1, const Hand& p2) {
    auto [s1, n1, v1] = best_score(p1);
    auto [s2, n2, v2] = best_score(p2);
    if (std::tie(s1, v1) > std::tie(s2, v2))
      return 1;
    else
      return 2;
  }
};

class P055 : public Solution {
 public:
  std::string solve() override {
    int count = 0;
    for (long long i = 1; i < 10'000; i++) {
      if (is_lychrel(i)) {
        count++;
      }
    }
    return std::to_string(count);
  }

 private:
  bool is_lychrel(long long n) {
    for (int i = 0; i < 50; i++) {
      n += euler::reverse_digits(n);
      if (euler::is_palindrome(n)) {
        return false;
      }
    }
    return true;
  }
};

class P056 : public Solution {
 public:
  std::string solve() override {
    int max_sum = 0;
    for (mpz_class a = 1; a < 100; a++) {
      for (mpz_class b = 1; b < 100; b++) {
        mpz_class power = euler::ipow(a, b);
        int sum = euler::digit_sum(power);
        max_sum = std::max(max_sum, sum);
      }
    }
    return std::to_string(max_sum);
  }
};

class P057 : public Solution {
 public:
  std::string solve() override {
    int ans = 0;
    mpz_class h0 = 0, k0 = 1, h1 = 1, k1 = 0;
    for (int a : std::views::take(sqrt_2_coefs(), 1000)) {
      mpz_class hn = a * h1 + h0;
      mpz_class kn = a * k1 + k0;
      if (euler::to_string(hn).size() > euler::to_string(kn).size()) {
        ans++;
      }
      h0 = h1;
      k0 = k1;
      h1 = hn;
      k1 = kn;
    }
    return std::to_string(ans);
  }

 private:
  std::generator<int> sqrt_2_coefs() {
    co_yield 1;
    while (true) {
      co_yield 2;
    }
  }
};

class P058 : public Solution {
 public:
  std::string solve() override {
    long long n = 0, p = 0;
    while (true) {
      ++n;
      p += prime_diagonal(n);
      if (p * 10 <= 1 + 4 * n) {
        return std::to_string(2 * n + 1);
      }
    }
    std::unreachable();
  }

 private:
  std::array<long long, 4> diag(long long n) {
    std::array<long long, 4> a;
    long long corner = (2 * n + 1) * (2 * n + 1);
    for (int i = 0; i < 4; i++) {
      a[i] = corner - 2 * i * n;
    }
    return a;
  }

  int prime_diagonal(long long n) {
    auto d = diag(n);
    int ans = 0;
    for (auto v : d) {
      if (euler::is_prime_mr(v)) {
        ans++;
      }
    }
    return ans;
  }
};

int main() {
  const std::vector<int> primes = euler::fill_vector(euler::sieve_generator(2'000'000));
  const std::unordered_set<int> prime_set(primes.begin(), primes.end());
  const std::vector<int> divisor_sums =
      euler::fill_vector(euler::sum_of_divisors_generator(28'123));
  std::vector<std::shared_ptr<Solution>> solutions = {
      std::make_shared<P001>(),
      std::make_shared<P002>(),
      std::make_shared<P003>(),
      std::make_shared<P004>(),
      std::make_shared<P005>(),
      std::make_shared<P006>(),
      std::make_shared<P007>(primes),
      std::make_shared<P008>(),
      std::make_shared<P009>(),
      std::make_shared<P010>(primes),
      std::make_shared<P011>(),
      std::make_shared<P012>(),
      std::make_shared<P013>(),
      std::make_shared<P014>(),
      std::make_shared<P015>(),
      std::make_shared<P016>(),
      std::make_shared<P017>(),
      std::make_shared<P018>(),
      std::make_shared<P019>(),
      std::make_shared<P020>(),
      std::make_shared<P021>(divisor_sums),
      std::make_shared<P022>(),
      std::make_shared<P023>(divisor_sums),
      std::make_shared<P024>(),
      std::make_shared<P025>(),
      std::make_shared<P026>(),
      std::make_shared<P027>(primes),
      std::make_shared<P028>(),
      std::make_shared<P029>(),
      std::make_shared<P030>(),
      std::make_shared<P031>(),
      std::make_shared<P032>(),
      std::make_shared<P033>(),
      std::make_shared<P034>(),
      std::make_shared<P035>(primes, prime_set),
      std::make_shared<P036>(),
      std::make_shared<P037>(primes, prime_set),
      std::make_shared<P038>(),
      std::make_shared<P039>(),
      std::make_shared<P040>(),
      std::make_shared<P041>(),
      std::make_shared<P042>(),
      std::make_shared<P043>(primes),
      std::make_shared<P044>(),
      std::make_shared<P045>(),
      std::make_shared<P046>(prime_set),
      std::make_shared<P047>(),
      std::make_shared<P048>(),
      std::make_shared<P049>(primes, prime_set),
      std::make_shared<P050>(primes, prime_set),
      std::make_shared<P051>(primes, prime_set),
      std::make_shared<P052>(),
      std::make_shared<P053>(),
      std::make_shared<P054>(),
      std::make_shared<P055>(),
      std::make_shared<P056>(),
      std::make_shared<P057>(),
      std::make_shared<P058>(),
  };

  std::vector<std::pair<std::string, long long>> results(solutions.size());
  std::transform(std::execution::par, solutions.begin(), solutions.end(), results.begin(),
                 [](const auto& solution) {
                   auto t0 = std::chrono::steady_clock::now();
                   std::string result = solution->solve();
                   auto t1 = std::chrono::steady_clock::now();
                   long long ms =
                       std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
                   return make_pair(result, ms);
                 });

  for (int i = 1; auto& r : results) {
    std::cout << i++ << "\t" << r.second << "ms\t" << r.first << "\n";
  }
  return 0;
}
