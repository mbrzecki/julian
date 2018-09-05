#ifndef JULIAN_EUROPEANOPT_HPP
#define JULIAN_EUROPEANOPT_HPP

#include <instruments/options/option.hpp>

namespace julian {
  /**
   * @file   europeanOpt.hpp
   * @brief  File contains implementation of  EuropeanOpt.
   */
  /** \ingroup options
   *  \brief Class implements Plain Vanilla European Option 
   *
   * Plain European Option can be only exercise at expiry date. 
   *
   * Pay-off:
   * * In case of Call
   * \f[max(Spot_{T}-K,0)\f]
   * * In case of Put
   * \f[max(K-Spot_{T},0)\f]
   */
  class EuropeanOpt: public Option {
  public:
    /** \brief default constructor
     */
    EuropeanOpt(){};
    /** \brief Constructor
     */
    EuropeanOpt(Date trade_date, Date start_date, Date expiry_date, Date delivery_date ,
		double notional, double strike, CallPut icp);

    double prizeAnalytically(const SmartPointer<MarketModel>&) const override;
    double prizePaths(std::vector<Path>,double) const override;
    
    Date getExpiry() const override;
    Date getMaturity() const override;
    double getStrike() const override;

    void recordFixing(Date,double) override;
    
    CallPut getType() const;
    double payoff(double) const override;

    std::tuple<Date,Date,double,double,CallPut> getSettings() const;
    
    virtual EuropeanOpt* clone() const override;

    /** \brief destructor
     */
    virtual ~EuropeanOpt(){};

    friend std::ostream& operator<<(std::ostream&, EuropeanOpt&);
    friend class boost::serialization::access;
  private:
    Date trade_date_;   /*!< \brief date of trade*/
    Date start_date_;   /*!< \brief date on which payoff is discounted*/
    Date expiry_date_;  /*!< \brief Date of establishing the pay off amount*/
    Date delivery_date_;  /*!< \brief Date when option is settled*/

    double notional_;   /*!< \brief notional of trade*/
    double strike_; /*!< \brief options strike*/
    CallPut icp_; /*!< \brief options type*/

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int){
      boost::serialization::base_object<Option>(*this);
      ar & BOOST_SERIALIZATION_NVP(trade_date_);
      ar & BOOST_SERIALIZATION_NVP(start_date_);
      ar & BOOST_SERIALIZATION_NVP(expiry_date_);
      ar & BOOST_SERIALIZATION_NVP(delivery_date_);

      ar & BOOST_SERIALIZATION_NVP(notional_);
      ar & BOOST_SERIALIZATION_NVP(strike_);
      ar & BOOST_SERIALIZATION_NVP(icp_);
    }
    
  };
} // julian
#endif
