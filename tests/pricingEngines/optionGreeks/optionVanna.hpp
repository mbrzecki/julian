BOOST_AUTO_TEST_SUITE(PricingEngines_OptionGreeks_optionVanna)

BOOST_AUTO_TEST_CASE(getRisks_GetCorrectVanna) {
  // Arrange
  AnalyticalPricingEngine prizer;
  SmartPointer<julian::OptionGreeks> risks = BuildGreeksReport()
    .withVanna(1e-4)
    .build();

  std::vector<BlackScholesModel> models;
  std::vector<EuropeanOpt> options;
  std::vector<std::map<std::string, double> > results;
  std::tie(models, options, results) = TestContainer::getOptionGreeksTestData();
    
  // Act
  std::vector<double> vanna;
  for (unsigned int i = 0; i < models.size(); i++) {
    auto report = risks->getRisks(models[i], prizer, options[i]);
    vanna.push_back(report["Vanna"]);
  }
  // Assert
  for (unsigned int i = 0; i < models.size(); i++) {
    BOOST_TEST(vanna[i] == results[i]["Vanna"], tt::tolerance(5e-4));
  }
}

BOOST_AUTO_TEST_SUITE_END()
