#include <iostream>
#include <sstream>
#include <execution>
#include <utility>
#include <string>
#include <generator>
#include <cmath>
#include <ranges>
#include <algorithm>
#include <vector>
#include <memory>
#include <numeric>
#include <array>

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

std::generator<int> fibonacci_generator() {
  int a = 0, b = 1;
  while (true) {
    co_yield b;
    int c = a + b;
    a = b;
    b = c;
  }
}

class P002 : public Solution {
  public:
  std::string solve() override {
    int ans = 0;
    for (int f : fibonacci_generator()) {
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

template<typename T>
std::generator<T> factor_integer(T n) {
  T factor = 2;
  T limit = static_cast<T>(sqrt(n));
  while (factor <= limit) {
    while (n % factor == 0) {
      co_yield factor;
      n /= factor;
    }
    factor++;
  }
  if (n > 1) {
    co_yield n;
  }
}

class P003 : public Solution{
  public:
   std::string solve() override {
     return std::to_string(std::ranges::max(factor_integer(600851475143LL)));
   }
};
 
bool is_palindrome(int n) {
  int reversed = 0, original = n;
  while (original) {
    reversed = reversed * 10 + original % 10;
    original /= 10;
  }
  return n == reversed;
}

class P004 : public Solution {
  public:
  std::string solve() override {
    int best = 0;
    for (int i = 100; i <= 999; i++) {
      for (int j = i; j <= 999; j++) {
        int product = i * j;
        if (is_palindrome(product)) {
          best = std::max(best, product);
        }
      }
    }
    return std::to_string(best);
  }
};

template<typename T>
T gcd(T a, T b) {
  while (b != 0) {
    T temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

template<typename T>
T lcm(T a, T b) { 
  return a / gcd(a, b) * b;
}

class P005 : public Solution {
  public:
  std::string solve() override {
    int ans = 1;
    for (int i = 2; i <= 20; i++) {
      ans = lcm(ans, i);
    }
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
    };
    return std::to_string(acc * acc - squares);
  }
};

std::generator<int> sieve_generator(int limit) {
  std::vector<bool> primes(limit + 1, true);
  int sqrt_limit = static_cast<int>(sqrt(limit));
  int p = 2;
  for (; p <= sqrt_limit; p++) {
    if (primes[p]) {
      co_yield p; // Yield the prime number
      for (int i = p * p; i <= limit; i += p) {
        primes[i] = false;
      }
    }
  }
  for (;p <= limit; p++) {
    if (primes[p]) {
      co_yield p; // Yield the prime number
    }
  }
}

class P007 : public Solution {
  public:
  P007(const std::vector<int>& primes) : primes(primes) {
  }

  std::string solve() override {
    return std::to_string(primes[10000]);
  }

  private:
  const std::vector<int>& primes;
};

std::generator<int> digit_generator(const std::string& str) {
  for (char c : str) {
    if (std::isdigit(c)) {
      co_yield static_cast<int>(c - '0');
    }
  }
}

template<typename T, int SIZE>
std::generator<std::array<T, SIZE>> window_generator(std::generator<T> gen) {
  std::array<int, SIZE> window;
  for (int i = 0; int elem : gen) {
    if (i < SIZE - 1) {
      window[i + 1] = elem;
    } else {
      std::rotate(window.begin(), window.begin() + 1, window.end());
      window[SIZE - 1] = elem;
      co_yield window;
    }
    i++;
  }
}

class P008 : public Solution {
  public:
  std::string solve() override {
    long long best = 0LL;
    for (auto window : window_generator<int, 13>(digit_generator(digits))) {
      long long product = std::accumulate(window.begin(), window.end(), 1LL, std::multiplies<long long>());
      best = std::max(best, product);
    }
    return std::to_string(best);
  } 

  private:
  const std::string digits = R"(
    73167176531330624919225119674426574742355349194934
    96983520312774506326239578318016984801869478851843
    85861560789112949495459501737958331952853208805511
    12540698747158523863050715693290963295227443043557
    66896648950445244523161731856403098711121722383113
    62229893423380308135336276614282806444486645238749
    30358907296290491560440772390713810515859307960866
    70172427121883998797908792274921901699720888093776
    65727333001053367881220235421809751254540594752243
    52584907711670556013604839586446706324415722155397
    53697817977846174064955149290862569321978468622482
    83972241375657056057490261407972968652414535100474
    82166370484403199890008895243450658541227588666881
    16427171479924442928230863465674813919123162824586
    17866458359124566529476545682848912883142607690042
    24219022671055626321111109370544217506941658960408
    07198403850962455444362981230987879927244284909188
    84580156166097919133875499200524063689912560717606
    05886116467109405077541002256983155200055935729725
    71636269561882670428252483600823257530420752963450
  )";
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
  P010(const std::vector<int>& primes) : primes(primes) {
  }
  std::string solve() override {
    auto valid_primes = primes 
        | std::views::take_while([](int p) { return p < 2'000'000; });
    auto sum = std::ranges::fold_left(valid_primes, 0LL, std::plus<long long>());
    return std::to_string(sum);
  }
  private:
  const std::vector<int>& primes;
};

template<typename T>
std::vector<T> fill_vector(std::generator<T> gen) {
  std::vector<T> vec;
  for (auto it = gen.begin(); it != gen.end(); ++it) {
    vec.push_back(*it);
  }
  return vec;
}

std::generator<int> numbers_generator(const std::string& grid) {
  std::istringstream iss(grid);
  int value;
  while (iss >> value) {
    co_yield value;
  }
}

class P011 : public Solution {
  public:
  std::string solve() override {
    std::vector<int> numbers = fill_vector(numbers_generator(source_grid));
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

  std::vector<std::pair<int, int>> directions = {
    {0, 1}, {1, 0}, {1, 1}, {1, -1}
  };

  std::string source_grid = R"(
    08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
    49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
    81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
    52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
    22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
    24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
    32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70
    67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21
    24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72
    21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95
    78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
    16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
    86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
    19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
    04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
    88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
    04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
    20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
    20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
    01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48
  )";
};

int main() {
  std::vector<int> primes = fill_vector(sieve_generator(2'000'000));
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
  };

  std::vector<std::string> results(solutions.size());
  std::transform(
    std::execution::par,
    solutions.begin(), solutions.end(),
    results.begin(),
    [](const auto& sol) {
      return sol->solve();
    }
  );

  for (auto& r : results) {
    std::cout << r << "\n";
  }
  return 0;
}
