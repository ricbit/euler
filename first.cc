// Compile with:
// g++-14 -std=c++23 -march=native -O3 -Wall first.cc -o first -ltbb -lgmpxx -lgmp

#include <gmpxx.h>

#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <complex>
#include <eigen3/Eigen/Dense>
#include <execution>
#include <generator>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "euler.hh"
#include "exactcover.hh"
#include "first_input.hh"
#include "poker.hh"
#include "spelling.hh"

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
    std::vector<int> numbers =
        euler::parse_numbers<int>(p011_input) | std::ranges::to<std::vector<int>>();
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
    auto stream = euler::triangular_generator() |
                  std::views::drop_while([](int t) { return euler::num_of_divisors(t) <= 500; });
    return std::to_string(*std::ranges::begin(stream));
  }
};

class P013 : public Solution {
 public:
  std::string solve() override {
    auto numbers =
        euler::parse_numbers<mpz_class>(p013_input) | std::ranges::to<std::vector<mpz_class>>();
    mpz_class sum = std::accumulate(numbers.begin(), numbers.end(), mpz_class(0));
    return sum.get_str().substr(0, 10);
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
    auto digits = euler::digit_generator(power.get_str()) | std::ranges::to<std::vector<int>>();
    int sum = std::accumulate(digits.begin(), digits.end(), 0);
    return std::to_string(sum);
  }
};

class P017 : public Solution {
 public:
  std::string solve() override {
    int ans = 0;
    for (int i = 1; i <= 1000; i++) {
      ans += count_letters(euler_spelling::to_number(i));
    }
    return std::to_string(ans);
  }

 private:
  int count_letters(std::string number) {
    return std::count_if(number.begin(), number.end(), [](char c) { return std::isalpha(c); });
  }
};

class P018 : public Solution {
 public:
  std::string solve() override {
    auto grid = euler::parse_triangle(p018_input);
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
    auto digits = euler::digit_generator(factorial.get_str()) | std::ranges::to<std::vector<int>>();
    int sum = std::accumulate(digits.begin(), digits.end(), 0);
    return std::to_string(sum);
  }
};

class P021 : public Solution {
 public:
  P021(const std::vector<int>& divisor_sums) : divisor_sums(divisor_sums) {}
  std::string solve() override {
    auto stream = std::views::iota(1, 10'000) | std::views::filter([&](int i) {
                    int sum = divisor_sums[i] - i;
                    return sum > i && sum < 10'000 && divisor_sums[sum] - sum == i;
                  }) |
                  std::views::transform([&](int i) { return divisor_sums[i]; });
    return std::to_string(std::accumulate(stream.begin(), stream.end(), 0));
  }

 private:
  const std::vector<int>& divisor_sums;
};

