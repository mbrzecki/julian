#ifndef JULIAN_INSTRUMENTAUXILIARYTYPES_HPP
#define JULIAN_INSTRUMENTAUXILIARYTYPES_HPP

#include <iostream>
#include <string>

namespace julian {

  /**
   * @file   instrumentAuxiliaryTypes.hpp
   * @brief  File contains types common to all financial instruments.
   */
  
  /** \brief Enumeration defining option types
   */  
  enum CallPut {
    CALL = 1,
    PUT = -1
  };

  /** \brief interface used by Boost serialization library
   */
  template<class Archive>
  void serialize(Archive & ar, CallPut & g, const unsigned int version) {
  }

}  // namespace julian
#endif 
