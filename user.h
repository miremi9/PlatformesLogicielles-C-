#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <iostream>

using namespace std;

class User
{
  private:
    string ID;
    string name;
    string password;
  public:
    User(std::string ID, std::string name, std::string password);

    string getName();

    int checkPassword(std::string  password2);

    string getID();

    string getPassword();
};

#endif // USER_H
