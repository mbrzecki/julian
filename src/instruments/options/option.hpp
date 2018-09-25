#ifndef JULIAN_OPTION_HPP
#define JULIAN_OPTION_HPP

#include <dates/date.hpp>
#include <vector>
#include <instruments/instrumentAuxiliaryTypes.hpp>
#include <utils/smartPointer.hpp>
#include <marketModels/marketModel.hpp>
#include <mathematics/stochasticProcesses/path.hpp>

namespace julian {

  /**
   * @file   option.hpp
   * @brief  File contains definition of financial option interface.
   */
  
  /** \ingroup options
   *  \brief Class is an abstract interface for single asset financial options.
   *
   */
  class Option {
  public:
    /** \brief Calculates payoff at expiry
     */
    virtual double payoff(double) const = 0;

    /** \brief returns expiry date
     */
    virtual Date getExpiry() const = 0;

    /** \brief returns maturity date
     */
    virtual Date getMaturity() const = 0;

    /** \brief returns strike
     *
     * \warning Returning strike is used to calculate the implied volatility, Exotic options may not have strike defined. But also implied volatility have no sense for exotic options. For exotic options this method should return the nan symbol.  
     *
     */
    virtual double getStrike() const = 0;

    /** \brief add fixing to option's schedule
     */
    virtual void recordFixing(Date,double); 
    
    /*! \name Monte Carlo Pricer 
     */
    //@{
    /** \brief calculates the option value basing on the paths provided by Monte Carlo Pricer
     */
    virtual double prizePaths(std::vector<Path> path, double df) const = 0;
    
    //@}


    /*! \name Analytical Pricer 
     */
    //@{
    
    /** \brief calculates the price of option using market model provided
     */
    virtual double prizeAnalytically(const SmartPointer<MarketModel>&) const = 0;
    //@}

    /** \brief Virtual copy constructor
     */
    virtual Option* clone() const = 0;

    /** \brief destructor
     */
    virtual ~Option(){};
    
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int) {
    }
  };
}  // namespae julian
#endif
