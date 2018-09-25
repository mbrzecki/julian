#include <utils/dataFrame.hpp>
#include <utils/utils.hpp>
#include <sstream>
#include <vector>
#include <string>
#include <utils/vectorOperations.hpp>
#include <boost/assert.hpp>

namespace julian {

  /** \brief Constructor.
   * \param file_name File name that will be read.
   * \param delimiter Separation sign in csv file.
   * \param first_row_is_column_names True if first row contains column names. 
   * \param primery_key Defines which column contains primary key of the table.
   * 
   * Create DataFrame on the basis of provided file.   
   */
  
  DataFrame::DataFrame(std::string file_name, char delimiter,
		       bool first_row_is_column_names, int primery_key) {
    // parsing file
    this->parseFile(file_name, delimiter);
    // creating column names
    this->createColumnNames(first_row_is_column_names);
    // creating primary key
    if (primery_key) {
      for (unsigned int i = 0; i < data_.size(); i++) {
	primary_key_[data_[i][primery_key-1]] = i+1;
      }
    }
  }
  /** \brief parse csv file, result of method is saved in DataFrame::data_
   *
   * \remark Method used by constructor. Bad practice, so better keep the method non-virtual.
   */  
  void DataFrame::parseFile(std::string file_name, char delimiter) {
    std::string row, item;
    std::ifstream in(file_name );
    if (in.good()) {
      while (getline(in, row)) {
	std::vector<std::string> R;

	/** \bug Function reads EOL sign
	 * All but last rows are read with EOL sign. This cause the problem with
	 * comparing signs. Below if statement solves the problem by cutting of the last
	 * char if it is a EOL. Not sure if this is a save solution.
	 */
	if (int(row.back()) == 13) {
	  row = row.substr(0, row.size()-1);
	}
	std::stringstream ss(row);
	while (getline(ss, item, delimiter)) {
	  R.push_back(item);
	}
	data_.push_back(R);
	nrows_++;
      }      
    } else {
      std::cout << "File " + file_name + " not find" << std::endl;
      assert(false);
    }
    in.close();
  }

  /** \brief creates columns names basing on the first row of csv file
   *
   * \remark Method used by constructor. Bad practice, so better keep the method non-virtual.
   */
  void DataFrame::createColumnNames(bool first_row) {
    if (first_row) {
      auto first_row = data_.front();
      for (unsigned int i = 0; i < first_row.size(); i++) {
	column_names_[first_row.at(i)] = i+1;
	ncols_++;
      }
      data_.erase(data_.begin());
      nrows_--;
    } else {
      for (unsigned int i = 0; i < data_.front().size(); i++) {
	column_names_["Col" + std::to_string(i+1)] = i + 1;	
	ncols_++;
      }
    }
  }

  /** \brief Reads cell in c-th column and r-th row
   * \param col column name
   * \param row row number
   * \return Returns content of cell as string
   */  
  std::string DataFrame::operator()(const int col, const int row) {
    return data_[row-1][col-1];
  }

  /** \brief Reads cell in  column named c and r-th row
   * \param col column name
   * \param row row number
   * \return Returns content of cell as string
   * \note May be used only when column names were defined.
   */ 
  std::string DataFrame::operator()(const std::string col, const int row) {
    return data_[row-1][column_names_[col]-1];
  }

  /** \brief Reads cell in column name and row holding primary key r
   * \param col column name
   * \param row row name
   * \return Returns content of cell as string
   * \note May be used only when column names and primary keys were defined.
   */ 
  std::string DataFrame::operator()(const std::string col,const std::string row) {
    return data_[primary_key_[row]-1][column_names_[col]-1];
  }

  /** \brief Reads column basic on column number
   * \param col column number
   * \return Returns column as vector of string
   */ 
  std::vector<std::string> DataFrame::operator()(int col) {
    std::vector<std::string> res;
    for (int i = 0; i < this->getNumberOfRows(); i++) {
      res.push_back(data_[i][col-1]);
    }
    return res;
  }

  /** \brief Reads column basic on column number
   * \param col column number
   * \return Returns column as vector of string
   * \note May be used only when column names were defined.
   */ 
  std::vector<std::string> DataFrame::operator()(std::string col) {
    std::vector<std::string> res;
    for (int i = 0; i < this->getNumberOfRows(); i++) {
      res.push_back(data_[i][column_names_[col]-1]);
    }
    return res;
  }

  /** \brief Reads cell in c-th column and r-th row
   * \param col column name
   * \param row row number
   * \return Returns content of cell as double
   */  
  double DataFrame::getDouble(const int col, const  int row) {
    return convertStr2Dbl(data_[row-1][col-1]);
  }

