# vp_api — header-only Alpaca Markets API types
add_library(vp_api INTERFACE)
add_library(vp::api ALIAS vp_api)

target_sources(vp_api INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include
    FILES
    include/vp/Account.h
    include/vp/AccountStatus.h
    include/vp/ActivityCategory.h
    include/vp/ActivityType.h
    include/vp/Adjustment.h
    include/vp/AlpacaTime.h
    include/vp/AssetClass.h
    include/vp/AssetExchange.h
    include/vp/AssetStatus.h
    include/vp/Calendar.h
    include/vp/Clock.h
    include/vp/ContractType.h
    include/vp/CorporateActionDateType.h
    include/vp/CorporateActionSubType.h
    include/vp/CorporateActionType.h
    include/vp/CorporateActionsType.h
    include/vp/CryptoFeed.h
    include/vp/DTBPCheck.h
    include/vp/DataFeed.h
    include/vp/Exchange.h
    include/vp/ExerciseStyle.h
    include/vp/MarketType.h
    include/vp/MostActivesBy.h
    include/vp/NewsImageSize.h
    include/vp/NonTradeActivityStatus.h
    include/vp/OptionsFeed.h
    include/vp/Order.h
    include/vp/OrderClass.h
    include/vp/OrderSide.h
    include/vp/OrderStatus.h
    include/vp/OrderType.h
    include/vp/PDTCheck.h
    include/vp/Position.h
    include/vp/PositionIntent.h
    include/vp/PositionSide.h
    include/vp/QueryOrderStatus.h
    include/vp/SupportedCurrencies.h
    include/vp/TimeFrame.h
    include/vp/TimeFrameUnit.h
    include/vp/TimeInForce.h
    include/vp/TradeActivityType.h
    include/vp/TradeConfirmationEmail.h
    include/vp/TradeEvent.h
    include/vp/alpaca_bars.h
    include/vp/alpaca_common_enums.h
    include/vp/alpaca_constants.h
    include/vp/QueryBuilder.h
    include/vp/Asset.h
    include/vp/AccountConfiguration.h
    include/vp/Watchlist.h
    include/vp/PortfolioHistory.h
    include/vp/OptionContract.h
    include/vp/CancelOrderResponse.h
    include/vp/ClosePositionResponse.h
    include/vp/TradeUpdate.h
    include/vp/GetOrdersRequest.h
    include/vp/GetOrderByIdRequest.h
    include/vp/ReplaceOrderRequest.h
    include/vp/OrderRequest.h
    include/vp/ClosePositionRequest.h
    include/vp/GetCalendarRequest.h
    include/vp/GetAssetsRequest.h
    include/vp/GetPortfolioHistoryRequest.h
    include/vp/CreateWatchlistRequest.h
    include/vp/UpdateWatchlistRequest.h
    include/vp/GetOptionContractsRequest.h
)

target_link_libraries(vp_api INTERFACE
    glaze::glaze
    date::date
)

target_include_directories(vp_api INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# --- Unit Tests ---
add_subdirectory(ut/)

# --- Install ---
include(GNUInstallDirs)

install(TARGETS vp_api
    EXPORT  vp_api-targets
    FILE_SET HEADERS
)

install(EXPORT      vp_api-targets
    NAMESPACE       vp::
    DESTINATION     ${CMAKE_INSTALL_LIBDIR}/cmake/vp_api
)

# Generate a minimal package-config so find_package(vp_api) works
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/vp_api-config-version.cmake"
    VERSION 0.1.0
    COMPATIBILITY AnyNewerVersion
)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/vp_api-config.cmake"
    "include(CMakeFindDependencyMacro)\n"
    "find_dependency(glaze)\n"
    "find_dependency(date)\n"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/vp_api-targets.cmake\")\n"
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/vp_api-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/vp_api-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/vp_api
)
