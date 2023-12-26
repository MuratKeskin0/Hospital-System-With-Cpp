#ifndef PATIENTMANAGER_H
#define PATIENTMANAGER_H

#include "../Headers/patient.h"

class PatientManager {
private:
    Patient* patientsDynamic;
    int dynamicArrayCapacity;
    int dynamicArraySize;

public:
    PatientManager();
    ~PatientManager();
    void addPatient(const Patient& patient);
    bool updatePatient(int id, const Patient& updatedPatient);
    bool deletePatient(int id);

    int getPatientCount() const;
    Patient getPatientAtIndex(int index) const;
};

#endif

