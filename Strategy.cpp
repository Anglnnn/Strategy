#include <iostream>
#include <string>
#include <vector>

// ����������� ���� ������㳿 ������ ����
class PlagiarismCheckerStrategy {
public:
  virtual bool checkPlagiarism(const std::string& code1, const std::string& code2) = 0;
};

// ��������� ������㳿, ��� ������� ��� ���� ������ �� ��������
class CharacterComparisonStrategy : public PlagiarismCheckerStrategy {
public:
  bool checkPlagiarism(const std::string& code1, const std::string& code2) override {
    // ����� ��������� ���� �����������
    // ������� true, ���� �������� ����, ������ - false
    return code1 == code2;
  }
};

// ��������� ������㳿, ��� ����������� �������� ��������� ����� ���� ����
class HashComparisonStrategy : public PlagiarismCheckerStrategy {
public:
  bool checkPlagiarism(const std::string& code1, const std::string& code2) override {
    // ����� ��������� ����� ����
    // ������� true, ���� �������� ����, ������ - false
    return getCodeHash(code1) == getCodeHash(code2);
  }

  std::size_t getCodeHash(const std::string& code) {
    // ����� ���������� ���� ����
    // ������� ��� ����
    return std::hash<std::string>{}(code);
  }
};

// ���� �����������, ���� ����������� �������� ��� ������ ����
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
