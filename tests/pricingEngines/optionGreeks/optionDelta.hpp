BOOST_AUTO_TEST_SUITE(PricingEngines_OptionGreeks_optionDelta)



BOOST_AUTO_TEST_CASE(getRisks_ForCentralDifferencingScheme_GetCorrectDelta) {
  // Arrange
  AnalyticalPricingEngine prizer;
  SmartPointer<julian::OptionGreeks> risks = BuildGreeksReport()
    .withDelta(1e-4, NumDiffScheme::CNTR)
    .build();

  std::vector<BlackScholesModel> models;
  std::vector<EuropeanOpt> options;
  std::vector<std::map<std::string, double> > results;
  std::tie(models, options, results) = TestContainer::getOptionGreeksTestData();
    
  // Act
  std::vector<double> delta;
  for (unsigned int i = 0; i < models.size(); i++) {
    auto report = risks->getRisks(models[i], prizer, options[i]);
    delta.push_back(report["Delta"]);
  }
  // Assert
  for (unsigned int i = 0; i < models.size(); i++) {
    BOOST_TEST(delta[i] == results[i]["Delta"], tt::tolerance(1e-5));
  }
}

BOOST_AUTO_TEST_CASE(getRisks_ForBackwardDifferencingScheme_GetCorrectDelta) {
  // Arrange
  AnalyticalPricingEngine prizer;
  SmartPointer<julian::OptionGreeks> risks = BuildGreeksReport()
    .withDelta(1e-4, NumDiffScheme::BWD)
    .build();

  std::vector<BlackScholesModel> models;
  std::vector<EuropeanOpt> options;
  std::vector<std::map<std::string, double> > results;
  std::tie(models, options, results) = TestContainer::getOptionGreeksTestData();
    
  // Act
  std::vector<double> delta;
  for (unsigned int i = 0; i < models.size(); i++) {
    auto report = risks->getRisks(models[i], prizer, options[i]);
    delta.push_back(report["Delta"]);
  }
  // Assert
  for (unsigned int i = 0; i < models.size(); i++) {
    BOOST_TEST(delta[i] == results[i]["Delta"], tt::tolerance(1e-5));
  }
}

BOOST_AUTO_TEST_CASE(getRisks_ForForwardDifferencingScheme_GetCorrectDelta) {
  // Arrange
  AnalyticalPricingEngine prizer;
  SmartPointer<julian::OptionGreeks> risks = BuildGreeksReport()
    .withDelta(1e-4, NumDiffScheme::FWD)
    .build();

  std::vector<BlackScholesModel> models;
  std::vector<EuropeanOpt> options;
  std::vector<std::map<std::string, double> > results;
  std::tie(models, options, results) = TestContainer::getOptionGreeksTestData();
    
  // Act
  std::vector<double> delta;
  for (unsigned int i = 0; i < models.size(); i++) {
    auto report = risks->getRisks(models[i], prizer, options[i]);
    delta.push_back(report["Delta"]);
  }
  // Assert
  for (unsigned int i = 0; i < models.size(); i++) {
    BOOST_TEST(delta[i] == results[i]["Delta"], tt::tolerance(1e-5));
  }
}

BOOST_AUTO_TEST_SUITE_END()
