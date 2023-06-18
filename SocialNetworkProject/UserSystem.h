#pragma once
#include "User.h"
#include "Vector.hpp"
const String usersFilename = "users.txt";

class UserSystem
{
    Vector<User>users;
    User* loggedUser = nullptr;
public:
    UserSystem();
    bool login(const String& firstName, const String& passwordHash);
    bool signup(String firstName, String lastName, String passwordHash, unsigned points);
    User* logout();
    User* getLoggedUser() const;
    ~UserSystem();
};


