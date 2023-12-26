#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    std::string dateTime;  // Date and time as a string
    std::string status;

public:
    Appointment(int appointmentId, int patientId, int doctorId, 
                const std::string& dateTime, const std::string& status);

    // Getters and setters
    int getAppointmentId() const;
    void setAppointmentId(int id);

    int getPatientId() const;
    void setPatientId(int id);

    int getDoctorId() const;
    void setDoctorId(int id);

    std::string getDateTime() const;
    void setDateTime(const std::string& dateTime);

    std::string getStatus() const;
    void setStatus(const std::string& status);

    // Other methods like reschedule, cancel, etc.
};

#endif

