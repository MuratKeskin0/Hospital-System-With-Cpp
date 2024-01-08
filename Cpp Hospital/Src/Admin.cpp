#include "../Headers/Admin.h"
#include "../Headers/Database.h"

Admin::Admin(int id, const std::string& username, const std::string& password)
    : Person(id, username, password) {
    // Find an available slot in the static array
    bool inserted = false;
    for (int i = 0; i < Database::MAX_ADMINS; ++i) {
        if (Database::admins[i] == nullptr) {
            Database::admins[i] = this;  // Store the pointer to the new Admin in the array
            inserted = true;
            break;
        }
    }

    if (!inserted) {
        std::cerr << "Error: Maximum number of admins reached. Admin not added." << std::endl;
    } else {
        Database::insertPerson(*this);  
    }
}

Admin::Admin() {}
