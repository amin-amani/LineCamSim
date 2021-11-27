cmake_minimum_required(VERSION 3.5)

project(LineCamSim LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(OpenCV REQUIRED)

set(OPENCV_INC "/usr/local/include/opencv4" )
include_directories(
            ${OPENCV_INC}
    )
add_executable(LineCamSim
  main.cpp
)
target_link_libraries(LineCamSim
    Qt5::Core
    ${OpenCV_LIBS}
    )
