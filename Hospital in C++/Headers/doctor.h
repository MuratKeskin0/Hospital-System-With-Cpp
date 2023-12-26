#ifndef DOCTOR_H
#define DOCTOR_H

#include "users.h"
#include <string>

class Doctor : public User {
private:
    std::string specialization;

public:
    Doctor(int id, const std::string &name, const std::string &address, const std::string &mobile, const std::string &specialization);
    std::string getSpecialization() const;
    void setSpecialization(const std::string &specialization);
};

#endif
