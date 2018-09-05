#include <juliant.hpp>
/**
 * \example simulatedAnnealingExample.cpp 
 * \brief This example show how to use simulated annealing algorithm to find  minimum. We used Rosenbrock function as test function.
 *
 * Rosenbrock function is a non-convex function, introduced by Howard H. Rosenbrock in 1960, which is used as a performance test problem for optimization algorithms.[1] It is also known as Rosenbrock's valley or Rosenbrock's banana function. See below.
 * \f[f(x,y)=(a-x)^{2}+b(y-x^{2})^{2}\f]
 * @image html rosenbrock.png
 * It has a global minimum at \f$ (x,y)=(a,a^{2})\f$.  
 *
 * Below we see output of programme
 * @verbinclude simulatedAnnealingExample.dox 
 */
 
using namespace julian;

int main() {
  //
  // Setting random number generator
  //
  Tausworthe rng;
  UniformDistribution u(-1.0, 1.0);
  CustomRandomVariable r(u, rng);
  
  //
  // Setting simulated annealing 
  //
  SimulatedAnnealing sim(rng, r);
  sim.setExponentialCooling(100.0, 0.05, 0.02);

  for (double a = 1.0; a < 10.0; a += 0.5) {
	  
    auto rosenbrock = [a](std::vector<double> x)->double {
      return std::pow(a-x.at(0), 2) + 100.0*std::pow(x.at(1)-std::pow(x.at(0), 2), 2);
    };
    //
    // Defining distribution for probability accept. We choose Boltzmann distribution
    //
    auto boltzmann = [](double E, double E_new, double T)->double {
      return -(E_new-E) / T;
    };

    //
    // Setting initial guess and solving optimization problem
    //	
    std::vector<double> x_init {10.0, 10.0};
    auto res = sim.calculate(rosenbrock, boltzmann, x_init, 100000);
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "a = " << a << std::endl;
    std::cout << "Simulation annealing solution " << res[0] << " " << res[1] << std::endl;
    std::cout << "Analytic solution             " << a << " " << a*a << std::endl << std::endl;
  }
}
