#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "patientManager.h"
#include "adminManager.h"
#include "doctorManager.h"
#include "appointmentManager.h"
// Include other necessary headers
const std::string PATIENTS_FILE = "patients.txt";
const std::string DOCTORS_FILE = "doctors.txt";
const std::string ADMINS_FILE = "admins.txt";
const std::string APPOINTMENTS_FILE = "appointments.txt";

class Database {
public:
    void savePatients(const std::string& filename, const PatientManager& patientManager);
    void loadPatients(const std::string& filename, PatientManager& patientManager);
    void saveAdmins(const std::string& filename, const AdminManager& adminManager);
    void loadAdmins(const std::string& filename, AdminManager& adminManager);
    void saveDoctors(const std::string& filename, const DoctorManager& doctorManager);
    void loadDoctors(const std::string& filename, DoctorManager& doctorManager);
     void saveAppointments(const std::string& filename, const AppointmentManager& appointmentManager); // New method
    void loadAppointments(const std::string& filename, AppointmentManager& appointmentManager); // New method
};

#endif
