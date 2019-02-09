set(cmake_version 3.13.1)

cmake_minimum_required(VERSION ${cmake_version})

set(AppName "fastmap")

project(${AppName} 
		VERSION 1.0.0.0
		LANGUAGES CXX)
		
message(STATUS "cur c++ compiler is:${CMAKE_CXX_COMPILER}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC -Wall")
set(CMAKE_BUILD_TYPE Debug)

set(SOURCES
			${CMAKE_SOURCE_DIR}/src/main.cpp
			)

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
add_executable(${AppName} ${SOURCES} ${RES_FILES})

file(COPY ${RES_FILES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/resources")
