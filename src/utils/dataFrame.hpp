#ifndef JULIAN_DATAFRAME_HPP
#define JULIAN_DATAFRAME_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <dates/date.hpp>
#include <dates/tenor.hpp>
#include <dates/timeUnit.hpp>
#include <utils/SmartPointer.hpp>
#include <utils/objectFactory.hpp>
#include <utils/valueFactory.hpp>
namespace julian {

  class DataEntryClerk;
  
  /**
   * @file   dataFrame.hpp
   * @brief  File contains definition of data frame.
   */
  
  /** \ingroup utils
   *  \brief Class used to handle data read from csv files.
   *
   * Class enables to load the csv file and read it contents. 
   * One can access the single cell or read whole columns. 
   * Class allows to choose cell using column and row numbers or, if defined, 
   * column names and primary keys. 
   */
  
  class DataFrame {
  public:
    DataFrame(){};
    DataFrame(std::string file_name,
	      char delimiter,
	      bool first_row_is_column_names,
	      int primery_key = 0);

    std::string operator()(const int col, const int row);
    std::string operator()(const std::string col, const int row);
    std::string operator()(const std::string col, const std::string row);

    std::vector<std::string> operator()(int col);
    std::vector<std::string> operator()(std::string col);

    double getDouble(const int col, const  int row);
    double getDouble(const std::string col, const int row);
    double getDouble(const std::string col, const std::string row);

    Date getDate(const int col, const  int row, Date::Format fmt);
    Date getDate(const std::string col, const int row, Date::Format fmt);
    Date getDate(const std::string col, const std::string row, Date::Format fmt);

    std::vector<std::string> getColumnNames() const;
    std::vector<std::string> getPrimaryKeys() const;
    std::map<std::string, std::string> getRow(int row) const;
    
    void append(const DataEntryClerk&);
    void append(const DataFrame&);

    void shape() const;
    void print(int n_rows = -1);
    void printToCsv(std::string file_name, char delimiter = ';');
    
    int getNumberOfRows() const;
    int getNumberOfColumns() const;
    
    template<class T>
    SmartPointer<T> getObject(const int col, const  int row);
    template<class T>
    SmartPointer<T> getObject(const std::string col, const int row);
    template<class T>
    SmartPointer<T> getObject(const std::string col, const std::string row);
    template<class T>
    T getValue(const int col, const  int row);
    template<class T>
    T getValue(const std::string col, const int row);
    template<class T>
    T getValue(const std::string col, const std::string row);

    template<class T>
    DataFrame filter(int col,T filter);
    template<class T>
    DataFrame filter(std::string col,T filter);
    
    friend std::ostream& operator<<(std::ostream&, DataFrame&);
  private:
    void parseFile(std::string file_name, char delimiter);
    void createColumnNames(bool first_row);
    //   void printHLine(std::vector<int> );
    
    std::vector<std::vector<std::string> > data_; /*!< \brief Holds data as 2d table of strings*/
    std::map<std::string,int> column_names_;      /*!< \brief Maps column name to column number */
    std::map<std::string,int> primary_key_;       /*!< \brief Maps row name to row number*/
    int ncols_ = 0;                               /*!< \brief number of columns*/
    int nrows_ = 0;                               /*!< \brief number of rows*/
  };

  /** \brief Reads cell in c-th column and r-th row
   * \param col column name
   * \param row row number
   * \return Returns content of cell. Method uses ObjectFactory to transform string into object.
   */  
  template<class T>
  SmartPointer<T> DataFrame::getObject(const int col, const int row) {
    return ObjectFactory<T>::instance().getObject(data_[row-1][col-1]);
  }

  /** \brief Reads cell in  column named c and r-th row
   * \param col column name
   * \param row row number
   * \return Returns content of cell.  Method uses ObjectFactory to transform string into object.
   * \note May be used only when column names were defined.
   */ 
  template<class T>
  SmartPointer<T> DataFrame::getObject(const std::string col, const int row) {
    BOOST_ASSERT_MSG(!column_names_.empty(), "Column names not defined");
    return ObjectFactory<T>::instance().getObject(data_[row-1][column_names_[col]-1]);
  }

