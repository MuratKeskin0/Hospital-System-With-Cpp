// Appointment.cpp
#include "../Headers/appointment.h"

// Constructor
Appointment::Appointment(int id, const Patient& patient, const Doctor& doctor, const Date& date, bool confirmed)
    : id(id), patient(patient), doctor(doctor), date(date), confirmed(confirmed) {}

// Getters
int Appointment::getId() const { return id; }
Patient Appointment::getPatient() const { return patient; }
Doctor Appointment::getDoctor() const { return doctor; }
Date Appointment::getDate() const { return date; }
bool Appointment::isConfirmed() const { return confirmed; }

// Setters
void Appointment::setPatient(const Patient& newPatient) { patient = newPatient; }
void Appointment::setDoctor(const Doctor& newDoctor) { doctor = newDoctor; }
void Appointment::setDate(const Date& newDate) { date = newDate; }
void Appointment::setConfirmed(bool newConfirmed) { confirmed = newConfirmed; }
