#include "../Headers/Database.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>

vector<Person *> Database::patients;
int Database::patientCount = 0;
int Database::patientID = 0;

vector<Person *> Database::doctors;
int Database::doctorCount = 0;
int Database::doctorID = 0;

vector<Person *> Database::admins;
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
                // Additional patient-specific logic
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
                // Additional doctor-specific logic
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
                // Additional admin-specific logic
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
            std::cout << "Patient has been written to the file successfully." << std::endl;
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
            std::cout << "Doctor has been written to the file successfully." << std::endl;
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
            std::cout << "Admin has been written to the file successfully." << std::endl;
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

int Database::readAdmin()
{
    ifstream file("../txtFiles/admin.txt");
    if (!file.is_open())
    {
        cerr << "Error while opening the file!" << endl;
        return -1;
    }

    char chunk[128];
    int lineNum = 0;
    Admin *admin = nullptr;
    int adminCount = 0;

    while (file.getline(chunk, sizeof(chunk)))
    {
        int newline_pos = strcspn(chunk, "\n");
        chunk[newline_pos] = '\0';

        if (lineNum % 3 == 0)
        {
            admin = new Admin;
            admin->setId(atoi(chunk));
            lineNum++;
        }
        else if (lineNum % 3 == 1)
        {
            admin->setUserName(chunk);
        }
        else if (lineNum % 3 == 2)
        {
            admin->setPassword(chunk);
            lineNum++;
            admins.push_back(admin);
            adminCount++;
        }
    }

    adminCount = adminCount;
    file.close();
    return 0;
}

