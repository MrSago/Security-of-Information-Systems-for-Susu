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
  const std::string alphabet_;
  const double propability_;
  const int velocity_;
  const int time_;
  const uint64_t S_min_;

  uint64_t S_;
  int lenght_;

  std::random_device rd_;
  std::mt19937 gen_;
  std::uniform_int_distribution<int> uid_;

 public:
  PasswordGenerator(std::string alphabet, double propability, int velocity,
                    int time)
      : alphabet_(alphabet),
        propability_(propability),
        velocity_(velocity),
        time_(time),
        S_min_(std::ceil(velocity * time / propability)),
        gen_(rd_()),
        uid_(0, alphabet_.length() - 1) {
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

  uint64_t GetSmin() const { return S_min_; }
  uint64_t GetS() const { return S_; }
  int GetLength() const { return lenght_; }

 private:
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

  const std::string alphabet = GenAlphabet('0', '9') + GenAlphabet('a', 'z') +
                               GenAlphabet('A', 'Z') + GenAlphabet('!', '/') +
                               GenAlphabet(':', '@');

  std::cout << "Alphabet: " << alphabet << '\n';
  std::cout << "Length: " << alphabet.length() << "\n\n";

  PasswordGenerator generator(alphabet, P, V, T);

  std::cout << "S* <= S = A**L" << '\n';
  std::cout << generator.GetSmin() << " <= " << generator.GetS() << " = "
            << alphabet.length() << "**" << generator.GetLength() << "\n\n";

  std::cout << "Password examples:\n";
  for (int i = 0; i < 10; ++i) {
    std::cout << generator.Generate() << '\n';
  }

  return 0;
}
