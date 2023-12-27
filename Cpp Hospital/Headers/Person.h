#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
public:
    Person(int id, const std::string& username, const std::string& password, const int &isAdmin);
    virtual ~Person();
    Person();

    // Getter functions
    int getId() const;
    std::string getUserName() const;
    std::string getPassword() const;

    // Setter functions
    void setId(int id);
    void setUserName(const std::string& username);
    void setPassword(const std::string& password);

private:
    int id;
    std::string username;
    std::string password;
    int isAdmin;
    friend int checkAdmin(Person *person);
};

#endif // PERSON_H
