#include <iostream>
#include <string>

//
// Simple option that will be created using builder pattern
//
class Option {
public:
  Option() {}
  Option(std::string type, double strike, double tenor):
    type_(type), strike_(strike), tenor_(tenor) {}
  
  void info() const {
    std::cout << "\nType \t" << type_
	      << "\nStrike \t" << strike_
	      << "\nTenor \t" << tenor_ << std::endl;
  }
private:
  std::string type_;
  double strike_;
  double tenor_;
};


class BuildOption {
public:
  BuildOption():
    type_("Call"), strike_(1.0), tenor_(1.0) {}
//
// This method are used to pass objects or literals that will be used to build option
//
  BuildOption& withType(std::string input) {
    type_ = input;
    return *this;
  }
  BuildOption& withStrike(double input) {
    strike_ = input;
    return *this;
  }
  BuildOption& withTenor(double input) {
    tenor_ = input;
    return *this;
  }
//
// Conversion  operator creates option from builder. In this method we can perform any calculations needed to build option.
//
  operator Option() {
    return Option(type_, strike_, tenor_);
  }
private:
  std::string type_;
  double strike_;
  double tenor_;
};

int main() {
  Option option1 = BuildOption()
    .withType("Put")
    .withStrike(1.1)
    .withTenor(1.5);

  Option option2 = BuildOption()
    .withTenor(1.5);

  Option option3 = BuildOption()
    .withStrike(0.8)
    .withTenor(1.5);
  
  option1.info();
  option2.info();
  option3.info();
}
