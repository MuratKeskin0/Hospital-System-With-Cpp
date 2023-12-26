#include "database.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>  // Include for std::cerr
#include "../Headers/patient.h"
#include "../Headers/admin.h"
#include "../Headers/doctor.h"
// Include other necessary headers
const std::string PATIENTS_FILE = "patients.txt";
const std::string DOCTORS_FILE = "doctors.txt";
const std::string ADMINS_FILE = "admins.txt";
const std::string APPOINTMENTS_FILE = "appointments.txt";


void Database::savePatients(const std::string& PATIENTS_FILE, const PatientManager& patientManager) {
    std::ofstream file(PATIENTS_FILE);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << PATIENTS_FILE << std::endl;
        return;
    }

    for (int i = 0; i < patientManager.getPatientCount(); ++i) { // Assuming a method to get patient count
        Patient patient = patientManager.getPatientAtIndex(i); // Assuming a method to access a patient by index
        file << patient.getId() << "," << patient.getName() << ","
             << patient.getAddress() << "," << patient.getMobile() << std::endl;
    }

    file.close();
}

void Database::loadPatients(const std::string& PATIENTS_FILE, PatientManager& patientManager) {
    std::ifstream file(PATIENTS_FILE);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << PATIENTS_FILE << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() == 4) { // Adjust for the number of Patient attributes
            Patient patient(std::stoi(tokens[0]), tokens[1], tokens[2], tokens[3]);
            patientManager.addPatient(patient); // Assuming a method to add patient
        }
    }

    file.close();
}

void Database::saveDoctors(const std::string& DOCTORS_FILE, const DoctorManager& doctorManager) {
    std::ofstream file(DOCTORS_FILE);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << DOCTORS_FILE << std::endl;
        return;
    }

    for (const auto& doctor : doctorManager.getAllDoctors()) { // Assuming a method to get all doctors
        file << doctor.getId() << "," << doctor.getName() << ","
             << doctor.getAddress() << "," << doctor.getMobile() << "," << doctor.getSpecialization() << std::endl;
    }

    file.close();
}

void Database::loadDoctors(const std::string& DOCTORS_FILE, DoctorManager& doctorManager) {
    std::ifstream file(DOCTORS_FILE);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << DOCTORS_FILE << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() == 5) { // Adjust for the number of Doctor attributes
            Doctor doctor(std::stoi(tokens[0]), tokens[1], tokens[2], tokens[3], tokens[4]);
            doctorManager.addDoctor(doctor);
        }
    }

    file.close();
}

void Database::saveAdmins(const std::string& ADMINS_FILE, const AdminManager& adminManager) {
    std::ofstream file(ADMINS_FILE);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << ADMINS_FILE << std::endl;
        return;
    }

    for (int i = 0; i < adminManager.getAdminCount(); ++i) { // Assuming a method to get admin count
        Admin admin = adminManager.getAdminAtIndex(i); // Assuming a method to access an admin by index
        file << admin.getId() << "," << admin.getName() << ","
             << admin.getAddress() << "," << admin.getMobile() << std::endl;
    }

    file.close();
}

void Database::loadAdmins(const std::string& ADMINS_FILE, AdminManager& adminManager) {
    std::ifstream file(ADMINS_FILE);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << ADMINS_FILE << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() == 4) { // Adjust for the number of Admin attributes
            Admin admin(std::stoi(tokens[0]), tokens[1], tokens[2], tokens[3]);
            adminManager.addAdmin(admin); // Assuming a method to add admin
        }
    }

    file.close();
}

void Database::saveAppointments(const std::string& APPOINTMENTS_FILE, const AppointmentManager& appointmentManager) {
    std::ofstream file(APPOINTMENTS_FILE);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << APPOINTMENTS_FILE << std::endl;
        return;
    }

    for (const auto& appointment : appointmentManager.getAppointments()) {
        file << appointment.getAppointmentId() << ","
             << appointment.getPatientId() << ","
             << appointment.getDoctorId() << ","
             << appointment.getDateTime() << ","
             << appointment.getStatus() << std::endl;
    }

    file.close();
}

void Database::loadAppointments(const std::string& APPOINTMENTS_FILE, AppointmentManager& appointmentManager) {
    std::ifstream file(APPOINTMENTS_FILE);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << APPOINTMENTS_FILE << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 5) {
            int appointmentId = std::stoi(tokens[0]);
            int patientId = std::stoi(tokens[1]);
            int doctorId = std::stoi(tokens[2]);
            std::string dateTime = tokens[3];
            std::string status = tokens[4];

            appointmentManager.addAppointment(Appointment(appointmentId, patientId, doctorId, dateTime, status));
        }
    }

    file.close();
}
