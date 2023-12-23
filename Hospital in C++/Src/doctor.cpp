// Doctor.cpp
#include "../Headers/doctor.h"

// Constructor
Doctor::Doctor(int id, const std::string& firstName, const std::string& lastName, const std::string& specialization)
    : id(id), firstName(firstName), lastName(lastName), specialization(specialization) {}

// Getters
int Doctor::getId() const { return id; }
std::string Doctor::getFirstName() const { return firstName; }
std::string Doctor::getLastName() const { return lastName; }
std::string Doctor::getSpecialization() const { return specialization; }

// Setters
void Doctor::setFirstName(const std::string& newFirstName) { firstName = newFirstName; }
void Doctor::setLastName(const std::string& newLastName) { lastName = newLastName; }
void Doctor::setSpecialization(const std::string& newSpecialization) { specialization = newSpecialization; }
