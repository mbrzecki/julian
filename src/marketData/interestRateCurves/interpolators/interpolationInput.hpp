#ifndef JULIAN_INTERPOLATIONINPUTS_HPP
#define JULIAN_INTERPOLATIONINPUTS_HPP

#include <vector>
#include <algorithm>
#include <dates/_all_dates.hpp>
#include <interestRates/interestRate.hpp>

namespace julian {
  namespace ir {
    /**
     * @file   interpolationInput.hpp
     * @brief  File contains interface of method that provides inputs to interpolation.
     */
    
    /** \ingroup interpolators
     * \brief Class is an abstract class that represents the subject of interpolation performed in swap curve operations. 
     *
     * This class is a interface of all interpolation inputs (compare ir::CompoundedInterpolator).
     *  
     */

    class InterpolationInput {
    public:
      /**
	 \brief Constructor.
	 
	 Default constructor.
      */
      InterpolationInput(){};
      
      /**
	 \brief Calculates inputs form DF
	 
	 Swap curve maintains interest rate term structure as vector of default factors. 
	 To perform an interpolation according to given convention (interpolation of zcr, fwd rates etc) one must transform DF to appropriate inputs. 
	 This method performs those calculations.
	 
	 \param DF1 Discount factor for date1
	 \param DF2 Discount factor for date2
	 \param rate Input gives the convention of interest rate (compounding and year fraction)
	 \param date0 today date
	 \param date1 middle date
	 \param date2 end date
      */
      virtual double operator()(double DF1,double DF2,InterestRate rate,Date date0,Date date1,Date date2) const = 0;
      
      /**
	 \brief Calculate DF form result of interpolation
	 
	 Method recalculates DF from interpolation inputs.
	 
	 \param x result of interpolation
	 \param rate Input gives the convention of interest rate (compounding and year fraction)
	 \param date1 middle date
	 \param date2 end date
      */
      virtual double getDF(double x,InterestRate rate,Date date1,Date date2) const = 0;
      
      /** \brief Virtual copy constructor
	  
	  Method is an implementation of virtual copy constructor.
      */
      virtual InterpolationInput* clone() const = 0;
      
      /** \brief Info about class
	  
	  Method returns string that containing information about class. 
      */
      virtual std::string info() const = 0;
      
      /**\brief Destructor
	 
	 Default destructor.
      */
      virtual ~InterpolationInput(){};
      friend class boost::serialization::access;
    private:

      /** \brief interface used by Boost serialization library
       */
      template<class Archive>
      void serialize(Archive & , const unsigned int) {
      }
    };
}
}
#endif