int Database::deleteAdmin(int id) {
    // Check if the ID is within a valid range
    if (id < 0 || id >= adminID) {
        std::cout << "Please enter a valid ID number!" << std::endl;
        return 0;
    }

    // Check if the admin exists in the vector
    auto it = std::find_if(admins.begin(), admins.end(), [id](const Person* person) {
        return person->getId() == id;
    });

    if (it == admins.end()) {
        std::cout << "Admin with ID " << id << " not found." << std::endl;
        return 0;
    }

    // Remove the admin from the vector
    delete *it;  // Free the memory
    admins.erase(it);

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
        delete patient; // Assuming patients were dynamically allocated
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
        id = std::stoi(line);  // First line is ID
        std::getline(file, username); // Second line is Username
        std::getline(file, phoneNumber); // Third line is Phone Number
        std::getline(file, gender); // Fourth line is Gender
        std::getline(file, password); // Fifth line is Password, which you might not want to display

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
        delete doctor; // Assuming patients were dynamically allocated
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
        id = std::stoi(line); // First line is ID
        std::getline(file, username); // Second line is Username
        std::getline(file, specialization); // Third line is Specialization
        std::getline(file, phoneNumber); // Fourth line is Phone Number
        std::getline(file, password); // Fifth line is Password, which you might not want to display

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
    /*for (auto& appointment : appointments) {
        delete appointment;  // Assuming patients were dynamically allocated
    }
    appointments.clear();*/

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

void Database::showAllAppointments()
{
    std::ifstream file("../txtFiles/appointment.txt");
    if (!file.is_open())
    {
        std::cerr << "Error while opening the file!" << std::endl;
        return;
    }

    int id, doctorId, patientId, typeInt;
    std::string date;
    bool isConfirmed;

    bool foundAppointments = false;
    while (file >> id >> patientId >> doctorId >> typeInt >> date >> isConfirmed)
    {
        foundAppointments = true;
        Appointment::Type type = static_cast<Appointment::Type>(typeInt);

        // Fetching doctor and patient usernames
        Doctor *doctor = findDoctorById(doctorId);
        Patient *patient = findPatientById(patientId);
        std::string doctorUsername = doctor ? doctor->getUserName() : "Unknown";
        std::string patientUsername = patient ? patient->getUserName() : "Unknown";

        std::cout << "Appointment ID: " << id << std::endl
                  << "Doctor ID: " << doctorId << " (Username: " << doctorUsername << ")" << std::endl
                  << "Patient ID: " << patientId << " (Username: " << patientUsername << ")" << std::endl
                  << "Type: " << static_cast<int>(type) << std::endl
                  << "Date: " << date << std::endl
                  << "Confirmed: " << (isConfirmed ? "Yes" : "No") << std::endl
                  << "-------------------------------\n";
    }

    if (!foundAppointments)
    {
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
    return nullptr; // Return nullptr if not found
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
    return nullptr; // Return nullptr if not found
}

Appointment *Database::findAppointmentById(int id)
{
    for (auto &appointment : appointments)
    {
        if (appointment->getId() == id)
        {
            return appointment; // Found the appointment with the given ID
        }
    }
    return nullptr; // No appointment found with the given ID
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
    std::ofstream temp("../database/temp.txt");
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
    std::remove("../database/appointment.txt");
    std::rename("../database/temp.txt", "../database/appointment.txt");

    return deletedCount; // Return the count of deleted appointments
}

void Database::showAllAppointmentsByDoctor(int doctorId)
{
    std::ifstream file("../txtFiles/appointment.txt");
    if (!file.is_open())
    {
        std::cerr << "Error while opening the file!" << std::endl;
        return;
    }

    int id, docId, patientId, typeInt;
    std::string date;
    bool isConfirmed;
    bool found = false;

    while (file >> id >> patientId >> docId >> typeInt >> date >> isConfirmed)
    {
        if (docId == doctorId)
        {
            found = true;
            Appointment::Type type = static_cast<Appointment::Type>(typeInt);
            Doctor *doctor = findDoctorById(docId);
            Patient *patient = findPatientById(patientId);

            std::string doctorUsername = doctor ? doctor->getUserName() : "Unknown";
            std::string patientUsername = patient ? patient->getUserName() : "Unknown";

            std::cout << "Appointment ID: " << id << std::endl
                      << "Doctor ID: " << docId << " (Username: " << doctorUsername << ")" << std::endl
                      << "Patient ID: " << patientId << " (Username: " << patientUsername << ")" << std::endl
                      << "Type: " << static_cast<int>(type) << std::endl
                      << "Date: " << date << std::endl
                      << "Confirmed: " << (isConfirmed ? "Yes" : "No") << std::endl
                      << "--------------------------------\n";
        }
    }

    if (!found)
    {
        std::cout << "No appointments found for Doctor ID " << doctorId << std::endl;
    }

    file.close();
}

void Database::showAppointmentsByPatient(int patientId)
{
    std::ifstream file("../txtFiles/appointment.txt");
    if (!file.is_open())
    {
        std::cerr << "Error while opening the file!" << std::endl;
        return;
    }

    int id, docId, patId, typeInt;
    std::string date;
    bool isConfirmed;
    bool found = false;

    while (file >> id >> patId >> docId >> typeInt >> date >> isConfirmed)
    {
        if (patId == patientId)
        {
            found = true;
            Appointment::Type type = static_cast<Appointment::Type>(typeInt);
            Doctor *doctor = findDoctorById(docId);
            Patient *patient = findPatientById(patId);

            std::string doctorUsername = doctor ? doctor->getUserName() : "Unknown";
            std::string patientUsername = patient ? patient->getUserName() : "Unknown";

            std::cout << "Appointment ID: " << id << std::endl
                      << "Doctor ID: " << docId << " (Username: " << doctorUsername << ")" << std::endl
                      << "Patient ID: " << patId << " (Username: " << patientUsername << ")" << std::endl
                      << "Type: " << static_cast<int>(type) << std::endl
                      << "Date: " << date << std::endl
                      << "Confirmed: " << (isConfirmed ? "Yes" : "No") << std::endl
                      << "--------------------------------\n";
        }
    }

    if (!found)
    {
        std::cout << "No appointments found for Patient ID " << patientId << std::endl;
    }

    file.close();
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
            return 0; // Indicate failure
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

        return 1; // Indicating successful deletion
    }

    return 0; // No matching appointment found
}

int Database::getTotalNumberOfAppointments()
{
    std::ifstream file("../txtFiles/appointment.txt");
    if (!file.is_open()) {
        std::cerr << "Error while opening the file!" << std::endl;
        return -1; // Indicate error
    }

    int lineCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        lineCount++;
    }

    file.close();

    // Assuming each appointment takes up 'n' lines in the file
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

bool Database::usernameExists(const string &username)
{
    // Check among patients
    for (const auto &patient : patients)
    {
        if (dynamic_cast<Patient *>(patient)->getUserName() == username)
        {
            return true;
        }
    }

    // Check among doctors
    for (const auto &doctor : doctors)
    {
        if (dynamic_cast<Doctor *>(doctor)->getUserName() == username)
        {
            return true;
        }
    }

    // Check among admins
    for (const auto &admin : admins)
    {
        if (dynamic_cast<Admin *>(admin)->getUserName() == username)
        {
            return true;
        }
    }

    // If username not found
    return false;
}

void Database::showPersonInformation(int id)
{
    // Attempt to find the person as a patient, doctor, or admin
    Patient* patient = findPatientById(id);
    Doctor* doctor = findDoctorById(id);
    Admin* admin = nullptr;

    // Check among admins
    auto adminIt = std::find_if(admins.begin(), admins.end(), [id](const Person* person) {
        return person->getId() == id;
    });

    if (adminIt != admins.end()) {
        admin = dynamic_cast<Admin*>(*adminIt);
    }

    // Display information based on the type of person found
    if (patient != nullptr) {
        std::cout << "Patient ID: " << patient->getId() << std::endl;
        std::cout << "Username: " << patient->getUserName() << std::endl;
        std::cout << "Phone Number: " << patient->getPhoneNumber() << std::endl;
        std::cout << "Gender: " << patient->getGender() << std::endl;
    } else if (doctor != nullptr) {
        std::cout << "Doctor ID: " << doctor->getId() << std::endl;
        std::cout << "Username: " << doctor->getUserName() << std::endl;
        std::cout << "Specialization: " << doctor->getSpecialization() << std::endl;
        std::cout << "Phone Number: " << doctor->getPhoneNumber() << std::endl;
    } else if (admin != nullptr) {
        std::cout << "Admin ID: " << admin->getId() << std::endl;
        std::cout << "Username: " << admin->getUserName() << std::endl;
    } else {
        std::cout << "No person found with ID " << id << "." << std::endl;
    }
}
