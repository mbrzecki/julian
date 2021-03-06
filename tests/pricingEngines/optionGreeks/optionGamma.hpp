BOOST_AUTO_TEST_SUITE(PricingEngines_OptionGreeks_optionGamma)

BOOST_AUTO_TEST_CASE(getRisks_ForCentralDifferencingScheme_GetCorrectGamma) {
  // Arrange
  AnalyticalPricingEngine prizer;
  SmartPointer<julian::OptionGreeks> risks = BuildGreeksReport()
    .withGamma(1e-4, NumDiffScheme::CNTR)
    .build();

  std::vector<BlackScholesModel> models;
  std::vector<EuropeanOpt> options;
  std::vector<std::map<std::string, double> > results;
  std::tie(models, options, results) = TestContainer::getOptionGreeksTestData();
    
  // Act
  std::vector<double> gamma;
  for (unsigned int i = 0; i < models.size(); i++) {
    auto report = risks->getRisks(models[i], prizer, options[i]);
    gamma.push_back(report["Gamma"]);
  }
  // Assert
  for (unsigned int i = 0; i < models.size(); i++) {
    BOOST_TEST(gamma[i] == results[i]["Gamma"], tt::tolerance(5e-4));
  }
}

BOOST_AUTO_TEST_CASE(getRisks_ForBackwardDifferencingScheme_GetCorrectGamma) {
  // Arrange
  AnalyticalPricingEngine prizer;
  SmartPointer<julian::OptionGreeks> risks = BuildGreeksReport()
    .withGamma(1e-4, NumDiffScheme::BWD)
    .build();

  std::vector<BlackScholesModel> models;
  std::vector<EuropeanOpt> options;
  std::vector<std::map<std::string, double> > results;
  std::tie(models, options, results) = TestContainer::getOptionGreeksTestData();
    
  // Act
  std::vector<double> gamma;
  for (unsigned int i = 0; i < models.size(); i++) {
    auto report = risks->getRisks(models[i], prizer, options[i]);
    gamma.push_back(report["Gamma"]);
  }
  // Assert
  for (unsigned int i = 0; i < models.size(); i++) {
    BOOST_TEST(gamma[i] == results[i]["Gamma"], tt::tolerance(5e-4));
  }
}

BOOST_AUTO_TEST_CASE(getRisks_ForForwardDifferencingScheme_GetCorrectGamma) {
  // Arrange
  AnalyticalPricingEngine prizer;
  SmartPointer<julian::OptionGreeks> risks = BuildGreeksReport()
    .withGamma(1e-4, NumDiffScheme::FWD)
    .build();

  std::vector<BlackScholesModel> models;
  std::vector<EuropeanOpt> options;
  std::vector<std::map<std::string, double> > results;
  std::tie(models, options, results) = TestContainer::getOptionGreeksTestData();
    
  // Act
  std::vector<double> gamma;
  for (unsigned int i = 0; i < models.size(); i++) {
    auto report = risks->getRisks(models[i], prizer, options[i]);
    gamma.push_back(report["Gamma"]);
  }
  // Assert
  for (unsigned int i = 0; i < models.size(); i++) {
    BOOST_TEST(gamma[i] == results[i]["Gamma"], tt::tolerance(5e-4));
  }
}

BOOST_AUTO_TEST_SUITE_END()
