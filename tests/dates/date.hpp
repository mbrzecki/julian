BOOST_AUTO_TEST_SUITE(dates_Date)

BOOST_AUTO_TEST_CASE(Constructor_GivenStringInFormat1_StringIsCorrectlyParsed) {
  // Arrange
  auto fmt = Date::Format::date1;
  
  // Act
  bool test1  = Date(2015, JAN, 30) == Date("2015-01-30", fmt);
  bool test2  = Date(2015, FEB,  3) == Date("2015-02-03", fmt);
  bool test3  = Date(2015, MAR,  2) == Date("2015-03-02", fmt);
  bool test4  = Date(2015, APR, 15) == Date("2015-04-15", fmt);
  bool test5  = Date(2015, MAY, 20) == Date("2015-05-20", fmt);
  bool test6  = Date(2015, JUN, 23) == Date("2015-06-23", fmt);
  bool test7  = Date(2015, JUL, 13) == Date("2015-07-13", fmt);
  bool test8  = Date(2015, AUG,  2) == Date("2015-08-02", fmt);
  bool test9  = Date(2015, SEP, 15) == Date("2015-09-15", fmt);
  bool test10 = Date(2015, OCT,  9) == Date("2015-10-09", fmt);
  bool test11 = Date(2015, NOV,  7) == Date("2015-11-07", fmt);
  bool test12 = Date(2015, DEC, 31) == Date("2015-12-31", fmt);
   // Assert

  BOOST_TEST(test1);
  BOOST_TEST(test2);
  BOOST_TEST(test3);
  BOOST_TEST(test4);
  BOOST_TEST(test5);
  BOOST_TEST(test6);
  BOOST_TEST(test7);
  BOOST_TEST(test8);
  BOOST_TEST(test9);
  BOOST_TEST(test10);
  BOOST_TEST(test11);
  BOOST_TEST(test12);
}

BOOST_AUTO_TEST_CASE(Constructor_GivenStringInFormat2_StringIsCorrectlyParsed) {
  // Arrange
  auto fmt = Date::Format::date2;
    
  // Act
  bool test1  = Date(2015, JAN, 30) == Date("15-01-30", fmt);
  bool test2  = Date(2015, FEB,  3) == Date("15-02-03", fmt);
  bool test3  = Date(2015, MAR,  2) == Date("15-03-02", fmt);
  bool test4  = Date(2015, APR, 15) == Date("15-04-15", fmt);
  bool test5  = Date(2015, MAY, 20) == Date("15-05-20", fmt);
  bool test6  = Date(2015, JUN, 23) == Date("15-06-23", fmt);
  bool test7  = Date(2015, JUL, 13) == Date("15-07-13", fmt);
  bool test8  = Date(2015, AUG,  2) == Date("15-08-02", fmt);
  bool test9  = Date(2015, SEP, 15) == Date("15-09-15", fmt);
  bool test10 = Date(2015, OCT,  9) == Date("15-10-09", fmt);
  bool test11 = Date(2015, NOV,  7) == Date("15-11-07", fmt);
  bool test12 = Date(2015, DEC, 31) == Date("15-12-31", fmt);
  
   // Assert

  BOOST_TEST(test1);
  BOOST_TEST(test2);
  BOOST_TEST(test3);
  BOOST_TEST(test4);
  BOOST_TEST(test5);
  BOOST_TEST(test6);
  BOOST_TEST(test7);
  BOOST_TEST(test8);
  BOOST_TEST(test9);
  BOOST_TEST(test10);
  BOOST_TEST(test11);
  BOOST_TEST(test12);
}

