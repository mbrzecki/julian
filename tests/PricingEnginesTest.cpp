#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PricingEngines
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

#include <juliant.hpp>
#include "factoryInit.hpp"
#include "testDataProvider.hpp"

#include "pricingEngines/OptionGreeks/optionPV.hpp"
#include "pricingEngines/OptionGreeks/optionDelta.hpp"
#include "pricingEngines/OptionGreeks/optionGamma.hpp"
 #include "pricingEngines/OptionGreeks/optionVanna.hpp"
 #include "pricingEngines/OptionGreeks/optionVega.hpp"
 #include "pricingEngines/OptionGreeks/optionVolga.hpp"
