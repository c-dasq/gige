# Root CMakeLists.txt for the overall Pylon project
cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0074 NEW)    # respect <PACKAGE>_ROOT variables in "find_package"
include(CMakePrintHelpers)

project(MVIE-gige VERSION 0.0)

find_package(pylon 7.3.0 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(JSONCPP jsoncpp)

include_directories(${JSONCPP_INCLUDE_DIRS})
include_directories(/usr/include/jsoncpp)
include_directories(/usr/include/jsoncpp/json)

add_subdirectory(enumerate)
add_subdirectory(grab)