  /** \brief Reads cell in column name and row holding primary key r
   * \param col column name
   * \param row row name
   * \return Returns content of cell as string  Method uses ObjectFactory to transform string into object.
   * \note May be used only when column names and primary keys were defined.
   */ 
  template<class T>
  SmartPointer<T> DataFrame::getObject(const std::string col, const std::string row) {
    BOOST_ASSERT_MSG(!primary_key_.empty(), "Primary key not defined");
    BOOST_ASSERT_MSG(!column_names_.empty(), "Column names not defined");
    return ObjectFactory<T>::instance().getObject(data_[primary_key_[row]-1][column_names_[col]-1]);
  }

  /** \brief Reads cell in c-th column and r-th row
   * \param col column name
   * \param row row number
   * \return Returns content of cell. Method uses ValueFactory to transform string into enumeration.
   */ 
  template<class T>
  T DataFrame::getValue(const int col, const  int row)  {
    return ValueFactory<T>::instance().getValue(data_[row-1][col-1]);
  }

  /** \brief Reads cell in  column named c and r-th row
   * \param col column name
   * \param row row number
   * \return Returns content of cell.  Method uses ValueFactory to transform string into  enumeration.
   * \note May be used only when column names were defined.
   */ 
  template<class T>
  T DataFrame::getValue(const std::string col, const int row)  {
    BOOST_ASSERT_MSG(!column_names_.empty(), "Column names not defined");
    return ValueFactory<T>::instance().getValue(data_[row-1][column_names_[col]-1]);
  }

  /** \brief Reads cell in column name and row holding primary key r
   * \param col column name
   * \param row row name
   * \return Returns content of cell as string   Method uses ValueFactory to transform string into  enumeration.
   * \note May be used only when column names and primary keys were defined.
   */ 
  template<class T>
  T DataFrame::getValue(const std::string col, const std::string row) {
    BOOST_ASSERT_MSG(!primary_key_.empty(), "Primary key not defined");
    BOOST_ASSERT_MSG(!column_names_.empty(), "Column names not defined");
    return ValueFactory<T>::instance().getValue(data_[primary_key_[row]-1][column_names_[col]-1]);
  }

  /**  \brief Filter the data frame basing on data hold in column
   *
   * \param col column identification
   * \param filter Functor with overloaded operator bool operator()(std::string), if functor returns true row is added to DataFrame that is returned by the method  
   */ 
  template<class T>
  DataFrame DataFrame::filter(int col,T filter) {
    DataFrame filtered;
    for (int r = 1; r <= nrows_; r++) {
      if (filter(data_[r-1][col-1])) {
	filtered.data_.push_back(data_[r-1]);
      }
    }
    
    filtered.column_names_ = column_names_;        
    filtered.ncols_ = ncols_;                    
    filtered.nrows_ = filtered.data_.size();

    return filtered;
  }
  
  /**  \brief Filter the data frame basing on data hold in column
   *
   * \param col column identification
   * \param filter Functor with overloaded operator bool operator()(std::string), if functor returns true row is added to DataFrame that is returned by the method  
   * \note May be used only when column names were defined.
   */ 
  template<class T>
  DataFrame DataFrame::filter(std::string col,T filter) {
    BOOST_ASSERT_MSG(!column_names_.empty(), "Column names not defined");
    DataFrame filtered;
    for (int r = 1; r <= nrows_; r++) {
      if (filter(data_[r-1][column_names_[col] - 1])) {
	filtered.data_.push_back(data_[r-1]);
      }
    }
    
    filtered.column_names_ = column_names_;        
    filtered.ncols_ = ncols_;                    
    filtered.nrows_ = filtered.data_.size();

    return filtered;
;
  }  
  /** \ingroup utils
   *  \brief Class used to provide data to julian::DataFrame.
   * 
   * Class saves input provided by user. Data Clark passed as argument to julian::DataFrame::append
   * adds a new data row to DataFrame. Keys of the map are interpreted as column names and values as observation inputs.
   */
  class DataEntryClerk {
  public:

    /** \brief Default constructor
     */
    DataEntryClerk(){};
    void add(std::string, std::string);
    void add(std::string, double);
    void add(std::string, int);
    void add(std::string, Date);
    void add(std::string, Tenor);

    /** \brief add a map to data
     *
     * Method adds map to the . The values of the map provided must be one of the type accepted by julian::DataFrame::add methods
     */
    template<typename T>
    void add(const std::map<std::string, T>& input) {
      for (auto item : input)
	add(item.first, item.second);
    }
    
    friend class DataFrame;
  private:
    std::map<std::string, std::string> data_; /*!< \brief Maps that stores inputs provided using method DataEntryClerk::add.*/
  };
  
}  // namespace julian


#endif
