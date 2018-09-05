#ifndef JULIAN_VALUEFACTORY_HPP
#define JULIAN_VALUEFACTORY_HPP

#include <map>
#include <string>

namespace julian {

  /**
   * @file   valueFactory.hpp
   * @brief  File contains definition of Factory pattern.
   */

  /** \ingroup utils
   *  \brief Class implements a factory pattern.
   *
   * Class implement singleton factory pattern. On the basis of string it creates the enumeration value is created.
   *
   * More information see \cite joshi \cite GoF
   */
  template<class T>
  class ValueFactory {
  public:
    static ValueFactory& instance();
    T getValue(std::string name);
    void registerValue(std::string,T);
  private:
    std::map<std::string,T> creators;  /*!< \brief Map holding the creators of class and their string codes*/

    /** \brief constructor
     *
     * Private constructors disables creating the instance of class 
     */
    ValueFactory(){}

    /** \brief copy constructor
     *
     * Private copy constructors disables copying the instance of class 
     */
    ValueFactory(const ValueFactory&){};

    /** \brief assignment constructor
     *
     * Private assignment constructor disables copying the instance of class 
     */   
    ValueFactory& operator=(const ValueFactory&){return *this;};
  };

  /** \brief returns reference to instance of singleton factory
   */
  template<class T>
  ValueFactory<T>& ValueFactory<T>::instance() {
    static ValueFactory theFactory;
    return theFactory;
  }

  /** \brief returns enumeration value 
   *
   * If the key was not found in map, the default object is returned (first in map).
   */
  template<class T>
  T ValueFactory<T>::getValue(std::string name)   {
    auto i = creators.find(name);
    if ( i == creators.end() )
      {
	std::cout << name << " is an unknown name" << std::endl;
	i == creators.begin();
      }
    return (i->second);
  }

  /** \brief registers an enumeration value
   *
   * Factory returns the enum basing on provided string, but first appropriate mapping must be created.
   * This method registers the enum value
   */
  template<class T>
  void ValueFactory<T>::registerValue(std::string name, T x) {
    creators.insert(std::pair<std::string,T>(name,x) );
  }

  /** \brief factory helper
   *
   * ValueFactoryHelper helps to insert a new value to factory's creator list. It also implements the instance of value creator. 
   */
  template <class T>
  class ValueFactoryHelper {
  public:
    ValueFactoryHelper(std::string,T value);

  };

  /** \brief  constructor
   *
   * Constructor registers the new value of new object type in factory's creator lists
   */ 
  template <class T>
  ValueFactoryHelper<T>::ValueFactoryHelper(std::string name, T value) {
    ValueFactory<T>& factory = ValueFactory<T>::instance();
    factory.registerValue(name,value);
  }
}  // namespace julian
#endif
