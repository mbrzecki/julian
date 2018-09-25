#include <iostream>
#include <memory>

// Deeply copying smart poitner
template< class T>
class SmartPointer {
 public:
  SmartPointer() {
    data_ptr = 0;
  }

  // When smart pointer is copied
  // call virtual copy constructor
  SmartPointer(const T& inner) {
    data_ptr = inner.clone();
  }

  // When smart pointer is destroyed
  // delete also the object it points to.
  ~SmartPointer() {
    if (data_ptr != 0)
      delete data_ptr;
  }

  // When smart pointer is copied,
  // clone inner data.  
  SmartPointer(const SmartPointer<T>& original) {
    if (original.data_ptr !=0) {
      data_ptr = original.data_ptr->clone();
    } else {
      data_ptr = 0;
    }
  }

  // When smart pointer is assigned,
  // clone inner data.
  SmartPointer& operator=(const SmartPointer<T>& original) {
    if (this != &original) {
      if (data_ptr != 0) {
	delete data_ptr;
      }
      data_ptr = (original.data_ptr != 0) ? original.data_ptr->clone() : 0;
    }
    return *this;
  }

  // deference operator overloading
  T* operator->() {
    return data_ptr;
  }

 private:
  T* data_ptr;
};

class Interface {
 public:
  Interface() {}

  // some virtual method
  virtual void info() = 0;

  // virtual copy constructor
  // object creates and returns its clone
  virtual Interface* clone() const;

  // virtual desctructor
  virtual ~Interface(){}
};

template<typename T>
class DeeplyCopyableClass : public Interface {
 public:
  // virtual copy constructor
  // object creates and returns its clone
  virtual Interface* clone() const {
    return new T(static_cast<const T&>(*this));
  }
};

class ConcreteClass1 : public DeeplyCopyableClass<ConcreteClass1> {
 public:
  // overriding virtual method
  void info() override {
    std::cout << "\tConcreteClass1: " << this  << "\n\n";
  }
  // deconstructor
  ~ConcreteClass1() override {
  }
};

class ConcreteClass2 : public Interface {
 public:
  ConcreteClass2(){};
  // overriding virtual method
  void info() override {
    std::cout << "\tConcreteClass2: " << this << "\n\n";
  }
  // virtual copy constructor
  // object creates and returns its clone
  ConcreteClass2* clone() const override {
    return new ConcreteClass2(*this);
  }
  // deconstructor
  ~ConcreteClass2() override {
  }
};


int main() {
  ConcreteClass1 d1;
  ConcreteClass2 d2;

  SmartPointer<Interface> dc_ptr1a = d1;
  SmartPointer<Interface> dc_ptr1b = dc_ptr1a;
  SmartPointer<Interface> dc_ptr1c(dc_ptr1a);

  std::shared_ptr<Interface> sh_ptr1a = std::make_shared<ConcreteClass1>(d1);
  std::shared_ptr<Interface> sh_ptr1b = sh_ptr1a;
  std::shared_ptr<Interface> sh_ptr1c(sh_ptr1a);

  std::cout << "Smart pointers for Concrete Class 1 "
	    << "(Curiously recurring template pattern)\n\n";
  std::cout << "Original deep copying smart pointer\n";
  dc_ptr1a->info();
  std::cout << "Assigned deep copying smart pointer\n";
  dc_ptr1b->info();
  std::cout << "Copied deep copying smart pointer\n";
  dc_ptr1c->info();

  std::cout << "Original shared smart pointer\n";
  sh_ptr1a->info();
  std::cout << "Assigned shared smart pointer\n";
  sh_ptr1b->info();
  std::cout << "Copied shared smart pointer\n";
  sh_ptr1c->info();

  SmartPointer<Interface> dc_ptr2a = d2;
  SmartPointer<Interface> dc_ptr2b = dc_ptr2a;
  SmartPointer<Interface> dc_ptr2c(dc_ptr2a);

  std::cout << "\n\nSmart pointers for Concrete Class 2 "
	    << "(Virtual copy constructor implemented in base class)\n\n";
  std::cout << "Original deep copying smart pointer\n";
  dc_ptr2a->info();
  std::cout << "Assigned deep copying smart pointer\n";
  dc_ptr2b->info();
  std::cout << "Copied deep copying smart pointer\n";
  dc_ptr2c->info();
}
