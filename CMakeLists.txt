set(cmake_version 3.13.1)

cmake_minimum_required(VERSION ${cmake_version})

set(AppName "fastmap")

project(${AppName} 
		VERSION 1.0.0.0
		LANGUAGES CXX)
		
message(STATUS "cur c++ compiler is:${CMAKE_CXX_COMPILER}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -DNDEBUG -fPIC -Wall")
#set(CMAKE_BUILD_TYPE Debug)

set(BOOST_ROOT "./threadpool11/threadpool11/ext/include")
set(Boost_NO_SYSTEM_PATHS ON)

add_subdirectory(threadpool11)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_FLAGS "-std=c++14 -O2 -DNDEBUG -fPIC -Wall -pthread")

set(TBB_DIR tbb2019_20181203oss/cmake)
find_package(TBB COMPONENTS tbb tbbmalloc tbb_preview REQUIRED)

set(INCLUDE_DIRS
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/threadpool11/threadpool11/include
	)
set(HEADERS 
	${CMAKE_SOURCE_DIR}/include/storage.h
	)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCES
	${SOURCE_DIR}/main.cpp
	${SOURCE_DIR}/storage.cpp
	)

include_directories("${INCLUDE_DIRS}")

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
#target_link_libraries (${AppName} threadpool11)
target_link_libraries (${AppName} ${TBB_IMPORTED_TARGETS})

file(COPY ${RES_FILES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/resources")
