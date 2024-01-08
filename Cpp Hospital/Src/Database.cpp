#include "../Headers/Database.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <map> 


static const int MAX_ADMINS = 3; 

vector<Person *> Database::patients;
int Database::patientCount = 0;
int Database::patientID = 0;

vector<Person *> Database::doctors;
int Database::doctorCount = 0;
int Database::doctorID = 0;

Person* Database::admins[MAX_ADMINS] = {nullptr};
int Database::adminCount = 0;
int Database::adminID = 0;

vector<Appointment *> Database::appointments;
int Database::appointmentCount = 0;
int Database::appointmentID = 0;

bool flagForDeleteAndUpdate = false;

// for instanceof feature in Cpp
template <typename Base, typename Derived>
static bool instanceof (const Derived *ptr)
{
    return dynamic_cast<const Base *>(ptr) != nullptr;
}

Person *Database::login(const string &username, const string &password)
{
    // Check among patients
    for (Person *person : patients)
    {
        if (person->getUserName() == username && person->getPassword() == password)
        {
            if (instanceof <Patient>(person))
            {
                cout << "Patient logged in: " << person->getUserName() << endl;
            }
            return person;
        }
    }

    // Check among doctors
    for (Person *person : doctors)
    {
        if (person->getUserName() == username && person->getPassword() == password)
        {
            if (instanceof <Doctor>(person))
            {
                cout << "Doctor logged in: " << person->getUserName() << endl;
            }
            return person;
        }
    }

    for (Person *person : admins)
    {
        if (person->getUserName() == username && person->getPassword() == password)
        {
            if (instanceof <Admin>(person))
            {
                cout << "Admin logged in: " << person->getUserName() << endl;
            }
            return person;
        }
    }

    // If no match found
    return nullptr;
}

void Database::insertPerson(const Person &person)
{
    if (instanceof <Patient>(&person))
    {
        std::ofstream file("../txtFiles/patient.txt", std::ios_base::app);

        if (!file.is_open())
        {
            std::cerr << "Error: Unable to open the file." << std::endl;
            return;
        }

        try
        {
            // Dynamic cast to check if it's actually a Patient and access Patient-specific fields
            const Patient &actualPatient = dynamic_cast<const Patient &>(person);

            file << actualPatient.getId() << '\n'
                 << actualPatient.getUserName() << '\n'
                 << actualPatient.getPhoneNumber() << '\n'
                 << actualPatient.getGender() << '\n'
                 << actualPatient.getPassword() << '\n';

            patientCount++;
        }
        catch (const std::bad_cast &)
        {
            std::cerr << "Error: Provided person is not a patient." << std::endl;
        }

        file.close();
    }
    else if (instanceof <Doctor>(&person))
    {
        std::ofstream file("../txtFiles/doctor.txt", std::ios_base::app);

        if (!file.is_open())
        {
            std::cerr << "Error: Unable to open the file." << std::endl;
            return;
        }

        try
        {
            const Doctor &actualDoctor = dynamic_cast<const Doctor &>(person);

            file << actualDoctor.getId() << '\n'
                 << actualDoctor.getUserName() << '\n'
                 << actualDoctor.getSpecialization() << '\n'
                 << actualDoctor.getPhoneNumber() << '\n'
                 << actualDoctor.getPassword() << '\n';

            doctorCount++;
        }
        catch (const std::bad_cast &)
        {
            std::cerr << "Error: Provided person is not a doctor." << std::endl;
        }

        file.close();
    }
    else if (instanceof <Admin>(&person))
    {
        std::ofstream file("../txtFiles/admin.txt", std::ios_base::app);

        if (!file.is_open())
        {
            std::cerr << "Error: Unable to open the file." << std::endl;
            return;
        }

        try
        {
            // Dynamic cast to check if it's actually a Patient and access Patient-specific fields
            const Admin &actualAdmin = dynamic_cast<const Admin &>(person);

            file << actualAdmin.getId() << '\n'
                 << actualAdmin.getUserName() << '\n'
                 << actualAdmin.getPassword() << '\n';

            adminCount++;
        }
        catch (const std::bad_cast &)
        {
            std::cerr << "Error: Provided person is not a patient." << std::endl;
        }

        file.close();
    }
    else
    {
        // Handle unknown person type
        std::cerr << "Error: Unknown type of person." << std::endl;
    }
}

