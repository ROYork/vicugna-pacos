# vp_trading — Alpaca Trading Client
add_library(vp_trading
    src/TradingClient.cpp
)

target_sources(vp_trading PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include
    FILES
    include/vp/TradingClient.h
)

target_link_libraries(vp_trading PUBLIC
    ixwebsocket
    vp_api
)

target_include_directories(vp_trading PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
