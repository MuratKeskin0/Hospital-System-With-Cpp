#ifndef PATIENT_H
#define PATIENT_H

#include "users.h"

class Patient : public User {
public:
    Patient() : User(0, "", "", "") {}
    Patient(int id, const std::string &name, const std::string &address, const std::string &mobile)
        : User(id, name, address, mobile) {}
};

#endif


