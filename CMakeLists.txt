cmake_minimum_required(VERSION 2.8)

project(UADetracConvertor)

find_package(OpenCV REQUIRED)

FIND_PACKAGE(Boost 1.40 COMPONENTS filesystem REQUIRED )

set(CMAKE_BUILD_TYPE Release)


include_directories(${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} )


set(SOURCE_FILES src/main.cpp src/tracker.cpp)

add_executable(UADetracConvertor ${SOURCE_FILES})

target_link_libraries(UADetracConvertor ${OpenCV_LIBS} ${Boost_LIBRARIES})
