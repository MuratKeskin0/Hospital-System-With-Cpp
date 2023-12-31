#ifndef DOCTOR_H
#define DOCTOR_H

#include "person.h"
#include <string>

class Doctor : public Person {
public:
    Doctor(int id, const std::string& username, const std::string& specialization, const std::string& phoneNumber, const std::string& password);

    Doctor();
    virtual ~Doctor() override{}

    // Getter and Setter functions
    std::string getSpecialization() const;
    void setSpecialization(const std::string& specialization);

    std::string getPhoneNumber() const;
    void setPhoneNumber(const std::string& phoneNumber);

    friend std::ostream& operator<<(std::ostream& os, const Doctor& doctor);

private:
    std::string specialization;
    std::string phoneNumber;
};

#endif // DOCTOR_H
