#include "../Headers/Admin.h"

Admin::Admin(int id, const std::string& username,const std::string& password,const int &isAdmin)
    : Person(id, "admin", "admin",1) { // Name is empty as it's not required for Admin
}

Admin::Admin(){}
