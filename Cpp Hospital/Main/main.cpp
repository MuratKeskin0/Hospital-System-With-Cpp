#include <iostream>
#include <string>
#include <vector>
#include "../Src/Person.cpp"
#include "../Src/Admin.cpp"
#include "../Src/Doctor.cpp"
#include "../Headers/Patient.h"
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
        if (isLoggedIn && (instanceof <Admin>(account) || (checkAdmin(account) == 1)))
        {
         
            printf("\n--------- Welcome Admin ---------\n", account->getUserName());
          

            int choice;
            string topicName = "";
            int optionLength = 0;
            

            string newTopicName;
            int newOptionLength;
            vector<string> newTopicOptions;
            bool flag;
            bool flagForUser = 0;
            int idVoteRate = 0;
            int idForOpenStatus = 0;
            int idForDeleteUser = 0;

            cout << "\n1- Create Topic" << endl;
            cout << "2- Show All Topics" << endl;
            cout << "3- Update Topic" << endl;
            cout << "4- Delete Topic" << endl;
            cout << "5- View your vote rates" << endl;
            cout << "6- Open/close topics for voting" << endl;
            cout << "7- Delete User Account" << endl;
            cout << "8- Logout" << endl;

          
            cout << "\nSelect an option : ";
         
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

            string name;
            string username;
            string password;
            string mail;

            
            }
        }
    }


void defaultInformation()
{
    Person *admin = new Patient(0, "admin","admin","admin","admin",1);
    Person *user1 = new Patient(1, "murat", "123", "male", "123",0);
    Person *user2 = new Patient(2, "mehmet" ,"321", "male", "321",0);
    Person *user3 =new Doctor(1,"doctor","eye","12345678","123",0);
}