#include <gmpxx.h>

#include <cmath>
#include <generator>
#include <sstream>
#include <string>
#include <vector>

namespace euler {

template <typename T>
T isqrt(const T& n) {
  if constexpr (std::is_same_v<T, int>) {
    if (n < 0) return 0;
    return static_cast<int>(std::sqrt(n));
  } else if constexpr (std::is_same_v<T, long long>) {
    if (n < 0) return 0;
    return static_cast<long long>(std::sqrtl(static_cast<long double>(n)));
  } else {
    if (n < 0) return 0;
    T x = n, y = (x + 1) / 2;
    while (y < x) {
      x = y;
      y = (x + n / x) / 2;
    }
    return x;
  }
}

template <>
mpz_class isqrt<mpz_class>(const mpz_class& n) {
  mpz_class r;
  mpz_sqrt(r.get_mpz_t(), n.get_mpz_t());
  return r;
}

std::generator<int> fibonacci_generator() {
  int a = 0, b = 1;
  while (true) {
    co_yield b;
    int c = a + b;
    a = b;
    b = c;
  }
}

template <typename T>
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

template <typename T>
std::generator<T> factor_integer(T n, const std::vector<int>& primes) {
  size_t index = 0;
  T limit = static_cast<T>(sqrt(n));
  while (index < primes.size() && primes[index] <= limit) {
    while (n % primes[index] == 0) {
      co_yield primes[index];
      n /= primes[index];
    }
    index++;
  }
  if (n > 1) {
    co_yield n;
  }
}

template <typename T>
T reverse_digits(T n) {
  T reversed = 0;
  T ten = T{10};
  while (n > 0) {
    reversed = reversed * ten + n % ten;
    n /= ten;
  }
  return reversed;
}

template <typename T>
bool is_palindrome(T n) {
  return n == reverse_digits(n);
}

template <>
bool is_palindrome<std::string>(std::string n) {
  return std::equal(n.begin(), n.begin() + n.size() / 2, n.rbegin());
}

bool is_square(long long n) {
  long long root = static_cast<long long>(sqrt(n));
  return root * root == n;
}

template <typename T>
T gcd(T a, T b) {
  while (b != 0) {
    T temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

template <typename T>
T lcm(T a, T b) {
  return a / gcd(a, b) * b;
}

std::generator<int> prime_sieve_generator(int limit) {
  std::vector<bool> primes(limit + 1, true);
  int sqrt_limit = static_cast<int>(sqrt(limit));
  int p = 2;
  for (; p <= sqrt_limit; p++) {
    if (primes[p]) {
      co_yield p;  // Yield the prime number
      for (int i = p * p; i <= limit; i += p) {
        primes[i] = false;
      }
    }
  }
  for (; p <= limit; p++) {
    if (primes[p]) {
      co_yield p;  // Yield the prime number
    }
  }
}

std::generator<int> mobius_sieve_generator(int limit) {
  std::vector<int> mobius(limit + 1, 1);
  int sqrt_limit = isqrt(limit);
  int p = 2;
  for (; p <= sqrt_limit; p++) {
    if (mobius[p] == 1) {  // p is prime
      for (int i = p; i <= limit; i += p) {
        mobius[i] *= -p;  // Mark multiples of p
      }
      for (int i = p * p; i <= limit; i += p * p) {
        mobius[i] = 0;  // Mark multiples of p^2
      }
    }
  }
  for (int i = 0; i <= limit; i++) {
    if (mobius[i] < 0) {
      co_yield 1;  // Yield 1 for square-free numbers
    } else if (mobius[i] > 0) {
      co_yield -1;  // Yield -1 for square-free numbers with an odd number of prime factors
    } else if (mobius[i] == 0) {
      co_yield 0;  // Yield 0 for non-square-free numbers
    }
  }
}

std::generator<int> digit_generator(const std::string& str) {
  for (char c : str) {
    if (std::isdigit(c)) {
      co_yield static_cast<int>(c - '0');
    }
  }
}

template <typename T>
concept HasGetSi = requires(T a) {
  { a.get_si() } -> std::convertible_to<int>;
};

template <HasGetSi T>
int to_int(T n) {
  return n.get_si();
}

template <typename T>
int to_int(T n) {
  return static_cast<int>(n);
}

std::string to_string(const mpz_class& n) {
  std::ostringstream oss;
  oss << n;
  return oss.str();
}

template <typename T>
int digit_sum(T n) {
  int sum = 0;
  while (n > 0) {
    T digit = n % 10;
    sum += to_int(digit);
    n /= 10;
  }
  return sum;
}

template <typename T, int SIZE>
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

template <typename T>
std::generator<T> parse_numbers(const std::string& number_list) {
  std::istringstream iss(number_list);
  T value;
  while (iss >> value) {
    co_yield value;
  }
}

std::generator<int> triangular_generator() {
  int triangular = 0, i = 1;
  while (true) {
    triangular += i;
    co_yield triangular;
    i++;
  }
  std::unreachable();
}

std::generator<std::pair<int, int>> group_factor_integer(int n) {
  int count = 0, last = 0;
  for (auto p : factor_integer(n)) {
    if (p != last) {
      if (last == 0) {
        count = 1;
      } else {
        co_yield {last, count};
        count = 1;
      }
      last = p;
    } else {
      count++;
    }
  }
  co_yield {last, count};
}

std::generator<std::pair<int, int>> group_factor_integer(int n, const std::vector<int>& primes) {
  int count = 0, last = 0;
  for (auto p : factor_integer(n, primes)) {
    if (p != last) {
      if (last == 0) {
        count = 1;
      } else {
        co_yield {last, count};
        count = 1;
      }
      last = p;
    } else {
      count++;
    }
  }
  co_yield {last, count};
}

int num_of_divisors(int n) {
  int ans = 1;
  for (auto [p, exp] : group_factor_integer(n)) {
    ans *= exp + 1;
  }
  return ans;
}

std::generator<long long> collatz_generator(long long n) {
  while (n != 1) {
    co_yield n;
    if (n % 2 == 0) {
      n /= 2;
    } else {
      n = 3 * n + 1;
    }
  }
  co_yield 1;
}

template <typename T>
T binomial(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  T result = 1;
  for (int i = 0; i < k; i++) {
    result *= n - i;
    result /= i + 1;
  }
  return result;
}

template <typename T>
constexpr T ipow(T base, T exp) {
  T res = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      res *= base;
    }
    base *= base;
    exp /= 2;
  }
  return res;
}

long long sum_of_divisors(long long n) {
  long long ans = 1;
  for (auto [p, exp] : group_factor_integer(n)) {
    ans *= (ipow<long long>(p, exp + 1) - 1) / (p - 1);
  }
  return ans;
}

template <typename T>
T modpow(T base, T exp, T mod) {
  T res = 1;
  base %= mod;
  while (exp > 0) {
    if (exp % 2 == 1) {
      res = res * base % mod;
    }
    base = base * base % mod;
    exp /= 2;
  }
  return res;
}

template <typename T>
constexpr T factorial(T n) {
  T result = 1;
  for (size_t i = 2; i <= static_cast<size_t>(n); i++) {
    result *= i;
  }
  return result;
}

int digits(long long n) { return static_cast<int>(std::floor(std::log10(n))) + 1; }

int digits(mpz_class n) { return n == 0 ? 1 : mpz_sizeinbase(n.get_mpz_t(), 10); }

std::string to_binary_string(int n) {
  std::string binary;
  while (n > 0) {
    binary.push_back((n % 2) + '0');
    n /= 2;
  }
  std::reverse(binary.begin(), binary.end());
  return binary;
}

std::generator<int> sum_of_divisors_generator(int limit) {
  co_yield 0;
  for (int i = 1; i <= limit; i++) {
    co_yield sum_of_divisors(i);
  }
}

template <typename T>
bool prime_test(T value) {
  for (int i = 2; i * i <= value; i++) {
    if (value % i == 0) {
      return false;
    }
  }
  return value > 1;
}

template <typename T>
std::generator<T> pandigital_generator(int n, int start) {
  std::vector<int> digits(n);
  for (int i = 0; i < n; i++) {
    digits[i] = '0' + i + start;
  }
  do {
    T value = static_cast<T>(0);
    for (int digit : digits) {
      value = value * 10 + digit - '0';
    }
    co_yield value;
  } while (std::next_permutation(digits.begin(), digits.end()));
}

template <typename T>
bool is_triangular(T n) {
  T n2 = 2 * n;
  T x = isqrt(n2);
  return x * (x + 1) / 2 == n;
}

long long square(long long n) { return n * n; }

long long triangular(long long n) { return n * (n + 1) / 2; }

long long pentagonal(long long n) { return n * (3 * n - 1) / 2; }

long long hexagonal(long long n) { return n * (2 * n - 1); }

long long heptagonal(long long n) { return n * (5 * n - 3) / 2; }

long long octagonal(long long n) { return n * (3 * n - 2); }

bool is_pentagonal(long long n) {
  long long d = 24 * n + 1;
  long long x = static_cast<long long>(sqrt(d));
  if (x * x != d) {
    return false;
  }
  return (1 + x) % 6 == 0;
}

template <std::size_t N>
consteval auto make_powers10() {
  std::array<long long, N> a{};
  a[0] = 1;
  for (std::size_t i = 1; i < N; ++i) {
    a[i] = a[i - 1] * 10;
  }
  return a;
}

constexpr auto powers10 = make_powers10<10>();

template <std::size_t N>
consteval std::array<int, N> make_factorials() {
  std::array<int, N> a = {};
  for (size_t i = 0; i < N; ++i) {
    a[i] = euler::factorial(i);
  }
  return a;
}

constexpr auto factorials = make_factorials<10>();

constexpr std::pair<int, long long> findsd(long long n) {
  long long d = n - 1;
  int s = 0;
  while ((d & 1) == 0) {
    d >>= 1;
    ++s;
  }
  return {s, d};
}

constexpr bool miller_rabin(long long n, long long a, int s, long long d) {
  if (n < 2) return false;
  long long x = modpow(a, d, n);
  if (x == 1 || x == n - 1) return false;  // probably prime
  for (int r = 1; r < s; ++r) {
    x = modpow(x, 2LL, n);
    if (x == n - 1) return false;  // probably prime
  }
  return true;  // composite
}

bool is_prime_mr(long long n) {
  if (n < 2) return false;
  if (n == 2 || n == 3) return true;

  // choose bases depending on n's range
  const std::vector<long long> bases = [&]() {
    if (n < 2LL)
      return std::vector<long long>{};
    else if (n < 2047LL)
      return std::vector<long long>{2};
    else if (n < 1373653LL)
      return std::vector<long long>{2, 3};
    else if (n < 9080191LL)
      return std::vector<long long>{31, 73};
    else if (n < 25326001LL)
      return std::vector<long long>{2, 3, 5};
    else if (n < 3215031751LL)
      return std::vector<long long>{2, 3, 5, 7};
    else if (n < 4759123141LL)
      return std::vector<long long>{2, 7, 61};
    else if (n < 1122004669633LL)
      return std::vector<long long>{2, 13, 23, 1662803};
    else if (n < 2152302898747LL)
      return std::vector<long long>{2, 3, 5, 7, 11};
    else if (n < 3474749660383LL)
      return std::vector<long long>{2, 3, 5, 7, 11, 13};
    else if (n < 341550071728321LL)
      return std::vector<long long>{2, 3, 5, 7, 11, 13, 17};
    else if (n < 3825123056546413051LL)
      return std::vector<long long>{2, 3, 5, 7, 11, 13, 17, 19, 23};
    /*else if (n < 318665857834031151167461LL)
        return std::vector<long long>{2,3,5,7,11,13,17,19,23,29,31,37};
    else if (n < 3317044064679887385961981LL)
        return std::vector<long long>{2,3,5,7,11,13,17,19,23,29,31,37,41};*/
    else
      throw std::domain_error("n too large for deterministic Miller-Rabin");
  }();

  auto [s, d] = findsd(n);
  for (long long a : bases) {
    if (miller_rabin(n, a, s, d)) return false;  // composite
  }
  return true;  // prime
}

template <typename T>
std::tuple<T, T, T> line_from_two_points(T x0, T y0, T x1, T y1) {
  T a = y0 - y1;
  T b = x1 - x0;
  T c = x1 * y0 - x0 * y1;

  if (b < 0 || (b == 0 && a < 0)) {
    a = -a;
    b = -b;
    c = -c;
  }

  long long g = euler::gcd(euler::gcd(std::llabs(a), std::llabs(b)), std::llabs(c));
  if (g > 1) {
    a /= g;
    b /= g;
    c /= g;
  }

  return {a, b, c};
}

std::generator<std::pair<mpz_class, mpz_class>> convergents(std::generator<long long> coefs) {
  mpz_class h0 = 0, k0 = 1;
  mpz_class h1 = 1, k1 = 0;
  for (int a : coefs) {
    mpz_class hn = a * h1 + h0;
    mpz_class kn = a * k1 + k0;
    co_yield {hn, kn};
    h0 = h1;
    k0 = k1;
    h1 = hn;
    k1 = kn;
  }
}

std::generator<long long> sqrt_coefs(long long n) {
  long long a0 = sqrt(static_cast<long double>(n));
  if (a0 * a0 == n) {
    co_return;
  }
  long long m = 0, d = 1, a = a0, p = 0;
  do {
    m = d * a - m;
    d = (n - m * m) / d;
    co_yield a;
    a = (a0 + m) / d;
    p++;
  } while (true);
  std::unreachable();
}

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

static inline std::string trim(const std::string& s) {
  auto first =
      std::find_if_not(s.begin(), s.end(), [](unsigned char c) { return std::isspace(c); });
  auto last = std::find_if_not(s.rbegin(), s.rend(), [](unsigned char c) {
                return std::isspace(c);
              }).base();
  return first < last ? std::string(first, last) : std::string();
}

std::vector<std::vector<long long>> parse_matrix(const std::string& input) {
  std::vector<std::vector<long long>> mat;
  std::istringstream in(input);
  std::string line;
  while (std::getline(in, line)) {
    line = trim(line);
    if (line.empty()) continue;  // skip blank lines

    std::vector<long long> row;
    std::istringstream lin(line);
    std::string token;
    while (std::getline(lin, token, ',')) {
      token = trim(token);
      row.push_back(std::stoll(token));
    }
    mat.push_back(std::move(row));
  }
  return mat;
}

std::generator<std::pair<mpz_class, mpz_class>> pell(long long D) {
  mpz_class mD{std::to_string(D)};
  for (auto [num, den] : euler::convergents(euler::sqrt_coefs(D))) {
    if (num * num - den * den * mD == 1) {
      co_yield {num, den};
    }
  }
  std::unreachable();
}

int euler_phi(int n) {
  for (auto [p, exp] : euler::group_factor_integer(n)) {
    n = n / p * (p - 1);
  }
  return n;
}

std::generator<std::pair<int, int>> walk_cantor_order() {
  for (int i : std::views::iota(0)) {
    for (int j : std::views::iota(0, i + 1)) {
      if (i % 2 == 0) {
        co_yield {j, i - j};  // Moving downwards
      } else {
        co_yield {i - j, j};  // Moving upwards
      }
    }
  }
}

template <class T>
std::generator<std::tuple<T, T, T>> pythagorean_triples(T N) {
  for (T m = 2; m * m <= N; ++m) {
    for (T n = 1; n < m; ++n) {
      if ((m - n) % 2 == 1 && euler::gcd(m, n) == 1) {
        T a = m * m - n * n;
        T b = 2 * m * n;
        T c = m * m + n * n;
        for (T k = 1; k * c <= N; k++) {
          co_yield {a * k, b * k, c * k};
        }
      }
    }
  }
}

template <typename T>
std::generator<std::tuple<T, T, T>> primitive_pythagorean_triples(T N) {
  for (T m = 2; m * m <= N; ++m) {
    for (T n = 1; n < m; ++n) {
      if ((m - n) % 2 == 1 && euler::gcd(m, n) == 1) {
        T a = m * m - n * n;
        T b = 2 * m * n;
        T c = m * m + n * n;
        co_yield {a, b, c};
      }
    }
  }
}

template <typename T, typename Q>
T multinomial(const Q& counts) {
  T n = 0;
  for (T count : counts) {
    n += count;
  }
  T result = factorial(n);
  for (T count : counts) {
    result /= factorial(count);
  }
  return result;
}

void print_sequence(auto& seq) {
  for (auto e : seq) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}

template <typename T>
std::generator<std::vector<T>> combinations(std::vector<T> elements, int k) {
  const int n = static_cast<int>(elements.size());
  if (k < 0 || k > n) co_return;

  std::vector<int> idx(k);
  std::iota(idx.begin(), idx.end(), 0);

  while (true) {
    std::vector<T> comb;
    comb.reserve(k);
    for (int i : idx) comb.push_back(elements[i]);
    co_yield comb;

    int i = k - 1;
    while (i >= 0 && idx[i] == n - k + i) --i;
    if (i < 0) break;
    ++idx[i];
    for (int j = i + 1; j < k; ++j) idx[j] = idx[j - 1] + 1;
  }
}

}  // namespace euler