#include <iostream>
#include <mysql.h>

#pragma once

class accont
{
    private:
        MYSQL *conn;
        std::string user; 
        std::string password;
        std::string id;
    public:
        accont(std::string user, std::string password);
        void login();
        void cadastro();
        void connection();
};