// Patient.h
#ifndef PATIENT_H
#define PATIENT_H

#include "string"

class Patient {
private:
    int id;
    std::string firstName;
    std::string lastName;
    int age;
    std::string gender;
    std::string phoneNumber;
    std::string password;
    bool isAdmin;

public:
    // Constructor
    Patient(int id, const std::string& firstName, const std::string& lastName, 
            int age, const std::string& gender, const std::string& phoneNumber,
            const std::string& password, bool isAdmin);

    // Getters
    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getPhoneNumber() const;
    std::string getPassword() const;
    bool isAdminUser() const;

    // Setters
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setAge(int age);
    void setGender(const std::string& gender);
    void setPhoneNumber(const std::string& phoneNumber);
    void setPassword(const std::string& password);
    void setAdminStatus(bool isAdmin);
};

#endif // PATIENT_H
