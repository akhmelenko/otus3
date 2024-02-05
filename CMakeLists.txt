# Cmake minimal version.
cmake_minimum_required(VERSION 3.10)

include(GoogleTest)

# Variables.
set(PATCH_VERSION 2 CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(allocator VERSION ${PROJECT_VERSION})

find_package(GTest REQUIRED)
# include(GoogleTest)

# configure_file(version_arg.h.in version_arg.h)

include_directories(version)

add_executable(allocator main.cpp)

# add_subdirectory(version)

add_executable(test_version test_version.cpp)

gtest_add_tests(TARGET test_version
                TEST_SUFFIX .noArgs
                TEST_LIST myGoogleTests
)
set_tests_properties(${myGoogleTests} PROPERTIES TIMEOUT 10)

set_target_properties(allocator test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Inclule Cmake binary directory to make code to see generated header files (version.h)
# CMAKE_BINARY_DIR - automaticaly substitute cmake build files directory.
# target_include_directories(version
#     PRIVATE "${CMAKE_BINARY_DIR}"
# )

# target_link_libraries(ip_filter PRIVATE
#     version
# )

if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
    # target_compile_options(version PRIVATE
    #     /W4
    # )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    # target_compile_options(version PRIVATE
    #     -Wall -Wextra -pedantic -Werror
    # )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS allocator RUNTIME DESTINATION bin)

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
    #GTest::gmock 
    # version 
)