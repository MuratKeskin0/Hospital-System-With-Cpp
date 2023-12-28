#ifndef DATABASE_H
#define DATABASE_H

#include "Person.h"
#include "Admin.h"
#include "Appointment.h"
#include "Doctor.h"
#include "Patient.h"
#include <vector>

using namespace std;

class Database
{
public:
    static vector<Person *> patients;
    static int patientCount;
    static int patientID;

    static vector<Person *> doctors;
    static int doctorCount;
    static int doctorID;

    static vector<Appointment *> appointments;
    static int appointmentCount;
    static int appointmentID;


    static Person *login(const string &username, const string &password);

    // Function about patient
    static void insertPatient(const Person &patient);
    static void insertPerson(const Person& person);
    static int readPatient();
    static void showAllPatients();
    static int deletePatient(const int id);
    static int updatePatientInformation(int id, const std::string& newUsername, const std::string& newPhoneNumber, const std::string& newGender, const std::string& newPassword);
    // Function about doctor
    static void insertDoctor(const Person &doctor);
    static int readDoctor();
    static void showAllDoctors();
    static int deleteDoctor(const int id);
    static int updateDoctorInformation(int id, const std::string& newUsername, const std::string& newSpecialization, const std::string& newPhoneNumber, const std::string& newPassword);
    // Function about appointment
    static void insertAppointment(const Appointment &appointment);
    static int readAppointment();
    static void showAllAppointments();
    static void deleteAppointment(int appointmentID);
    static void updateAppointmentInfo (int id, Appointment::Type newType, const Doctor& newDoctor, const Patient& newPatient, const std::string& newDate, bool newIsConfirmed);
    static void changeConfirmationStatus(int appointmentID);
    
    //complex functions
    static int deleteAppointmentsByDoctor(int doctorId);
    static int deleteAppointmentsByPatient(int patientId);
    static void showAllAppointmentsByDoctor(int doctorId);
    static void showAppointmentsByPatient(int patientId);
    static int deleteAppointmentsByDoctorandId(int doctorId, int appointmentId);
    static int getTotalNumberOfAppointments();
    static Doctor* findDoctorById(int id);
    static Patient* findPatientById(int id);

    static void setAllIdNumbers();
    
    

};

#endif