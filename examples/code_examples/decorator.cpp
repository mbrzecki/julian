#include <iostream>

//
// Here we create the sample hierarchy of objects
//
class StochasticProcess {
public:
  virtual void info() = 0;
};

//
// WienerProcess is object that will be used as base object.
//
class WienerProcess: public StochasticProcess {
public:
  void info(){cout << "\nWiener Process" ;};
};

//
// This class decorator provides the interface for objects modifying behaviour  of base objects
//
class StochasticProcessDecorator: public StochasticProcess {
public:
  StochasticProcessDecorator(StochasticProcess* stochastic_process): stochastic_process_(stochastic_process) {}
  void virtual info() {
    stochastic_process_->info();
  }
  
private:
  StochasticProcess* stochastic_process_;
};

//
// Following objects are concrete instances of decorators 
//
class ConstantDrift: public StochasticProcessDecorator {
public:
  ConstantDrift(StochasticProcess* stochastic_process):StochasticProcessDecorator(stochastic_process){}
  void info()  {
    StochasticProcessDecorator::info();
    std::cout << " with constant drift";
  }
};

class MeanReversion: public StochasticProcessDecorator {
public:
  MeanReversion(StochasticProcess* stochastic_process):StochasticProcessDecorator(stochastic_process){}
  void info()  {
    StochasticProcessDecorator::info();
    std::cout << " with mean reversion";
  }
};

class PoisonJumps: public StochasticProcessDecorator {
public:
  PoisonJumps(StochasticProcess* stochastic_process):StochasticProcessDecorator(stochastic_process){}
  void info()  {
    StochasticProcessDecorator::info();
    std::cout << " with jumps";
  }
};

int main() {
  StochasticProcess* process1 = new MeanReversion( new WienerProcess);
  StochasticProcess* process2 = new PoisonJumps( new ConstantDrift(new WienerProcess));

  process1->info();
  process2->info();
}

