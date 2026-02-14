# hello_TradingClient example
add_executable(hello_TradingClient
    main.cpp
)

target_link_libraries(hello_TradingClient PRIVATE
    vp_trading
)
