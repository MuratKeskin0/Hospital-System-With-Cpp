#ifndef ADMINMANAGER_H
#define ADMINMANAGER_H

#include "../Headers/admin.h"

class AdminManager {
private:
    static const int MAX_ADMINS = 100;  // Adjust the size as needed
    Admin adminsStatic[MAX_ADMINS];
    int staticArraySize = 0;

public:
    void addAdmin(const Admin& admin);
    bool updateAdmin(int id, const Admin& updatedAdmin);
    bool deleteAdmin(int id);

    int getAdminCount() const;
    Admin getAdminAtIndex(int index) const;
};

#endif

