// Database.h
#ifndef DATABASE_H
#define DATABASE_H

#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include <vector>
#include <string>

class Database {
private:
    std::vector<Patient> patients;
    std::vector<Doctor> doctors;
    std::vector<Appointment> appointments;

public:
    Database();

    // File operations
    void loadFromFile();
    void saveToFile();

    // Patient operations
    void addPatient(const Patient& patient);
    std::vector<Patient> getPatients() const;

    // Doctor operations
    void addDoctor(const Doctor& doctor);
    std::vector<Doctor> getDoctors() const;

    // Appointment operations
    void addAppointment(const Appointment& appointment);
    std::vector<Appointment> getAppointments() const;

    // Additional methods as needed...
};

#endif // DATABASE_H
