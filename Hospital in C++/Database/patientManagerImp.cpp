#include "PatientManager.h"

PatientManager::PatientManager() : patientsDynamic(nullptr), dynamicArrayCapacity(0), dynamicArraySize(0) {}

PatientManager::~PatientManager() {
    delete[] patientsDynamic;
}

void PatientManager::addPatient(const Patient& patient) {
    if (dynamicArraySize == dynamicArrayCapacity) {
        // Resize the array
        dynamicArrayCapacity = (dynamicArrayCapacity == 0) ? 1 : dynamicArrayCapacity * 2;
        Patient* newPatients = new Patient[dynamicArrayCapacity];
        
        for (int i = 0; i < dynamicArraySize; ++i) {
            newPatients[i] = patientsDynamic[i];
        }

        delete[] patientsDynamic;
        patientsDynamic = newPatients;
    }

    patientsDynamic[dynamicArraySize++] = patient;
}

bool PatientManager::updatePatient(int id, const Patient& updatedPatient) {
    for (int i = 0; i < dynamicArraySize; ++i) {
        if (patientsDynamic[i].getId() == id) {
            patientsDynamic[i] = updatedPatient;
            return true; // Update successful
        }
    }
    return false; // Patient not found
}

bool PatientManager::deletePatient(int id) {
    for (int i = 0; i < dynamicArraySize; ++i) {
        if (patientsDynamic[i].getId() == id) {
            for (int j = i; j < dynamicArraySize - 1; ++j) {
                patientsDynamic[j] = patientsDynamic[j + 1];
            }
            dynamicArraySize--;
            return true; // Deletion successful
        }
    }
    return false; // Patient not found
}

int PatientManager::getPatientCount() const {
    return dynamicArraySize;
}

Patient PatientManager::getPatientAtIndex(int index) const {
    if (index >= 0 && index < dynamicArraySize) {
        return patientsDynamic[index];
    }
    // Handle invalid index
    // You can throw an exception or return a default-constructed Patient object
    // Example: throw std::out_of_range("Index out of bounds");
    return Patient(); // Return default Patient if index is invalid
}