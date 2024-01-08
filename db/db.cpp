
#include "db.h"

DataBase::DataBase(Connection* connection, std::string& username, std::string& password) : connection_(connection) {
            connection_->Login(username, password);
            std::cout << "Logged In" << std::endl;
        }
DataBase::~DataBase() { 
    connection_->Logout();
    std::cout << "Logged Out" << std::endl;    
}