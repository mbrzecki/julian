#ifndef JULIAN_INTERPOLATION_HPP
#define JULIAN_INTERPOLATION_HPP

#include <vector>
#include <algorithm>
#include <string>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace julian {

  /**
   * @file   interpolation.hpp
   * @brief  File contains interface of interpolation methods.
   */
  
  /** \ingroup interpolation
   *
   * \brief Class is an abstract type expressing the concept of interpolation.
   *
   * This class is a interface of all interpolation techniques.
   * 
   * \note Interpolation is only defined for interval defined by the first and the last argument given. The interpolation objects do not extrapolate values outside the interval.
   * \pre x vector must be sorted.
   */
  
  class Interpolation {
  public:
    /**
       \brief Constructor.
       
       Default constructor.
    */
    Interpolation(){};

    /**
       \brief Operator performing calculation.
       
       This operator returns the value of interpolant for x_init argument. Interpolant is fitted to (x,y) points.
    */
    
    virtual double operator()(const std::vector<double>& x,const std::vector<double>& y,const double& x_int) const = 0;
    
    /** \brief Virtual copy constructor
	
	Method is an implementation of virtual copy constructor.
    */
    virtual Interpolation* clone() const = 0;
    
    /** \brief Info about class
	
	Method returns string that containing information about class. 
    */
    virtual std::string info() const = 0;
    
    /** \brief return the minimum number of points required by the interpolation
    */
    virtual unsigned int getMinSize() const = 0;
    
    /** \brief Destructor
     
       Default destructor.
    */
    virtual ~Interpolation(){};
    friend class boost::serialization::access;
  private:
    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int) {
    }
  };
}  //  namespace julian
#endif
