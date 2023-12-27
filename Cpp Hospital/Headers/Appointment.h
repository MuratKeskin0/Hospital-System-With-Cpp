#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "Doctor.h"
#include "Patient.h"
#include <string>

class Appointment {
public:
    enum class Type { GENERAL, SPECIAL };

    Appointment(int id, Type type, const Doctor& doctor, const Patient& patient, const std::string& date, bool isConfirmed);

    // Getter and Setter functions
    int getId() const;
    void setId(int newId);

    Type getType() const;
    void setType(Type newType);

    Doctor getDoctor() const;
    void setDoctor(const Doctor& newDoctor);

    Patient getPatient() const;
    void setPatient(const Patient& newPatient);

    std::string getDate() const;
    void setDate(const std::string& newDate);

    bool getIsConfirmed() const;
    void setIsConfirmed(bool newIsConfirmed);

private:
    int id;
    Type type;
    Doctor doctor;
    Patient patient;
    std::string date;
    bool isConfirmed;
};

#endif // APPOINTMENT_H
