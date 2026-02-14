cmake_minimum_required(VERSION 3.26)

project(VicugnaPacosPrj LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --- date ---
find_package(date QUIET)
if(NOT date_FOUND)
  message(STATUS "date not found locally — fetching v3.0.4")
  FetchContent_Declare(
    date
    GIT_REPOSITORY https://github.com/HowardHinnant/date
    GIT_TAG        v3.0.4
  )
  FetchContent_MakeAvailable(date)
endif()

# --- glaze (always fetch specific version) ---
FetchContent_Declare(
  glaze
  GIT_REPOSITORY https://github.com/stephenberry/glaze.git
  GIT_TAG        v5.5.5
)
FetchContent_MakeAvailable(glaze)

# --- GoogleTest ---
find_package(GTest QUIET)
if(NOT GTest_FOUND)
  message(STATUS "GTest not found locally — fetching v1.17.0")
  FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
  )
  FetchContent_MakeAvailable(GoogleTest)
endif()

# --- IXWebSocket (always fetch — needs specific TLS configuration) ---
FetchContent_Declare(
  ixwebsocket
  GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
  GIT_TAG        v11.4.5
)
set(USE_TLS ON CACHE BOOL "Enable TLS support" FORCE)
set(USE_OPEN_SSL ON CACHE BOOL "Use OpenSSL for TLS" FORCE)
FetchContent_MakeAvailable(ixwebsocket)

# Reference Python API (not built — downloaded for developer reference only)
FetchContent_Declare(
  alpaca_py
  GIT_REPOSITORY https://github.com/alpacahq/alpaca-py.git
  GIT_TAG        v0.43.2
  SOURCE_SUBDIR  _does_not_exist_
)
FetchContent_MakeAvailable(alpaca_py)

add_subdirectory(vp_api)
add_subdirectory(vp_trading)
add_subdirectory(vp_examples)