  /** \brief Reads cell in  column named c and r-th row
   * \param col column name
   * \param row row number
   * \return Returns content of cell as double
   * \note May be used only when column names were defined.
   */ 
  double DataFrame::getDouble(const std::string col, const int row) {
    return convertStr2Dbl(data_[row-1][column_names_[col]-1]);
  }

  /** \brief Reads cell in column name and row holding primary key r
   * \param col column name
   * \param row row number
   * \return Returns content of cell as double
   * \note May be used only when column names and primary keys were defined.
   */ 
  double DataFrame::getDouble(const std::string col, const std::string row) {
    return convertStr2Dbl(data_[primary_key_[row]-1][column_names_[col]-1]);
  }

  /** \brief Reads cell in c-th column and r-th row
   * \param col column name
   * \param row row number
   * \param fmt Date format (compare Date::Format)
   * \return Returns content of cell as a date formatted according to fmt
   */  
  Date DataFrame::getDate(const int col, const  int row, Date::Format fmt) {
    return Date(data_[row-1][col-1], fmt);
  }

  /** \brief Reads cell in  column named c and r-th row
   * \param col column name
   * \param row row number
   * \param fmt Date format (compare Date::Format)
   * \return Returns content of cell as a date formatted according to fmt 
   * \note May be used only when column names were defined.
   */ 
  Date DataFrame::getDate(const std::string col, const int row, Date::Format fmt) {
    return Date(data_[row-1][column_names_[col]-1], fmt);
  }

  /** \brief Reads cell in column name and row holding primary key r
   * \param col column name
   * \param row row number
   * \param fmt Date format (compare Date::Format)
   * \return Returns content of cell as a date formatted according to fmt
   * \note May be used only when column names and primary keys were defined.
   */ 
  Date DataFrame::getDate(const std::string col, const std::string row, Date::Format fmt) {
    return Date(data_[primary_key_[row]-1][column_names_[col]-1], fmt);
  }

  /** \brief adds data stored by DataEntryClerk
   * 
   * Data stored in DataEntryClerK:data_ are added. If new columns are added, 
   * old rows are filled with "." representing missing.
   */
  void DataFrame::append(const DataEntryClerk& entry) {
    if (ncols_) {
      for (auto item : entry.data_) { 
	if ( column_names_.find(item.first) == column_names_.end() ) {
	  column_names_[item.first] = column_names_.size();
	  ncols_++;
	  for (auto& row : data_) {
	    row.push_back(".");
	  }
	} 
      }
      std::vector<std::string> row(ncols_,".");
      for (auto item : entry.data_) {
	row.at(column_names_[item.first]-1) = item.second;
      }
      data_.push_back(row);
    } else {
      std::vector<std::string> row;
      for (auto item : entry.data_) {
	column_names_[item.first] = column_names_.size();
	row.push_back(item.second);
	ncols_++;
      }
      data_.push_back(row);
    }
    nrows_++;
  }
  
  /** \brief Prints DataFrame
   */
  void DataFrame::print(int n_rows) {
    auto column_names = getColumnNames();
    std::cout << "\n";
    // width of columns
    std::vector<int> widths;
    for (int i = 0; i < ncols_; i++) {
      auto col_name = column_names.at(i);
      unsigned int width = col_name.size();
      for (int j = 0 ; j < nrows_; j++) {
     	auto cell = data_[j][i];
     	width = cell.size() > width ? cell.size() : width;
      }
      widths.push_back(width+3);
    }
    
    // print line
    for (auto& n : widths)
      for (int i =0; i < n ; i++)
    	std::cout << "-";
    std::cout << std::endl;

    // printing col names
    for (int i = 0; i < ncols_; i++) {
      std::cout << std::setw(widths.at(i)) << column_names.at(i);
    }
    std::cout << std::endl;

    // print line
    for (auto& n : widths)
      for (int i =0; i < n ; i++)
    	std::cout << "-";
    std::cout << std::endl;

    // printing rows
    for (int j = 0 ; j < nrows_; j++) {
      for (int i = 0; i < ncols_; i++) {
    	auto cell = data_[j][i];
    	std::cout << std::setw(widths.at(i)) << cell;
      }
      std::cout << std::endl;
      if (n_rows > 0 && n_rows-1 < j) 
    	break;
    }
    
    // print line
    for (auto& n : widths)
      for (int i =0; i < n ; i++)
    	std::cout << "-";
    std::cout << std::endl;
  }

  /** \brief prints DataFrame to csv file
   * \param file_name
   * \param delimiter separator used in csv file, by default set to semicolon
   *
   */

