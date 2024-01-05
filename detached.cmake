# Basic definitions.
message("Detached script Start")

message("TEST_VARIABLE=${TEST_VARIABLE}")

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

set(TEST_VARIABLE 66)
