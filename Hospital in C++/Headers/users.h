#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    int id;
    std::string name;
    std::string address;
    std::string mobile;

public:
    User(int id, const std::string &name, const std::string &address, const std::string &mobile);
    virtual ~User() {}

    int getId() const;
    void setId(int id);
    std::string getName() const;
    void setName(const std::string &name);
    std::string getAddress() const;
    void setAddress(const std::string &address);
    std::string getMobile() const;
    void setMobile(const std::string &mobile);
};

#endif
