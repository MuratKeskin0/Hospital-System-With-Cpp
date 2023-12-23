// Patient.cpp
#include "../Headers/patient.h"

Patient::Patient(int id, const std::string& firstName, const std::string& lastName, 
                 int age, const std::string& gender, const std::string& phoneNumber,
                 const std::string& password, bool isAdmin)
    : id(id), firstName(firstName), lastName(lastName), age(age), gender(gender),
      phoneNumber(phoneNumber), password(password), isAdmin(isAdmin) {}

int Patient::getId() const { return id; }
std::string Patient::getFirstName() const { return firstName; }
std::string Patient::getLastName() const { return lastName; }
int Patient::getAge() const { return age; }
std::string Patient::getGender() const { return gender; }
std::string Patient::getPhoneNumber() const { return phoneNumber; }
std::string Patient::getPassword() const { return password; }
bool Patient::isAdminUser() const { return isAdmin; }

void Patient::setFirstName(const std::string& newFirstName) { firstName = newFirstName; }
void Patient::setLastName(const std::string& newLastName) { lastName = newLastName; }
void Patient::setAge(int newAge) { age = newAge; }
void Patient::setGender(const std::string& newGender) { gender = newGender; }
void Patient::setPhoneNumber(const std::string& newPhoneNumber) { phoneNumber = newPhoneNumber; }
void Patient::setPassword(const std::string& newPassword) { password = newPassword; }
void Patient::setAdminStatus(bool newIsAdmin) { isAdmin = newIsAdmin; }
