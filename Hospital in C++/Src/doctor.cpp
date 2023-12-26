#include "Doctor.h"

Doctor::Doctor(int id, const std::string &name, const std::string &address, const std::string &mobile, const std::string &specialization)
    : User(id, name, address, mobile), specialization(specialization) {}

std::string Doctor::getSpecialization() const {
    return specialization;
}

void Doctor::setSpecialization(const std::string &newSpecialization) {
    specialization = newSpecialization;
}

