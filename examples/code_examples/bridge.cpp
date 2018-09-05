#include <iostream>
#include <string>
#include <random>

class YF {
public:
  virtual std::string info();
  virtual ~YF() {
  }
};

class Act360 : public YF {
public:
  std::string info() {
    return " act360";
  }
  ~Act360() {
  }
};

class Act365 : public YF {
public:
  std::string info() {
    return " act365";
  }
  ~Act365() {
  }
};

class ActActIsda : public YF {
public:
  std::string info() {
    return " actact_isda";
  }
  ~ActActIsda() {
  }
};

class Rate {
public:
  Rate(YF* yf): yf_(yf) {}
  virtual std::string info() = 0;

protected:
  YF* getYF() {
    return yf_;
  }

private:
  YF* yf_;
};

class SimpleRate : public Rate {
public:
  SimpleRate(YF* yf): Rate(yf) {}
  std::string info() {
    return "Simple rate" + getYF()->info();
  }
  ~SimpleRate() {
  }
};

class CompoundedRate : public Rate {
public:
  CompoundedRate(YF* yf): Rate(yf) {}
  std::string info() {
    return "Compounded rate" + getYF()->info();
  }
  ~CompoundedRate() {
  }
};


int main() {
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> random_compounding(1, 2);
  std::uniform_int_distribution<int> random_yf(1, 3);

  Rate* rate = 0;
  YF* yf = 0;

  switch (random_yf(e) ) {
  case 1: yf = new Act360;
    break;
  case 2: yf = new Act365;
    break;
  case 3: yf = new ActActIsda;
    break;
  }

  switch (random_compounding(e) ) {
  case 1: rate = new SimpleRate(yf);
    break;
  case 2: rate = new CompoundedRate(yf);
    break;
  }

  std::cout << rate->info();

}
