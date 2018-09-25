#ifndef JULIAN_RUNTIMEMEASURMENT_HPP
#define JULIAN_RUNTIMEMEASURMENT_HPP

#include <string>
#include <iostream>
#include <chrono>

namespace julian {

  /**
   * @file   RunTimeMeasurment.hpp
   * @brief  File contains definition of class that measures run time.
   */
  
  /** \ingroup utils
   *  \brief Class used to measure run time of the program.
   *
   * RunTimeMeasurment measures time from the creation of the instance to its deconstruction. One can also check the time during the lifetime of the object.
   *
   * All informations are printed in console.
   */

  class RunTimeMeasurment {
  public:
    RunTimeMeasurment();
    void getTime(std::string);
    ~RunTimeMeasurment();
  
  private:
    void timeDisplay(double);
    std::chrono::time_point<std::chrono::system_clock> start_; /*!< \brief Recorded moment of object creation.*/
    std::chrono::time_point<std::chrono::system_clock> last_; /*!< \brief Recorded moment of object last time measurement.*/
  };
}
#endif
