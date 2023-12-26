#ifndef DOCTORMANAGER_H
#define DOCTORMANAGER_H

#include <vector>
#include "../Headers/doctor.h"

class DoctorManager {
private:
    std::vector<Doctor> doctors;

public:
    void addDoctor(const Doctor& doctor);
    bool updateDoctor(int id, const Doctor& updatedDoctor);
    bool deleteDoctor(int id);

    const std::vector<Doctor>& getAllDoctors() const;
};

#endif
