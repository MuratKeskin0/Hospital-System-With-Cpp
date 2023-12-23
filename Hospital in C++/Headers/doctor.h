// Doctor.h
#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>

class Doctor {
private:
    int id;
    std::string firstName;
    std::string lastName;
    std::string specialization;

public:
    // Constructor
    Doctor(int id, const std::string& firstName, const std::string& lastName, const std::string& specialization);

    // Getters
    int getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getSpecialization() const;

    // Setters
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setSpecialization(const std::string& specialization);
};

#endif // DOCTOR_H
