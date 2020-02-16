add_executable(TestMarketDataEndpoint TestMarketDataEndpoint.cc)
target_link_libraries(TestMarketDataEndpoint ssl crypto rest util ${Boost_LIBRARIES})

