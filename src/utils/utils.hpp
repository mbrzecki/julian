#ifndef JULIAN_UTILS_HPP
#define JULIAN_UTILS_HPP

#include <iostream>
#include <vector>
#include <dates/date.hpp>
#include <map>
namespace julian {

  /**
   * @file   utils.hpp
   * @brief  File contains small programming tools
   */

   /** \brief Prints the variable
   */
  #define SHOW(x) std::cout <<"\nName: "<< #x << "\n" << x << "\n"

  bool isCloseEnough(double x1, double x2, int n);

  double roundNumber(double,int);
  
  void writeToCsv(std::string file_name, std::map<std::string,std::vector<double> > data);
 
  double convertStr2Dbl(std::string);
  
  std::string convertDbl2Str(double);

  std::vector<double> convertStr2Dbl(std::vector<std::string>);

  std::pair<std::string, std::string> catchDataAndSettingFileNames(int ac, char* av[]);
}
#endif
