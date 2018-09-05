#include <juliant.hpp>
#include <utils/serialization.hpp>
#include <utils/serializationGUID.hpp>
#include <utility>

/**
 * \example serializationExample.cpp 
 * \brief This example show how to serialize and deserialize objects. 
 *
 * @verbinclude serializationExample.dox 
 *
 */
using namespace julian;

int main() {
  //
  // Creating objects to serialize
  //
  std::map<std::string, InterestRate> rates;
  SimpleRate comp1;
  ExponentialRate comp2;

  ACT365 yf1;
  ActActISDA yf2;

  InterestRate rate1(comp1, yf1);
  InterestRate rate2(comp1, yf2);
  InterestRate rate3(comp2, yf1);
  rates["Rate1"] = rate1;
  rates["Rate2"] = rate2;
  rates["Rate3"] = rate3;
  //
  // Serialization
  //
  std::cout << "Serializing objects" << std::endl;
  serializeBinary(rates,"rates.dat");
  //
  // Deserialization
  //
  std::cout << "Deserializing objects" << std::endl;
  std::map<std::string, InterestRate> rates_reread = deserializeBinary<std::map<std::string, InterestRate> >("rates.dat");

  for (auto x : rates_reread) {
    std::cout << x.first << "\n" << x.second << std::endl  << std::endl;
  }

}
