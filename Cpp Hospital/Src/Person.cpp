#include "../Headers/Person.h"

Person::Person(int id, const std::string &username, const std::string &password)
    : id(id), username(username), password(password)
{
    
}

// Virtual Destructor
Person::~Person() {}
Person::Person()
{
}


int Person::getId() const
{
    return id;
}

std::string Person::getUserName() const
{
    return username;
}

std::string Person::getPassword() const
{
    return password;
}

void Person::setId(int id)
{
    this->id = id;
}

void Person::setUserName(const std::string &username)
{
    this->username = username;
}

void Person::setPassword(const std::string &password)
{
    this->password = password;
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "ID: " << person.getId() << ", Username: " << person.getUserName();
        return os;
    }


