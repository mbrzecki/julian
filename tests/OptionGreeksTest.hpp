BOOST_AUTO_TEST_SUITE(OptionGreeks)

BOOST_AUTO_TEST_CASE(OptionDelta_KnownTest, *boost::unit_test::label("OptionGreeks_KnownTest")) {
  // Arrange
  AnalyticalPricingEngine prizer;
  auto model  = TestContainer::GetBlackScholesModel();
  auto option = TestContainer::GetEuropeanOpt();
  
  SmartPointer<julian::OptionGreeks> risks = BuildGreeksReport()
    .withDelta(1e-4, NumDiffScheme::CNTR,"Delta_cntr")
    .withDelta(1e-4, NumDiffScheme::FWD, "Delta_fwd")
    .withDelta(1e-4, NumDiffScheme::BWD, "Delta_bwd")
    .build();
    
  // Act
  auto rr = risks->getRisks(model, prizer, option);
  
  // Assert
  BOOST_TEST(rr["Delta_cntr"] == 625.84955, tt::tolerance(1e-5));
  BOOST_TEST(rr["Delta_fwd"] == 625.84955, tt::tolerance(1e-5));
  BOOST_TEST(rr["Delta_bwd"] == 625.84955, tt::tolerance(1e-5));
}

BOOST_AUTO_TEST_CASE(OptionGamma_KnownTest, *boost::unit_test::label("OptionGreeks_KnownTest")) {
  // Arrange
  AnalyticalPricingEngine prizer;
  auto model  = TestContainer::GetBlackScholesModel();
  auto option = TestContainer::GetEuropeanOpt();
  
  SmartPointer<julian::OptionGreeks> risks = BuildGreeksReport()
    .withGamma(1e-3, NumDiffScheme::CNTR,"Gamma_cntr")
    .withGamma(1e-3, NumDiffScheme::FWD, "Gamma_fwd")
    .withGamma(1e-3, NumDiffScheme::BWD, "Gamma_bwd")
    .build();
    
  // Act
  auto rr = risks->getRisks(model, prizer, option);
  
  // Assert
  BOOST_TEST(rr["Gamma_cntr"] == 16.73872, tt::tolerance(5e-5));
  BOOST_TEST(rr["Gamma_fwd"] == 16.73872, tt::tolerance(5e-5));
  BOOST_TEST(rr["Gamma_bwd"] == 16.73872, tt::tolerance(5e-5));
}



BOOST_AUTO_TEST_SUITE_END()
