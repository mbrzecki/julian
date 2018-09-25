#ifndef JULIAN_BOND_HPP
#define JULIAN_BOND_HPP

#include <dates/_all_dates.hpp>
#include <utils/utils.hpp>
#include <marketData/interestRateCurves/irCurve.hpp>

namespace julian {
  /**
   * @file   bond.hpp
   * @brief  File contains interface for all bond instruments.
   */
   
/** \ingroup bonds
 * \brief Class is an abstract class expressing the concept of bonds. 
 *
 * Class implements the interface for bonds.  
 */
  
  class Bond {
  public:
    /** \brief constructor
     */
    Bond(){};

    /** \brief prize bonds
     * \param curve Interest rate curve used to discount CFs
     * \return price of bonds
     */
    virtual double prize(const SmartPointer<ir::Curve>& curve) const = 0;

    /** \brief prize bonds
     * \param discounting_curve Interest rate curve used to discount CFs
     * \param projection_curve Interest rate curve used to estimate floating CFs
     * \return price of bonds
     */
    virtual double prize(const SmartPointer<ir::Curve>& discounting_curve,
			 const SmartPointer<ir::Curve>& projection_curve) const = 0;
    
    /** \brief bond valuation
     * \param curve Interest rate curve used to discount CFs
     */
    virtual void valuation(const SmartPointer<ir::Curve>& curve) const = 0;

    /** \brief bond valuation
     * \param discounting_curve Interest rate curve used to discount CFs
     * \param projection_curve Interest rate curve used to estimate floating CFs
     */
    virtual void valuation(const SmartPointer<ir::Curve>& discounting_curve,
			   const SmartPointer<ir::Curve>& projection_curve) const = 0;

    /** \brief returns the bond's principal  
     */
    virtual double getPrincipal() const = 0;
    
    /** \brief returns the bond's maturity  
     */
    virtual Date getDate() const = 0;

    /** \brief destructor
     */
    virtual ~Bond(){};

    /** \brief virtual copy constructor
     */
    virtual Bond* clone() const = 0;
  private:
  };
}

#endif
