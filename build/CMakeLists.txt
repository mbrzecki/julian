cmake_minimum_required(VERSION 3.6.2)
project (jULIAN_T)

# setting cmake scripts dir
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/included_scripts/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "./static_lib")

# compilation flags, linker flags

set( COMPILE_FLAGS "-std=c++17 -pedantic -Wall -Wextra -O3")
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
set( CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols")

link_directories(/usr/local/lib)

# searching for libraries needed

find_package( Boost REQUIRED COMPONENTS serialization program_options unit_test_framework)
find_package( Armadillo)
include( FIND_OOQP)
include( FIND_BLAS)
include( FIND_GSL)
include( FIND_MA27)
include( FIND_LAPACK)
include( FIND_GFORTRAN)
# include( FIND_QUANTLIB)

# adding directories with header files

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${ARMADILLO_INCLUDE_DIRS})
include_directories(../src)

# adding directories with source files

file(GLOB DATES "../src/dates/*.cpp")
file(GLOB YFS "../src/dates/yearFractions/*.cpp")
file(GLOB CALENDARS "../src/dates/calendars/*.cpp")
file(GLOB TIMEGRIDS "../src/dates/timeGrids/*.cpp")	

file(GLOB RATES "../src/interestRates/*.cpp")

file(GLOB INSTRUMENTS "../src/instruments/*.cpp")
file(GLOB LINEAR "../src/instruments/linear/*.cpp")
file(GLOB OPTIONS "../src/instruments/options/*.cpp")
file(GLOB BONDS "../src/instruments/bonds/*.cpp")

file(GLOB MARKETDATA "../src/marketData/*.cpp")
file(GLOB CURVES "../src/marketData/interestRateCurves/*.cpp")
file(GLOB CURVESINTER "../src/marketData/interestRateCurves/interpolators/*.cpp")
file(GLOB CURVESESTIM "../src/marketData/interestRateCurves/estimators/*.cpp")
file(GLOB CURVESCOST "../src/marketData/interestRateCurves/estimators/costFunctions/*.cpp")

file(GLOB VOLSURFACE "../src/marketData/volatility/*.cpp")

file(GLOB MARKETMODELS "../src/marketModels/*.cpp")

file(GLOB INTERPOLATION "../src/mathematics/interpolation/*.cpp")
file(GLOB REGRESSION "../src/mathematics/regressions/*.cpp")
file(GLOB NUMALG "../src/mathematics/numericalAlgorithms/*.cpp")
file(GLOB DISTRIBUTION "../src/mathematics/distributions/*.cpp")
file(GLOB STATS "../src/mathematics/statistics/*.cpp")
file(GLOB STOCHPROCESS "../src/mathematics/stochasticProcesses/*.cpp")
file(GLOB RNGS "../src/mathematics/RNGs/*.cpp")

file(GLOB PRICINGENGINES "../src/pricingEngines/*.cpp")
file(GLOB ANALYTICALPRICINGENGINES "../src/pricingEngines/analytical/*.cpp")
file(GLOB PVGREEKS "../src/pricingEngines/optionGreeks/*.cpp")

file(GLOB UTILS "../src/utils/*.cpp")


# creating macro variablesmake    

set(SOURCES ${DATES} ${YFS} ${CALENDARS} ${TIMEGRIDS}
	    ${RATES}
	    ${INSTRUMENTS} ${LINEAR} ${OPTIONS} ${BONDS}
	    ${MARKETDATA} ${CURVES} ${CURVESINTER} ${CURVESESTIM} ${CURVESCOST}
	    ${VOLSURFACE}
	    ${PRICINGENGINES} ${PVGREEKS} ${ANALYTICALPRICINGENGINES}
	    ${MARKETMODELS}
	    ${DISTRIBUTION} ${INTERPOLATION} ${NUMALG} ${REGRESSION} ${STATS} ${STOCHPROCESS} ${RNGS}
	    ${UTILS})	
	    
set(LINK_FLAG ${GSL_LIBRARIES} ${OOQP_LIBRARIES} ${MA27_LIBRARY} ${GFORTRAN} ${BLAS_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_SERIALIZATION_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${ARMADILLO_LIBRARIES})

# object library

add_library(julek OBJECT ${SOURCES})

# creating executables on the basis of cpp files in mains directory

file( GLOB APP_SOURCES "../mains/*.cpp" )
foreach( sourcefile ${APP_SOURCES} )

	 string( REGEX REPLACE "^.*/mains/" "" filename ${sourcefile})
	 string( REPLACE ".cpp" "" name ${filename} )

	 add_executable( ${name} ${sourcefile} $<TARGET_OBJECTS:julek>)
	 target_link_libraries(${name} ${LINK_FLAG})
	 
endforeach( sourcefile ${APP_SOURCES} )

option(TESTS "Add test suites" OFF)
if(TESTS)
    add_executable( TestSuites ../tests/test_suite.cpp $<TARGET_OBJECTS:julek>)
    target_link_libraries(TestSuites ${LINK_FLAG})    
endif(TESTS)
unset(TESTS CACHE)
