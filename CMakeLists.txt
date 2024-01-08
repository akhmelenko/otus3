# Cmake minimal version.
cmake_minimum_required(VERSION 3.10)

include(GoogleTest)

# INCREMENT IN MAIN CMakeLists.txt.
# Basic definitions.
set(CACHE_FILE ${CMAKE_SOURCE_DIR}/build_number_cache.txt)
# Read number from file and increment.
if(EXISTS ${CACHE_FILE})
    file(READ ${CACHE_FILE} INCREMENTED_VALUE)
    math(EXPR INCREMENTED_VALUE "${INCREMENTED_VALUE}+1")
else()
    set(INCREMENTED_VALUE "1")
endif()
# Update cache file.
file(WRITE ${CACHE_FILE} ${INCREMENTED_VALUE})
message("Build number: ${INCREMENTED_VALUE}")

# Variables.
set(PATCH_VERSION ${INCREMENTED_VALUE} CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(version VERSION ${PROJECT_VERSION})

find_package(GTest REQUIRED)
# include(GoogleTest)

configure_file(version_arg.h.in version_arg.h)

include_directories(version)
include_directories(db)

add_executable(helloworld_cli main.cpp)

# Detatched script file.
add_custom_command(
    TARGET helloworld_cli
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND}
        -D TEST_VARIABLE=55
        -P ${CMAKE_SOURCE_DIR}/"detached.cmake"
)

add_subdirectory(version)
add_subdirectory(db)

add_executable(test_version test_version.cpp)

gtest_add_tests(TARGET test_version
                TEST_SUFFIX .noArgs
                TEST_LIST myGoogleTests
)
set_tests_properties(${myGoogleTests} PROPERTIES TIMEOUT 10)

message("TEST_VARIABLE after script=${TEST_VARIABLE}")

set_target_properties(helloworld_cli version db test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Inclule Cmake binary directory to make code to see generated header files (version.h)
# CMAKE_BINARY_DIR - automaticaly substitute cmake build files directory.
target_include_directories(version
    PRIVATE "${CMAKE_BINARY_DIR}"
)

message("CMAKE_BINARY_DIR=" "${CMAKE_BINARY_DIR}")
# Automaticaly generated version variables:
message("PROJECT_VERSION_MAJOR=" "${PROJECT_VERSION_MAJOR}")
message("PROJECT_VERSION_MINOR=" "${PROJECT_VERSION_MINOR}")
message("PROJECT_VERSION_PATCH=" "${PROJECT_VERSION_PATCH}")
message("PROJECT_VERSION_TWEAK=" "${PROJECT_VERSION_TWEAK}")


target_link_libraries(helloworld_cli PRIVATE
    version
    db
)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(version PRIVATE
        /W4
    )
    target_compile_options(db PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(db PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)

target_include_directories(test_version PRIVATE ${GTEST_INCLUDE_DIRS} ${GMock_INCLUDE_DIR})
target_link_libraries(test_version PRIVATE 
    GTest::gtest 
    # GTest::gmock 
    version 
    db
)
