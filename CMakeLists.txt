# min requirement

cmake_minimum_required(VERSION 3.1.0)

# setting cpp 11 
set (CMAKE_CXX_STANDARD 11)

# project name
project (LinAlg)

# seting prefix
SET(CMAKE_INSTALL_PREFIX "./" CACHE INTERNAL "Prefix prepended to install directories" FORCE)
# include paths

INCLUDE_DIRECTORIES(./include)

# get sources
# Find source files
file(GLOB SOURCES src/*.cpp)

# executable name
#add_executable(myapp ${SOURCES})

# library name for lib project
add_library (linalg SHARED ${SOURCES})

install(TARGETS linalg DESTINATION lib)
#install(FILES pmaths.h DESTINATION include)

# setting out put paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
