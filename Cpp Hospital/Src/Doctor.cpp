#include "../Headers/Doctor.h"

// Constructor
Doctor::Doctor(int id, const std::string& username, const std::string& specialization, const std::string& phoneNumber, const std::string& password,const int &isAdmin)
    : Person(id, username, password,0), specialization(specialization), phoneNumber(phoneNumber) {
}

Doctor::Doctor(){}

// Getter for specialization
std::string Doctor::getSpecialization() const {
    return specialization;
}

// Setter for specialization
void Doctor::setSpecialization(const std::string& specialization) {
    this->specialization = specialization;
}

// Getter for phone number
std::string Doctor::getPhoneNumber() const {
    return phoneNumber;
}

// Setter for phone number
void Doctor::setPhoneNumber(const std::string& phoneNumber) {
    this->phoneNumber = phoneNumber;
}
