#include "../Headers/appointment.h"

Appointment::Appointment(int appointmentId, int patientId, int doctorId, 
                         const std::string& dateTime, const std::string& status)
    : appointmentId(appointmentId), patientId(patientId), doctorId(doctorId),
      dateTime(dateTime), status(status) {}

int Appointment::getAppointmentId() const {
    return appointmentId;
}

void Appointment::setAppointmentId(int id) {
    appointmentId = id;
}

// Getter and setter for patientId
int Appointment::getPatientId() const {
    return patientId;
}

void Appointment::setPatientId(int id) {
    patientId = id;
}

// Getter and setter for doctorId
int Appointment::getDoctorId() const {
    return doctorId;
}

void Appointment::setDoctorId(int id) {
    doctorId = id;
}

// Getter and setter for dateTime
std::string Appointment::getDateTime() const {
    return dateTime;
}

void Appointment::setDateTime(const std::string& dateTime) {
    this->dateTime = dateTime;
}

// Getter and setter for status
std::string Appointment::getStatus() const {
    return status;
}

void Appointment::setStatus(const std::string& status) {
    this->status = status;
}

