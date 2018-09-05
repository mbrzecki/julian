#ifndef JULIAN_IRCURVEINTERPOLATOR_HPP
#define JULIAN_IRCURVEINTERPOLATOR_HPP

#include <dates/_all_dates.hpp>
#include <vector>
#include <interestRates/interestRate.hpp>
#include <dates/calendars/calendar.hpp>

namespace julian {
  namespace ir {

    /**
     * @file  irCurveInterpolator.hpp
     * @brief File contains definition of interface of interest rate curve interpolator. 
     */
    
    /** \ingroup ir_interpolators
     * \brief Class implements the interface of interest rate curve interpolator
     *
     * The ir::Interpolator is used by ir::InterpolatedCurve. Thanks to delegating the interpolation 
     * to separate hierarchy of classes we achieve flexibility of defining the curves.  
     *
     */

    class Interpolator {
    public:
      Interpolator(){};

      /** \brief interpolates curve for a given date 
       */
      virtual double operator()(const Calendar&, const InterestRate&, const Date&,
				const std::vector<Date>&, const std::vector<double>&, const Date&) const = 0;
      
      /** \brief virtual copy constructor 
       */
      virtual Interpolator* clone() const = 0;

      /** \brief destructor
       */
      virtual ~Interpolator(){};
      
      /** \brief returns name of a class 
       */
      virtual std::string info() const =0;
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
