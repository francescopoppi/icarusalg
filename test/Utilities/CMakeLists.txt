cet_test(rounding_test USE_BOOST_UNIT)
cet_test(ChangeMonitor_test USE_BOOST_UNIT)

cet_test(FastAndPoorGauss_test
  LIBRARIES
    ROOT::MathCore
    ROOT::Hist
    ROOT::RIO
    ROOT::Core
  USE_BOOST_UNIT
  )

cet_test(SampledFunction_test USE_BOOST_UNIT)

cet_test(FixedBins_test USE_BOOST_UNIT)
cet_test(IntegerRanges_test USE_BOOST_UNIT)

cet_test(BinningSpecs_test
  LIBRARIES
    icarusalg_Utilities
  USE_BOOST_UNIT
  )
cet_test(NonRandomCounter_test
  LIBRARIES
    icarusalg_Utilities
    CLHEP::CLHEP
  USE_BOOST_UNIT
  )
