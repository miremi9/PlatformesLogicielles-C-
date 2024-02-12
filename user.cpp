#include "user.h"

User::User(std::string ID, std::string name, std::string password)
{
    this->ID = ID;
    this->name = name;
    this->password = password;
}

string User::getName()
{
    return name;
}

int User::checkPassword(std::string  password2)
{
    return password2.compare(password);
}

string User::getID()
{
    return ID;
}

string User::getPassword(){
    return password;
}
