#include "../Headers/Admin.h"
#include "../Headers/Database.h"

Admin::Admin(int id, const std::string& username,const std::string& password)
    : Person(id, username, password) { 
    Database::admins.push_back(this);
    Database::insertPerson(*this);
}

Admin::Admin(){}