  void DataFrame::printToCsv(std::string file_name, char delimiter) {
    std::vector<std::string> column_names = this->getColumnNames();

    std::ofstream file;
    std::string csv = file_name + ".csv";
    try {
      file.open(csv.c_str());
      int i = 1;
      for (auto col : column_names) {
	file << col;
	if (i++ < ncols_)
	  file << delimiter;
      }
      file << std::endl;
      for (auto row : data_) {
	i = 1;
	for (auto cell : row) {
	  file << cell;
	  if (i++ < ncols_)
	    file << delimiter;
	}
	file << std::endl;
      }
      file.close();
    } catch (std::ios_base::failure &fail) {
      std::cout << "Could not open file " << csv;
    }
  }

  /** \brief Returns primary keys as vector of strings
   */
  std::vector<std::string> DataFrame::getPrimaryKeys() const {
    std::vector<std::string> res;
    for (auto item : primary_key_) {
      res.push_back(item.first);
    }
    return res;
  }

  /** \brief Returns column names as vector of strings
   */
  std::vector<std::string> DataFrame::getColumnNames() const {
    std::vector<std::string> res;
    if (not column_names_.empty()) {
      for (int i = 1; i <= ncols_; i++) {
	for (auto input : column_names_) {
	  if (input.second == i) {
	    res.push_back(input.first);
	  }
	}
      }
    }
    return res;
  }

  /** \brief Returns number of rows
   */
  int DataFrame::getNumberOfRows() const {
    return nrows_;
  }

  /** \brief Returns number of columns
   */
  int DataFrame::getNumberOfColumns() const {
    return ncols_;
  }

  /** \brief Returns row in form of std::map
   */
  std::map<std::string, std::string> DataFrame::getRow(int r) const {
    auto row = data_[r-1];
    auto cols = this->getColumnNames();
    std::map<std::string, std::string > results;
    std::transform( cols.begin(), cols.end(), row.begin(), 
		    std::inserter(results, results.end() ), std::make_pair<std::string const&,std::string const&> );
    return results;
  }

  /** \brief Appends one data frame to another
   */
  void DataFrame::append(const DataFrame& appended) {
    for (int row = 1; row <= appended.getNumberOfRows(); row++) {
      auto temp = appended.getRow(row);
      DataEntryClerk input;
      input.add<std::string>(temp);
      this->append(input);
    }
  }
  
  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, DataFrame& df) {
    s << "\nObject: DataFrame\n";
    s << "Size: " << df.ncols_ << " col " << df.nrows_ << " rows\n" ; 
    auto column_names = df.getColumnNames();

    // width of columns
    std::vector<int> widths;
    for (int i = 0; i < df.ncols_; i++) {
      auto col_name = column_names.at(i);
      unsigned int width = col_name.size();
      for (int j = 0 ; j < df.nrows_; j++) {
     	auto cell = df.data_[j][i];
     	width = cell.size() > width ? cell.size() : width;
      }
      widths.push_back(width+3);
    }
    
    // print line
    for (auto& n : widths)
      for (int i =0; i < n ; i++)
    	s << "-";
    s << std::endl;

    // printing col names
    for (int i = 0; i < df.ncols_; i++) {
      s << std::setw(widths.at(i)) << column_names.at(i);
    }
    s << std::endl;

    // print line
    for (auto& n : widths)
      for (int i =0; i < n ; i++)
    	s << "-";
    s << std::endl;

    // printing rows
    for (int j = 0 ; j < df.nrows_; j++) {
      for (int i = 0; i < df.ncols_; i++) {
    	auto cell = df.data_[j][i];
    	s << std::setw(widths.at(i)) << cell;
      }
      s << std::endl;
    }

    // print line
    for (auto& n : widths)
      for (int i =0; i < n ; i++)
    	s << "-";
     s << std::endl;

    return s;
  }

  /** \brief adds a string input
   */
  void DataEntryClerk::add(std::string col, std::string input) {
    data_[col] = input;
  }

  /** \brief adds a double input
   */
  void DataEntryClerk::add(std::string col, double input) {
    data_[col] = std::to_string(input);
  }

  /** \brief adds a int input
   */
  void DataEntryClerk::add(std::string col, int input) {
    data_[col] = std::to_string(input);
  }

  /** \brief adds a date input
   */
  void DataEntryClerk::add(std::string col, Date input) {
    data_[col] = input.getString();
  }

  /** \brief adds a tenor input
   */
  void DataEntryClerk::add(std::string col, Tenor input) {
    std::string temp = input;
    data_[col] = temp;
  }
}  // namespace julian
