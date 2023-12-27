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
    for (Person* person : patients) {
        if (person->getUserName() == username && person->getPassword() == password) {
            if (instanceof<Patient>(person)) {
                cout << "Patient logged in: " << person->getUserName() << endl;
                // Additional patient-specific logic
            }
            return person;
        }
    }

    // Check among doctors
    for (Person* person : doctors) {
        if (person->getUserName() == username && person->getPassword() == password) {
            if (instanceof<Doctor>(person)) {
                cout << "Doctor logged in: " << person->getUserName() << endl;
                // Additional doctor-specific logic
            }
            return person;
        }
    }

    // If no match found
    return nullptr;
}

void Database::insertPatient(const Person& patient) {
    std::ofstream file("../txtFiles/patient.txt", std::ios_base::app);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    try {
        // Dynamic cast to check if it's actually a Patient and access Patient-specific fields
        const Patient& actualPatient = dynamic_cast<const Patient&>(patient);

        file << actualPatient.getId() << '\n'
             << actualPatient.getUserName() << '\n'
             << actualPatient.getPhoneNumber() << '\n'
             << actualPatient.getGender() << '\n'
             << actualPatient.getPassword() << '\n';

        patientCount++;
        std::cout << "Patient has been written to the file successfully." << std::endl;
    } catch (const std::bad_cast&) {
        std::cerr << "Error: Provided person is not a patient." << std::endl;
    }

    file.close();
}

int Database::readPatient() {
    ifstream file("../txtFiles/patient.txt");
    if (!file.is_open()) {
        cerr << "Error while opening the file!" << endl;
        return -1;
    }

    char chunk[128];
    int lineNum = 0;
    Patient *patient = nullptr;
    int patientCount = 0;

    while (file.getline(chunk, sizeof(chunk))) {
        int newline_pos = strcspn(chunk, "\n");
        chunk[newline_pos] = '\0';

        if (lineNum % 5 == 0) {
            patient = new Patient;
            patient->setId(atoi(chunk));
            lineNum++;
        } else if (lineNum % 5 == 1) {
            patient->setUserName(chunk);
            lineNum++;
        } else if (lineNum % 5 == 2) {
            patient->setPhoneNumber(chunk);
            lineNum++;
        } else if (lineNum % 5 == 3) {
            patient->setGender(chunk);
            lineNum++;
        } else if (lineNum % 5 == 4) {
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

int Database::deletePatient(int id) {
    // Check if the ID is within a valid range
    if (id < 0 || id >= patientID) {
        cout << "Please enter a valid ID number!" << endl;
        return 0;
    }

    // Check if the patient exists in the vector
    auto it = find_if(patients.begin(), patients.end(), [id](const Person* person) {
        return person->getId() == id;
    });

    if (it == patients.end()) {
        cout << "Patient with ID " << id << " not found." << endl;
        return 0;
    }

    // Remove the patient from the vector
    delete *it;  // Free the memory
    patients.erase(it);

    // Update the patient.txt file
    ifstream file("../txtFiles/patient.txt");
    ofstream temp("../txtFiles/temp.txt");

    if (!file.is_open() || !temp.is_open()) {
        cout << "Error while opening the file!" << endl;
        return 1;
    }

    char chunk[128];
    int lineNum = 0;
    bool skipPerson = false;

    while (file.getline(chunk, sizeof(chunk))) {
        if (lineNum % 5 == 0 && std::atoi(chunk) == id) {
            skipPerson = true;
        }

        if (!skipPerson) {
            temp << chunk << "\n";
        }

        if (++lineNum % 5 == 0) {
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

int Database::updatePatientInformation(int id, const string& newUsername, const string& newPhoneNumber, const string& newGender, const string& newPassword) {
    // Check if ID is valid
    if (id < 0 || id >= patientID) {
        cout << "Invalid patient ID." << endl;
        return 0;
    }

    // Find the patient in the vector
    auto it = find_if(patients.begin(), patients.end(), [id](const Person* person) {
        return person->getId() == id;
    });

    if (it == patients.end()) {
        cout << "Patient with ID " << id << " not found." << endl;
        return 0;
    }

    // Dynamically cast Person pointer to Patient pointer
    Patient* patient = dynamic_cast<Patient*>(*it);
    if (patient != nullptr) {
        patient->setUserName(newUsername);
        patient->setPhoneNumber(newPhoneNumber);
        patient->setGender(newGender);
        patient->setPassword(newPassword);
        cout << "Patient information updated successfully." << endl;
    } else {
        cout << "Error updating patient information." << endl;
    }

    return 1;
}

void Database::setAllIdNumbers()
{
    // For user
    int maxForUser = Database::patients[0]->getId();
    for (int i = 0; i < Database::patients.size(); i++)
    {
        if (maxForUser < Database::patients[i]->getId())
        {
            maxForUser = Database::patients[i]->getId();
        }
    }
    Database::patientID = maxForUser + 1;
}