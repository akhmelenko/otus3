#pragma once

#include <iostream>
#include <string>

class Connection {
    public:
    virtual bool Login(std::string& username, std::string& password) = 0;
    virtual bool Logout() = 0;
};

class DataBase {
    public:
        DataBase(Connection* connection, std::string& username, std::string& password);
        ~DataBase();
    private:
        Connection* connection_;
};
