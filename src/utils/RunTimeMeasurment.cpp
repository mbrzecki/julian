#include <utils/RunTimeMeasurment.hpp>
#include <cmath>
#include <iomanip>
#include <string>

namespace julian {

  /** \brief Constructor
   *
   * Constructor records the moment when the object was created. 
   */

  RunTimeMeasurment::RunTimeMeasurment() {
    start_ = std::chrono::system_clock::now();
    last_  = start_;
  }

  /** \brief Records time 
   *
   * Prints the time that passed from the moment the object's creation and time that passed from last measurement. One can add a commentary that will be printed on console.
   */

  void RunTimeMeasurment::getTime(std::string s = "") {
    std::chrono::time_point<std::chrono::system_clock> now;
    now = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = now-start_;
    double time_from_start = elapsed_seconds.count();

    elapsed_seconds = now-last_;
    double time_from_last = elapsed_seconds.count();

    std::cout << "\n**********************************\n";
    std::cout << "FromStart: ";
    timeDisplay(time_from_start);
    std::cout << "\nFromLastMeasure: ";
    timeDisplay(time_from_last);
    std::cout << "\nComment: " << s;
    std::cout << "\n**********************************\n\n";
    last_ = now;
  }

  /** \brief Destructor
   *
   * Destructor prints the length of lifetime of the object. 
   */
  RunTimeMeasurment::~RunTimeMeasurment() {
    std::chrono::time_point<std::chrono::system_clock> end;
    end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end-start_;
  double time = elapsed_seconds.count();
  std::cout << "\n\n\n\n**********************************\n";
  std::cout << "ProgrammeRunTime:";
  timeDisplay(time);
  std::cout << "\n**********************************\n\n";
  }

  /** \brief Helper class
   *
   * Methods formats the time from milliseconds to format hh:mm:ss:ms
   */
  void RunTimeMeasurment::timeDisplay(double time) {
    double milisecond = std::fmod(time, 1.0);
    time = time - milisecond;
    double seconds = std::fmod(time, 60.0);
    time = (time - seconds) / 60.0;
    double minutes = std::fmod(time, 60.0);
    time = (time - minutes) /60.0;
    double hours = time;
    std::string zeros = "";

    if (milisecond*1000 < 10) {
      zeros = "00";
    } else if (milisecond*1000 < 100) {
      zeros = "0";
    }

    std::cout << std::setprecision(0) << std::fixed;
    if (hours != 0.0)
      std::cout << hours << "h";
    if (minutes != 0.0)
      std::cout << minutes << "m";
    std::cout << seconds << "s" << zeros
	      << milisecond*1000.0 << "ms";
    std::cout << std::setprecision(6);
  }
}  // namespace julian