int Database::readAdmin() {
    std::ifstream file("../txtFiles/admin.txt");
    if (!file.is_open()) {
        std::cerr << "Error while opening the file!" << std::endl;
        return -1;
    }

    char chunk[128];
    int lineNum = 0;
    Admin *admin = nullptr;
    int currentAdminIndex = 0; // Index to keep track of the current position in the static array

    while (file.getline(chunk, sizeof(chunk))) {
        int newline_pos = std::strcspn(chunk, "\n");
        chunk[newline_pos] = '\0';

        if (lineNum % 3 == 0) {
            // Check if there is space left in the array
            if (currentAdminIndex >= MAX_ADMINS) {
                std::cerr << "Error: Maximum number of admins reached." << std::endl;
                break;
            }
            admin = new Admin;
            admin->setId(std::atoi(chunk));
        } else if (lineNum % 3 == 1) {
            admin->setUserName(chunk);
        } else if (lineNum % 3 == 2) {
            admin->setPassword(chunk);

            // Add the admin to the array and increment the index
            admins[currentAdminIndex++] = admin;
        }
        lineNum++;
    }

    file.close();
    return 0;
}

int Database::deleteAdmin(int id) {
    if (id < 0) {
        std::cout << "Please enter a valid ID number!" << std::endl;
        return 0;
    }

    bool found = false;

    for (int i = 0; i < MAX_ADMINS; ++i) {
        if (admins[i] != nullptr && admins[i]->getId() == id) {
            delete admins[i]; // Free the memory
            admins[i] = nullptr; // Set the pointer to nullptr after deletion
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Admin with ID " << id << " not found." << std::endl;
        return 0;
    }

    // Update the admin.txt file
    std::ifstream file("../txtFiles/admin.txt");
    std::ofstream temp("../txtFiles/temp.txt");

    if (!file.is_open() || !temp.is_open()) {
        std::cout << "Error while opening the file!" << std::endl;
        return 1;
    }

    char chunk[128];
    int lineNum = 0;
    bool skipPerson = false;

    while (file.getline(chunk, sizeof(chunk))) {
        if (lineNum % 3 == 0 && std::atoi(chunk) == id) {
            skipPerson = true;
        }

        if (!skipPerson) {
            temp << chunk << "\n";
        }

        if (++lineNum % 3 == 0) {
            skipPerson = false;
        }
    }

    file.close();
    temp.close();

    std::remove("../txtFiles/admin.txt");
    std::rename("../txtFiles/temp.txt", "../txtFiles/admin.txt");

    std::cout << "Admin with ID " << id << " has been deleted successfully." << std::endl;

    return 0;
}


int Database::readPatient()
{
    // Clear existing patients to avoid duplicates
    for (auto &patient : patients)
    {
        delete patient; 
    }
    patients.clear();
    ifstream file("../txtFiles/patient.txt");
    if (!file.is_open())
    {
        cerr << "Error while opening the file!" << endl;
        return -1;
    }

    char chunk[128];
    int lineNum = 0;
    Patient *patient = nullptr;
    int patientCount = 0;

    while (file.getline(chunk, sizeof(chunk)))
    {
        int newline_pos = strcspn(chunk, "\n");
        chunk[newline_pos] = '\0';

        if (lineNum % 5 == 0)
        {
            patient = new Patient;
            patient->setId(atoi(chunk));
            lineNum++;
        }
        else if (lineNum % 5 == 1)
        {
            patient->setUserName(chunk);
            lineNum++;
        }
        else if (lineNum % 5 == 2)
        {
            patient->setPhoneNumber(chunk);
            lineNum++;
        }
        else if (lineNum % 5 == 3)
        {
            patient->setGender(chunk);
            lineNum++;
        }
        else if (lineNum % 5 == 4)
        {
            patient->setPassword(chunk);
            lineNum++;
            patients.push_back(patient);
            patientCount++;
        }
    }

    patientCount = patientCount;
    file.close();
    return 0;
}

int Database::deletePatient(int id)
{
    // Check if the ID is within a valid range
    if (id < 0 || id >= patientID)
    {
        cout << "Please enter a valid ID number!" << endl;
        return 0;
    }

    // Check if the patient exists in the vector
    auto it = find_if(patients.begin(), patients.end(), [id](const Person *person)
                      { return person->getId() == id; });

    if (it == patients.end())
    {
        cout << "Patient with ID " << id << " not found." << endl;
        return 0;
    }

    // Remove the patient from the vector
    delete *it; // Free the memory
    patients.erase(it);

    // Update the patient.txt file
    ifstream file("../txtFiles/patient.txt");
    ofstream temp("../txtFiles/temp.txt");

    if (!file.is_open() || !temp.is_open())
    {
        cout << "Error while opening the file!" << endl;
        return 1;
    }

    char chunk[128];
    int lineNum = 0;
    bool skipPerson = false;

    while (file.getline(chunk, sizeof(chunk)))
    {
        if (lineNum % 5 == 0 && std::atoi(chunk) == id)
        {
            skipPerson = true;
        }

        if (!skipPerson)
        {
            temp << chunk << "\n";
        }

        if (++lineNum % 5 == 0)
        {
            skipPerson = false;
        }
    }

    file.close();
    temp.close();

    std::remove("../txtFiles/patient.txt");
    std::rename("../txtFiles/temp.txt", "../txtFiles/patient.txt");

    cout << "Patient with ID " << id << " has been deleted successfully." << endl;

    return 0;
}

int Database::updatePatientInformation(int id, const string &newUsername, const string &newPhoneNumber, const string &newGender, const string &newPassword)
{
    // Check if ID is valid
    if (id < 0 || id >= patientID)
    {
        cout << "Invalid patient ID." << endl;
        return 0;
    }

    // Find the patient in the vector
    auto it = find_if(patients.begin(), patients.end(), [id](const Person *person) { return person->getId() == id; });

    if (it == patients.end())
    {
        cout << "Patient with ID " << id << " not found." << endl;
        return 0;
    }

    // Dynamically cast Person pointer to Patient pointer
    Patient *patient = dynamic_cast<Patient *>(*it);
    if (patient != nullptr)
    {
        patient->setUserName(newUsername);
        patient->setPhoneNumber(newPhoneNumber);
        patient->setGender(newGender);
        patient->setPassword(newPassword);
    }
    else
    {
        cout << "Error updating patient information." << endl;
        return 0;
    }

    // Update the patient.txt file
    ofstream file("../txtFiles/patient.txt");
    if (!file.is_open())
    {
        cerr << "Error while opening the file!" << endl;
        return 1;
    }

    for (const auto &p : patients)
    {
        Patient *pat = dynamic_cast<Patient *>(p);
        if (pat)
        {
            file << pat->getId() << '\n'
                 << pat->getUserName() << '\n'
                 << pat->getPhoneNumber() << '\n'
                 << pat->getGender() << '\n'
                 << pat->getPassword() << '\n';
        }
    }

    file.close();
    cout << "Patient information updated successfully." << endl;
    return 1;
}

void Database::showAllPatients()
{
    std::ifstream file("../txtFiles/patient.txt");
    if (!file.is_open())
    {
        std::cerr << "Error while opening the file!" << std::endl;
        return;
    }

    std::string line;
    int id;
    std::string username, phoneNumber, gender, password;

    bool foundPatients = false;
    while (std::getline(file, line))
    {
        id = std::stoi(line);  
        std::getline(file, username); 
        std::getline(file, phoneNumber); 
        std::getline(file, gender);
        std::getline(file, password); 

        foundPatients = true;

        std::cout << "Patient ID: " << id << std::endl;
        std::cout << "Username: " << username << std::endl;
        std::cout << "Phone Number: " << phoneNumber << std::endl;
        std::cout << "Gender: " << gender << std::endl;
        std::cout << "-------------------------------\n";
    }

    if (!foundPatients)
    {
        std::cout << "No patients found." << std::endl;
    }

    file.close();
}

int Database::readDoctor()
{
    // Clear existing patients to avoid duplicates
    for (auto &doctor : doctors)
    {
        delete doctor; 
    }
    doctors.clear();
    std::ifstream file("../txtFiles/doctor.txt");
    if (!file.is_open())
    {
        std::cerr << "Error while opening the file!" << std::endl;
        return -1;
    }

    char chunk[128];
    int lineNum = 0;
    Doctor *doctor = nullptr;

    while (file.getline(chunk, sizeof(chunk)))
    {
        if (lineNum % 5 == 0)
        {
            doctor = new Doctor;
            doctor->setId(std::atoi(chunk));
        }
        else if (lineNum % 5 == 1)
        {
            doctor->setUserName(chunk);
        }
        else if (lineNum % 5 == 2)
        {
            doctor->setSpecialization(chunk);
        }
        else if (lineNum % 5 == 3)
        {
            doctor->setPhoneNumber(chunk);
        }
        else if (lineNum % 5 == 4)
        {
            doctor->setPassword(chunk);
            doctors.push_back(doctor);
        }
        lineNum++;
    }

    file.close();
    return 0;
}

void Database::showAllDoctors()
{
    std::ifstream file("../txtFiles/doctor.txt");
    if (!file.is_open())
    {
        std::cerr << "Error while opening the file!" << std::endl;
        return;
    }

    std::string line;
    int id;
    std::string username, specialization, phoneNumber, password;

    bool foundDoctors = false;
    while (std::getline(file, line))
    {
        id = std::stoi(line); 
        std::getline(file, username); 
        std::getline(file, specialization); 
        std::getline(file, phoneNumber); 
        std::getline(file, password); 

        foundDoctors = true;

        std::cout << "Doctor ID: " << id << std::endl;
        std::cout << "Username: " << username << std::endl;
        std::cout << "Specialization: " << specialization << std::endl;
        std::cout << "Phone Number: " << phoneNumber << std::endl;
        std::cout << "-------------------------------\n";
    }

    if (!foundDoctors)
    {
        std::cout << "No doctors found." << std::endl;
    }

    file.close();
}

int Database::deleteDoctor(int id)
{
    // Check if the ID is within a valid range
    if (id < 0 || id >= doctorID)
    {
        std::cout << "Please enter a valid ID number!" << std::endl;
        return 0;
    }

    // Check if the doctor exists in the vector
    auto it = std::find_if(doctors.begin(), doctors.end(), [id](const Person *person)
                           { return person->getId() == id; });

    if (it == doctors.end())
    {
        std::cout << "Doctor with ID " << id << " not found." << std::endl;
        return 0;
    }

    // Remove the doctor from the vector
    delete *it; // Free the memory
    doctors.erase(it);

    // Update the doctor.txt file
    std::ifstream file("../txtFiles/doctor.txt");
    std::ofstream temp("../txtFiles/temp.txt");

    if (!file.is_open() || !temp.is_open())
    {
        std::cout << "Error while opening the file!" << std::endl;
        return 1;
    }

    char chunk[128];
    int lineNum = 0;
    bool skipPerson = false;

    while (file.getline(chunk, sizeof(chunk)))
    {
        if (lineNum % 5 == 0 && std::atoi(chunk) == id)
        {
            skipPerson = true;
        }

        if (!skipPerson)
        {
            temp << chunk << "\n";
        }

        if (++lineNum % 5 == 0)
        {
            skipPerson = false;
        }
    }

    file.close();
    temp.close();

    std::remove("../txtFiles/doctor.txt");
    std::rename("../txtFiles/temp.txt", "../txtFiles/doctor.txt");

    std::cout << "Doctor with ID " << id << " has been deleted successfully." << std::endl;

    return 0;
}

int Database::updateDoctorInformation(int id, const std::string &newUsername, const std::string &newSpecialization, const std::string &newPhoneNumber, const std::string &newPassword)
{
    // Check if ID is valid
    if (id < 0 || id >= doctorID)
    {
        std::cout << "Invalid doctor ID." << std::endl;
        return 0;
    }

    // Find the doctor in the vector
    auto it = std::find_if(doctors.begin(), doctors.end(), [id](const Person *person)
                           { return person->getId() == id; });

    if (it == doctors.end())
    {
        std::cout << "Doctor with ID " << id << " not found." << std::endl;
        return 0;
    }

    // Dynamically cast Person pointer to Doctor pointer
    Doctor *doctor = dynamic_cast<Doctor *>(*it);
    if (doctor != nullptr)
    {
        doctor->setUserName(newUsername);
        doctor->setSpecialization(newSpecialization);
        doctor->setPhoneNumber(newPhoneNumber);
        doctor->setPassword(newPassword);
        std::cout << "Doctor information updated successfully." << std::endl;
    }
    else
    {
        std::cout << "Error updating doctor information." << std::endl;
        return 0;
    }

    // Update the doctor.txt file
    std::ifstream file("../txtFiles/doctor.txt");
    std::ofstream temp("../txtFiles/temp.txt");

    if (!file.is_open() || !temp.is_open())
    {
        std::cout << "Error while opening the file!" << std::endl;
        return 1;
    }

    char chunk[128];
    int lineNum = 0;

    while (file.getline(chunk, sizeof(chunk)))
    {
        int docId = (lineNum % 5 == 0) ? std::atoi(chunk) : -1;
        if (docId == id)
        {
            if (lineNum % 5 == 0)
                temp << id << "\n";
            else if (lineNum % 5 == 1)
                temp << newUsername << "\n";
            else if (lineNum % 5 == 2)
                temp << newSpecialization << "\n";
            else if (lineNum % 5 == 3)
                temp << newPhoneNumber << "\n";
            else if (lineNum % 5 == 4)
                temp << newPassword << "\n";
        }
        else
        {
            temp << chunk << "\n";
        }
        lineNum++;
    }

    file.close();
    temp.close();

    std::remove("../txtFiles/doctor.txt");
    std::rename("../txtFiles/temp.txt", "../txtFiles/doctor.txt");

    return 1;
}

// Appointment
void Database::insertAppointment(const Appointment &appointment)
{
    std::ofstream file("../txtFiles/appointment.txt", std::ios::app);

    if (!file)
    {
        std::cerr << "Error while opening the appointment file for writing." << std::endl;
        return;
    }

    try
    {
        file << appointment.getId() << '\n'
             << appointment.getPatient().getId() << '\n'
             << appointment.getDoctor().getId() << '\n'
             << static_cast<int>(appointment.getType()) << '\n'
             << appointment.getDate() << '\n'
             << appointment.getIsConfirmed() << '\n';

        if (!file.good())
        {
            throw std::runtime_error("Failed to write to the appointment file.");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    file.close();
}

int Database::readAppointment()
{
    // Clear existing patients to avoid duplicates
    for (auto& appointment : appointments) {
        delete appointment;  
    }
    appointments.clear();

    std::ifstream file("../database/appointment.txt");
    if (!file)
    {
        std::cerr << "Error while opening the file!" << std::endl;
        return -1;
    }

    int id, doctorId, patientId, typeInt;
    std::string date;
    bool isConfirmed;

    while (file >> id >> patientId >> doctorId >> typeInt >> date >> isConfirmed)
    {
        Appointment::Type type = static_cast<Appointment::Type>(typeInt);

        Doctor *doctor = findDoctorById(doctorId);
        Patient *patient = findPatientById(patientId);

        if (doctor && patient)
        {
            Appointment *appointment = new Appointment(id, type, *doctor, *patient, date, isConfirmed);
            appointments.push_back(appointment);
        }
        else
        {
            std::cerr << "Error: Doctor or Patient not found for Appointment ID " << id << std::endl;
        }
    }

    file.close();
    return 0;
}

void Database::showAllAppointments() {
    std::ifstream file("../txtFiles/appointment.txt");
    if (!file.is_open()) {
        std::cerr << "Error while opening the file!" << std::endl;
        return;
    }

    int id, doctorId, patientId, typeInt;
    std::string date;
    bool isConfirmed;
    bool foundAppointments = false;

    while (file >> id >> patientId >> doctorId >> typeInt >> date >> isConfirmed) {
        Appointment::Type type = static_cast<Appointment::Type>(typeInt);

        // Create temporary objects for doctor and patient
        Doctor tempDoctor = findDoctorById(doctorId) ? *findDoctorById(doctorId) : Doctor();
        Patient tempPatient = findPatientById(patientId) ? *findPatientById(patientId) : Patient();

        // Create a temporary Appointment object
        Appointment tempAppointment(id, type, tempDoctor, tempPatient, date, isConfirmed);

        // Use overloaded operator to print Appointment details
        std::cout << tempAppointment << std::endl;
        std::cout << "-------------------------------\n";

        foundAppointments = true;
    }

    if (!foundAppointments) {
        std::cout << "No appointments found." << std::endl;
    }

    file.close();
}

void Database::deleteAppointment(int appointmentID)
{
    auto it = std::find_if(appointments.begin(), appointments.end(), [appointmentID](const Appointment *appointment)
       { return appointment->getId() == appointmentID; });

    if (it == appointments.end())
    {
        std::cout << "Appointment with ID " << appointmentID << " not found." << std::endl;
        return;
    }

    delete *it;
    appointments.erase(it);

    std::ifstream file("../txtFiles/appointment.txt");
    std::ofstream temp("../txtFiles/temp.txt");

    if (!file.is_open() || !temp.is_open())
    {
        std::cout << "Error while opening the file!" << std::endl;
        return;
    }

    int id, doctorId, patientId, typeInt;
    std::string date;
    bool isConfirmed;

    while (file >> id >> patientId >> doctorId >> typeInt >> date >> isConfirmed)
    {
        if (id != appointmentID)
        {
            temp << id << '\n'
                 << patientId << '\n'
                 << doctorId << '\n'
                 << typeInt << '\n'
                 << date << '\n'
                 << isConfirmed << '\n';
        }
    }

    file.close();
    temp.close();

    std::remove("../txtFiles/appointment.txt");
    std::rename("../txtFiles/temp.txt", "../txtFiles/appointment.txt");

    std::cout << "Appointment with ID " << appointmentID << " has been deleted successfully." << std::endl;
}

void Database::changeConfirmationStatus(int appointmentID) {
    bool found = false;
    for (Appointment* appointment : appointments) {
        if (appointment->getId() == appointmentID) {
            appointment->setIsConfirmed(!appointment->getIsConfirmed());
            found = true;
            std::cout << "Appointment confirmation status changed." << std::endl;
            break; // Exit loop once appointment is found and updated
        }
    }

    if (!found) {
        std::cout << "Appointment with ID " << appointmentID << " not found." << std::endl;
        return;
    }

    // Update the appointment.txt file
    std::ofstream temp("../txtFiles/temp.txt");
    if (!temp.is_open()) {
        std::cerr << "Error while opening the temporary file for writing!" << std::endl;
        return;
    }

    for (const auto& appointment : appointments) {
        temp << appointment->getId() << '\n'
             << appointment->getPatient().getId() << '\n'
             << appointment->getDoctor().getId() << '\n'
             << static_cast<int>(appointment->getType()) << '\n'
             << appointment->getDate() << '\n'
             << appointment->getIsConfirmed() << '\n';
    }

    temp.close();

    // Replace the old file with the updated file
    std::remove("../txtFiles/appointment.txt");
    std::rename("../txtFiles/temp.txt", "../txtFiles/appointment.txt");
}

void Database::updateAppointmentInfo(int id, Appointment::Type newType, const Doctor &newDoctor, const Patient &newPatient, const std::string &newDate, bool newIsConfirmed)
{
    for (auto &appointment : appointments)
    {
        if (appointment->getId() == id)
        {
            appointment->setType(newType);
            appointment->setDoctor(newDoctor);
            appointment->setPatient(newPatient);
            appointment->setDate(newDate);
            appointment->setIsConfirmed(newIsConfirmed);

            // Update appointment.txt file to reflect these changes
            std::ofstream temp("../database/temp.txt");
            if (!temp.is_open())
            {
                std::cerr << "Error while opening the temporary file for writing!" << std::endl;
                return;
            }

            for (const auto &app : appointments)
            {
                temp << app->getId() << '\n'
                     << app->getPatient().getId() << '\n'
                     << app->getDoctor().getId() << '\n'
                     << static_cast<int>(app->getType()) << '\n'
                     << app->getDate() << '\n'
                     << app->getIsConfirmed() << '\n';
            }

            temp.close();

            // Replace the old file with the updated file
            std::remove("../database/appointment.txt");
            std::rename("../database/temp.txt", "../database/appointment.txt");

            std::cout << "Appointment with ID " << id << " has been updated successfully." << std::endl;
            return;
        }
    }

    std::cout << "No appointment found with ID " << id << std::endl;
}

// Complex functions
Doctor *Database::findDoctorById(int id)
{
    for (auto &doctor : doctors)
    {
        Doctor *docPtr = dynamic_cast<Doctor *>(doctor);
        if (docPtr && docPtr->getId() == id)
        {
            return docPtr;
        }
    }
    return nullptr; 
}

Patient *Database::findPatientById(int id)
{
    for (auto &patient : patients)
    {
        Patient *patPtr = dynamic_cast<Patient *>(patient);
        if (patPtr && patPtr->getId() == id)
        {
            return patPtr;
        }
    }
    return nullptr; 
}

Appointment *Database::findAppointmentById(int id)
{
    for (auto &appointment : appointments)
    {
        if (appointment->getId() == id)
        {
            return appointment; 
        }
    }
    return nullptr; 
}

int Database::deleteAppointmentsByDoctor(int doctorId)
{
    int deletedCount = 0;
    auto it = appointments.begin();

    while (it != appointments.end())
    {
        if ((*it)->getDoctor().getId() == doctorId)
        {
            delete *it; // Free the memory
            it = appointments.erase(it);
            deletedCount++;
        }
        else
        {
            ++it;
        }
    }

    // Update the appointment.txt file
    std::ofstream temp("../txtFiles/temp.txt");
    if (!temp.is_open())
    {
        std::cerr << "Error while opening the temporary file for writing!" << std::endl;
        return deletedCount;
    }

    for (const auto &appointment : appointments)
    {
        temp << appointment->getId() << '\n'
             << appointment->getPatient().getId() << '\n'
             << appointment->getDoctor().getId() << '\n'
             << static_cast<int>(appointment->getType()) << '\n'
             << appointment->getDate() << '\n'
             << appointment->getIsConfirmed() << '\n';
    }

    temp.close();

    // Replace the old file with the updated file
    std::remove("../txtFiles/appointment.txt");
    std::rename("../txtFiles/temp.txt", "../txtFiles/appointment.txt");

    return deletedCount;
}

int Database::deleteAppointmentsByPatient(int patientId)
{
    int deletedCount = 0;
    auto it = appointments.begin();

    while (it != appointments.end())
    {
        if ((*it)->getPatient().getId() == patientId)
        {
            delete *it; // Free the memory
            it = appointments.erase(it);
            deletedCount++;
        }
        else
        {
            ++it;
        }
    }

    // Update the appointment.txt file
    std::ofstream temp("../txtFiles/temp.txt");
    if (!temp.is_open())
    {
        std::cerr << "Error while opening the temporary file for writing!" << std::endl;
        return deletedCount;
    }

    for (const auto &appointment : appointments)
    {
        temp << appointment->getId() << '\n'
             << appointment->getPatient().getId() << '\n'
             << appointment->getDoctor().getId() << '\n'
             << static_cast<int>(appointment->getType()) << '\n'
             << appointment->getDate() << '\n'
             << appointment->getIsConfirmed() << '\n';
    }

    temp.close();

    // Replace the old file with the updated file
    std::remove("../txtFiles/appointment.txt");
    std::rename("../txtFiles/temp.txt", "../txtFiles/appointment.txt");

    return deletedCount; 
}

int Database::showAllAppointmentsByDoctor(int doctorId) {
    std::ifstream file("../txtFiles/appointment.txt");
    if (!file.is_open()) {
        std::cerr << "Error while opening the file!" << std::endl;
        return 1;  // Return 1 to indicate file opening error
    }

    int id, docId, patientId, typeInt;
    std::string date;
    bool isConfirmed;
    bool found = false;

    while (file >> id >> patientId >> docId >> typeInt >> date >> isConfirmed) {
        if (docId == doctorId) {
            found = true;
            Appointment::Type type = static_cast<Appointment::Type>(typeInt);
            Doctor *doctor = findDoctorById(docId);
            Patient *patient = findPatientById(patientId);

            if (!doctor || !patient) {
                std::cerr << "Error: Doctor or Patient not found for Appointment ID " << id << std::endl;
                continue;
            }

            Appointment tempAppointment(id, type, *doctor, *patient, date, isConfirmed);
            std::cout << tempAppointment << std::endl;
        }
    }

    file.close();

    if (!found) {
        std::cout << "No appointments found for Doctor ID " << doctorId << std::endl;
        return 1;  // Return 1 to indicate no appointments found
    }

    return 0;  // Return 0 to indicate success
}


int Database::showAppointmentsByPatient(int patientId) {
    std::ifstream file("../txtFiles/appointment.txt");
    if (!file.is_open()) {
        std::cerr << "Error while opening the file!" << std::endl;
        return 1;
    }

    int id, docId, patId, typeInt;
    std::string date;
    bool isConfirmed;
    bool found = false;

    while (file >> id >> patId >> docId >> typeInt >> date >> isConfirmed) {
        if (patId == patientId) {
            found = true;
            Appointment::Type type = static_cast<Appointment::Type>(typeInt);
            Doctor *doctor = findDoctorById(docId);
            Patient *patient = findPatientById(patId);

            // If doctor or patient not found, use placeholders
            if (!doctor || !patient) {
                std::cerr << "Error: Doctor or Patient not found for Appointment ID " << id << std::endl;
                continue;
            }

            // Creating a temporary Appointment object
            Appointment tempAppointment(id, type, *doctor, *patient, date, isConfirmed);
            // Using the overloaded << operator to display the appointment information
            std::cout << tempAppointment << std::endl;
        }
    }

    if (!found) {
        std::cout << "No appointments found for Patient ID " << patientId << std::endl;
        return 1;
    }
    
    file.close();

    return 0;
}

int Database::deleteAppointmentsByDoctorandId(int doctorId, int appointmentId)
{
    auto it = std::find_if(appointments.begin(), appointments.end(), [&](const Appointment *appointment)
                           { return appointment->getId() == appointmentId && appointment->getDoctor().getId() == doctorId; });

    if (it != appointments.end())
    {
        delete *it;
        appointments.erase(it);

        // Update the appointment.txt file
        std::ofstream temp("../database/temp.txt");
        if (!temp.is_open())
        {
            std::cerr << "Error while opening the temporary file for writing!" << std::endl;
            return 0;
        }

        for (const auto &appointment : appointments)
        {
            temp << appointment->getId() << '\n'
                 << appointment->getPatient().getId() << '\n'
                 << appointment->getDoctor().getId() << '\n'
                 << static_cast<int>(appointment->getType()) << '\n'
                 << appointment->getDate() << '\n'
                 << appointment->getIsConfirmed() << '\n';
        }

        temp.close();

        // Replace the old file with the updated file
        std::remove("../database/appointment.txt");
        std::rename("../database/temp.txt", "../database/appointment.txt");

        return 1; // successful deletion
    }

    return 0; // No matching appointment found
}

int Database::getTotalNumberOfAppointments()
{
    std::ifstream file("../txtFiles/appointment.txt");
    if (!file.is_open()) {
        std::cerr << "Error while opening the file!" << std::endl;
        return -1; 
    }

    int lineCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        lineCount++;
    }

    file.close();

    int n=6;
    return lineCount / n;
}

void Database::setAllIdNumbers()
{
    int maxPatientId = 0, maxDoctorId = 0, maxAppointmentId = 0;

    // Find the maximum ID among patients
    for (auto &patient : patients)
    {
        Patient *patPtr = dynamic_cast<Patient *>(patient);
        if (patPtr)
        {
            maxPatientId = std::max(maxPatientId, patPtr->getId());
        }
    }
    patientID = maxPatientId + 1;

    // Find the maximum ID among doctors
    for (auto &doctor : doctors)
    {
        Doctor *docPtr = dynamic_cast<Doctor *>(doctor);
        if (docPtr)
        {
            maxDoctorId = std::max(maxDoctorId, docPtr->getId());
        }
    }
    doctorID = maxDoctorId + 1;

    // Find the maximum ID among appointments
    for (auto &appointment : appointments)
    {
        maxAppointmentId = std::max(maxAppointmentId, appointment->getId());
    }
    appointmentID = maxAppointmentId + 1;
}

int Database::deleteAllData()
{
    const char *files[] = {"../txtFiles/patient.txt", "../txtFiles/appointment.txt", "../txtFiles/doctor.txt", "../txtFiles/admin.txt"};
    int *counts[] = {&Database::patientCount, &Database::doctorCount, &Database::adminCount, &Database::appointmentCount};
    const int fileCount = sizeof(files) / sizeof(files[0]);

    for (int i = 0; i < fileCount; ++i)
    {
        FILE *file = fopen(files[i], "w");

        if (file == NULL)
        {
            printf("Error while opening the file %s!\n", files[i]);
            return 1;
        }

        fclose(file);
        *counts[i] = 0;
    }

    return 0;
}

bool Database::usernameExists(const string &username) {
    // Check in patients file
    std::ifstream patientFile("../txtFiles/patient.txt");
    std::string patientLine;
    while (std::getline(patientFile, patientLine)) {
        std::string patientUsername;
        std::getline(patientFile, patientUsername); // Username is the second line for each entry
        if (patientUsername == username) {
            return true;
        }
        // Skip the rest of the patient's data to move to the next entry
        for (int i = 0; i < 3; i++) {
            std::getline(patientFile, patientLine);
        }
    }

    // Check in doctors file
    std::ifstream doctorFile("../txtFiles/doctor.txt");
    std::string doctorLine;
    while (std::getline(doctorFile, doctorLine)) {
        std::string doctorUsername;
        std::getline(doctorFile, doctorUsername); // Username is the second line for each entry
        if (doctorUsername == username) {
            return true;
        }
        // Skip the rest of the doctor's data to move to the next entry
        for (int i = 0; i < 3; i++) {
            std::getline(doctorFile, doctorLine);
        }
    }

    // Check in admins file
    std::ifstream adminFile("../txtFiles/admin.txt");
    std::string adminLine;
    while (std::getline(adminFile, adminLine)) {
        std::string adminUsername;
        std::getline(adminFile, adminUsername); // Username is the second line for each entry
        if (adminUsername == username) {
            return true;
        }
        // Skip the password line to move to the next entry
        std::getline(adminFile, adminLine);
    }

    // If username not found in any file
    return false;
}

void Database::showPatientDoctorRatio() {
    int numberOfPatients = 0;
    int numberOfDoctors = 0;

    // Counting the number of patients
    numberOfPatients = Database::patients.size();

    // Counting the number of doctors
    numberOfDoctors = Database::doctors.size();

    // Calculating and displaying the ratio
    if (numberOfDoctors == 0) {
        cout << "No doctors available to calculate the patient-to-doctor ratio." << endl;
    } else {
        double ratio = static_cast<double>(numberOfPatients) / numberOfDoctors;
        cout << "Ratio of number of patients per doctor: " << ratio << endl;
    }
}

void Database::addAppointment(const Appointment& appointment) {
    appointments.push_back(new Appointment(appointment));
    insertAppointment(appointment);
}

void Database::showPersonInformation(const Person *person, int id) {
    if (person == nullptr) {
        cout << "No person found with ID " << id << "." << endl;
        return;
    }

    // Use dynamic_cast to check the type of the person and then use the overloaded << operator
    if (auto *patient = dynamic_cast<const Patient*>(person)) {
        cout << *patient << endl;
    } else if (auto *doctor = dynamic_cast<const Doctor*>(person)) {
        cout << *doctor << endl;
    } else if (auto *admin = dynamic_cast<const Admin*>(person)) {
        cout << *admin << endl;
    } else {
        cout << "Unknown person type." << endl;
    }
}

void Database::showPatientAppointmentCounts() {
    std::map<int, int> appointmentCountPerPatient;

    // Count appointments for each patient
    for (const auto &appointment : appointments) {
        int patientId = appointment->getPatient().getId();
        appointmentCountPerPatient[patientId]++;
    }

    // Create and initialize the 2D array using double pointers
    int totalPatients = patients.size();
    int maxAppointments = 0;

    // Find the maximum number of appointments any patient has
    for (const auto &count : appointmentCountPerPatient) {
        if (count.second > maxAppointments) {
            maxAppointments = count.second;
        }
    }

    int **patientAppointmentCounts = new int*[totalPatients];
    for (int i = 0; i < totalPatients; ++i) {
        patientAppointmentCounts[i] = new int[maxAppointments](); // Initialize with zeroes
    }

    // Map patients' IDs to indexes in the array
    std::map<int, int> patientIdToIndex;
    for (int i = 0; i < totalPatients; ++i) {
        patientIdToIndex[patients[i]->getId()] = i;
    }

    // Update the counts in the array
    for (const auto &appointment : appointments) {
        int patientId = appointment->getPatient().getId();
        int patientIndex = patientIdToIndex[patientId];
        int appointmentIndex = appointmentCountPerPatient[patientId] - 1;
        patientAppointmentCounts[patientIndex][appointmentIndex]++;
    }

    // Display the appointment counts
    for (int i = 0; i < totalPatients; ++i) {
        std::cout << "Patient ID " << patients[i]->getId() << " appointments: ";
        for (int j = 0; j < maxAppointments; ++j) {
            std::cout << patientAppointmentCounts[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Clean up the 2D array
    for (int i = 0; i < totalPatients; ++i) {
        delete[] patientAppointmentCounts[i];
    }
    delete[] patientAppointmentCounts;
}