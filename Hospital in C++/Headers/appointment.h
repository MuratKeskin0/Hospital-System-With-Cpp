// Appointment.h
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "Patient.h"
#include "Doctor.h"
#include <string>

struct Date {
    int day;
    int month;
    int year;
};

class Appointment {
private:
    int id;
    Patient patient;
    Doctor doctor;
    Date date;
    bool confirmed;

public:
    // Constructor
    Appointment(int id, const Patient& patient, const Doctor& doctor, const Date& date, bool confirmed);

    // Getters
    int getId() const;
    Patient getPatient() const;
    Doctor getDoctor() const;
    Date getDate() const;
    bool isConfirmed() const;

    // Setters
    void setPatient(const Patient& patient);
    void setDoctor(const Doctor& doctor);
    void setDate(const Date& date);
    void setConfirmed(bool confirmed);
};

#endif // APPOINTMENT_H
