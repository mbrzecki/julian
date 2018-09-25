#ifndef JULIAN_STOCHASTICPROCESS_HPP
#define JULIAN_STOCHASTICPROCESS_HPP

#include <mathematics/stochasticProcesses/path.hpp>
#include <utils/smartPointer.hpp>
#include <mathematics/RNGs/uniformRNG.hpp>

namespace julian {
  /**
   * @file   stochasticProcess.hpp
   * @brief  File contains interface for stochastic processes.
   */
  /** \ingroup stochasticProcesses
   * \brief Class is an abstract type expressing the concept of stochastic process.

   Stochastic process is a mathematical object generating discrete time series (Path) according to certain dynamics.  

   */
  
  class StochasticProcess {
  public:
    /**
       \brief Constructor.
       
       Default constructor.
    */
    StochasticProcess(){};

    /**
       \brief generates path 
       
       * \param initial_value Value of the process for t = 0;
       * \param grid points in time for which the value of process is generated   
       * \param rng random number generator that will be used to generate stochastic process
       * \return path representing time series 
    */
    virtual Path getPath(double initial_value, const TimeGrid& grid, SmartPointer<UniformRNG>& rng) const = 0;

    /**
       \brief generates path 
       
       * \param initial_value Value of the process for t = 0;
       * \param grid points in time for which the value of process is generated   
       * \param rnds random number that will be used to generate the path
       * \return path representing time series 
       */
    virtual Path getPath(double initial_value, const TimeGrid& grid, const std::vector<double>& rnds) const = 0;

    /**
       \brief Virtual copy constructor
    */
    virtual StochasticProcess* clone() const = 0;

    /**
       \brief Destructor.
       
       Default destructor.
    */
    virtual ~StochasticProcess(){};
    
  private:
  };
}  // namespace julian

#endif
