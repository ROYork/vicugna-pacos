# curl_references example
find_package(CURL REQUIRED)

add_executable(curl_references
    main.cpp
    get_assets.cpp
)

target_link_libraries(curl_references PRIVATE
    vp_trading
    CURL::libcurl
)
