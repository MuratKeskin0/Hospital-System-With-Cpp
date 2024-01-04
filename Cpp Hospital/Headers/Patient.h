#ifndef PATIENT_H
#define PATIENT_H

#include "person.h"
#include <string>

class Patient : public Person {
public:
    Patient(int id, const std::string& username, const std::string& phoneNumber, const std::string& gender, const std::string& password);
     
    Patient();
    virtual ~Patient() override{}
    // Getter and Setter functions
    std::string getPhoneNumber() const;
    void setPhoneNumber(const std::string& phoneNumber);

    std::string getGender() const;
    void setGender(const std::string& gender);

    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);

private:
    std::string phoneNumber;
    std::string gender;
};

#endif // PATIENT_H

