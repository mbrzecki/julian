#include <iostream>
#include <cmath>

//
// Lines contain definition of structure holding parameters of quadratic function
//
struct params_quadratic {
  double a,b,c;
};

// 
// Definition of quadratic function. Note that quadratic function accepts: 
// argument x and void pointer, which is later casted to structure holding function's parameters.
//
double quadratic(double x, void* p) {
  struct params_quadratic * pp = (struct params_quadratic*)p;
  return pp->a*x*x + pp->b*x + pp->c;
}

struct params_sinus {
  double A,w,fi;
};

// 
// Definition of another function. Note that sin_ function has the same 
// interface as the quadratic function, despite being parametrized with different structure.
//
double sinus(double x, void* p) {
  struct params_sinus * pp = (struct params_sinus*)p;
  return pp->A*sin(pp->w*x+pp->fi);
}

// 
// Definition of numerical algorithm. We define structure holding function and its parameters.
// fwdDiff approximates derivative using numerical scheme. 
//
struct functional_struct {
  double (*f)(double, void*);
  void* p;
};

double fwdDiff(functional_struct func, double x) {
  double h = 1e-5;
  return (func.f(x+h, func.p) - func.f(x, func.p)) / h;
}

// 
// We define C++ adapter for functional structure.
// Adapter inherits functional_structure's fields. Apart from those fields it has also a functor object.
// Function call transform functor's operator() with into free function with interface accepted by numerical algorithm fwdDiff.
// The whole Adapter object is passed to fwdDiff by void pointer, which allows passing all data hold by Functor to numerical algorithm.
//
template<typename F>
class Adapter : public functional_struct {
  public:
  Adapter(const F& functor) : functor_(functor) {
    f = &Adapter::call;
    p = this;
  }
  private:
  static double call(double x, void *params) {
    return static_cast<Adapter*>(params)->functor_(x);
  }
  const F& functor_;
};

// 
// Wrapper function casts Adapter to functional_struct and calls numerical algorithm. 
// Thanks to this construction user can call numerical algorithm just by defining lambda expression and calling wrapper function.
// There is no need to define separate parameter structures or free functions. In case more advanced setting up algorithm is more complex.
// Wrapper function helps us to hide this procedure.
//
template<typename F>
double fwdDiffWrapper(F f, double x) {
  Adapter<decltype(f)> adapter(f);
  functional_struct* lambda_f = static_cast<functional_struct*>(&adapter);
  return fwdDiff(*lambda_f, x);
}

int main() {
  params_quadratic params1 {4.0, 2.0, 1.0};

  functional_struct f1;
  f1.f = &quadratic;
  f1.p = &params1;

  params_sinus params2 {2.0, 1.0, 5.0};

  functional_struct f2;
  f2.f = &sinus;
  f2.p = &params2;
  
  std::cout << "Numerical algorithm - using pointer to function\n";
  std::cout << "Quadratic function\t" << fwdDiff(f1, 1.0) << std::endl;
  std::cout << "Sin function\t\t"     << fwdDiff(f2, 1.0) << std::endl;
  
  double a = 4.0, b = 2.0, c  = 1.0;
  auto lambda1 =[a, b, c](double x)->double {
    return a*x*x + b*x + c;
  };
  
  double A = 2.0, w = 1.0, fi = 5.0;
  auto lambda2 =[A, w, fi](double x)->double {
    return A*sin(w*x+fi);
  };
  
  std::cout << "Numerical algorithm - using wrapper\n"; 
  std::cout << "Quadratic function\t" << fwdDiffWrapper(lambda1, 1.0) << std::endl;
  std::cout << "Sin function\t\t"     << fwdDiffWrapper(lambda2, 1.0);
}
