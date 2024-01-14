#include "../Headers/Appointment.h"
#include "../Headers/Database.h"
#include <iostream>


// Constructor
Appointment::Appointment(int id, Type type, const Doctor& doctor, const Patient& patient, const std::string& date, bool isConfirmed)
    : id(id), type(type), doctor(doctor), patient(patient), date(date), isConfirmed(isConfirmed) {
        /*Database::appointments.push_back(this);
        Database::insertAppointment(*this);-*/
        //I remove this because I wanted to use operator overloading, so in order to prevent infinity loop, I did remove this.
}

// Getter for ID
int Appointment::getId() const {
    return id;
}

// Getter for Type
Appointment::Type Appointment::getType() const {
    return type;
}

// Getter for Doctor
Doctor Appointment::getDoctor() const {
    return doctor;
}

// Getter for Patient
Patient Appointment::getPatient() const {
    return patient;
}

// Getter for Date
std::string Appointment::getDate() const {
    return date;
}

// Getter for Confirmation Status
bool Appointment::getIsConfirmed() const {
    return isConfirmed;
}

// Setter for ID
void Appointment::setId(int newId) {
    id = newId;
}

// Setter for Type
void Appointment::setType(Type newType) {
    type = newType;
}

// Setter for Doctor
void Appointment::setDoctor(const Doctor& newDoctor) {
    doctor = newDoctor;
}

// Setter for Patient
void Appointment::setPatient(const Patient& newPatient) {
    patient = newPatient;
}

// Setter for Date
void Appointment::setDate(const std::string& newDate) {
    date = newDate;
}

// Setter for Confirmation Status
void Appointment::setIsConfirmed(bool newIsConfirmed) {
    isConfirmed = newIsConfirmed;
}
std::ostream& operator<<(std::ostream& os, const Appointment& appointment) {
    os << "Appointment ID: " << appointment.getId()
       << ", Type: " << (appointment.getType() == Appointment::Type::GENERAL ? "General" : "Emergency")
       << ", Doctor: " << appointment.getDoctor().getUserName()
       << ", Patient: " << appointment.getPatient().getUserName()
       << ", Date: " << appointment.getDate()
       << ", Confirmed: " << (appointment.getIsConfirmed() ? "Yes" : "No");
    return os;
}


