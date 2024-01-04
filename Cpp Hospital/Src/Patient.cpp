#include "../Headers/Patient.h"
#include "../Headers/Database.h"

// Constructor
Patient::Patient(int id, const std::string& username, const std::string& phoneNumber, const std::string& gender, const std::string& password)
    : Person(id, username, password), phoneNumber(phoneNumber), gender(gender) {
    Database::patients.push_back(this);
    Database::insertPerson(*this);
}

Patient::Patient(){}

// Getter for phone number
std::string Patient::getPhoneNumber() const {
    return phoneNumber;
}

// Setter for phone number
void Patient::setPhoneNumber(const std::string& phoneNumber) {
    this->phoneNumber = phoneNumber;
}

// Getter for gender
std::string Patient::getGender() const {
    return gender;
}

// Setter for gender
void Patient::setGender(const std::string& gender) {
    this->gender = gender;
}

std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << static_cast<const Person&>(patient); // Call Person's operator<<
    os << ", Phone Number: " << patient.getPhoneNumber() 
       << ", Gender: " << patient.getGender();
    return os;
}