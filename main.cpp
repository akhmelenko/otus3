#include "version/version.h"
#include "db/dummy_connection.h"
#include "db/db.h"

#include <iostream>

int main (int, char **) {
    std::cout << "Version: " << version() << std::endl;
    std::cout << "Hello, world!" << std::endl;
    DummyConnection dc;
    std::string nic = "my_nic";
    std::string pass = "my_pass";
    DataBase db(&dc, nic, pass);
    return 0;
}
