cmake_minimum_required(VERSION ${cmake_version})

project(${AppName}_tests)

add_subdirectory(googletest)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(storage_tests storage_tests.cpp ${SOURCE_DIR}/storage.cpp)
