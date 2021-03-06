set(cmake_version 3.13.1)

cmake_minimum_required(VERSION ${cmake_version})

set(AppName "fastmap")

set(CMAKE_C_COMPILER "/usr/local/Cellar/gcc/8.2.0/bin/gcc-8")
set(CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc/8.2.0/bin/g++-8")

project(${AppName} 
		VERSION 1.0.0.0
		LANGUAGES CXX)
		
message(STATUS "cur c++ compiler is:${CMAKE_CXX_COMPILER}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -DNDEBUG -fPIC -Wall")

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(HEADERS 
	        ${INCLUDE_DIR}/storage.h
	        )

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCES
			${SOURCE_DIR}/main.cpp
			${SOURCE_DIR}/storage.cpp
			)

include_directories("${INCLUDE_DIR}")

# set(BOOST_COMPONENTS 
# 	        container
# 	        )

# set(Boost_USE_STATIC_LIBS ON)

# find_package (Boost 1.69.0 COMPONENTS ${BOOST_COMPONENTS} REQUIRED)

# include_directories(${Boost_INCLUDE_DIRS})

set(RES_FILES
	${CMAKE_SOURCE_DIR}/resources/insert.txt
	${CMAKE_SOURCE_DIR}/resources/read.txt
)

# Setup testing
enable_testing()
add_subdirectory(tests)

# Create application
add_executable(${AppName} ${SOURCES} ${HEADERS} ${RES_FILES})

file(COPY ${RES_FILES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/resources")
