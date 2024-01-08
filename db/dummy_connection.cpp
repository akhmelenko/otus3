
#include "dummy_connection.h"

#include <iostream>

bool DummyConnection::Login(std::string& username, std::string& password) {
    std::cout << "DummyConnection Logged In with " 
    << username << " " << password << std::endl;
    return true;
}
bool DummyConnection::Logout() {
    std::cout << "DummyConnection Logged Out" << std::endl;
    return true;
}