BOOST_AUTO_TEST_CASE(Constructor_GivenStringInFormat3_StringIsCorrectlyParsed) {
  // Arrange
  auto fmt = Date::Format::date3;

  // Act
  bool test1  = Date(2015, JAN, 30) == Date("2015JAN30", fmt);
  bool test2  = Date(2015, FEB,  3) == Date("2015FEB03", fmt);
  bool test3  = Date(2015, MAR,  2) == Date("2015MAR02", fmt);
  bool test4  = Date(2015, APR, 15) == Date("2015APR15", fmt);
  bool test5  = Date(2015, MAY, 20) == Date("2015MAY20", fmt);
  bool test6  = Date(2015, JUN, 23) == Date("2015JUN23", fmt);
  bool test7  = Date(2015, JUL, 13) == Date("2015JUL13", fmt);
  bool test8  = Date(2015, AUG,  2) == Date("2015AUG02", fmt);
  bool test9  = Date(2015, SEP, 15) == Date("2015SEP15", fmt);
  bool test10 = Date(2015, OCT,  9) == Date("2015OCT09", fmt);
  bool test11 = Date(2015, NOV,  7) == Date("2015NOV07", fmt);
  bool test12 = Date(2015, DEC, 31) == Date("2015DEC31", fmt);
  
  // Assert
  BOOST_TEST(test1);
  BOOST_TEST(test2);
  BOOST_TEST(test3);
  BOOST_TEST(test4);
  BOOST_TEST(test5);
  BOOST_TEST(test6);
  BOOST_TEST(test7);
  BOOST_TEST(test8);
  BOOST_TEST(test9);
  BOOST_TEST(test10);
  BOOST_TEST(test11);
  BOOST_TEST(test12);
  
}

BOOST_AUTO_TEST_CASE(Constructor_GivenStringInFormat4_StringIsCorrectlyParsed) {
  // Arrange
  auto fmt = Date::Format::date4;

  // Act
  bool test1  = Date(2015, JAN, 30) == Date("2015/01/30", fmt);
  bool test2  = Date(2015, FEB,  3) == Date("2015/02/03", fmt);
  bool test3  = Date(2015, MAR,  2) == Date("2015/03/02", fmt);
  bool test4  = Date(2015, APR, 15) == Date("2015/04/15", fmt);
  bool test5  = Date(2015, MAY, 20) == Date("2015/05/20", fmt);
  bool test6  = Date(2015, JUN, 23) == Date("2015/06/23", fmt);
  bool test7  = Date(2015, JUL, 13) == Date("2015/07/13", fmt);
  bool test8  = Date(2015, AUG,  2) == Date("2015/08/02", fmt);
  bool test9  = Date(2015, SEP, 15) == Date("2015/09/15", fmt);
  bool test10 = Date(2015, OCT,  9) == Date("2015/10/09", fmt);
  bool test11 = Date(2015, NOV,  7) == Date("2015/11/07", fmt);
  bool test12 = Date(2015, DEC, 31) == Date("2015/12/31", fmt);
  
  // Assert
  BOOST_TEST(test1);
  BOOST_TEST(test2);
  BOOST_TEST(test3);
  BOOST_TEST(test4);
  BOOST_TEST(test5);
  BOOST_TEST(test6);
  BOOST_TEST(test7);
  BOOST_TEST(test8);
  BOOST_TEST(test9);
  BOOST_TEST(test10);
  BOOST_TEST(test11);
  BOOST_TEST(test12);
}

BOOST_AUTO_TEST_CASE(Constructor_GivenStringInFormat5_StringIsCorrectlyParsed) {
  // Arrange
  auto fmt = Date::Format::date5;

  // Act
  bool test1  = Date(2015, JAN, 30) == Date("30/01/2015", fmt);
  bool test2  = Date(2015, FEB,  3) == Date("03/02/2015", fmt);
  bool test3  = Date(2015, MAR,  2) == Date("02/03/2015", fmt);
  bool test4  = Date(2015, APR, 15) == Date("15/04/2015", fmt);
  bool test5  = Date(2015, MAY, 20) == Date("20/05/2015", fmt);
  bool test6  = Date(2015, JUN, 23) == Date("23/06/2015", fmt);
  bool test7  = Date(2015, JUL, 13) == Date("13/07/2015", fmt);
  bool test8  = Date(2015, AUG,  2) == Date("02/08/2015", fmt);
  bool test9  = Date(2015, SEP, 15) == Date("15/09/2015", fmt);
  bool test10 = Date(2015, OCT,  9) == Date("09/10/2015", fmt);
  bool test11 = Date(2015, NOV,  7) == Date("07/11/2015", fmt);
  bool test12 = Date(2015, DEC, 31) == Date("31/12/2015", fmt);
  
  // Assert
  BOOST_TEST(test1);
  BOOST_TEST(test2);
  BOOST_TEST(test3);
  BOOST_TEST(test4);
  BOOST_TEST(test5);
  BOOST_TEST(test6);
  BOOST_TEST(test7);
  BOOST_TEST(test8);
  BOOST_TEST(test9);
  BOOST_TEST(test10);
  BOOST_TEST(test11);
  BOOST_TEST(test12);
}

