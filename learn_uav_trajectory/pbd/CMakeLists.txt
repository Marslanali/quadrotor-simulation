cmake_minimum_required(VERSION 3.5.1)
project(programming_by_demonstration)

set(CMAKE_CXX_STANDARD 11)
# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES
        main.cpp
        ${PROJECT_SOURCE_DIR}/src/datapoints.cpp
        ${PROJECT_SOURCE_DIR}/src/demonstrations.cpp
        ${PROJECT_SOURCE_DIR}/src/gmm.cpp
        ${PROJECT_SOURCE_DIR}/src/gmr.cpp
        ${PROJECT_SOURCE_DIR}/src/mvn.cpp
        ${PROJECT_SOURCE_DIR}/src/emInitilization.cpp
        ${PROJECT_SOURCE_DIR}/src/emInitilizationMlpack.cpp)
set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/datapoints.h
        ${PROJECT_SOURCE_DIR}/include/demonstrations.h
        ${PROJECT_SOURCE_DIR}/include/gmm.h
        ${PROJECT_SOURCE_DIR}/include/gmr.h
        ${PROJECT_SOURCE_DIR}/include/mvn.h
        ${PROJECT_SOURCE_DIR}/include/emInitilization.h
        ${PROJECT_SOURCE_DIR}/include/emInitilizationMlpack.h)

add_executable(programming_by_demonstration ${SOURCE_FILES}  ${HEADER_FILES} )

## Armadillo Libraries and MLPACK Libraries
find_package(Armadillo 5.04 REQUIRED)
#Matplotlib-cpp Libraries
find_package(PythonLibs 2.7)

# find libraries
find_library(ARMADILLO_LIBRARIES armadillo)

#target includes
include_directories(include ${PYTHON_INCLUDE_DIRS} ${ARMADILLO_INCLUDE_DIRS} ${MLPACK_INCLUDE_DIRS})

#target link .so libraries
target_link_libraries(programming_by_demonstration ${PYTHON_LIBRARIES}  ${ARMADILLO_LIBRARIES}  /usr/local/lib/libmlpack.so)



#target_include_directories(programming_by_demonstration PRIVATE ${PYTHON_INCLUDE_DIRS})
#target_link_libraries(programming_by_demonstration ${PYTHON_LIBRARIES})

## MLPACK
#add extra include directories
#include_directories(/usr/local/include)
# add extra lib directories
#link_directories(/usr/lib/x86_64-linux-gnu)
#target_link_libraries(programming_by_demonstration libmlpack.so )




