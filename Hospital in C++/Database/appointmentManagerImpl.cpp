#include "appointmentManager.h"

AppointmentManager::AppointmentManager() : nextAppointmentId(1) {}

int AppointmentManager::createAppointment(int patientId, int doctorId, const std::string& dateTime, const std::string& status) {
    int appointmentId = nextAppointmentId++;
    Appointment newAppointment(appointmentId, patientId, doctorId, dateTime, status);
    appointments.push_back(newAppointment);
    return appointmentId; // Return the ID of the newly created appointment
}

bool AppointmentManager::deleteAppointment(int appointmentId) {
    for (auto it = appointments.begin(); it != appointments.end(); ++it) {
        if (it->getAppointmentId() == appointmentId) {
            appointments.erase(it);
            return true;
        }
    }
    return false;
}

bool AppointmentManager::updateAppointment(int appointmentId, int patientId, int doctorId, const std::string& dateTime, const std::string& status) {
    for (auto& appointment : appointments) {
        if (appointment.getAppointmentId() == appointmentId) {
            appointment.setPatientId(patientId);
            appointment.setDoctorId(doctorId);
            appointment.setDateTime(dateTime);
            appointment.setStatus(status);
            return true;
        }
    }
    return false;
}

void AppointmentManager::addAppointment(const Appointment& appointment) {
    appointments.push_back(appointment);
}

const std::vector<Appointment>& AppointmentManager::getAppointments() const {
    return appointments;
}

