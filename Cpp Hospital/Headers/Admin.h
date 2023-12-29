#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"

class Admin : public Person {
public:
    Admin(int id, const std::string& username,const std::string& password);
    Admin();
};

#endif // ADMIN_H