BOOST_AUTO_TEST_CASE(Constructor_GivenStringInFormat6_StringIsCorrectlyParsed) {
  // Arrange
  auto fmt = Date::Format::date6;

  // Act
  bool test1  = Date(2015, JAN, 30) == Date("30JAN2015", fmt);
  bool test2  = Date(2015, FEB,  3) == Date("03FEB2015", fmt);
  bool test3  = Date(2015, MAR,  2) == Date("02MAR2015", fmt);
  bool test4  = Date(2015, APR, 15) == Date("15APR2015", fmt);
  bool test5  = Date(2015, MAY, 20) == Date("20MAY2015", fmt);
  bool test6  = Date(2015, JUN, 23) == Date("23JUN2015", fmt);
  bool test7  = Date(2015, JUL, 13) == Date("13JUL2015", fmt);
  bool test8  = Date(2015, AUG,  2) == Date("02AUG2015", fmt);
  bool test9  = Date(2015, SEP, 15) == Date("15SEP2015", fmt);
  bool test10 = Date(2015, OCT,  9) == Date("09OCT2015", fmt);
  bool test11 = Date(2015, NOV,  7) == Date("07NOV2015", fmt);
  bool test12 = Date(2015, DEC, 31) == Date("31DEC2015", fmt);
  
  // Assert
  BOOST_TEST(test1);
  BOOST_TEST(test2);
  BOOST_TEST(test3);
  BOOST_TEST(test4);
  BOOST_TEST(test5);
  BOOST_TEST(test6);
  BOOST_TEST(test7);
  BOOST_TEST(test8);
  BOOST_TEST(test9);
  BOOST_TEST(test10);
  BOOST_TEST(test11);
  BOOST_TEST(test12);
}

