#ifndef JULIAN_SERIALIZATION_HPP
#define JULIAN_SERIALIZATION_HPP

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/map.hpp>
#include <boost/assert.hpp>

#include <interestRates/_all_interestRate.hpp>
#include <instruments/_all_instruments.hpp>

  /**
   * @file   serialization.hpp
   * @brief  File contains functions used in serialization process.
   */

  /** \ingroup utils				       
   *
   * \fn void serializeText(T object,std::string file)
   * \brief Serialize object to text file
   * \note Class T must have serialization interface implemented.
   */
template<class T>
void serializeText(T object,std::string file) {
  std::ofstream ofs(file);
  boost::archive::text_oarchive oa(ofs);
  oa << BOOST_SERIALIZATION_NVP(object);
}

  /** \ingroup utils				       
   *
   * \fn void serializeBinary(T object,std::string file)
   * \brief Serialize object to binary file
   * \note Class T must have serialization interface implemented.
   */
template<class T>
void serializeBinary(T object,std::string file) {
  std::ofstream ofs(file);
  boost::archive::binary_oarchive oa(ofs);
  oa << BOOST_SERIALIZATION_NVP(object);
}

  /** \ingroup utils				       
   *
   * \fn void serializeXML(T object,std::string file)
   * \brief Serialize object to xml file
   * \note Class T must have serialization interface implemented.
   */
template<class T>
void serializeXML(T object,std::string file) {
  std::ofstream ofs(file);
  boost::archive::xml_oarchive oa(ofs);
  oa << BOOST_SERIALIZATION_NVP(object);
}


  /** \ingroup utils				       
   *
   * \fn T deserializeText(std::string file)
   * \brief Deserializes object from text  file
   * \note Class T must have serialization interface implemented.
   */
template<class T>
T deserializeText(std::string file) {
  T obj;
  std::ifstream ifs(file);
  BOOST_ASSERT_MSG(ifs.good(),"file does not exists");
  boost::archive::text_iarchive ia(ifs);
  ia >> BOOST_SERIALIZATION_NVP(obj);
  
  return obj;
}

  /** \ingroup utils				       
   *
   * \fn T deserializeBinary(std::string file)
   * \brief Deserializes object from binary file
   * \note Class T must have serialization interface implemented.
   */
template<class T>
T deserializeBinary(std::string file) {
  T obj;
  std::ifstream ifs(file);
  BOOST_ASSERT_MSG(ifs.good(),"file does not exists");
  boost::archive::binary_iarchive ia(ifs);
  ia >> BOOST_SERIALIZATION_NVP(obj);

  return obj;
}

  /** \ingroup utils				       
   *
   * \fn T deserializeXML(std::string file)
   * \brief Deserializes object from xml file
   * \note Class T must have serialization interface implemented.
   */
template<class T>
T deserializeXML(std::string file) {
  T obj;
  std::ifstream ifs(file);
  BOOST_ASSERT_MSG(ifs.good(),"file does not exists");
  boost::archive::xml_iarchive ia(ifs);
  ia >> BOOST_SERIALIZATION_NVP(obj);

  return obj;
}

namespace boost { 
  namespace serialization {
    /** \ brief interfacing serialization function with boost::serialization
	*/
    template<class Archive, class T>
    inline void save(Archive & ar,
		     const julian::SmartPointer< T > &t,
		     const unsigned int  ){
      const T * const tx = t->clone();
      ar << BOOST_SERIALIZATION_NVP(tx);
    }
    /** \ brief interfacing serialization function with boost::serialization
	*/
    template<class Archive, class T>
    inline void load( Archive & ar,
		      julian::SmartPointer< T > &t,
		      const unsigned int ) {
      T *pTarget;
      ar >> BOOST_SERIALIZATION_NVP(pTarget);
      t = *pTarget;
    }
    /** \ brief interfacing serialization function with boost::serialization
	*/
    template<class Archive, class T>
    inline void serialize(Archive & ar,
			  julian::SmartPointer< T > &t,
			  const unsigned int file_version  ){
      boost::serialization::split_free(ar, t, file_version);
    }
  } // namespace serialization
} // namespace boost

#endif

