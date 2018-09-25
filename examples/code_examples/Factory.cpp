#include <iostream>
#include <map>
#include <string>
#include <random>

//
// Factory, implemented as singleton, posses std::map creators which consists of 
// names of the object as key and functor creating the appropriate object as value.   
//
template<class T>
class Factory {
public:
  typedef T* (*CreateT)();
  static Factory& instance();
  T* getObject(std::string name);
  void registerObject(std::string, CreateT );
  ~Factory(){};
private:
  std::map<std::string, CreateT > creators;
  Factory(){}
  Factory(const Factory&){}
  Factory& operator = (const Factory&){ return *this;}
};

//
// Register helps to create the creators map inputs.
//
template<class T>
void Factory<T>::registerObject(std::string name, CreateT f) {
  creators.insert(std::pair<std::string,CreateT>(name,f) );
}

//
// This method is called by an user to create a proper object
//
template<class T>
T* Factory<T>::getObject(std::string name) {
  auto i = creators.find(name); 
  return (i->second)();
}

//
// Because the Factory is implemented as singleton, one can refer to its instance using this method 
//
template<class T>
Factory<T>& Factory<T>::instance() {
  static Factory theFactory;
  return theFactory;
}

//
// Helpers are used to automatize creating creators 
//
template <class Base,class Derived>
class FactoryHelper {
public:
  FactoryHelper(std::string);
  static Base* create();
};

template <class Base,class Derived>
Base* FactoryHelper<Base,Derived>::create() {
  return new Derived;
}

template <class Base,class Derived>
FactoryHelper<Base,Derived>::FactoryHelper(std::string name) {
  Factory<Base>& factory = Factory<Base>::instance();
  factory.registerObject(name,FactoryHelper<Base,Derived>::create);
}

//
// Here we create a simple hierarchy of objects
//
class Instrument {
public:
  Instrument(){};
  virtual void info() const = 0;
  ~Instrument(){};
};

class Deposit: public Instrument {
public:
  Deposit(){};
  virtual void info() const {
    std::cout << "deposit";
  }
  ~Deposit(){};
};

class FRA: public Instrument {
public:
  FRA(){};
  virtual void info() const {
    std::cout << "FRA";
  }
  ~FRA(){};
};

class IRS: public Instrument {
public:
  IRS(){};
  virtual void info() const{
    std::cout << "IRS";
  }
  ~IRS(){};
};

//
// Here re create factory producing instruments. 
// Anonymous namespace is used just to forbid access to created factory helpers
//
namespace {
  FactoryHelper< Instrument, Deposit> registerDepo("Depo");
  FactoryHelper< Instrument, FRA> registerFRA("FRA");
  FactoryHelper< Instrument, IRS> registerSwap("IRS");
}

int main() {
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> random_instrument(1, 3);

  std::string instrument;
  switch (random_instrument(e) ) {
  case 1: instrument = "Depo";
    break;
  case 2: instrument = "FRA";
    break;
  case 3: instrument = "IRS";
    break;
  }

  Instrument* ptr_choice = Factory<Instrument>::instance().getObject(instrument);
  std::cout << "Selected instrument is ";
  ptr_choice->info();
  
}
