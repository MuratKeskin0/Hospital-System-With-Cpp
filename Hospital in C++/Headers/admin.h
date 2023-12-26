#ifndef ADMIN_H
#define ADMIN_H

#include "users.h"

class Admin : public User {
public:
    Admin() : User(0, "", "", "") {} 
    Admin(int id, const std::string &name, const std::string &address, const std::string &mobile)
        : User(id, name, address, mobile) {}
};

#endif
