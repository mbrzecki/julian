#ifndef JULIAN_SIMULATEDANNEALING_HPP
#define JULIAN_SIMULATEDANNEALING_HPP

#include <cmath>
#include <vector>
#include <utils/smartPointer.hpp>
#include <mathematics/RNGs/uniformRNG.hpp>
#include <mathematics/distributions/randomVariable.hpp>

namespace julian {
  /**
   * @file   simulatedAnnealing.hpp
   * @brief  File contains definition of simulated annealing algorithm.
   */
  
  /** \ingroup minimizers
   *
   * \brief Class implements Simulated Annealing minimizer
   *
   * Simulating annealing is a stochastic algorithm used to solve optimization problems.
   * 
   * Quoting authors of \b Numerical \b Recipes (Chapter 10.9 \cite NumRec):
   * 
   * *At the heart of the method of simulated annealing is an analogy with thermodynamics,
   * specifically with the way that liquids freeze and crystallize, or metals cool
   * and anneal. At high temperatures, the molecules of a liquid move freely with respect
   * to one another. If the liquid is cooled slowly, thermal mobility is lost. The atoms are
   * often able to line themselves up and form a pure crystal that is completely ordered
   * over a distance up to billions of times the size of an individual atom in all directions.
   * This crystal is the state of minimum energy for this system.*
   *
   * The pseudo-code of simulated annealing's algorithm is presented below:
   * \verbatim
    x = initial guess
    x_best = x
    E = f(x)
    E_best = E
    for temperature in cooling_schedule:
        iter = 0
        while iter < maximum number of steps:
           x_new = pick a neighbour of x
           E_new = f(x_new) 
   
           if E_new <= E_best:
               x_best = x_new
               E_best = E_new
           
	       if E_new < E:
               x = x_new
               E = E_new
           else if ( U(0,1) < acceptance_probability(E, E_new, T)
               x = x_new
               E = E_new
            
	   iter++
    \endverbatim 
   * 
   * Cooling schedule is a series of decreasing real numbers. The *temperature* influences the acceptance probability. For more details see \cite coolingschemes
   *
   * The neighbour is picked from distribution provided by user. The distribution expected value should be equal to zero. Usually it is a normal or uniform distribution.
   *
   * Acceptance probability is the probability of moving to a new state. If new steps is a step of lower energy the probability of taking the step is 1.0.
   * In other case the probability is calculated using the acceptance probability function and compared to randomly picked number from standard uniform distribution.
   * It means that algorithm can choose the non-optimal state, what makes the algorithm immune to local minimums. 
   * Larger increases in energy of the system should be less probably. The probability of such steps should decrease with temperature of the system.  
   * Kirkpatrick et al. choose the Boltzmann distribution: \f$p = e^{-(E_{new} - E)/(kT)}\f$ , justified by analogy with the transitions of a physical systems.
   * It also corresponds to the Metropolis–Hastings algorithm (see \cite hastings). The implemented algorithm enables usage of any acceptance probability. 
   *
   * For more details see also: \cite physicsmontecarlo \cite Sherer \cite simAnneal1 
   */

  class SimulatedAnnealing {
  public:
    /** \brief Constructor
     */
    SimulatedAnnealing(SmartPointer<UniformRNG> rng, SmartPointer<RandomVariable> rand):
      step_(rand), rng_(rng) {}


    void setCoolingSchedule(const std::vector<double>& cooling_schedule);
    void setLinearCooling(double Tstart, double Tend, double param);
    void setExponentialCooling(double Tstart, double Tend, double param);

    template<typename F, typename PA>
    double calculate(F f,PA prob_accept,double x_initial, int iters_per_t);    
    template<typename F, typename PA>
    std::vector<double> calculate(F f,PA prob_accept,std::vector<double> x_initial, int iters_per_t);

    double takeStep(double x);
    std::vector<double> takeStep(std::vector<double> x);
    /** \brief Destructor
     */
    ~SimulatedAnnealing(){}
  private:
    SmartPointer<RandomVariable> step_; /*!< \brief Distribution used in picking of neighbour state*/
    SmartPointer<UniformRNG> rng_; /*!< \brief Random number generator used in acceptance of new state*/
    std::vector<double> cooling_schedule_; /*!< \brief Cooling schedule*/
  };
  
  /** \brief Method finds the minimum of provided function 
   *
   * \param f One-dimensional function which optimum we are looking for. f should be a functor.
   * \param prob_accept Probability acceptance function
   * \param x_initial Initial guess
   * \param iters_per_t Number of iterations taken for each temperature value
   * \returns the x for which function f obtains its minimum
   */
  template<typename F, typename PA>
  double SimulatedAnnealing::calculate(F f,PA prob_accept, double x_initial, int iters_per_t) { 
    double x = x_initial;
    double x_best = x;
    double x_new;
    
    double E = f(x_initial); 
    double E_best = E;
    double E_new;
    
    for (auto T : cooling_schedule_) {
      for (int iter = 0; iter < iters_per_t; iter++) {
	x_new = takeStep(x);
	E_new = f(x_new);
	if (E_new <= E_best) {
	  x_best = x_new;
	  E_best = E_new;
	}
	
	if (E_new < E) {
	  x = x_new;
	  E = E_new;
	} else if ( rng_->getRandom() < prob_accept(E, E_new, T)) { 
	  x = x_new;
	  E = E_new;
	}
      }
    }
    return x_best;
  }

  /** \brief Method finds the minimum of provided function 
   *
   * \param f Multi-dimensional function which optimum we are looking for. f should be a functor.
   * \param prob_accept Probability acceptance function
   * \param x_initial Initial guess
   * \param iters_per_t Number of iterations taken for each temperature value
   * \returns the x for which function f obtains its minimum
   */
  template<typename F, typename PA>
  std::vector<double> SimulatedAnnealing::calculate(F f, PA prob_accept, std::vector<double> x_initial, int iters_per_t) {
    std::vector<double> x = x_initial;
    std::vector<double> x_best = x;
    std::vector<double> x_new;
    
    double E = f(x_initial); 
    double E_best = E;
    double E_new;
        
    for (auto T : cooling_schedule_) {
      for (int iter = 0; iter < iters_per_t; iter++) {
	x_new = takeStep(x);
	E_new = f(x_new);
	
	if (E_new <= E_best) {
	  x_best = x_new;
	  E_best = E_new;
	}
	
	if (E_new < E) {
	  x = x_new;
	  E = E_new;
	} else if ( rng_->getRandom() < prob_accept(E, E_new, T)) { 
	  x = x_new;
	  E = E_new;
	}
      }
    }
    
    return x_best;
  }
}  // namespace julian

#endif /* SIMULATEDANNEALING_HPP */
