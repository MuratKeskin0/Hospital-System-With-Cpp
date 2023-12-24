#include "../Headers/database.h"
// Include other necessary headers...

Database db;  // Global database object

void login();
void adminInterface();
void doctorInterface();
void patientInterface();

int main() {
    db.loadFromFile();
    login();
    db.saveToFile();
    return 0;
}

void login() {
    // Implement login functionality
    // Based on user type, call adminInterface(), doctorInterface(), or patientInterface()
}

void adminInterface() {
    // Admin-specific functionalities
    // Example: Add/remove doctor, view all appointments, etc.
}

void doctorInterface() {
    // Doctor-specific functionalities
    // Example: View appointments, update profile, etc.
}

void patientInterface() {
    // Patient-specific functionalities
    // Example: Book/cancel appointments, update personal information, etc.
}

// Implement other helper functions as needed
