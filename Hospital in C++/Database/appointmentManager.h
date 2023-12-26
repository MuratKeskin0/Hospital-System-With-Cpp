#ifndef APPOINTMENTMANAGER_H
#define APPOINTMENTMANAGER_H

#include <vector>
#include "../Headers/appointment.h"

class AppointmentManager {
private:
    std::vector<Appointment> appointments;
    int nextAppointmentId; // To keep track of the next available appointment ID

public:
    AppointmentManager();

    int createAppointment(int patientId, int doctorId, const std::string& dateTime, const std::string& status);
    bool deleteAppointment(int appointmentId);
    bool updateAppointment(int appointmentId, int patientId, int doctorId, const std::string& dateTime, const std::string& status);
    void addAppointment(const Appointment& appointment);

    const std::vector<Appointment>& getAppointments() const;
};

#endif
