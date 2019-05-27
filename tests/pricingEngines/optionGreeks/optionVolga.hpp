BOOST_AUTO_TEST_SUITE(PricingEngines_OptionGreeks_optionVolga)

BOOST_AUTO_TEST_CASE(getRisks_ForCentralDifferencingScheme_GetCorrectVolga) {
  // Arrange
  AnalyticalPricingEngine prizer;
  SmartPointer<julian::OptionGreeks> risks = BuildGreeksReport()
    .withVolga(1e-5, NumDiffScheme::CNTR)
    .build();

  std::vector<BlackScholesModel> models;
  std::vector<EuropeanOpt> options;
  std::vector<std::map<std::string, double> > results;
  std::tie(models, options, results) = TestContainer::getOptionGreeksTestData();
    
  // Act
  std::vector<double> volga;
  for (unsigned int i = 0; i < models.size(); i++) {
    auto report = risks->getRisks(models[i], prizer, options[i]);
    volga.push_back(report["Volga"]);
  }
  // Assert
  for (unsigned int i = 0; i < models.size(); i++) {
    BOOST_TEST(volga[i] == results[i]["Volga"], tt::tolerance(5e-4));
  }
}

BOOST_AUTO_TEST_CASE(getRisks_ForBackwardDifferencingScheme_GetCorrectVolga) {
  // Arrange
  AnalyticalPricingEngine prizer;
  SmartPointer<julian::OptionGreeks> risks = BuildGreeksReport()
    .withVolga(1e-5, NumDiffScheme::BWD)
    .build();

  std::vector<BlackScholesModel> models;
  std::vector<EuropeanOpt> options;
  std::vector<std::map<std::string, double> > results;
  std::tie(models, options, results) = TestContainer::getOptionGreeksTestData();
    
  // Act
  std::vector<double> volga;
  for (unsigned int i = 0; i < models.size(); i++) {
    auto report = risks->getRisks(models[i], prizer, options[i]);
    volga.push_back(report["Volga"]);
  }
  // Assert
  for (unsigned int i = 0; i < models.size(); i++) {
    BOOST_TEST(volga[i] == results[i]["Volga"], tt::tolerance(5e-4));
  }
}

BOOST_AUTO_TEST_CASE(getRisks_ForForwardDifferencingScheme_GetCorrectVolga) {
  // Arrange
  AnalyticalPricingEngine prizer;
  SmartPointer<julian::OptionGreeks> risks = BuildGreeksReport()
    .withVolga(1e-5, NumDiffScheme::CNTR)
    .build();

  std::vector<BlackScholesModel> models;
  std::vector<EuropeanOpt> options;
  std::vector<std::map<std::string, double> > results;
  std::tie(models, options, results) = TestContainer::getOptionGreeksTestData();
    
  // Act
  std::vector<double> volga;
  for (unsigned int i = 0; i < models.size(); i++) {
    auto report = risks->getRisks(models[i], prizer, options[i]);
    volga.push_back(report["Volga"]);
  }
  // Assert
  for (unsigned int i = 0; i < models.size(); i++) {
    BOOST_TEST(volga[i] == results[i]["Volga"], tt::tolerance(5e-4));
  }
}

BOOST_AUTO_TEST_SUITE_END()
