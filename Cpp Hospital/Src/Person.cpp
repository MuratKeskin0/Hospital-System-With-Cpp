#include "../Headers/Person.h"

// Constructor
Person::Person(int id, const std::string &username, const std::string &password)
    : id(id), username(username), password(password)
{
    
}

// Virtual Destructor
Person::~Person() {}
Person::Person()
{
}

/*int checkAdmin(Person *person) // friend function
{
    if (person->isAdmin == 1 || person->getId() == 0)
    {
        person->isAdmin = 1;
        return 1;
    }
    person->isAdmin = 0;
    return 0;
}*/

// Getters
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

// Setters
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
