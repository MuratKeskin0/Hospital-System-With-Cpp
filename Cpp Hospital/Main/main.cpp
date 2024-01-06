#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "../Src/Person.cpp"
#include "../Src/Admin.cpp"
#include "../Src/Doctor.cpp"
#include "../Src/Patient.cpp"
#include "../Src/Database.cpp"
#include "../Src/Appointment.cpp"

using namespace std;

int Display();
void defaultInformation();

int main()
{
    defaultInformation();
    Database::setAllIdNumbers();
    Database::readPatient();
    Database::readDoctor();
    Database::readAdmin();
    Display();

    return 0;
}

int Display()
{
    Person *account;
    int option;
    int isLoggedIn = 0;

    while (true)
    {
        if (isLoggedIn && (instanceof <Admin>(account)))
        {

            printf("\n--------- Welcome Admin %s ---------\n", account->getUserName().c_str());

            int choice;

            cout << "\n1- Create Appointment" << endl;
            cout << "2- Show All Appointments" << endl;
            cout << "3- Update Appointment" << endl;
            cout << "4- Delete Appointment" << endl;
            cout << "5- Create Doctor" << endl;
            cout << "6- Show All Doctors" << endl;
            cout << "7- Update Doctor" << endl;
            cout << "8- Delete Doctor" << endl;
            cout << "9- Create Patient" << endl;
            cout << "10- Show All Patients" << endl;
            cout << "11- Update Patient" << endl;
            cout << "12- Delete Patient" << endl;
            cout << "13- Total Number of All Appointments" << endl;
            cout << "14- Change the statue of an Appointment" << endl;
            cout << "15- Ratio of number of patients per doctor" << endl;
            cout << "16- show Patient Appointment Counts" << endl;
            cout << "17- Logout" << endl;

            cout << "\nSelect an option : ";

            cin >> choice;

            if (cin.fail())
            {
                cin.clear();                                                   // Clear the error state of cin
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                cout << "Invalid input for choice. Please enter a number." << endl;
            }
            switch (choice)
            {
            case 1:
            {
                int doctorId, patientId, typeInt;
                string date;

                Database::showAllDoctors();
                cout << "Enter Doctor ID: ";
                cin >> doctorId;
                if (cin.fail())
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    cout << "Invalid input for Doctor ID. Please enter a number." << endl;
                    break;
                }

                // Validate the doctor ID
                Doctor *doctor = Database::findDoctorById(doctorId);
                if (!doctor)
                {
                    cout << "No doctor found with ID " << doctorId << "!" << endl;
                    break;
                }

                Database::showAllPatients();
                cout << "Enter Patient ID: ";
                cin >> patientId;
                if (cin.fail())
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    cout << "Invalid input for Patient ID. Please enter a number." << endl;
                    break;
                }

                // Validate the patient ID
                Patient *patient = Database::findPatientById(patientId);
                if (!patient)
                {
                    cout << "No patient found with ID " << patientId << "!" << endl;
                    break;
                }

                cout << "Enter Appointment Date (e.g., 2023-12-31): ";
                cin >> date;

                // Check if there's already an appointment with the same doctor on the same date
                bool appointmentExists = std::any_of(Database::appointments.begin(), Database::appointments.end(),
                [&doctorId, &date](const Appointment *appointment)
                {
                         return appointment->getDoctor().getId() == doctorId && appointment->getDate() == date;
                    });

                if (appointmentExists)
                {
                    cout << "An appointment with this doctor on the specified date already exists." << endl;
                    break;
                }

                 cout << "Enter Appointment Type (0 for General, 1 for Emergency, etc.): ";
                cin >> typeInt;
                if (cin.fail() || typeInt < 0 || typeInt > 1)
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore bad input
                    cout << "Invalid appointment type entered." << endl;
                    break;
                }
                Appointment::Type type = static_cast<Appointment::Type>(typeInt);

                // Create the Appointment object
                Appointment *newAppointment = new Appointment(Database::appointmentID++, type, *doctor, *patient, date, false);
                Database::addAppointment(*newAppointment);

                cout << "Appointment created successfully with ID " << newAppointment->getId() << "!" << endl;
            }

            break;

            case 2:
                Database::showAllAppointments();
                break;

            case 3:
            {
                int appointmentId;
                Database::showAllAppointments();
                cout << "Enter Appointment ID to update: ";
                cin >> appointmentId;

                if (cin.fail())
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    cout << "Invalid input for Doctor ID. Please enter a number." << endl;
                    break;
                }

                // Validate appointment ID
                Appointment *existingAppointment = Database::findAppointmentById(appointmentId);
                if (!existingAppointment)
                {
                    cout << "No appointment found with ID " << appointmentId << "!" << endl;
                    break;
                }

                // Gather new details for the appointment
                int newDoctorId, newPatientId, newTypeInt;
                string newDate;

                Database::showAllDoctors();
                cout << "Enter new Doctor ID: ";
                cin >> newDoctorId;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                    break; 
                }

                Doctor *newDoctor = Database::findDoctorById(newDoctorId);
                if (!newDoctor)
                {
                    cout << "Doctor with ID " << newDoctorId << " not found." << endl;
                    break; 
                }

                Database::showAllPatients();
                cout << "Enter new Patient ID: ";
                cin >> newPatientId;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                    break;
                }

                Patient *newPatient = Database::findPatientById(newPatientId);
                if (!newPatient)
                {
                    cout << "Patient with ID " << newPatientId << " not found." << endl;
                    break;
                }

                cout << "Enter new Appointment Date (e.g., 2023-12-31): ";
                cin >> newDate;

                bool appointmentExists = std::any_of(Database::appointments.begin(), Database::appointments.end(),
                [&newDoctorId, &newDate](const Appointment *appointment)
                   {
                     return appointment->getDoctor().getId() == newDoctorId && appointment->getDate() == newDate;
                 });

                if (appointmentExists)
                {
                    cout << "An appointment with this doctor on the specified date already exists." << endl;
                    break;
                }

                cout << "Enter new Appointment Type (0 for General, 1 for Emergency, etc.): ";
                cin >> newTypeInt;
                if (cin.fail() || newTypeInt < 0 || newTypeInt > 1)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid appointment type entered." << endl;
                    break; 
                }

                // Update the appointment details
                existingAppointment->setDoctor(*Database::findDoctorById(newDoctorId));
                existingAppointment->setPatient(*Database::findPatientById(newPatientId));
                existingAppointment->setDate(newDate);
                existingAppointment->setType(static_cast<Appointment::Type>(newTypeInt));

                cout << "Appointment updated successfully with ID " << existingAppointment->getId() << "!" << endl;
            }
            break;

            case 4:
            {
                int appointmentId;
                Database::showAllAppointments();
                cout << "Enter Appointment ID to delete: ";
                cin >> appointmentId;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Invalid input for Doctor ID. Please enter a number." << endl;
                    break;
                }

                Appointment *appointment = Database::findAppointmentById(appointmentId);

                if (!appointment)
                {
                    cout << "No appointment found with ID " << appointmentId << "!" << endl;
                    break;
                }

                Database::deleteAppointment(appointmentId);
                break;
            }

            case 5:
            {
                string username, specialization, phoneNumber, password;

                cout << "Enter Doctor's Username: ";
                cin >> username;
                if (username.empty() || Database::usernameExists(username))
                {
                    cout << "Invalid or existing username. Please try again." << endl;
                    break;
                }

                cout << "Enter Doctor's Specialization: ";
                cin >> specialization;
                if (specialization.empty())
                {
                    cout << "Specialization cannot be empty. Please try again." << endl;
                    break;
                }

                cout << "Enter Doctor's Phone Number: ";
                cin >> phoneNumber;
                if (cin.fail())
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    cout << "Invalid input for phoneNumber. Please enter a number." << endl;
                    break;
                }

                cout << "Enter Doctor's Password: ";
                cin >> password;

                // Create a new Doctor instance
                Doctor *newDoctor = new Doctor(Database::doctorID++, username, specialization, phoneNumber, password);
                cout << "Doctor created successfully with ID " << newDoctor->getId() << "!" << endl;
            }
            break;

            case 6:
                Database::showAllDoctors();
                break;

            case 7: 
            {
                int doctorId;
                Database::showAllDoctors();
                cout << "Enter Doctor ID to update: ";
                cin >> doctorId;

                if (cin.fail())
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    cout << "Invalid input for Doctor ID. Please enter a number." << endl;
                    break;
                }

                // Validate doctor ID
                Doctor *existingDoctor = Database::findDoctorById(doctorId);
                if (!existingDoctor)
                {
                    cout << "No doctor found with ID " << doctorId << "!" << endl;
                    break;
                }

                // Gather new details for the doctor
                string newUsername, newSpecialization, newPhoneNumber, newPassword;

                cout << "Enter new Username (leave blank to keep existing): ";
                cin >> newUsername;
                if (!newUsername.empty() && Database::usernameExists(newUsername))
                {
                    cout << "Username already exists. Please choose a different one." << endl;
                    break;
                }
                if (newUsername.empty())
                    newUsername = existingDoctor->getUserName();

                cout << "Enter new Specialization (leave blank to keep existing): ";
                cin >> newSpecialization;
                if (newSpecialization.empty())
                    newSpecialization = existingDoctor->getSpecialization();

                cout << "Enter new Phone Number (leave blank to keep existing): ";
                cin >> newPhoneNumber;
                if (newPhoneNumber.empty())
                    newPhoneNumber = existingDoctor->getPhoneNumber();

                cout << "Enter new Password (leave blank to keep existing): ";
                cin >> newPassword;
                if (newPassword.empty())
                    newPassword = existingDoctor->getPassword();

                // Update the doctor's details
                Database::updateDoctorInformation(doctorId, newUsername, newSpecialization, newPhoneNumber, newPassword);
                cout << "Doctor information updated successfully." << endl;

                break;
            }

            case 8:
            {
                int doctorId;
                Database::showAllDoctors();
                cout << "Enter Doctor ID to delete: ";
                cin >> doctorId;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Invalid input for Doctor ID. Please enter a number." << endl;
                    break;
                }

                Doctor *doctor = Database::findDoctorById(doctorId);

                if (!doctor)
                {
                    cout << "No doctor found with ID " << doctorId << "!" << endl;
                    break;
                }

                Database::deleteDoctor(doctorId);
                Database::deleteAppointmentsByDoctor(doctorId);
            }
            break;

            case 9:
            {
                string username, phoneNumber, gender, password;

                cout << "Enter Patient's Username: ";
                cin >> username;
                if (username.empty() || Database::usernameExists(username))
                {
                    cout << "Invalid or existing username. Please try again." << endl;
                    break;
                }

                cout << "Enter Patient's phoneNumber: ";
                cin >> phoneNumber;
                if (phoneNumber.empty())
                {
                    cout << "phoneNumber cannot be empty. Please try again." << endl;
                    break;
                }

                cout << "Enter Patient's Gender: ";
                cin >> gender;
                if (gender.empty())
                {
                    cout << "gender cannot be empty. Please try again." << endl;
                    break;
                }

                cout << "Enter Patient's Password: ";
                cin >> password;
                if (password.empty())
                {
                    cout << "password cannot be empty. Please try again." << endl;
                    break;
                }

                // Create a new Patient instance
                Patient *newPatient = new Patient(Database::patientID++, username, phoneNumber, gender, password);
                cout << "Patient created successfully with ID " << newPatient->getId() << "!" << endl;
            }
            break;

            case 10:
                Database::showAllPatients();
                break;

            case 11:
            {
                int patientId;
                Database::showAllPatients();
                cout << "Enter Patient ID to update: ";
                cin >> patientId;

                if (cin.fail())
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    cout << "Invalid input for Patient ID. Please enter a number." << endl;
                    break;
                }

                // Validate doctor ID
                Patient *existingPatient = Database::findPatientById(patientId);
                if (!existingPatient)
                {
                    cout << "No patient found with ID " << patientId << "!" << endl;
                    break;
                }

                // Gather new details for the doctor
                string newUsername, newPhoneNumber, newGender, newPassword;

                cout << "Enter new Username (leave blank to keep existing): ";
                cin >> newUsername;
                if (!newUsername.empty() && Database::usernameExists(newUsername))
                {
                    cout << "Username already exists. Please choose a different one." << endl;
                    break;
                }
                if (newUsername.empty())
                    newUsername = existingPatient->getUserName();

                cout << "Enter new phone number (leave blank to keep existing): ";
                cin >> newPhoneNumber;
                if (newPhoneNumber.empty())
                    newPhoneNumber = existingPatient->getPhoneNumber();

                cout << "Enter new gender (leave blank to keep existing): ";
                cin >> newGender;
                if (newGender.empty())
                    newGender = existingPatient->getGender();

                cout << "Enter new Password (leave blank to keep existing): ";
                cin >> newPassword;
                if (newPassword.empty())
                    newPassword = existingPatient->getPassword();

                // Update the doctor's details
                Database::updatePatientInformation(patientId, newUsername, newPhoneNumber, newGender, newPassword);
                cout << "Patient information updated successfully." << endl;

                break;
            }

            case 12:
            {
                int patientId;
                Database::showAllPatients();
                cout << "Enter Patient ID to delete: ";
                cin >> patientId;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Invalid input for Patient ID. Please enter a number." << endl;
                    break;
                }

                Patient *patient = Database::findPatientById(patientId);

                if (!patient)
                {
                    cout << "No Patient found with ID " << patientId << "!" << endl;
                    break;
                }

                Database::deletePatient(patientId);
                Database::deleteAppointmentsByPatient(patientId);
            }
            break;

            case 13:
                cout << "Total number of all appointments: ";
                cout << Database::getTotalNumberOfAppointments() << endl;
                break;

            case 14:
            {
                int appointmentId;
                Database::showAllAppointments();
                cout << "Enter the Appointment ID to change status: ";
                cin >> appointmentId;

                if (cin.fail())
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    cout << "Invalid input. Please enter a number." << endl;
                    break;
                }

                Appointment *appointment = Database::findAppointmentById(appointmentId);
                if (appointment == nullptr)
                {
                    cout << "Appointment with ID " << appointmentId << " not found." << endl;
                    break;
                }

                Database::changeConfirmationStatus(appointmentId);
                cout << "Appointment status changed successfully." << endl;
            }
            break;

            case 15:
                Database::showPatientDoctorRatio();
                break;

            case 16:
                Database::showPatientAppointmentCounts();
                break;
            
            case 17:
                isLoggedIn = 0;
                break;

            default:
                break;
            }
        }
        else if (isLoggedIn && (instanceof <Patient>(account)))
        {

            printf("\n--------- Welcome Patient %s ---------\n", account->getUserName().c_str());

            int choice;

            cout << "\n1- Show patient information\n";
            cout << "2- Update patient information\n";
            cout << "3- Create  an appointment\n";
            cout << "4- Delete an appointment\n";
            cout << "5- View your appointments\n";
            cout << "6- Delete your account\n";
            cout << "7- Logout" << endl;

            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();                                                   // Clear the error state of cin
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                cout << "Invalid input for choice. Please enter a number." << endl;
            }

            switch (choice)
            {
            case 1:
                cout << "Patient's information" << endl;
                Database::showPersonInformation(account,account->getId());
                break;
            case 2:
            {
                // Validate doctor ID
                Patient *existingPatient = Database::findPatientById(account->getId());
                if (!existingPatient)
                {
                    cout << "No patient found with ID " << account->getId() << "!" << endl;
                    break;
                }

                // Gather new details for the doctor
                string newUsername, newPhoneNumber, newGender, newPassword;

                cout << "Enter new Username (leave blank to keep existing): ";
                cin >> newUsername;
                if (!newUsername.empty() && Database::usernameExists(newUsername))
                {
                    cout << "Username already exists. Please choose a different one." << endl;
                    break;
                }
                if (newUsername.empty())
                    newUsername = existingPatient->getUserName();

                cout << "Enter new phone number (leave blank to keep existing): ";
                cin >> newPhoneNumber;
                if (newPhoneNumber.empty())
                    newPhoneNumber = existingPatient->getPhoneNumber();

                cout << "Enter new gender (leave blank to keep existing): ";
                cin >> newGender;
                if (newGender.empty())
                    newGender = existingPatient->getGender();

                cout << "Enter new Password (leave blank to keep existing): ";
                cin >> newPassword;
                if (newPassword.empty())
                    newPassword = existingPatient->getPassword();

                // Update the doctor's details
                Database::updatePatientInformation(account->getId(), newUsername, newPhoneNumber, newGender, newPassword);
                cout << "Patient information updated successfully." << endl;
            }
            break;
            case 3:
            {
                int doctorId, typeInt;
                string date;

                Database::showAllDoctors();
                cout << "Enter Doctor ID: ";
                cin >> doctorId;
                if (cin.fail())
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    cout << "Invalid input for Doctor ID. Please enter a number." << endl;
                    break;
                }

                // Validate the doctor ID
                Doctor *doctor = Database::findDoctorById(doctorId);
                if (!doctor)
                {
                    cout << "No doctor found with ID " << doctorId << "!" << endl;
                    break;
                }

                cout << "Enter Appointment Date (e.g., 2023-12-31): ";
                cin >> date;

                // Check if there's already an appointment with the same doctor on the same date
                bool appointmentExists = std::any_of(Database::appointments.begin(), Database::appointments.end(),
                 [&doctorId, &date](const Appointment *appointment)
                    {
                     return appointment->getDoctor().getId() == doctorId && appointment->getDate() == date;
                    });

                if (appointmentExists)
                {
                    cout << "An appointment with this doctor on the specified date already exists." << endl;
                    break;
                }

                cout << "Enter Appointment Type (0 for General, 1 for Emergency, etc.): ";
                cin >> typeInt;
                if (cin.fail() || typeInt < 0 || typeInt > 1)
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore bad input
                    cout << "Invalid appointment type entered." << endl;
                    break;
                }
                Appointment::Type type = static_cast<Appointment::Type>(typeInt);

                // Create the Appointment object
                Appointment *newAppointment = new Appointment(Database::appointmentID++, type, *doctor, *dynamic_cast<Patient *>(account), date, false);
                Database::addAppointment(*newAppointment);

                cout << "Appointment created successfully with ID " << newAppointment->getId() << "!" << endl;
            }

            break;
            case 4:
            {
                int appointmentId;
                Database::showAppointmentsByPatient(account->getId());
                cout << "Enter Appointment ID to delete: ";
                cin >> appointmentId;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Invalid input for Doctor ID. Please enter a number." << endl;
                    break;
                }

                Appointment *appointment = Database::findAppointmentById(appointmentId);

                if (!appointment)
                {
                    cout << "No appointment found with ID " << appointmentId << "!" << endl;
                    break;
                }

                Database::deleteAppointment(appointmentId);
                break;
            }
            break;
            case 5:
                Database::showAppointmentsByPatient(account->getId());
                break;
            case 6:
                Database::deleteAppointmentsByPatient(account->getId());
                Database::deletePatient(account->getId());
                isLoggedIn = 0;
                break;
            case 7:
                isLoggedIn = 0;
                break;

            default:
                cout << "invalid choice" << endl;
                if (cin.fail())
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    cout << "Invalid input for Doctor ID. Please enter a number." << endl;
                    break;
                }
                break;
            }
        }
        else if (isLoggedIn && (instanceof <Doctor>(account)))
        {

            printf("\n--------- Welcome Doctor %s ---------\n", account->getUserName().c_str());

            int choice;

            cout << "\n1- Show doctor information\n";
            cout << "2- Update doctor information\n";
            cout << "3- Delete an appointment\n";
            cout << "4- View your appointments\n";
            cout << "5- Change statue of your appointments\n";
            cout << "6- Delete your account\n";
            cout << "7- Logout\n";

            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();                                                   // Clear the error state of cin
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                cout << "Invalid input for choice. Please enter a number." << endl;
            }
            switch (choice)
            {
            case 1:
                Database::showPersonInformation(account,account->getId());
                break;
            case 2:
            {
                // Validate doctor ID
                Doctor *existingDoctor = Database::findDoctorById(account->getId());
                if (!existingDoctor)
                {
                    cout << "No doctor found with ID " << account->getId() << "!" << endl;
                    break;
                }

                // Gather new details for the doctor
                string newUsername, newSpecialization, newPhoneNumber, newPassword;

                cout << "Enter new Username (leave blank to keep existing): ";
                cin >> newUsername;
                if (!newUsername.empty() && Database::usernameExists(newUsername))
                {
                    cout << "Username already exists. Please choose a different one." << endl;
                    break;
                }
                if (newUsername.empty())
                    newUsername = existingDoctor->getUserName();

                cout << "Enter new Specialization (leave blank to keep existing): ";
                cin >> newSpecialization;
                if (newSpecialization.empty())
                    newSpecialization = existingDoctor->getSpecialization();

                cout << "Enter new Phone Number (leave blank to keep existing): ";
                cin >> newPhoneNumber;
                if (newPhoneNumber.empty())
                    newPhoneNumber = existingDoctor->getPhoneNumber();

                cout << "Enter new Password (leave blank to keep existing): ";
                cin >> newPassword;
                if (newPassword.empty())
                    newPassword = existingDoctor->getPassword();

                // Update the doctor's details
                Database::updateDoctorInformation(account->getId(), newUsername, newSpecialization, newPhoneNumber, newPassword);
                cout << "Doctor information updated successfully." << endl;
            }
            break;
            case 3:
            {
                int appointmentId;
                Database::showAllAppointmentsByDoctor(account->getId());
                cout << "Enter Appointment ID to delete: ";
                cin >> appointmentId;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Invalid input for Doctor ID. Please enter a number." << endl;
                    break;
                }

                Appointment *appointment = Database::findAppointmentById(appointmentId);

                if (!appointment)
                {
                    cout << "No appointment found with ID " << appointmentId << "!" << endl;
                    break;
                }

                Database::deleteAppointment(appointmentId);
                break;
            }
            break;
            case 4:
                Database::showAllAppointmentsByDoctor(account->getId());
                break;
            case 5:
            {
                int appointmentId;
                Database::showAllAppointmentsByDoctor(account->getId());
                cout << "Enter the Appointment ID to change status: ";
                cin >> appointmentId;

                if (cin.fail())
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    cout << "Invalid input. Please enter a number." << endl;
                    break;
                }

                // Check if the appointment belongs to this doctor
                Appointment *appointment = Database::findAppointmentById(appointmentId);
                if (appointment == nullptr || appointment->getDoctor().getId() != account->getId())
                {
                    cout << "Appointment with ID " << appointmentId << " not found or does not belong to you." << endl;
                    break;
                }

                Database::changeConfirmationStatus(appointmentId);
                cout << "Appointment status changed successfully." << endl;
            }
            break;

            case 6:
                Database::deleteAppointmentsByDoctor(account->getId());
                Database::deleteDoctor(account->getId());
                isLoggedIn = 0;
                break;
            case 7:
                isLoggedIn = 0;
                break;

            default:
                break;
            }
        }
        else
        {

            cout << "\n--------- WELCOME TO HOSPITAL SYSTEM ---------\n";

            cout << "1- Login\n";
            cout << "2- Register\n";
            cout << "3- Exit\n";

            cout << "\nSelect an option: ";
            cin >> option;

            if (cin.fail())
            {
                cin.clear();                                                   // Clear the error state of cin
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                cout << "Invalid input for choice . Please enter a number." << endl;
            }

            std::string username;
            string password;
            string specialization;
            string phoneNumber;
            string gender;

            switch (option)
            {
            case 1:
                cout << "\nEnter your username: " << endl;
                cin >> username;

                if (username.empty() || !(Database::usernameExists(username)) )
                    {
                        printf("There is no one who has '%s' as a username.\n", username.c_str());
                        break;
                    }

                cout << "Enter your password: " << endl;
                cin >> password;

                cout << "\nLogging in...\n\n";
                account = Database::login(username, password);
                if (account != NULL)
                {
                    isLoggedIn = true;
                    break;
                }
                else
                {
                    cout << "User not found! Please try again.\n";
                }
                break;

            case 2:
                
                cout << "1- Doctor\n";
                cout << "2- Patient\n";
                cout << "3- Exit\n";

                int option;
                cout << "Enter type for register:" << endl;
                cin >> option;

                if (cin.fail())
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    cout << "Invalid input for choice . Please enter a number." << endl;
                }

                switch (option)
                {
                case 1:
                {
                    string username, specialization, phoneNumber, password;

                    cout << "Enter Doctor's Username: ";
                    cin >> username;
                    if (username.empty() || Database::usernameExists(username))
                    {
                        cout << "Invalid or existing username. Please try again." << endl;
                        break;
                    }

                    cout << "Enter Doctor's Specialization: ";
                    cin >> specialization;
                    if (specialization.empty())
                    {
                        cout << "Specialization cannot be empty. Please try again." << endl;
                        break;
                    }

                    cout << "Enter Doctor's Phone Number: ";
                    cin >> phoneNumber;
                    if (cin.fail())
                    {
                        cin.clear();                                                   // Clear the error state of cin
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                        cout << "Invalid input for phoneNumber. Please enter a number." << endl;
                        break;
                    }

                    cout << "Enter Doctor's Password: ";
                    cin >> password;

                    // Create a new Doctor instance
                    Doctor *newDoctor = new Doctor(Database::doctorID++, username, specialization, phoneNumber, password);
                    cout << "Doctor created successfully with ID " << newDoctor->getId() << "!" << endl;
                    isLoggedIn = true;
                    Display();
                }
                case 2:
                {
                    string username, phoneNumber, gender, password;

                    cout << "Enter Patient's Username: ";
                    cin >> username;
                    if (username.empty() || Database::usernameExists(username))
                    {
                        cout << "Invalid or existing username. Please try again." << endl;
                        break;
                    }

                    cout << "Enter Patient's phoneNumber: ";
                    cin >> phoneNumber;
                    if (phoneNumber.empty())
                    {
                        cout << "phoneNumber cannot be empty. Please try again." << endl;
                        break;
                    }

                    cout << "Enter Patient's Gender: ";
                    cin >> gender;
                    if (gender.empty())
                    {
                        cout << "gender cannot be empty. Please try again." << endl;
                        break;
                    }

                    cout << "Enter Patient's Password: ";
                    cin >> password;
                    if (password.empty())
                    {
                        cout << "password cannot be empty. Please try again." << endl;
                        break;
                    }

                    // Create a new Patient instance
                    Patient *newPatient = new Patient(Database::patientID++, username, phoneNumber, gender, password);
                    cout << "Patient created successfully with ID " << newPatient->getId() << "!" << endl;

                    isLoggedIn = true;
                    Display();
                }

                case 3:
                    break;
                default:
                    cout << "invalid option, try again" << endl;
                    break;
                }
                break;

            case 3:
                cout << "\n------------ Goodbye! ------------\n";
                Database::deleteAllData();
                return 0;

            default:
                cout << "Invalid option. try again.\n";
                break;
            }
        }
    }
    return 0;
}

void defaultInformation()
{
    Person *admin = new Admin(0, "admin", "admin");
    Person *user1 = new Patient(1, "murat", "123", "male", "123");
    Person *user2 = new Patient(2, "mehmet", "321", "male", "321");
    Person *user3 = new Doctor(1, "doctor", "eye", "12345678", "123");
}