BOOST_AUTO_TEST_CASE(getDay_returnsDayNumber) {
  // Arrange
  Date date(2015, MAR, 13);
  // Act
  bool test = date.getDay() == 13;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(getMonth_returnsMonthNumber) {
  // Arrange
  Date date(2015, MAR, 13);
  // Act
  bool test = date.getMonth() == 3;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(getYear_returnsYearNumber) {
  // Arrange
  Date date(2015, MAR, 13);
  // Act
  bool test = date.getYear() == 2015;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(getString_returnsDateAsString) {
  // Arrange
  Date date1(2015, MAR,  6);
  Date date2(2015, APR, 21);
  Date date3(2015, OCT,  6);
  Date date4(2015, DEC, 26);
  // Act
  bool test1 = date1.getString() == "2015-03-06";
  bool test2 = date2.getString() == "2015-04-21";
  bool test3 = date3.getString() == "2015-10-06";
  bool test4 = date4.getString() == "2015-12-26";
  // Assert
  BOOST_TEST(test1);
  BOOST_TEST(test2);
  BOOST_TEST(test3);
  BOOST_TEST(test4);
}

BOOST_AUTO_TEST_CASE(getN_givenDate_RetunNumberOfDaysFrom1900JAN01) {
  // Arrange
  Date date(2015,JUN,13);
  int date_number = 42168;
  // Act
  bool test = date.getN() == date_number;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(setDay_providedDayToDate_DayIsCorrectlyChanged) {
  // Arrange
  Date date(2015, OCT, 1);
  // Act
  date.setDay(15);
  bool test = date.getDay() == 15;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(setMonth_providedMonthToDate_MonthIsCorrectlyChanged) {
  // Arrange
  Date date(2015, OCT, 1);
  // Act
  date.setMonth(2);
  bool test = date.getMonth() == 2;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(setYear_providedYearToDate_YearIsCorrectlyChanged) {
  // Arrange
  Date date(2015, OCT, 1);
  // Act
  date.setYear(2018);
  bool test = date.getYear() == 2018;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(increament_IncreaseDayByOne) {
  // Arrange
  Date date(2015, APR, 10);
  // Act
  date++;
  bool test = date.getDay() == 11;
  // Assert
  BOOST_TEST(test);
}


BOOST_AUTO_TEST_CASE(decreament_DecreaseDayByOne) {
  // Arrange
  Date date(2015, APR, 10);
  // Act
  date--;
  bool test = date.getDay() == 9;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(moveToEndOfMonth_MovesDateToEndOfMonth) {
  // Arrange
  Date date(2015,APR,13);
  Date date_eom(2015, APR, 30);
  // Act
  date.moveToEndOfMonth();
  bool test = date == date_eom;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(moveToEndOfYear_MovesDateToEndOfYear) {
  // Arrange
  Date date(2015,APR,13);
  Date date_eoy(2015, DEC, 31);
  // Act
  date.moveToEndOfYear();
  bool test = date == date_eoy;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(isValid_givenValidDate_returnsTrue) {
  // Arrange
  Date date(2018,5,17);
  // Act
  bool test = date.isValid();
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(isValid_givenInvalidDate_returnsFalse) {
  // Arrange
  Date date1(2018,13,17);
  Date date2(2018,12,32);
  Date date3(2018,2,29);
  // Act
  bool test1 = date1.isValid();
  bool test2 = date2.isValid();
  bool test3 = date3.isValid();
  // Assert
  BOOST_TEST(!test1);
  BOOST_TEST(!test2);
  BOOST_TEST(!test3);
}

BOOST_AUTO_TEST_CASE(isLeapYear_givenLeapYear_returnsTrue) {
  // Arrange
  Date date(2012,5,17);
  // Act
  bool test = date.isLeapYear();
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(isLeapYear_givenNonLeapYear_returnsFalse) {
  // Arrange
  Date date(2018,12,17);
  // Act
  bool test = date.isLeapYear();
  // Assert
  BOOST_TEST(!test);
}

BOOST_AUTO_TEST_CASE(isEndOfMonth_givenEOM_returnsTrue) {
  // Arrange
  Date date(2012,5,31);
  // Act
  bool test = date.isEndOfMonth();
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(isEndOfMonth_givenNotEOM_returnsFalse) {
  // Arrange
  Date date(2018,12,17);
  // Act
  bool test = date.isEndOfMonth();
  // Assert
  BOOST_TEST(!test);
}

BOOST_AUTO_TEST_CASE(isEndOfYear_givenEOY_returnsTrue) {
  // Arrange
  Date date(2012,12,31);
  // Act
  bool test = date.isEndOfYear();
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(isEndOfYear_givenNotEOY_returnsFalse) {
  // Arrange
  Date date(2018,11,30);
  // Act
  bool test = date.isEndOfYear();
  // Assert
  BOOST_TEST(!test);
}

BOOST_AUTO_TEST_CASE(addingTenor_returnsDateShiftedByTenor) {
  // Arrange
  Date date(2018,JAN,1);

  // Act
  Date date_plus_1D = date + 1*DAY;
  Date date_plus_2W = date + 2*WEEK;
  Date date_plus_3M = date + 3*MONTH;
  Date date_plus_2Q = date + 2*QUARTER;
  Date date_plus_1Y = date + 1*YEAR;
  
  bool test1 = date_plus_1D == Date(2018,JAN,2);
  bool test2 = date_plus_2W == Date(2018,JAN,15);
  bool test3 = date_plus_3M == Date(2018,APR,1);
  bool test4 = date_plus_2Q == Date(2018,JUL,1);
  bool test5 = date_plus_1Y == Date(2019,JAN,1);
  
  // Assert
  BOOST_TEST(test1);
  BOOST_TEST(test2);
  BOOST_TEST(test3);
  BOOST_TEST(test4);
  BOOST_TEST(test5);
}

BOOST_AUTO_TEST_CASE(substractingTenor_returnsDateShiftedByTenor) {
  // Arrange
  Date date(2018,MAY,15);

  // Act
  Date date_plus_1D = date - 1*DAY;
  Date date_plus_2W = date - 2*WEEK;
  Date date_plus_3M = date - 3*MONTH;
  Date date_plus_2Q = date - 2*QUARTER;
  Date date_plus_1Y = date - 1*YEAR;
  
  bool test1 = date_plus_1D == Date(2018,MAY,14);
  bool test2 = date_plus_2W == Date(2018,MAY,1);
  bool test3 = date_plus_3M == Date(2018,FEB,15);
  bool test4 = date_plus_2Q == Date(2017,NOV,15);
  bool test5 = date_plus_1Y == Date(2017,MAY,15);
  
  // Assert
  BOOST_TEST(test1);
  BOOST_TEST(test2);
  BOOST_TEST(test3);
  BOOST_TEST(test4);
  BOOST_TEST(test5);
}

BOOST_AUTO_TEST_CASE(equality_whenGivenTheSameDates_ReturnsTrue) {
  // Arrange
  Date date1(2018,MAY,1);
  Date date2(2018,MAY,1);
  // Act
  bool test = date1 == date2;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(equality_whenGivenDifferentDates_ReturnsFalse) {
  // Arrange
  Date date1(2018,MAY,1);
  Date date2(2018,MAY,2);
  // Act
  bool test = date1 == date2;
  // Assert
  BOOST_TEST(!test);
}

BOOST_AUTO_TEST_CASE(nonequality_whenGivenTheSameDates_ReturnsFalse) {
  // Arrange
  Date date1(2018,MAY,1);
  Date date2(2018,MAY,1);
  // Act
  bool test = date1 != date2;
  // Assert
  BOOST_TEST(!test);
}

BOOST_AUTO_TEST_CASE(nonequality_whenGivenDifferentDates_ReturnsTrue) {
  // Arrange
  Date date1(2018,MAY,1);
  Date date2(2018,MAY,2);
  // Act
  bool test = date1 != date2;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(smaller_whenGivenTheSameDates_ReturnsFalse) {
  // Arrange
  Date date1(2018,MAY,1);
  Date date2(2018,MAY,1);
  // Act
  bool test = date1 < date2;
  // Assert
  BOOST_TEST(!test);
}

BOOST_AUTO_TEST_CASE(smaller_whenFirstDateIsLaterThenSecond_ReturnsFalse) {
  // Arrange
  Date date1(2018,MAY,2);
  Date date2(2018,MAY,1);
  // Act
  bool test = date1 < date2;
  // Assert
  BOOST_TEST(!test);
}

BOOST_AUTO_TEST_CASE(smaller_whenFirstDateIsEarlierThenSecond_ReturnsTrue) {
  // Arrange
  Date date1(2018,MAY,1);
  Date date2(2018,MAY,2);
  // Act
  bool test = date1 < date2;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(larger_whenGivenTheSameDates_ReturnsFalse) {
  // Arrange
  Date date1(2018,MAY,1);
  Date date2(2018,MAY,1);
  // Act
  bool test = date1 > date2;
  // Assert
  BOOST_TEST(!test);
}

BOOST_AUTO_TEST_CASE(larger_whenFirstDateIsLaterThenSecond_ReturnsTrue) {
  // Arrange
  Date date1(2018,MAY,2);
  Date date2(2018,MAY,1);
  // Act
  bool test = date1 > date2;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(larger_whenFirstDateIsEarlierThenSecond_ReturnsFalse) {
  // Arrange
  Date date1(2018,MAY,1);
  Date date2(2018,MAY,2);
  // Act
  bool test = date1 > date2;
  // Assert
  BOOST_TEST(!test);
}

BOOST_AUTO_TEST_CASE(smallerEqual_whenGivenTheSameDates_ReturnsTrue) {
  // Arrange
  Date date1(2018,MAY,1);
  Date date2(2018,MAY,1);
  // Act
  bool test = date1 <= date2;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(smallerEqual_whenFirstDateIsLaterThenSecond_ReturnsFalse) {
  // Arrange
  Date date1(2018,MAY,2);
  Date date2(2018,MAY,1);
  // Act
  bool test = date1 <= date2;
  // Assert
  BOOST_TEST(!test);
}

BOOST_AUTO_TEST_CASE(smallerEqual_whenFirstDateIsEarlierThenSecond_ReturnsTrue) {
  // Arrange
  Date date1(2018,MAY,1);
  Date date2(2018,MAY,2);
  // Act
  bool test = date1 <= date2;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(largerEqual_whenGivenTheSameDates_ReturnsTrue) {
  // Arrange
  Date date1(2018,MAY,1);
  Date date2(2018,MAY,1);
  // Act
  bool test = date1 >= date2;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(largerEqual_whenFirstDateIsLaterThenSecond_ReturnsTrue) {
  // Arrange
  Date date1(2018,MAY,2);
  Date date2(2018,MAY,1);
  // Act
  bool test = date1 >= date2;
  // Assert
  BOOST_TEST(test);
}

BOOST_AUTO_TEST_CASE(largerEqual_whenFirstDateIsEarlierThenSecond_ReturnsFalse) {
  // Arrange
  Date date1(2018,MAY,1);
  Date date2(2018,MAY,2);
  // Act
  bool test = date1 >= date2;
  // Assert
  BOOST_TEST(!test);
}

BOOST_AUTO_TEST_SUITE_END()
