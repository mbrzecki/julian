#ifndef FORMATTERS_HPP
#define FORMATTERS_HPP

#include <string>

namespace julian {
namespace formatter {
	  
  /**
   * @file   formatters.hpp
   * @brief  File contains definition of formatters.
   */
  /** \ingroup utils
   */
    
  std::string currency(double);
  std::string percentage(double);
}  // namespace formatter 
}  // namespace julian
#endif
