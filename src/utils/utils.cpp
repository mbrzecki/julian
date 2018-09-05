#include <utils/utils.hpp>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>
#include <boost/program_options.hpp>

namespace julian {

  /** \ingroup utils				       
   *
   * \fn bool isCloseEnough(double x1, double x2, int n)
   * \brief Function checks if difference between two numbers is small enough.
   * 
   * \param x1 First number
   * \param x2 Second number
   * \param n 
   * \return True if difference between x1 and x2 is smaller than $10^{-n}$
   */
  bool isCloseEnough(double x1, double x2, int n) {
    double diff = std::abs(x1-x2);
    double treshold = std::pow(0.1, n);

    if (diff < treshold) {
      return true;
    }
    return false;
  }

  /** \ingroup utils				       
   *
   * \fn double roundNumber(double x, int n) 
   * \brief Function rounds number to a decimal place.
   * 
   * \param x Rounded number
   * \param n Decimal place
   * \return Rounded to a n-th decimal place
   */
  double roundNumber(double x, int n) {
    int i = pow(10, n-1);
    double result = floor(x*5*i + 0.5) / i /5.0;
    return result;
  }

  /** \ingroup utils				       
   *
   * \fn double convertStr2Dbl(std::string input)  
   * \brief Function converts string to double.
   *
   * \param  input 
   * \return double 
   */

  double convertStr2Dbl(std::string input) {
    std::istringstream iss(input);
    double x;
    if (!(iss >> x))
      BOOST_ASSERT_MSG( 1 ,"Cannot convert to double ");
    return x;
  }

  /** \ingroup utils				       
   *
   * \fn std::string convertDbl2Str(double) 
   * \brief Function converts double to string
   *
   * \param  input 
   * \return std::string 
   */
  std::string convertDbl2Str(double input) {
    std::ostringstream strs;
    strs << input;
    return strs.str();
  }
  
  /** \ingroup utils				       
   *
   * \fn std::vector<double> convertStr2Dbl(std::vector<std::string> input)  
   * \brief Function converts vector of strings to vector of doubles.
   *
   * \param  input 
   * \return std::vector<double> 
   */
  std::vector<double> convertStr2Dbl(std::vector<std::string> input) {
    std::vector<double> ret;
    for (auto item : input) {
      ret.push_back(convertStr2Dbl(item));
    }
    return ret;
  }


  
  /** \ingroup utils				       
   *
   * \fn void writeToCsv(std::string file_name, std::map<std::string,std::vector<double> > data)  
   * \brief Function saves data to csv file.
   * 
   *  Function writes data to csv. Keys of map representing data are columns names. Columns are map's values
   *
   * \param file_name name of the file 
   * \param data std map where keys are column names and values are columns. 
   */

  void writeToCsv(std::string file_name, std::map<std::string, std::vector<double> > data) {
    std::vector<std::string> labels;
    std::vector<std::vector<double> > values;
    for (auto it : data) {
      labels.push_back(it.first);
      values.push_back(it.second);
    }

    std::ofstream file;
    std::string csv = file_name + ".csv";
    try {
      file.open(csv.c_str());
      for (auto lab : labels) {
	file << lab << ";";
      }
      file << std::endl;
      for (unsigned int i = 0; i < values.front().size(); i++) {
	for (auto lab : labels) {
	  file << data[lab].at(i) << ";";
	}
	file << std::endl;
      }
      file.close();
    } catch (std::ios_base::failure &fail) {
      std::cout << "Could not open file " << csv;
    }  
  }

  /** \ingroup utils				       
   *
   * \fn std::pair<std::string, std::string> catchDataAndSettingFileNames(int ac, char* av[]) 
   * \brief Function uses boost::program_options to catch the name of data and setting file
   * 
   * The function catches the program options, that is (name, value) pairs from the user. 
   * Allowed programme options are *data* and *settings* .
   * 
   * \return std::pair of strings: first string is name of data file, second name of settings file
   */
  std::pair<std::string, std::string> catchDataAndSettingFileNames(int ac, char* av[]) {
    std::string data_file, settings_file;
    try  {
      boost::program_options::options_description desc("Allowed options");
      desc.add_options()
	("data", boost::program_options::value<std::string>()  , "csv file with data")
	("settings",boost::program_options::value<std::string>(), "csv file with settings");
      boost::program_options::variables_map vm;
      boost::program_options::store(boost::program_options::parse_command_line(ac, av, desc), vm);
      boost::program_options::notify(vm);

      if (vm.count("data")) {
	data_file  = vm["data"].as<std::string>();
      }
      if (vm.count("settings")) {
	settings_file  = vm["settings"].as<std::string>();
      }
    }
    catch(std::exception& e) {
      std::cerr << "error: " << e.what() << "\n";
    }
    catch(...) {
      std::cerr << "Exception of unknown type!\n";
    }
    return std::make_pair(data_file, settings_file);
  }
}  // namespace julian
