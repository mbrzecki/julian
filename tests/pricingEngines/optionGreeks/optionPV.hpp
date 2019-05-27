BOOST_AUTO_TEST_SUITE(PricingEngines_OptionGreeks_optionPV)

BOOST_AUTO_TEST_CASE(getRisks_GetCorrectPV) {
  // Arrange
  AnalyticalPricingEngine prizer;
  OptionPV pv;

  std::vector<BlackScholesModel> models;
  std::vector<EuropeanOpt> options;
  std::vector<std::map<std::string, double> > results;
  std::tie(models, options, results) = TestContainer::getOptionGreeksTestData();
    
  // Act
  std::vector<double> PVs;
  for (unsigned int i = 0; i < models.size(); i++) {
    auto risks = pv.getRisks(models[i], prizer, options[i]);
    PVs.push_back(risks["PV"]);
  }
  // Assert
  for (unsigned int i = 0; i < models.size(); i++) {
    BOOST_TEST(PVs[i] == results[i]["PV"], tt::tolerance(1e-6));
  }
}


BOOST_AUTO_TEST_SUITE_END()
