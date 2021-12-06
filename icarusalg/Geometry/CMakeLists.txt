
cet_make(
  SUBDIRS "details"
  LIBRARIES
          larcorealg_Geometry
          larcorealg_CoreUtils
          messagefacility::MF_MessageLogger
          fhiclcpp::fhiclcpp
          cetlib::cetlib
          cetlib_except::cetlib_except
          ROOT::Core
          ROOT::Physics
          ROOT::Geom
          ROOT::GenVector
        )


add_subdirectory(gdml)

install_headers(SUBDIRS "details")
install_fhicl(SUBDIRS "details")
install_source(SUBDIRS "details")


