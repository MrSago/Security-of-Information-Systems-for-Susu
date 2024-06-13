/*
  Lab1: Password Generator
  Gordeev Alexander Sergeevich, KE-401
*/

#include <cmath>
#include <cstdint>
#include <iostream>
#include <random>

constexpr std::string GenAlphabet(char start, char end) {
  std::string result;
  result.reserve(end - start + 1);
  for (char i = start; i <= end; ++i) {
    result.push_back(i);
  }
  return result;
}

class PasswordGenerator {
 private:
  const double propability_;
  const int velocity_;
  const int time_;
  const std::string alphabet_;
  const uint64_t S_min_;

  uint64_t S_;
  int lenght_;

  std::random_device rd_;
  std::mt19937 gen_;
  std::uniform_int_distribution<int> uid_;

 public:
  PasswordGenerator(double propability, int velocity, int time,
                    int alphabet_bitmask)
      : propability_(propability),
        velocity_(velocity),
        time_(time),
        alphabet_(GetAlphabetFromBitmask(alphabet_bitmask)),
        S_min_(std::ceil(velocity * time / propability)),
        gen_(rd_()),
        uid_(0, alphabet_.length() - 1) {
    if (alphabet_.length() == 0) {
      throw std::invalid_argument("Alphabet is empty");
    }
    CalcMinLength();
  }

  std::string Generate() {
    std::string result;
    result.reserve(lenght_ + 1);
    for (int i = 0; i < lenght_; ++i) {
      result.push_back(alphabet_[uid_(gen_)]);
    }
    return result;
  }

  std::string GetAlphabet() const { return alphabet_; }
  uint64_t GetSmin() const { return S_min_; }
  uint64_t GetS() const { return S_; }
  int GetLength() const { return lenght_; }

 private:
  std::string GetAlphabetFromBitmask(int alphabet_bitmask) {
    std::string result;
    result += (alphabet_bitmask & (1 << 0) ? GenAlphabet('0', '9') : "");
    result += (alphabet_bitmask & (1 << 1) ? GenAlphabet('a', 'z') : "");
    result += (alphabet_bitmask & (1 << 2) ? GenAlphabet('A', 'Z') : "");
    result += (alphabet_bitmask & (1 << 3)
                   ? GenAlphabet('!', '/') + GenAlphabet(':', '@')
                   : "");
    return result;
  }

  void CalcMinLength() {
    for (S_ = 0, lenght_ = 1; S_ < S_min_;) {
      S_ = std::pow(alphabet_.length(), ++lenght_);
    }
  }
};

int main() {
  // Variant #2
  constexpr double P = 1e-5;       // 10**(-5)
  constexpr int V = 3;             // passwords/minute
  constexpr int T = 10 * 24 * 60;  // minutes

  std::cout << "Lab1: Password Generator\n";
  std::cout << "Gordeev Alexander Sergeevich, KE-401\n\n";

  std::cout << "Variant #2\n";
  std::cout << "P = " << P << '\n';
  std::cout << "V = " << V << '\n';
  std::cout << "T = " << T << "\n\n";

  PasswordGenerator generator(P, V, T, 0b0001);

  uint64_t S_min = generator.GetSmin();
  uint64_t S = generator.GetS();
  std::string A = generator.GetAlphabet();
  int L = generator.GetLength();

  std::cout << "Alphabet: " << A << '\n';
  std::cout << "Length: " << A.length() << "\n\n";

  std::cout << "S* <= S = A**L" << '\n';
  std::cout << S_min << " <= " << S << " = " << A.length() << "**" << L
            << "\n\n";

  std::cout << "Password examples:\n";
  for (int i = 0; i < 10; ++i) {
    std::cout << generator.Generate() << '\n';
  }

  return 0;
}