class P022 : public Solution {
 public:
  std::string solve() override {
    auto names = p022_input;
    std::sort(names.begin(), names.end());
    auto stream = std::views::zip_transform(
        [&](auto i, auto name) -> long long { return this->name_score(name) * (i + 1); },
        std::views::iota(0), names);
    return std::to_string(std::ranges::fold_left(stream, 0LL, std::plus<long long>()));
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
      : primes(primes | std::views::filter([](int p) { return p < 1000; }) |
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
    ans %= digits;
    return ans.get_str();
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
    std::vector<std::pair<euler_poker::Hand, euler_poker::Hand>> hands;
    std::istringstream infile(p054_input);
    std::string line;
    while (std::getline(infile, line)) {
      std::istringstream iss(line);
      std::vector<std::string> s;
      std::string token;
      while (iss >> token) s.push_back(token);
      if (s.size() != 10) continue;
      hands.emplace_back(euler_poker::parse_hand({s[0], s[1], s[2], s[3], s[4]}),
                         euler_poker::parse_hand({s[5], s[6], s[7], s[8], s[9]}));
    }
    int p1wins = 0;
    for (const auto& [p1, p2] : hands) {
      if (euler_poker::winner(p1, p2) == 1) ++p1wins;
    }
    return std::to_string(p1wins);
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
  bool is_lychrel(unsigned long long n) {
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
    for (auto [hn, kn] : std::views::take(euler::convergents(sqrt_2_coefs()), 1000)) {
      if (euler::to_string(hn).size() > euler::to_string(kn).size()) {
        ans++;
      }
    }
    return std::to_string(ans);
  }

 private:
  std::generator<long long> sqrt_2_coefs() {
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

class P059 : public Solution {
 public:
  std::string solve() override {
    auto text = std::views::split(p059_input, ',') | std::views::transform([](auto number) {
                  std::string s;
                  for (char x : number) s += x;
                  return std::stoi(s);
                }) |
                std::ranges::to<std::vector<int>>();
    for (char k1 = 'a'; k1 <= 'z'; k1++) {
      for (char k2 = 'a'; k2 <= 'z'; k2++) {
        for (char k3 = 'a'; k3 <= 'z'; k3++) {
          std::string key = {k1, k2, k3};
          std::string decrypted;
          for (size_t i = 0; i < text.size(); i++) {
            decrypted += static_cast<char>(text[i] ^ key[i % 3]);
          }
          if (decrypted.find(" the ") != std::string::npos) {
            int sum = std::accumulate(decrypted.begin(), decrypted.end(), 0);
            return std::to_string(sum);
          }
        }
      }
    }
    std::unreachable();
  }
};

class P060 : public Solution {
 public:
  P060(const std::vector<int>& primes) : primes(primes) {}
  std::string solve() override {
    auto small_primes = primes | std::views::take_while([](int p) { return p < 10000; }) |
                        std::ranges::to<std::vector<int>>();
    pairs.resize(1500);
    for (size_t i = 0; i < small_primes.size(); i++) {
      pairs[i].set(i);
      for (size_t j = i + 1; j < small_primes.size(); j++) {
        int p1 = small_primes[i];
        int p2 = small_primes[j];
        if (is_prime_pair(p1, p2)) {
          pairs[i].set(j);
          pairs[j].set(i);
        }
      }
    }
    mask_t mask;
    mask.set();
    return search(0, 0, 0, mask);
  }

 private:
  using mask_t = std::bitset<1500>;
  std::string search(int start, int size, int current, mask_t mask) {
    if (size == 5) {
      return std::to_string(current);
    }
    for (size_t i = start; i < pairs.size(); i++) {
      if ((mask & pairs[i]).count() >= 5) {
        auto ans = search(i + 1, size + 1, current + primes[i], mask & pairs[i]);
        if (!ans.empty()) {
          return ans;
        }
      }
    }
    return "";
  }
  bool is_prime_pair(int p1, int p2) {
    std::string s1 = std::to_string(p1);
    std::string s2 = std::to_string(p2);
    return euler::is_prime_mr(std::stoll(s1 + s2)) && euler::is_prime_mr(std::stoll(s2 + s1));
  }
  const std::vector<int>& primes;
  std::vector<mask_t> pairs;
};

class P061 : public Solution {
 public:
  std::string solve() override {
    auto seq = std::ranges::transform_view(
                   figurates, [this](auto figurate) { return four_digits(figurate); }) |
               std::ranges::to<std::vector<prefix_t>>();
    for (auto& [prefix, values] : seq[5]) {
      for (auto value : values) {
        if (int ans = search(seq, value, 1 << 5, value, value)) {
          return std::to_string(ans);
        }
      }
    }
    std::unreachable();
  }

 private:
  using prefix_t = std::unordered_map<int, std::unordered_set<int>>;
  int search(auto& seq, int start, int mask, int current, int first) {
    if (mask == 0x3F) {
      return start % 100 == first / 100 ? current : 0;
    }
    for (int i = 0; i < 6; i++) {
      if ((mask & (1 << i)) == 0) {
        if (!seq[i][start % 100].empty()) {
          for (auto value : seq[i][start % 100]) {
            if (int ans = search(seq, value, mask | (1 << i), current + value, first)) {
              return ans;
            }
          }
        }
      }
    }
    return 0;
  }
  static auto constexpr figurates = {euler::square,    euler::triangular, euler::pentagonal,
                                     euler::hexagonal, euler::heptagonal, euler::octagonal};
  prefix_t four_digits(auto figurate) {
    auto figurate_gen = std::views::iota(0) | std::views::transform(figurate) |
                        std::views::drop_while([](int n) { return n < 1000; }) |
                        std::views::take_while([](int n) { return n < 10000; });
    prefix_t prefix;
    for (auto n : figurate_gen) {
      prefix[n / 100].insert(n);
    }
    return prefix;
  }
};

class P062 : public Solution {
 public:
  std::string solve() override {
    std::unordered_map<std::string, std::vector<long long>> cubes;
    for (auto cube : gen_cubes()) {
      std::string key = std::to_string(cube);
      sort(key.begin(), key.end());
      cubes[key].push_back(cube);
      if (cubes[key].size() == 5) {
        return std::to_string(cubes[key][0]);
      }
    }
    std::unreachable();
  }

 private:
  std::generator<long long> gen_cubes() {
    for (auto i : std::views::iota(1LL)) {
      co_yield i* i* i;
    }
  }
};

class P063 : public Solution {
 public:
  std::string solve() override {
    int count = 0;
    for (mpz_class n = 1; n <= 9; n++) {
      for (mpz_class d = 1; d <= 21; d++) {
        if (euler::ipow(n, d).get_str().size() == d) {
          count++;
        }
      }
    }
    return std::to_string(count);
  }
};

class P064 : public Solution {
 public:
  std::string solve() override {
    int count = 0;
    for (int n = 1; n <= 10000; n++) {
      if (period(n) % 2 == 1) {
        count++;
      }
    }
    return std::to_string(count);
  }

 private:
  int period(int n) {
    int a0 = euler::isqrt(n);
    if (a0 * a0 == n) {
      return 0;
    }
    int m = 0, d = 1, a = a0, p = 0;
    do {
      m = d * a - m;
      d = (n - m * m) / d;
      a = (a0 + m) / d;
      p++;
    } while (a != 2 * a0);
    return p;
  }
};

class P065 : public Solution {
 public:
  std::string solve() override {
    auto [num, den] = *std::views::drop(euler::convergents(euler_e_coefs()), 99).begin();
    return std::to_string(euler::digit_sum(num));
  }

 private:
  std::generator<long long> euler_e_coefs() {
    co_yield 2;
    for (int i : std::views::iota(1)) {
      co_yield 1;
      co_yield 2 * i;
      co_yield 1;
    }
  }
};

class P066 : public Solution {
 public:
  std::string solve() override {
    mpz_class best_x = 0;
    int best_index = 0;
    for (int n : std::views::iota(2, 1001)) {
      if (!euler::is_square(n)) {
        auto [num, den] = *euler::pell(n).begin();
        if (num > best_x) {
          best_x = num;
          best_index = n;
        }
      }
    }
    return std::to_string(best_index);
  }
};

class P067 : public Solution {
 public:
  std::string solve() override {
    auto grid = euler::parse_triangle(p067_input);
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
};

class P068 : public Solution {
 public:
  std::string solve() override {
    auto p = std::views::iota(1, 11) | std::ranges::to<std::vector<int>>();
    std::string best;

    do {
      if (is_valid(p)) {
        std::string u = unique_str(p);
        if (u.size() == 16 and u > best) {
          best = u;
        }
      }
    } while (std::next_permutation(p.begin(), p.end()));
    return best;
  }

 private:
  bool is_valid(const std::vector<int>& p) {
    int target = get_sum(p, ring[0]);
    for (const auto& r : ring) {
      if (get_sum(p, r) != target) {
        return false;
      }
    }
    return true;
  }
  static constexpr std::array<std::array<int, 3>, 5> ring = {
      std::array{1, 2, 3}, std::array{4, 3, 5}, std::array{6, 5, 7}, std::array{8, 7, 9},
      std::array{10, 9, 2}};

  int get_sum(const std::vector<int>& p, const std::array<int, 3>& r) {
    auto stream = r | std::views::transform([&p](int x) { return p[x - 1]; });
    return std::ranges::fold_left(stream, 0, std::plus<int>());
  }

  std::string get_string(const std::vector<int>& p, const std::array<int, 3>& r) {
    auto stream = r | std::views::transform([&p](int x) { return std::to_string(p[x - 1]); });
    return std::ranges::fold_left(stream, "", std::plus<std::string>());
  }

  std::string unique_str(const std::vector<int>& p) {
    auto externals = ring | std::views::transform([&p](const auto& r) { return p[r[0] - 1]; }) |
                     std::ranges::to<std::vector<int>>();
    auto parts = ring | std::views::transform([&](const auto& r) { return get_string(p, r); }) |
                 std::ranges::to<std::vector<std::string>>();
    int start = std::ranges::distance(externals.begin(), std::ranges::min_element(externals));
    auto stream = std::views::iota(0, 5) |
                  std::views::transform([&](int j) { return parts[(start + j) % 5]; });
    return std::ranges::fold_left(stream, "", std::plus<std::string>());
  }
};

class P069 : public Solution {
 public:
  P069(const std::vector<int>& primes) : primes(primes) {}
  std::string solve() override {
    int ans = 1;
    for (int i : std::views::iota(0)) {
      int next = ans * primes[i];
      if (next > 1'000'000) {
        return std::to_string(ans);
      }
      ans = next;
    }
    std::unreachable();
  }

 private:
  const std::vector<int>& primes;
};

class P070 : public Solution {
 public:
  P070(const std::vector<int>& primes) : primes(primes) {}
  std::string solve() override {
    double best = 2.0;
    int best_index = 0;
    int limit = sqrt(10'000'000);
    int psize = primes.size();
    for (int i = 0; primes[i] < limit; i++) {
      for (int j = i + 1; j < psize && primes[i] * primes[j] < 10'000'000; j++) {
        int n = primes[i] * primes[j];
        int tot = (primes[i] - 1) * (primes[j] - 1);
        double frac = static_cast<double>(n) / tot;
        if (frac < best) {
          auto n_str = std::to_string(n);
          auto tot_str = std::to_string(tot);
          if (std::ranges::is_permutation(n_str, tot_str)) {
            best = frac;
            best_index = n;
          }
        }
      }
    }
    return std::to_string(best_index);
  }

 private:
  const std::vector<int>& primes;
};

class P071 : public Solution {
 public:
  std::string solve() override {
    long long goal_num = 3, goal_den = 7;
    long long cur_num = 0, cur_den = 1;
    for (long long i = 2; i < 1'000'000; i++) {
      long long f_num = i * goal_num / goal_den, f_den = i;
      long long g = euler::gcd(f_num, f_den);
      f_num /= g;
      f_den /= g;
      if (smaller(f_num, f_den, goal_num, goal_den) && smaller(cur_num, cur_den, f_num, f_den)) {
        cur_num = f_num;
        cur_den = f_den;
      }
    }
    return std::to_string(cur_num);
  }

 private:
  bool smaller(long long a_num, long long a_den, long long b_num, long long b_den) {
    return a_num * b_den < a_den * b_num;
  }
};

class P072 : public Solution {
 public:
  P072(const std::vector<int>& primes) : primes(primes) {}
  std::string solve() override {
    std::vector<int> phi(1'000'001);
    for (int p : primes | std::views::take_while([](int p) { return p <= 1'000; })) {
      for (int i = p; i <= 1'000'000; i += p) {
        if (phi[i] == 0) {
          phi[i] = p;
        }
      }
    }
    long long ans = 0;
    phi[1] = 1;
    for (int d = 2; d <= 1'000'000; d++) {
      if (phi[d] == 0 || phi[d] == d) {
        phi[d] = d - 1;
      } else {
        int ans = phi[d] - 1;
        int n = d / phi[d];
        int f = phi[d];
        while (n % phi[d] == 0) {
          n /= phi[d];
          ans *= phi[d];
          f *= phi[d];
        }
        phi[d] = ans * phi[d / f];
      }
      ans += phi[d];
    }
    return std::to_string(ans);
  }

 private:
  const std::vector<int>& primes;
};

class P073 : public Solution {
 public:
  std::string solve() override { return std::to_string(stern_brocot(1, 2, 2, 5, 1, 3)); }

 private:
  int stern_brocot(int lnum, int lden, int mnum, int mden, int rnum, int rden) {
    if (mden > 12000) return 0;
    int ans = 1;
    ans += stern_brocot(lnum, lden, lnum + mnum, lden + mden, mnum, mden);
    ans += stern_brocot(mnum, mden, rnum + mnum, rden + mden, rnum, rden);
    return ans;
  }
};

class P074 : public Solution {
 public:
  P074() : chain(4'000'000, 0) {}
  std::string solve() override {
    int ans = 0;
    for (int i = 1; i < 1'000'000; i++) {
      if (eval_chain(i, -1, 0).first == 60) {
        ans++;
      }
    }
    return std::to_string(ans);
  }

 private:
  std::pair<int, int> eval_chain(int n, int offset, int loop) {
    int next = factorial_digits(n);
    if (next == n) {
      chain[n] = 1;
      return {1, loop};
    }
    if (chain[next] > 0) {
      chain[n] = chain[next] + 1;
      return {chain[next] + 1, loop};
    }
    if (chain[next] < 0) {
      chain[n] = chain[next] - offset + 2;
      return {chain[next] - offset + 2, next};
    }
    chain[n] = offset - 1;
    auto [size, next_loop] = eval_chain(next, offset - 1, loop);
    if (chain[next_loop] >= chain[n] && next_loop > 0) {
      chain[n] = chain[next];
      return {chain[next], n == next_loop ? 0 : next_loop};
    } else {
      chain[n] = size + 1;
      return {size + 1, next_loop};
    }
  }
  int factorial_digits(int n) {
    int ans = 0;
    while (n) {
      ans += euler::factorials[n % 10];
      n /= 10;
    }
    return ans;
  }
  std::vector<int> chain;
};

class P075 : public Solution {
 public:
  std::string solve() override {
    std::vector<int> count(1'500'001, 0);
    for (auto [a, b, c] : euler::pythagorean_triples(1'500'000)) {
      int perimeter = a + b + c;
      if (perimeter > 1'500'000) continue;
      count[perimeter]++;
    }
    int ans = 0;
    for (int i = 1; i <= 1'500'000; i++) {
      if (count[i] == 1) {
        ans++;
      }
    }
    return std::to_string(ans);
  }
};

class P076 : public Solution {
 public:
  std::string solve() override {
    std::vector<long long> ways(101, 0);
    ways[0] = 1;
    for (int i = 1; i <= 100; i++) {
      for (int j = i; j <= 100; j++) {
        ways[j] += ways[j - i];
      }
    }
    return std::to_string(ways[100] - 1);
  }
};

class P077 : public Solution {
 public:
  P077(const std::vector<int>& primes) : primes(primes) {}
  std::string solve() override {
    for (int i : std::views::iota(2)) {
      if (search(i, 0) > 5000) {
        return std::to_string(i);
      }
    }
    std::unreachable();
  }

 private:
  const std::vector<int>& primes;
  std::map<std::pair<int, int>, int> memo;
  int search(int n, int cur) {
    if (n == 0) {
      return 1;
    }
    if (memo.contains({n, cur})) {
      return memo[{n, cur}];
    }
    int ans = 0;
    for (int i = cur; primes[i] <= n; i++) {
      ans += search(n - primes[i], i);
    }
    return memo[{n, cur}] = ans;
  }
};

class P078 : public Solution {
 public:
  std::string solve() override {
    std::vector<long long> ways(60001, 0);
    auto pentagonals = std::views::iota(0) |
                       std::views::transform([this](int n) { return generalized_pentagonal(n); }) |
                       std::views::take_while([](int p) { return p < 60000; }) |
                       std::ranges::to<std::vector<int>>();
    ways[0] = 1;
    for (int i = 1; i <= 60000; i++) {
      for (int j = 0; pentagonals[j] <= i; j++) {
        int sign = (j % 4 < 2) ? 1 : -1;
        ways[i] = (ways[i] + sign * ways[i - pentagonals[j]]) % 1'000'000;
      }
      if (ways[i] % 1'000'000 == 0) {
        return std::to_string(i);
      }
    }
    std::unreachable();
  }

 private:
  int generalized_pentagonal(int n) {
    int x = n / 2 + 1;
    if (n % 2 == 1) {
      x = -x;
    }
    return euler::pentagonal(x);
  }
};

class P079 : public Solution {
 public:
  std::string solve() override {
    auto [graph, digits] = build_graph();
    std::vector<bool> done(10, true);
    for (int d : digits) {
      done[d] = false;
    }
    int goal = digits.size();
    std::string ans;
    std::vector<int> incoming(10);
    for (int total = 0; total < goal; total++) {
      std::fill(incoming.begin(), incoming.end(), 0);
      for (int d : digits) {
        if (done[d]) continue;
        for (int neighbor : graph[d]) {
          if (!done[neighbor]) {
            incoming[d]++;
          }
        }
      }
      int min_index = find_min_incoming(incoming, done);
      ans += std::to_string(min_index);
      done[min_index] = true;
    }
    return ans;
  }

 private:
  using graph_t = std::unordered_map<int, std::unordered_set<int>>;
  using digits_t = std::unordered_set<int>;
  std::pair<graph_t, digits_t> build_graph() {
    graph_t graph;
    digits_t digits;
    for (int source : euler::parse_numbers<int>(p079_input)) {
      int a = source / 100;
      int b = (source / 10) % 10;
      int c = source % 10;
      graph[c].insert(a);
      graph[c].insert(b);
      graph[b].insert(a);
      digits.insert(a);
      digits.insert(b);
      digits.insert(c);
    }
    return make_pair(graph, digits);
  }
  int find_min_incoming(const auto& done, const auto& incoming) {
    int min_incoming = 100, min_index = -1;
    for (int i = 0; i < 10; i++) {
      if (incoming[i] < min_incoming && !done[i]) {
        min_incoming = incoming[i];
        min_index = i;
      }
    }
    return min_index;
  }
};

class P080 : public Solution {
 public:
  std::string solve() override {
    int sum = 0;
    for (int i = 1; i <= 100; i++) {
      if (euler::is_square(i)) continue;
      mpz_class n = i * euler::ipow<mpz_class>(10, 200);
      mpz_class root = euler::isqrt(n);
      std::string root_str = root.get_str();
      for (int i = 0; i < 100; i++) {
        sum += root_str[i] - '0';
      }
    }
    return std::to_string(sum);
  }
};

class P081 : public Solution {
 public:
  std::string solve() override {
    auto mat = euler::parse_matrix(p081_input);
    std::vector<std::vector<long long>> ans(80, std::vector<long long>(80, 0));
    for (int x = 79; x >= 0; x--) {
      for (int y = 79; y >= 0; y--) {
        if (x == 79) {
          if (y == 79) {
            ans[x][y] = mat[x][y];
          } else {
            ans[x][y] = mat[x][y] + ans[x][y + 1];
          }
        } else {
          if (y == 79) {
            ans[x][y] = mat[x][y] + ans[x + 1][y];
          } else {
            ans[x][y] = std::min<long long>(mat[x][y] + ans[x + 1][y], mat[x][y] + ans[x][y + 1]);
          }
        }
      }
    }
    return std::to_string(ans[0][0]);
  }
};

class P082 : public Solution {
 public:
  std::string solve() override {
    auto mat = euler::parse_matrix(p082_input);
    std::vector<std::vector<long long>> ans(80, std::vector<long long>(80, 0));
    for (int y = 0; y < 80; y++) {
      ans[y][79] = mat[y][79];
    }
    for (int x = 78; x >= 0; x--) {
      for (int yenter = 0; yenter < 80; yenter++) {
        long long best = 1'000'000;
        for (int yexit = 0; yexit < 80; yexit++) {
          long long partial = ans[yexit][x + 1];
          for (int k = std::min(yenter, yexit); k <= std::max(yenter, yexit); k++) {
            partial += mat[k][x];
          }
          if (partial < best) {
            best = partial;
          }
        }
        ans[yenter][x] = best;
      }
    }
    long long best = 1'000'000;
    for (int y = 0; y < 80; y++) {
      if (ans[y][0] < best) {
        best = ans[y][0];
      }
    }
    return std::to_string(best);
  }
};

class P083 : public Solution {
 public:
  std::string solve() override {
    auto mat = euler::parse_matrix(p083_input);
    pos start{0, 0};
    std::priority_queue<std::pair<long long, pos>> next;
    std::set<pos> visited;
    next.push({-mat[0][0], start});
    while (!next.empty()) {
      auto [score, cur] = next.top();
      next.pop();
      visited.insert(cur);
      if (cur == pos{79, 79}) {
        return std::to_string(-score);
      }
      for (int i = 0; i < 4; i++) {
        pos cnext{cur.first + dir[i].first, cur.second + dir[i].second};
        if (!visited.contains(cnext) && cnext.first >= 0 && cnext.first < 80 && cnext.second >= 0 &&
            cnext.second < 80) {
          next.push({score - mat[cnext.first][cnext.second], cnext});
        }
      }
    }
    std::unreachable();
  }

 private:
  using pos = std::pair<int, int>;
  const std::vector<pos> dir{pos{0, 1}, pos{0, -1}, pos{1, 0}, pos{-1, 0}};
};

class P084 : public Solution {
 public:
  std::string solve() override {
    Eigen::Matrix<double, 40 * 3 + 1, 40 * 3 + 1> mat;
    mat.setZero();
    for (int pos = 0; pos < 40; pos++) {
      for (int doubles = 0; doubles < 3; doubles++) {
        for (auto [d1, d2] : moves()) {
          int level = 0;
          if (d1 == d2) {
            level = (doubles + 1) * 40;
            if (doubles == 2) {
              mat(JAIL + 0, pos + doubles * 40) += basestep;
              continue;
            }
          }
          int dest = (pos + d1 + d2) % 40;
          if (dest == G2J) {
            dest = JAIL;
          } else if (dest == CC1 || dest == CC2 || dest == CC3) {
            for (int i = 0; i < 16; i++) {
              int newdest = i == 0 ? GO : i == 1 ? JAIL : dest;
              mat(newdest + level, pos + doubles * 40) += smallstep;
            }
            continue;
          } else if (dest == CH1 || dest == CH2 || dest == CH3) {
            for (int i = 0; i < 16; i++) {
              int newdest = chance(dest, i);
              mat(newdest + level, pos + doubles * 40) += smallstep;
            }
            continue;
          }
          mat(dest + level, pos + doubles * 40) += basestep;
        }
      }
    }
    for (int i = 0; i < 40 * 3; i++) {
      mat(i, i) -= 1.0;
      mat(40 * 3, i) = 1.0;
    }
    Eigen::Vector<double, 40 * 3 + 1> b;
    b.setZero();
    b(40 * 3) = 1.0;
    auto x = mat.colPivHouseholderQr().solve(b);
    std::vector<std::pair<double, int>> results;
    for (int i = 0; i < 40; i++) {
      double prob = x[i] + x[i + 40] + x[i + 80];
      results.emplace_back(prob, i);
    }
    std::sort(results.rbegin(), results.rend());
    return std::format("{:02d}{:02d}{:02d}", results[0].second, results[1].second,
                       results[2].second);
  }

 private:
  std::generator<std::pair<int, int>> moves() {
    for (int i = 1; i <= sides; i++) {
      for (int j = 1; j <= sides; j++) {
        co_yield {i, j};
      }
    }
  }
  int chance(int dest, int i) {
    switch (i) {
      case 0:
        return GO;
      case 1:
        return JAIL;
      case 2:
        return C1;
      case 3:
        return E3;
      case 4:
        return H2;
      case 5:
        return nextrail(dest);
      case 6:
        return nextrail(dest);
      case 7:
        return nextutil(dest);
      case 8:
        return (dest + 40 - 3) % 40;
    }
    return dest;
  }
  int nextrail(int dest) {
    if (dest == CH1) return R2;
    if (dest == CH2) return R3;
    if (dest == CH3) return R1;
    std::unreachable();
  }
  int nextutil(int dest) {
    if (dest == CH1) return U1;
    if (dest == CH2) return U2;
    if (dest == CH3) return U1;
    std::unreachable();
  }
  const int GO = 0, G2J = 30, JAIL = 10, CH1 = 7, CH2 = 22, CH3 = 36;
  const int CC1 = 2, CC2 = 17, CC3 = 33;
  const int R1 = 5, R2 = 15, R3 = 25;
  const int U1 = 12, U2 = 28, C1 = 11, E3 = 24, H2 = 39;
  const int sides = 4;
  const double basestep = 1.0 / sides / sides;
  const double smallstep = basestep / 16;
};

class P085 : public Solution {
 public:
  std::string solve() override {
    constexpr long long M = 2'000'000;
    const int limit = euler::isqrt(M);
    comp best{M * M, 0};
    for (int i = 1; i <= limit; i++) {
      double bb = invert(i, M);
      for (int b = std::floor(bb); b <= std::ceil(bb); b++) {
        int r = rects(i, b);
        comp cur{(r - M) * (r - M), i * b};
        if (cur < best) {
          best = cur;
        }
      }
    }
    return std::to_string(best.second);
  }

 private:
  using comp = std::pair<long long, int>;
  int rects(int a, int b) { return a * b * (1 + a + b + a * b) / 4; }
  double invert(int a, int c) {
    double sq = std::sqrt(static_cast<double>(a + a * a + 16 * c) / (a * (1 + a)));
    return (sq - 1) / 2;
  }
};

class P086 : public Solution {
 public:
  std::string solve() override { return ""; }
};

class P087 : public Solution {
 public:
  P087(const std::vector<int>& primes) : primes(primes) {}
  std::string solve() override {
    std::vector<int> visited;
    visited.reserve(2'000'000);
    for (int p4 : primes) {
      int p4v = p4 * p4 * p4 * p4;
      if (p4v >= 50'000'000) {
        break;
      }
      for (int p3 : primes) {
        int p3v = p3 * p3 * p3;
        if (p4v + p3v >= 50'000'000) {
          break;
        }
        for (int p2 : primes) {
          int p2v = p2 * p2;
          int sum = p4v + p3v + p2v;
          if (sum >= 50'000'000) {
            break;
          }
          visited.push_back(sum);
        }
      }
    }
    std::sort(visited.begin(), visited.end());
    int cur = 0, sum = 0;
    for (int v : visited) {
      if (v != cur) {
        sum++;
        cur = v;
      }
    }
    return std::to_string(sum);
  }

 private:
  const std::vector<int>& primes;
};

class P090 : public Solution {
 public:
  std::string solve() override {
    std::vector<int> six_digits;
    const int mask = (1 << 6) + (1 << 9);
    for (unsigned int i = 0; i < 1024; i++) {
      if (std::popcount(i) == 6) {
        int dice = i;
        if (dice & mask) {
          dice |= mask;
        }
        six_digits.push_back(dice);
      }
    }
    int ans = 0;
    for (int d1 : six_digits) {
      for (int d2 : six_digits) {
        if (valid(d1, d2)) {
          ans++;
        }
      }
    }
    return std::to_string(ans / 2);
  }

 private:
  bool valid(int d1, int d2) {
    for (int i = 1; i < 10; i++) {
      int square = i * i;
      int a = (1 << (square / 10)), b = (1 << (square % 10));
      if (!(((d1 & a) && (d2 & b)) || ((d1 & b) && (d2 & a)))) {
        return false;
      }
    }
    return true;
  }
};

class P091 : public Solution {
 public:
  std::string solve() override {
    std::set<Triangle> ans;
    for (int x1 = 0; x1 <= 50; x1++) {
      for (int x2 = x1; x2 <= 50; x2++) {
        int starty = x1 == 0 ? 1 : 0;
        for (int y1 = starty; y1 <= 50; y1++) {
          for (int y2 = 0; y2 <= 50; y2++) {
            int a = dist(0, 0, x1, y1);
            int b = dist(0, 0, x2, y2);
            int c = dist(x1, y1, x2, y2);
            int h = std::max({a, b, c});
            if (2 * h == a + b + c && std::min({a, b, c}) > 0) {
              Triangle t = {{x1, y1}, {x2, y2}};
              if (t.first > t.second) {
                std::swap(t.first, t.second);
              }
              ans.insert(t);
            }
          }
        }
      }
    }
    return std::to_string(ans.size());
  }

 private:
  using Triangle = std::pair<std::pair<int, int>, std::pair<int, int>>;
  int dist(int x1, int y1, int x2, int y2) { return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2); }
};

class P092 : public Solution {
 public:
  std::string solve() override {
    int ans = 0;
    for (auto digits : split(7, 0, Histogram{})) {
      int sum = 0;
      for (int d = 0; d <= 9; d++) {
        sum += digits[d] * d * d;
      }
      if (sum > 0 && chain(sum) == 89) {
        ans += euler::multinomial<long long>(digits);
      }
    }
    return std::to_string(ans);
  }

 private:
  using Histogram = std::array<int, 10>;
  int digit_square_sum(int n) {
    int ans = 0;
    while (n) {
      int d = n % 10;
      ans += d * d;
      n /= 10;
    }
    return ans;
  }
  int chain(int n) {
    while (true) {
      if (n == 1 or n == 89) {
        return n;
      }
      n = digit_square_sum(n);
    }
    std::unreachable();
  }
  std::generator<Histogram> split(int n, int start, Histogram current) {
    if (n == 0) {
      co_yield current;
      co_return;
    }
    if (start == 9) {
      current[9] += n;
      co_yield current;
      co_return;
    }
    for (int i = 0; i <= n; i++) {
      Histogram next = current;
      if (i > 0) {
        next[start] += i;
      }
      for (auto h : split(n - i, start + 1, next)) {
        co_yield h;
      }
    }
    co_return;
  }
};

class P093 : public Solution {
 public:
  std::string solve() override {
    std::vector<int> digits(9);
    std::iota(digits.begin(), digits.end(), 1);
    auto range = euler::combinations(digits, 4) |
                 std::views::transform([this](auto comb) { return make_pair(count(comb), comb); });
    auto ans = std::ranges::max(range).second;
    return std::to_string(ans[0] * 1000 + ans[1] * 100 + ans[2] * 10 + ans[3]);
  }

 private:
  using op_t = std::function<double(double, double)>;
  std::array<op_t, 6> ops = {[](double a, double b) { return a + b; },
                             [](double a, double b) { return a - b; },
                             [](double a, double b) { return b - a; },
                             [](double a, double b) { return a * b; },
                             [](double a, double b) { return near(b, 0) ? 0 : a / b; },
                             [](double a, double b) { return near(a, 0) ? 0 : b / a; }};

  static bool near(double a, double b) {
    const double eps = 1e-4;
    return abs(a - b) < eps;
  }

  int count(std::vector<int> int_digits) {
    std::set<int> s;
    for (auto op1 : ops) {
      for (auto op2 : ops) {
        for (auto op3 : ops) {
          std::sort(int_digits.begin(), int_digits.end());
          do {
            std::array<double, 4> digits;
            std::transform(int_digits.begin(), int_digits.end(), digits.begin(),
                           [](int d) { return static_cast<double>(d); });
            auto value1 = op3(op1(digits[0], digits[1]), op2(digits[2], digits[3]));
            if (near(value1, std::round(value1))) {
              s.insert(static_cast<int>(std::round(value1)));
            }
            auto value2 = op1(digits[0], op2(digits[1], op3(digits[2], digits[3])));
            if (near(value2, std::round(value2))) {
              s.insert(static_cast<int>(std::round(value2)));
            }
          } while (std::next_permutation(int_digits.begin(), int_digits.end()));
        }
      }
    }
    for (int i = 1; i <= 9'999; i++) {
      if (!s.contains(i)) {
        return i;
      }
    }
    std::unreachable();
  }
};

class P094 : public Solution {
 public:
  std::string solve() override {
    mpz_class ans = sum_over(-1) + sum_over(1);
    return ans.get_str();
  }

 private:
  mpz_class sum_over(int side) {
    mpz_class ans = 0;
    for (auto perimeter : iter_sides(side)) {
      if (perimeter >= 1'000'000'000) {
        return ans;
      }
      ans += perimeter;
    }
    std::unreachable();
  }

  std::generator<mpz_class> iter_sides(int offset) {
    for (auto [x, y] : euler::pell(3)) {
      mpz_class yy = 2 * y;
      mpz_class a = (euler::isqrt<mpz_class>(yy * yy * 3 + 4) + offset) / 3;
      if (a > 0 && heron(a, a, a + offset)) {
        co_yield 3 * a + offset;
      }
    }
    std::unreachable();
  }

  bool heron(mpz_class a, mpz_class b, mpz_class c) {
    mpz_class area_sq = (a + b + c) * (a + b - c) * (a - b + c) * (-a + b + c) / 16;
    if (area_sq <= 0) {
      return false;
    }
    return euler::is_square(area_sq);
  }
};

class P095 : public Solution {
 public:
  P095(const std::vector<int>& divisor_sums) : divisor_sums(divisor_sums) {}
  std::string solve() override {
    int M = 1'000'000;
    int goal = M;
    int max_size = 0;
    std::vector<int> seen(M + 1, 0);
    for (int i = 2; i <= M; i++) {
      if (seen[i] > 0) {
        continue;
      }
      int j = i;
      seen[i] = i;
      while ((j = divisor_sums[j] - j) != i) {
        if (j < 2 || j > M || seen[j] > 0) {
          break;
        }
        seen[j] = i;
      }
      if (j < 2 || j > M || seen[j] < i) {
        continue;
      }
      int size = 0;
      int start = j;
      while ((j = divisor_sums[j] - j) != start) {
        size++;
      }
      if (size > max_size) {
        goal = j;
        while ((j = divisor_sums[j] - j) != start) {
          if (j < goal) {
            goal = j;
          }
        }
        max_size = size;
      }
    }
    return std::to_string(goal);
  }

 private:
  const std::vector<int>& divisor_sums;
};

class P096 : public Solution {
 public:
  std::string solve() override {
    eval_solution solution;
    std::istringstream iss(p096_input);
    for (std::string grid, number; iss >> grid >> number;) {
      // read the grid from stdin.
      char given[9][9];
      std::string line;
      for (int j = 0; j < 9; j++) {
        iss >> line;
        for (int i = 0; i < 9; i++) {
          given[j][i] = line[i] - '1';
        }
      }

      // build the exact cover matrix.
      std::vector<std::vector<bool>> mat(9 * 9 * 9, std::vector<bool>(9 * 9 * 4, false));
      for (int digit = 0; digit < 9; digit++)
        for (int row = 0; row < 9; row++)
          for (int col = 0; col < 9; col++) {
            if (given[row][col] >= 0 && given[row][col] != digit) continue;
            int i = digit + col * 9 + row * 9 * 9;
            mat[i][col + row * 9] = true;
            mat[i][9 * 9 + row * 9 + digit] = true;
            mat[i][9 * 9 * 2 + col * 9 + digit] = true;
            int box = (row / 3) * 3 + col / 3;
            mat[i][9 * 9 * 3 + box * 9 + digit] = true;
          }

      // print the solution.
      euler_exactcover::exactcover(mat, solution);
    }
    return std::to_string(solution.total);
  }

 private:
  // callback to sum the solutions found.
  struct eval_solution {
    int total = 0;
    void operator()(const std::vector<int>& solution) {
      char tab[9][9];
      memset(tab, 0, sizeof tab);
      for (auto it : solution) tab[it / 9 / 9][it / 9 % 9] = 1 + it % 9;
      int code = tab[0][0] * 100 + tab[0][1] * 10 + tab[0][2];
      total += code;
    }
  };
};

class P097 : public Solution {
 public:
  std::string solve() override {
    const mpz_class M = euler::ipow<mpz_class>(10, 10);
    mpz_class exp = euler::modpow<mpz_class>(2, 7830457, M);
    mpz_class ans = (28433 * exp + 1) % M;
    return ans.get_str();
  }
};

int main() {
  const auto [primes, first_prime] = euler::linear_sieve(2'000'000);
  const std::unordered_set<int> prime_set(primes.begin(), primes.end());
  const auto divisor_sums = euler::all_divisors(1'000'000, first_prime);

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
      std::make_shared<P059>(),
      std::make_shared<P060>(primes),
      std::make_shared<P061>(),
      std::make_shared<P062>(),
      std::make_shared<P063>(),
      std::make_shared<P064>(),
      std::make_shared<P065>(),
      std::make_shared<P066>(),
      std::make_shared<P067>(),
      std::make_shared<P068>(),
      std::make_shared<P069>(primes),
      std::make_shared<P070>(primes),
      std::make_shared<P071>(),
      std::make_shared<P072>(primes),
      std::make_shared<P073>(),
      std::make_shared<P074>(),
      std::make_shared<P075>(),
      std::make_shared<P076>(),
      std::make_shared<P077>(primes),
      std::make_shared<P078>(),
      std::make_shared<P079>(),
      std::make_shared<P080>(),
      std::make_shared<P081>(),
      std::make_shared<P082>(),
      std::make_shared<P083>(),
      std::make_shared<P084>(),
      std::make_shared<P085>(),
      std::make_shared<P086>(),
      std::make_shared<P087>(primes),
      std::make_shared<P086>(),
      std::make_shared<P086>(),
      std::make_shared<P090>(),
      std::make_shared<P091>(),
      std::make_shared<P092>(),
      std::make_shared<P093>(),
      std::make_shared<P094>(),
      std::make_shared<P095>(divisor_sums),
      std::make_shared<P096>(),
      std::make_shared<P097>(),
  };

  std::vector<std::pair<std::string, long long>> results(solutions.size());
  std::transform(std::execution::par, solutions.begin(), solutions.end(), results.begin(),
                 [&](const auto& solution) {
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
