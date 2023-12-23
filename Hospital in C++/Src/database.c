// Database.cpp
#include "../Headers/database.h"
#include <fstream>
#include <iostream>

Database::Database() {
    loadFromFile();
}

void Database::loadFromFile() {
    // Implement logic to load data from files
    // You can use std::ifstream and read data for patients, doctors, and appointments
}

void Database::saveToFile() {
    // Implement logic to save data to files
    // You can use std::ofstream to write data for patients, doctors, and appointments
}

void Database::addPatient(const Patient& patient) {
    patients.push_back(patient);
}

std::vector<Patient> Database::getPatients() const {
    return patients;
}

void Database::addDoctor(const Doctor& doctor) {
    doctors.push_back(doctor);
}

std::vector<Doctor> Database::getDoctors() const {
    return doctors;
}

void Database::addAppointment(const Appointment& appointment) {
    appointments.push_back(appointment);
}

std::vector<Appointment> Database::getAppointments() const {
    return appointments;
}

// Additional method implementations...
