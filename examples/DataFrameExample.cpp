#include <juliant.hpp>


/**
 * \example DataFrameExample.cpp 
 * 	
 * \brief Example shows how to handle data using DataFrame. 
 *
 * Below we can see the example's listing 
 * @verbinclude DataFrameExample.dox 
 */

using namespace julian;

class wapon {
public:
  virtual void info() const = 0;
  virtual wapon* clone() const = 0;
  virtual ~wapon(){}
};

class Sword : public wapon {
public:
  void info() const override {
    std::cout << "sword" << std::endl;
  };
  Sword* clone() const override {
    return new Sword(*this);
  };
  ~Sword(){}
};

class Sling : public wapon {
public:
  void info() const override {
    std::cout << "Sling" << std::endl;
  };
  Sling* clone() const override {
    return new Sling(*this);
  };
  ~Sling(){}
};


namespace {
  ObjectFactoryHelper< wapon, Sword> register1("sword");
  ObjectFactoryHelper< wapon, Sling> register2("sling");
}

int main() {
  //
  // Creating an empty data frame
  //
  
  DataFrame df1;

  //
  // Adding few rows. To add a new row we use DataEntryClerk object.
  // Add method is overloaded so it accepts different types of data
  //
  DataEntryClerk data1;
  data1.add("Id", "id01");
  data1.add("Name", "Frodo");
  data1.add("Age", 50);
  data1.add("City", "Shire");
  
  DataEntryClerk data2;
  data2.add("Id", "id02");
  data2.add("Name", "Samwise");
  data2.add("Age", 35);
  data2.add("City", "Shire");
  data2.add("Birthday", Date(1968, SEP, 22));
  
  DataEntryClerk data3;
  data3.add("Id", "id03");
  data3.add("Name", "Boromir");
  data3.add("Age", 40);
  data3.add("City", "Gondor");

  DataEntryClerk data4;
  data4.add("Id", "id04");
  data4.add("Name", "Legolas");
  data4.add("Age", "2931");
  data4.add("City", "Woodland Realm");

  //
  // DataEntryClerk can be also constructed using std::map
  //
  std::map<std::string, std::string> map;
  map["Id"]   = "id05"; 
  map["Name"] = "Gimli";
  map["Age"]  = "139";
  map["City"] = "Blue Mountains";
  DataEntryClerk data5;
  data5.add(map);
  
  df1.append(data1);
  df1.append(data2);
  df1.append(data3);
  df1.append(data4);
  df1.append(data5);
  
  //
  // We can print data frame using print method.
  // Note that because only one entry data contained Birthday,
  // all but one row have missing value in columnd Birthday
  //
  std::cout << "Print data frame";
  df1.print();

  std::cout << "\nPrint first three rows";
  df1.print(3);

  std::cout << "\nPrint data frame using << operator";
  std::cout << df1;

  //
  // Let's filter data
  //
  std::cout << "\nFiltered data (age < 50)";
  auto filtered_data = df1.filter("Age",[](std::string x)->bool{return std::stoi(x)<50;});
  filtered_data.print();

  //
  // Merging two data frames
  //
  DataEntryClerk data6;
  data6.add("Id", "id06");
  data6.add("Name", "Aragorn");
  data6.add("Age", 87);
  data6.add("City", "Gondor");
  data6.add("Weapon", "sword");
  
  DataEntryClerk data7;
  data7.add("Id", "id07");
  data7.add("Name", "Meriadoc");
  data7.add("Age", 34);
  data7.add("City", "Shire");
  data7.add("Weapon", "sling");

  DataFrame df2;
  df2.append(data6);
  df2.append(data7);

  df1.append(df2);
  std::cout << "\nMerged dataframes";
  df1.print();

  //
  // Saving to csv file
  //
  df1.printToCsv("df", ';');

  //
  // Reading from Csv
  //  

  DataFrame df("df.csv", ';', true, 3);
  
  //
  // Accessing data stored in data frame
  //

  std::cout << "\nReading using number of row and number of col " << df(4, 1);
  std::cout << "\nReading using number of row and name of col   " << df("Name", 1);
  std::cout << "\nReading using id of row and name of col       " << df("Name", "id01");

  Date date = df.getDate("Birthday", 2, Date::Format::date1);
  std::cout << "\n\nRead date " << date;
  
  //
  // Reading row as std::map
  //
  std::cout << "\nRead row as map\n\n";
  auto row = df.getRow(2);
  for (auto d : row) {
    std::cout << std::setw(8) << d.first << " " <<  d.second << std::endl;
  }
  std::cout << std::endl;
  //
  // If factory is initialized we can directly construct object
  // basing on data preserved in DataFrame  
  //
  auto weapon_of_kate  = df.getObject<wapon>("Weapon", "id06");
  auto weapon_of_brain = df.getObject<wapon>("Weapon", "id07");

  std::cout << "Aragorn's weapon is\n";
  weapon_of_kate->info();
  std::cout << "Meriadoc's weapon is\n";
  weapon_of_brain->info();
}
