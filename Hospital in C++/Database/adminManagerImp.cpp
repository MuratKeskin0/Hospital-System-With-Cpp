#include "AdminManager.h"

void AdminManager::addAdmin(const Admin& admin) {
    if (staticArraySize < MAX_ADMINS) {
        adminsStatic[staticArraySize++] = admin;
    } else {
        // Handle array full situation
    }
}

bool AdminManager::updateAdmin(int id, const Admin& updatedAdmin) {
    for (int i = 0; i < staticArraySize; ++i) {
        if (adminsStatic[i].getId() == id) {
            adminsStatic[i] = updatedAdmin;
            return true; // Update successful
        }
    }
    return false; // Admin not found
}

bool AdminManager::deleteAdmin(int id) {
    for (int i = 0; i < staticArraySize; ++i) {
        if (adminsStatic[i].getId() == id) {
            for (int j = i; j < staticArraySize - 1; ++j) {
                adminsStatic[j] = adminsStatic[j + 1];
            }
            staticArraySize--;
            return true; // Deletion successful
        }
    }
    return false; // Admin not found
}

int AdminManager::getAdminCount() const {
    return staticArraySize;
}

Admin AdminManager::getAdminAtIndex(int index) const {
    if (index >= 0 && index < staticArraySize) {
        return adminsStatic[index];
    }
    // Handle invalid index
    // You can throw an exception or return a default-constructed Admin object
    // Example: throw std::out_of_range("Index out of bounds");
    return Admin(); // Return default Admin if index is invalid
}

