#include <iostream>
#include <random>

class European;
class American;
class Asian;

//
// We define two Hierarchy of objects. The pricing models hierarchy and the option type hierarchy.
// Model objects use statical polymorphism
//
class Model {
public:
  Model(){};
  virtual void prize(European) = 0;
  virtual void prize(American) = 0;
  virtual void prize(Asian) = 0;

  virtual ~Model(){};
};    

class BlackScholes: public Model {
public:
  BlackScholes(){};
  void prize(European) override;
  void prize(American) override;
  void prize(Asian) override;
  virtual ~BlackScholes(){};
};

class Heston: public Model {
public:
  Heston(){};
  void prize(European) override; 
  void prize(American) override;
  void prize(Asian) override;
  virtual ~Heston(){};
};

//
// Option objects that perform dynamic polymorphism
//
class Option {
public:
  Option(){};
  void virtual prize(Model* m) = 0;
  virtual ~Option(){};
};

class European : public Option {
public:
  European(){};
  void virtual prize(Model* m) {
    m->prize(*this);
  }
  virtual ~European() {};
};

class American : public Option {
public:
  American(){};
  void virtual prize(Model* m) {
    m->prize(*this);
  }
  virtual ~American() {};
};

class Asian : public Option {
public:
  Asian(){};
  void virtual prize(Model* m) {
    m->prize(*this);
  }
  virtual ~Asian() {};
};


class Engine {
public:
  Engine(){};
  void prize(Model* m,Option* o) {
    o->prize(m);
  }
  virtual ~Engine(){};
};


int main() {
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> random_model(1, 2);
  std::uniform_int_distribution<int> random_option(1, 3);

  Model* model = 0;
  Option* option = 0;

  switch (random_model(e) ) {
  case 1: model = new BlackScholes;break;
  case 2: model = new Heston;break;
  }

  switch (random_option(e) ) {
  case 1: option = new European;break;
  case 2: option = new Asian;break;
  case 3: option = new American;break;
  }

  Engine prizing_engine;

  //
  // Note that behaviour of this method is dependent on two polymorphic types
  //
  prizing_engine.prize(model, option);
  
  return 0;
}


void BlackScholes::prize(European) {
  std::cout << "European Option prized with Black Scholes";
}
void BlackScholes::prize(American) {
  std::cout << "American Option prized with Black Scholes";
}
void BlackScholes::prize(Asian) {
  std::cout << "Asian Option prized with Black Scholes";
}
void Heston::prize(European) {
  std::cout << "European Option prized with Heston";
}
void Heston::prize(American) {
  std::cout << "American Option prized with Heston";
}
void Heston::prize(Asian) {
  std::cout << "Asian Option prized with Heston";
}
