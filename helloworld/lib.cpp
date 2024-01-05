#include "lib.h"

#include "version.h"

#include <iostream>

int version() {
    std::cout << "PROJECT_VERSION_PATCH: " << PROJECT_VERSION_PATCH << std::endl;
    return PROJECT_VERSION_PATCH;
}
