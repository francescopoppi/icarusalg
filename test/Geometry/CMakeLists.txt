
# geometry test on ICARUS geometries

#
# the following are tests equivalent to the module ones, but with no framework
#
# unit test (use the hard-coded channel mapping for ICARUS geometry)
cet_test(geometry_icarus_test
  SOURCES geometry_icarus_test.cxx
  TEST_ARGS test_geometry_icarus.fcl
  LIBRARIES icarusalg_Geometry
            larcorealg_Geometry
            larcorealg::GeometryTestLib
            messagefacility::MF_MessageLogger
            fhiclcpp::fhiclcpp
            cetlib_except::cetlib_except
	    ROOT::Core
#  OPTIONAL_GROUPS Broken
)


# unit test (use the hard-coded configuration for ICARUS geometry)
# this uses BOOST for the test
cet_test(geometry_iterator_icarus_test
  SOURCES geometry_iterator_icarus_test.cxx
  TEST_ARGS test_geometry_iterators_icarus.fcl
  LIBRARIES icarusalg_Geometry
            larcorealg_Geometry
            larcorealg::GeometryTestLib
            messagefacility::MF_MessageLogger
            fhiclcpp::fhiclcpp
            cetlib_except::cetlib_except
	    ROOT::Core
  USE_BOOST_UNIT
)


# unit test (use the hard-coded configuration for ICARUS geometry)
cet_test(geometry_iterator_loop_icarus_test
  SOURCES geometry_iterator_loop_icarus_test.cxx
  TEST_ARGS test_geometry_iterators_icarus.fcl
  LIBRARIES icarusalg_Geometry
            larcorealg_Geometry
            larcorealg::GeometryTestLib
            messagefacility::MF_MessageLogger
            fhiclcpp::fhiclcpp
            cetlib_except::cetlib_except
	    ROOT::Core
)



install_headers()
install_source()
