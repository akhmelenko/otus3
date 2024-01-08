#pragma once

#include "db.h"

#include <string>
#include <iostream>

class DummyConnection : public Connection {
    public:
    bool Login(std::string& username, std::string& password) override;
    bool Logout() override;
};
