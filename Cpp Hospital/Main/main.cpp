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
    start:
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
            cout << "15- Delete User Account" << endl;
            cout << "16- Logout" << endl;

            cout << "\nSelect an option : ";

            cin >> choice;
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
                if (cin.fail() || typeInt < -1 || typeInt > 2)
                {
                    cin.clear();                                                   // Clear the error state of cin
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore bad input
                    cout << "Invalid appointment type entered." << endl;
                    break;
                }
                Appointment::Type type = static_cast<Appointment::Type>(typeInt);

                // Create the Appointment object
                Appointment *newAppointment = new Appointment(Database::appointmentID++, type, *doctor, *patient, date, false);

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
                    break;  // Exit the function or handle the error appropriately
                }

                Doctor *newDoctor = Database::findDoctorById(newDoctorId);
                if (!newDoctor)
                {
                    cout << "Doctor with ID " << newDoctorId << " not found." << endl;
                    break; // Exit the function or handle the error appropriately
                }


                Database::showAllPatients();
                cout << "Enter new Patient ID: ";
                cin >> newPatientId;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                    break; // Exit the function or handle the error appropriately
                }

                Patient *newPatient = Database::findPatientById(newPatientId);
                if (!newPatient)
                {
                    cout << "Patient with ID " << newPatientId << " not found." << endl;
                    break; // Exit the function or handle the error appropriately
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
                    break; // Exit the function or handle the error appropriately
                }

                // Update the appointment details
                existingAppointment->setDoctor(*Database::findDoctorById(newDoctorId));
                existingAppointment->setPatient(*Database::findPatientById(newPatientId));
                existingAppointment->setDate(newDate);
                existingAppointment->setType(static_cast<Appointment::Type>(newTypeInt));

                cout << "Appointment updated successfully with ID " << existingAppointment->getId() << "!" << endl;
            }
            break;

            case 16:
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
            cout << "2- Create  an appointment\n";
            cout << "3- Delete an appointment\n";
            cout << "4- View your appointments\n";
            cout << "5- Delete your account\n";
            cout << "6- Logout" << endl;

            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                /* code */
                break;
            case 6:
                isLoggedIn = 0;
                break;

            default:
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
            cout << "5- Delete your account\n";
            cout << "6- Logout\n";

            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                /* code */
                break;
            case 6:
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

            string username;
            string password;
            string specialization;
            string phoneNumber;
            string gender;

            switch (option)
            {
            case 1:
                cout << "\nEnter your username: " << endl;
                cin >> username;

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
                    // continue;
                }
                break;

            case 2:
                cout << "Enter type for register:" << endl;
                cout << "1- Doctor\n";
                cout << "2- Patient\n";
                cout << "3- Exit\n";

                int option;
                cin >> option;

                switch (option)
                {
                case 1:
                    cout << "Enter your username: ";
                    cin >> username;

                    cout << "Enter your specialization: ";
                    cin >> specialization;

                    cout << "Enter your phoneNumber: ";
                    cin >> phoneNumber;

                    cout << "Enter your password: ";
                    cin >> password;

                    account = new Doctor(Database::doctorID, username, specialization, phoneNumber, password);
                    cout << "\nAccount created successfully!\n\n";
                    Database::doctorID++;
                    isLoggedIn = true;
                    goto start;
                case 2:
                    cout << "Enter your username: ";
                    cin >> username;

                    cout << "Enter your phoneNumber: ";
                    cin >> phoneNumber;

                    cout << "Enter your gender: ";
                    cin >> gender;

                    cout << "Enter your password: ";
                    cin >> password;

                    account = new Patient(Database::patientID, username, phoneNumber, gender, password);
                    cout << "\nAccount created successfully!\n\n";
                    Database::patientID++;
                    isLoggedIn = true;
                    goto start;
                case 3:
                    return 0;
                default:
                    cout << "invalid option, try again";
                    break;
                }
                break;

            case 3:
                cout << "\n------------ Goodbye! ------------\n";
                Database::deleteAllData();
                return 0;

            default:
                cout << "Invalid option. Please select 1, 2, or 3.\n";
            }
        }
    }
}

void defaultInformation()
{
    Person *admin = new Admin(0, "admin", "admin");
    Person *user1 = new Patient(1, "murat", "123", "male", "123");
    Person *user2 = new Patient(2, "mehmet", "321", "male", "321");
    Person *user3 = new Doctor(1, "doctor", "eye", "12345678", "123");
}