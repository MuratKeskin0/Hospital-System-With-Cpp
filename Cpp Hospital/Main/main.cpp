#include <iostream>
#include <string>
#include <vector>
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

            printf("\n--------- Welcome Admin ---------\n", account->getUserName());

            int choice;

            string newTopicName;
            int newOptionLength;
            vector<string> newTopicOptions;
            bool flag;
            bool flagForUser = 0;
            int idVoteRate = 0;
            int idForOpenStatus = 0;
            int idForDeleteUser = 0;

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
        }
        else if (isLoggedIn && (instanceof <Patient>(account)))
        {

            printf("\n--------- Welcome Doctor ---------\n", account->getUserName());

            int choice;

            cout << "\n1- Show doctor information\n";
            cout << "2- Update doctor information\n";
            cout << "3- Delete an appointment\n";
            cout << "4- View your appointments\n";
            cout << "5- Delete your account\n";
            cout << "6- Delete User Account" << endl;
            cout << "7- Logout" << endl;

            cout << "Enter your choice: ";
            cin >> choice;
        }
        else if (isLoggedIn && (instanceof <Doctor>(account)))
        {

            printf("\n--------- Welcome Admin ---------\n", account->getUserName());

            int choice;

            cout << "\n1- Show doctor information\n";
            cout << "2- Update doctor information\n";
            cout << "3- Delete an appointment\n";
            cout << "4- View your appointments\n";
            cout << "5- Delete your account\n";
            cout << "6- Logout\n";
            cout << "7- Delete User Account" << endl;

            cout << "Enter your choice: ";
            cin >> choice;
        }
        else
        {

            cout << "\n--------- WELCOME TO HOSPITAL SYSTEM ---------\n";

            cout << "1- Login\n";
            cout << "2- Register\n";
            cout << "3- Exit\n";

            cout << "\nSelect an option: ";
            cin >> option;

            // cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string username;
            string password;
            switch (option)
            {
            case 1:
                cout << "\nEnter your username: " << endl;
                cin >> username ;

                cout << "Enter your password: " << endl;
                cin >> password ;

                cout << "\nLogging in...\n\n";
                account = Database::login(username, password);
                if (account != nullptr)
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
/*
                cout << "Enter your username: ";
                getline(cin, username);

                cout << "Enter your password: ";
                getline(cin, password);

                account = new User(Database::userID, name, username, password, mail, 0);
                cout << "\nAccount created successfully!\n\n";
                Database::userID++;
                isLoggedIn = true;
                break;
*/
            case 3:
                cout << "\n------------ Goodbye! ------------\n";
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