#include <iostream>
#include <string>
#include <random>

class Interpolation {
public:
  virtual std::string info() = 0;
  virtual ~Interpolation(){};
};

class LinearInterpolation : public Interpolation {
public:
  std::string info() override {
    return "linear interpolation";
  }
  ~LinearInterpolation() {}
};

class QuadraticInterpolation : public Interpolation {
public:
  std::string info() override {
    return "quandratic interpolation";
  }
  ~QuadraticInterpolation() {}
};

class SwapCurve {
public:
  SwapCurve(Interpolation* interpolation):
    interpolation_(interpolation) {}
  void info() {
    std::cout << "Swap curve using "
	      << interpolation_->info();
  }
private:
  Interpolation* interpolation_;
};

int main() {
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> random_interpolation(1, 2);

  Interpolation* interpolation;
  switch (random_interpolation(e)) {
  case 1: interpolation = new LinearInterpolation;
    break;
  case 2: interpolation = new QuadraticInterpolation;
    break;
  }
  
  SwapCurve curve(interpolation);
  curve.info();
}
