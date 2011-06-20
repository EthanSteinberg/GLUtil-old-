cmake_minimum_required(VERSION 2.6)

project(GLFont)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
   message(FATAL_ERROR "ERROR: Building in source, please build out of it")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -march=native -std=c++0x  -g -O0 -Wshadow")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")	

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/arch)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(Boost_ADDITIONAL_VERSIONS "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
set(BOOST_COMPONENTS system thread date_time)

find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(SFML REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_PATH})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_PATH})

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

include_directories(lib/jsoncpp-src-0.5.0/include)

set(JSONCPPLIB
   ${CMAKE_HOME_DIRECTORY}/lib/jsoncpp-src-0.5.0/libs/linux-gcc-4.5.3/libjson_linux-gcc-4.5.3_libmt.a)

add_library(jsoncpp STATIC IMPORTED)
set_target_properties(jsoncpp PROPERTIES IMPORTED_LOCATION ${JSONCPPLIB})


install(FILES ${JSONCPPLIB} DESTINATION lib/GLUtil)

add_subdirectory(src) 


