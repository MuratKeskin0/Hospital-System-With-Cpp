#include "../Headers/Doctor.h"
#include "../Headers/Database.h"
#include <iostream>


Doctor::Doctor(int id, const std::string& username, const std::string& specialization, const std::string& phoneNumber, const std::string& password)
    : Person(id, username, password), specialization(specialization), phoneNumber(phoneNumber) {
    Database::doctors.push_back(this);
    Database::insertPerson(*this);
}

Doctor::Doctor(){}

std::string Doctor::getSpecialization() const {
    return specialization;
}

void Doctor::setSpecialization(const std::string& specialization) {
    this->specialization = specialization;
}

std::string Doctor::getPhoneNumber() const {
    return phoneNumber;
}

void Doctor::setPhoneNumber(const std::string& phoneNumber) {
    this->phoneNumber = phoneNumber;
}

// Overload of operator<< for Doctor
std::ostream& operator<<(std::ostream& os, const Doctor& doctor) {
    os << static_cast<const Person&>(doctor); // Call Person's operator<<
    os << ", Specialization: " << doctor.getSpecialization() 
       << ", Phone Number: " << doctor.getPhoneNumber();
    return os;
}
