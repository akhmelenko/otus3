#define BOOST_TEST_MODULE test_version

#include "helloworld/lib.h"

#include <boost/test/unit_test.hpp>
// #include <gtest/gtest.h>

#include <iostream>

// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wc99-extensions"

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version)
// #pragma GCC diagnostic pop 
{
    std::cout << "version=" << version() << std::endl;
    BOOST_CHECK(version() > 6);
}

BOOST_AUTO_TEST_SUITE_END()
