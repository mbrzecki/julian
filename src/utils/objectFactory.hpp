#ifndef JULIAN_OBJECTFACTORY_HPP
#define JULIAN_OBJECTFACTORY_HPP

#include <map>
#include <string>
#include <typeinfo>
#include <utils/smartPointer.hpp>

 
namespace julian {

  /**
   * @file   objectFactory.hpp
   * @brief  File contains definition of Factory pattern.
   */

  /** \ingroup utils
   *  \brief Class implements a factory pattern.
   *
   * Class implement singleton factory pattern. On the basis of string it creates the object and returns SmartPointer to this object.
   *
   * More information see \cite joshi \cite GoF
   */

  template<class T>
  class ObjectFactory {
  public:
	/** \brief auxiliary definition of smart pointer
	*/
    typedef SmartPointer<T> (*CreateT)();

    static ObjectFactory& instance();
    SmartPointer<T> getObject(std::string name);
    void registerObject(std::string, CreateT );

    /** \brief destructor
     */
    ~ObjectFactory(){};
  private:
    std::map<std::string, CreateT > creators; /*!< \brief Map holding the creators of class and their string codes*/
    /** \brief constructor
     *
     * Private constructors disables creating the instance of class 
     */
    ObjectFactory(){}

    /** \brief copy constructor
     *
     * Private copy constructors disables copying the instance of class 
     */
    ObjectFactory(const ObjectFactory&){}

    /** \brief assignment constructor
     *
     * Private assignment constructor disables copying the instance of class 
     */
    ObjectFactory& operator = (const ObjectFactory&){ return *this;}
  };

  /** \brief registers an object
   *
   * Factory returns the object basing on provided string, but first appropriate mapping must be created.
   * This method registers the object
   */
  template<class T>
  void ObjectFactory<T>::registerObject(std::string name, CreateT f) {
    creators.insert(std::pair<std::string,CreateT>(name,f) );
  }

  /** \brief returns the a SmartPointer pointing new object of type dependent on string provided 
   *
   * If the key was not found in map, the default object is returned (first in map).
   */
  template<class T>
  SmartPointer<T> ObjectFactory<T>::getObject(std::string name) {
    auto i = creators.find(name);
    if ( i == creators.end() ) {
      std::cout << name << " is an unknown name" << std::endl;
      return (creators.begin()->second)();
    }  
    return (i->second)();
  }

  /** \brief returns reference to instance of singleton factory
   */
  template<class T>
  ObjectFactory<T>& ObjectFactory<T>::instance() {
    static ObjectFactory theFactory;
    return theFactory;
  }

  /** \brief factory helper
   *
   * ObjectFactoryHelper helps to insert a new object to factory's creator list. It also implements the instance of object creator. 
   */
  template <class Base,class Derived>
  class ObjectFactoryHelper {
  public:
    ObjectFactoryHelper(std::string);
    static SmartPointer<Base> create();
  };

  /** \brief creator
   *
   * This method is called by factor to create derived object and return it as SmartPointer to base class
   */
  template <class Base,class Derived>
  SmartPointer<Base> ObjectFactoryHelper<Base,Derived>::create() {
    Derived a;
    return a;
  }

  /** \brief  constructor
   *
   * Constructor registers the creator of new object type in factory's creator lists
   */ 
  template <class Base,class Derived>
  ObjectFactoryHelper<Base,Derived>::ObjectFactoryHelper(std::string name) {
    ObjectFactory<Base>& factory = ObjectFactory<Base>::instance();
    factory.registerObject(name, ObjectFactoryHelper<Base,Derived>::create);
  }
}
#endif
