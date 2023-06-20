#include <iostream>
#include <string>
#include <vector>

// Абстрактний клас стратегії пошуку копій
class PlagiarismCheckerStrategy {
public:
  virtual bool checkPlagiarism(const std::string& code1, const std::string& code2) = 0;
};

// Реалізація стратегії, яка порівнює два коди символ за символом
class CharacterComparisonStrategy : public PlagiarismCheckerStrategy {
public:
  bool checkPlagiarism(const std::string& code1, const std::string& code2) override {
    // Логіка порівняння коду посимвольно
    // Повертає true, якщо виявлено копію, інакше - false
    return code1 == code2;
  }
};

// Реалізація стратегії, яка використовує алгоритм порівняння хешів двох кодів
class HashComparisonStrategy : public PlagiarismCheckerStrategy {
public:
  bool checkPlagiarism(const std::string& code1, const std::string& code2) override {
    // Логіка порівняння хешів коду
    // Повертає true, якщо виявлено копію, інакше - false
    return getCodeHash(code1) == getCodeHash(code2);
  }

  std::size_t getCodeHash(const std::string& code) {
    // Логіка обчислення хешу коду
    // Повертає хеш коду
    return std::hash<std::string>{}(code);
  }
};

// Клас користувача, який використовує стратегію для пошуку копій
class PlagiarismChecker {
private:
  PlagiarismCheckerStrategy* strategy;

public:
  PlagiarismChecker(PlagiarismCheckerStrategy* strategy) : strategy(strategy) {}

  void setStrategy(PlagiarismCheckerStrategy* newStrategy) {
    strategy = newStrategy;
  }

  bool isPlagiarized(const std::string& code1, const std::string& code2) {
    return strategy->checkPlagiarism(code1, code2);
  }
};

int main() {
  std::string code1 = "function add(a, b) { return a + b; }";
  std::string code2 = "function multiply(x, y) { return x * y; }";
  std::string code3 = "function add(a, b) { return a + b; }";

  PlagiarismChecker checker(new CharacterComparisonStrategy());
  bool isPlagiarized = checker.isPlagiarized(code1, code2);
  std::cout << "Is code1 plagiarized from code2? " << (isPlagiarized ? "Yes" : "No") << std::endl;

  checker.setStrategy(new HashComparisonStrategy());
  isPlagiarized = checker.isPlagiarized(code1, code3);
  std::cout << "Is code1 plagiarized from code3? " << (isPlagiarized ? "Yes" : "No") << std::endl;

  return 0;
}
