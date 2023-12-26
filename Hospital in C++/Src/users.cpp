#include "../Headers/users.h"

User::User(int id, const std::string &name, const std::string &address, const std::string &mobile)
    : id(id), name(name), address(address), mobile(mobile) {}

int User::getId() const {
    return id;
}

void User::setId(int newId) {
    id = newId;
}

std::string User::getName() const {
    return name;
}

void User::setName(const std::string &newName) {
    name = newName;
}

std::string User::getAddress() const {
    return address;
}

void User::setAddress(const std::string &newAddress) {
    address = newAddress;
}

std::string User::getMobile() const {
    return mobile;
}

void User::setMobile(const std::string &newMobile) {
    mobile = newMobile;
}
