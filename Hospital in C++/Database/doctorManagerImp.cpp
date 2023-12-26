#include "DoctorManager.h"
#include <algorithm>

void DoctorManager::addDoctor(const Doctor& doctor) {
    doctors.push_back(doctor);
}

bool DoctorManager::updateDoctor(int id, const Doctor& updatedDoctor) {
    for (auto& doctor : doctors) {
        if (doctor.getId() == id) {
            doctor = updatedDoctor;
            return true; // Update successful
        }
    }
    return false; // Doctor not found
}

bool DoctorManager::deleteDoctor(int id) {
    auto it = std::find_if(doctors.begin(), doctors.end(), [id](const Doctor& doctor) {
        return doctor.getId() == id;
    });

    if (it != doctors.end()) {
        doctors.erase(it);
        return true; // Deletion successful
    }
    return false; // Doctor not found
}

const std::vector<Doctor>& DoctorManager::getAllDoctors() const {
    return doctors;
}