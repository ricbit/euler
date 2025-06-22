// Compile with:
// g++-14 -std=c++23 -march=native -O3 -Wall first.cc -o first -ltbb -lgmpxx -lgmp

#include <iostream>
#include <chrono>
#include <set>
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
#include <unordered_set>
#include <gmpxx.h>

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

class P003 : public Solution {
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
    }
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

template<typename T>
std::generator<T> parse_numbers(const std::string& grid) {
  std::istringstream iss(grid);
  T value;
  while (iss >> value) {
    co_yield value;
  }
}

class P011 : public Solution {
  public:
  std::string solve() override {
    std::vector<int> numbers = fill_vector(parse_numbers<int>(source_grid));
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

std::generator<int> triangular_generator() {
  int triangular = 0, i = 1; 
  while (true) {
    triangular += i;
    co_yield triangular;
    i++;
  }
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

int num_of_divisors(int n) {
  int ans = 1;
  for (auto [p, exp] : group_factor_integer(n)) {
    ans *= exp + 1;
  }
  return ans;
}

class P012 : public Solution {
  public:
  std::string solve() override {
    for (int t : triangular_generator()) {
      if (num_of_divisors(t) > 500) {
        return std::to_string(t);      
      }
    }
    std::unreachable();
  }
};

class P013 : public Solution {
  public:
  std::string solve() override {
    auto numbers = fill_vector<mpz_class>(parse_numbers<mpz_class>(source_numbers));
    mpz_class sum = std::accumulate(numbers.begin(), numbers.end(), mpz_class(0));
    std::ostringstream oss;
    oss << sum;
    return oss.str().substr(0, 10);
  }
  private:
  std::string source_numbers = R"(
37107287533902102798797998220837590246510135740250
46376937677490009712648124896970078050417018260538
74324986199524741059474233309513058123726617309629
91942213363574161572522430563301811072406154908250
23067588207539346171171980310421047513778063246676
89261670696623633820136378418383684178734361726757
28112879812849979408065481931592621691275889832738
44274228917432520321923589422876796487670272189318
47451445736001306439091167216856844588711603153276
70386486105843025439939619828917593665686757934951
62176457141856560629502157223196586755079324193331
64906352462741904929101432445813822663347944758178
92575867718337217661963751590579239728245598838407
58203565325359399008402633568948830189458628227828
80181199384826282014278194139940567587151170094390
35398664372827112653829987240784473053190104293586
86515506006295864861532075273371959191420517255829
71693888707715466499115593487603532921714970056938
54370070576826684624621495650076471787294438377604
53282654108756828443191190634694037855217779295145
36123272525000296071075082563815656710885258350721
45876576172410976447339110607218265236877223636045
17423706905851860660448207621209813287860733969412
81142660418086830619328460811191061556940512689692
51934325451728388641918047049293215058642563049483
62467221648435076201727918039944693004732956340691
15732444386908125794514089057706229429197107928209
55037687525678773091862540744969844508330393682126
18336384825330154686196124348767681297534375946515
80386287592878490201521685554828717201219257766954
78182833757993103614740356856449095527097864797581
16726320100436897842553539920931837441497806860984
48403098129077791799088218795327364475675590848030
87086987551392711854517078544161852424320693150332
59959406895756536782107074926966537676326235447210
69793950679652694742597709739166693763042633987085
41052684708299085211399427365734116182760315001271
65378607361501080857009149939512557028198746004375
35829035317434717326932123578154982629742552737307
94953759765105305946966067683156574377167401875275
88902802571733229619176668713819931811048770190271
25267680276078003013678680992525463401061632866526
36270218540497705585629946580636237993140746255962
24074486908231174977792365466257246923322810917141
91430288197103288597806669760892938638285025333403
34413065578016127815921815005561868836468420090470
23053081172816430487623791969842487255036638784583
11487696932154902810424020138335124462181441773470
63783299490636259666498587618221225225512486764533
67720186971698544312419572409913959008952310058822
95548255300263520781532296796249481641953868218774
76085327132285723110424803456124867697064507995236
37774242535411291684276865538926205024910326572967
23701913275725675285653248258265463092207058596522
29798860272258331913126375147341994889534765745501
18495701454879288984856827726077713721403798879715
38298203783031473527721580348144513491373226651381
34829543829199918180278916522431027392251122869539
40957953066405232632538044100059654939159879593635
29746152185502371307642255121183693803580388584903
41698116222072977186158236678424689157993532961922
62467957194401269043877107275048102390895523597457
23189706772547915061505504953922979530901129967519
86188088225875314529584099251203829009407770775672
11306739708304724483816533873502340845647058077308
82959174767140363198008187129011875491310547126581
97623331044818386269515456334926366572897563400500
42846280183517070527831839425882145521227251250327
55121603546981200581762165212827652751691296897789
32238195734329339946437501907836945765883352399886
75506164965184775180738168837861091527357929701337
62177842752192623401942399639168044983993173312731
32924185707147349566916674687634660915035914677504
99518671430235219628894890102423325116913619626622
73267460800591547471830798392868535206946944540724
76841822524674417161514036427982273348055556214818
97142617910342598647204516893989422179826088076852
87783646182799346313767754307809363333018982642090
10848802521674670883215120185883543223812876952786
71329612474782464538636993009049310363619763878039
62184073572399794223406235393808339651327408011116
66627891981488087797941876876144230030984490851411
60661826293682836764744779239180335110989069790714
85786944089552990653640447425576083659976645795096
66024396409905389607120198219976047599490197230297
64913982680032973156037120041377903785566085089252
16730939319872750275468906903707539413042652315011
94809377245048795150954100921645863754710598436791
78639167021187492431995700641917969777599028300699
15368713711936614952811305876380278410754449733078
40789923115535562561142322423255033685442488917353
44889911501440648020369068063960672322193204149535
41503128880339536053299340368006977710650566631954
81234880673210146739058568557934581403627822703280
82616570773948327592232845941706525094512325230608
22918802058777319719839450180888072429661980811197
77158542502016545090413245809786882778948721859617
72107838435069186155435662884062257473692284509516
20849603980134001723930671666823555245252804609722
53503534226472524250874054075591789781264330331690  
  )";
};

std::generator<long long> collatz_generator(long long n) {
  while (n != 1) {
    co_yield n;
    if (n % 2 == 0) {
      n /= 2;
    } else {
      n = 3 * n + 1;
    }
  }
  co_yield 1; // Yield the last element
}

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
      for (long long value : collatz_generator(i)) {
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
      for (long long value : collatz_generator(i)) {
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

template<typename T>
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

class P015 : public Solution {
  public:
  std::string solve() override {
    long long paths = binomial<long long>(40, 20);
    return std::to_string(paths);
  }
};

class P016 : public Solution {
  public:
  std::string solve() override {
    mpz_class power = mpz_class{1} << 1000;
    auto digits = fill_vector(digit_generator(power.get_str()));
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
    return std::count_if(number.begin(), number.end(), [](char c) {
      return std::isalpha(c);
    });
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
    "one",     "two",      "three",   "four",    "five",
    "six",     "seven",    "eight",   "nine",    "ten",
    "eleven",  "twelve",   "thirteen","fourteen","fifteen",
    "sixteen", "seventeen","eighteen","nineteen","twenty"
  };

  const std::array<std::string_view, 10> tens_names = {
    "",       "",       "twenty", "thirty", "forty",
    "fifty",  "sixty",  "seventy","eighty", "ninety"
  };
};

std::vector<std::vector<int>> parse_triangle(const std::string& source) {
  std::vector<std::vector<int>> triangle;
  for (size_t line = 0, i = 0; auto value : parse_numbers<int>(source)) {
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

class P018 : public Solution {
  public:
  std::string solve() override {
    auto grid = parse_triangle(triangle_source);
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
  std::string triangle_source = R"(
75
95 64
17 47 82
18 35 87 10
20 04 82 47 65
19 01 23 75 03 34
88 02 77 73 07 63 67
99 65 04 28 06 16 70 92
41 41 26 56 83 40 80 70 33
41 48 72 33 47 32 37 16 94 29
53 71 44 65 25 43 91 52 97 51 14
70 11 33 28 77 73 17 78 39 68 17 57
91 71 52 38 17 14 91 43 58 50 27 29 48
63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
)";
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
    auto digits = fill_vector(digit_generator(factorial.get_str()));
    int sum = std::accumulate(digits.begin(), digits.end(), 0);
    return std::to_string(sum);
  }
};

template<typename T>
T ipow(T base, T exp) {
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

int sum_of_divisors(int n) {
  int ans = 1;
  for (auto [p, exp] : group_factor_integer(n)) {
    ans *= (ipow(p, exp + 1) -  1) / (p - 1);
  }
  return ans;
}

class P021 : public Solution {
  public:
  P021(const std::vector<int>& divisor_sums) : divisor_sums(divisor_sums) {
  }
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
    return std::accumulate(name.begin(), name.end(), 0, [](int acc, char c) {
      return acc + (std::toupper(c) - 'A' + 1);
    });
  }
};

class P023 : public Solution {
  public:
  P023(const std::vector<int>& divisor_sums) : divisor_sums(divisor_sums) {
  }
  std::string solve() override {
    const int limit = 28123;
    std::vector<int> abundants;
    for (int i = 1; i <= limit; i++) {
      if (divisor_sums[i] - i > i) {
        abundants.push_back(i);
      }
    }

    std::vector<bool> non_abundant_sum(limit + 1, true);
    for (size_t i = 0; i <= abundants.size(); i++) {
      for (size_t j = i; j <= abundants.size(); j++) {
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
  P027(const std::vector<int>& primes) : primes(primes 
    | std::ranges::views::filter([](int p) { return p < 1000; })
    | std::ranges::to<std::unordered_set<int>>()) {
  }
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
    int sum = 1, current = 1;;
    for (int i = 2; i <= 1001; i += 2) {
      for (int j = 0; j < 4; j++) {
        current += i;
        sum += current;
      }
    }
    return std::to_string(sum);
  }
};

template<typename T>
T modpow(T base, T exp, T prime) {
  T res = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      res = res * base % prime;
    }
    base = base * base % prime;
    exp /= 2;
  }
  return res;
}

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
        digit_sum += ipow(value % 10, 5);
        value /= 10;
      }
      if (digit_sum == i) {
        sum += i;
      }
    }
    return std::to_string(sum);
  }
};

std::generator<int> sum_of_divisors_generator(int limit) {
  co_yield 0;
  for (int i = 1; i <= limit; i++) {
    co_yield sum_of_divisors(i);
  }
}

int main() {
  std::vector<int> primes = fill_vector(sieve_generator(2'000'000));
  std::vector<int> divisor_sums = fill_vector(sum_of_divisors_generator(28'123));
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
  };

  std::vector<std::pair<std::string, long long>> results(solutions.size());
  std::transform(
    std::execution::par,
    solutions.begin(), solutions.end(),
    results.begin(),
    [](const auto& solution) {
      auto t0 = std::chrono::steady_clock::now();
      std::string result = solution->solve();
      auto t1 = std::chrono::steady_clock::now();
      long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
      return make_pair(result, ms);
    }
  );

  for (int i = 1; auto& r : results) {
    std::cout << i++ << "\t" << r.second << "ms\t" << r.first << "\n";
  }
  return 0;
}
