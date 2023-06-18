#pragma once
#include "Unique.h"
#include "String.h"
#include <iostream>
#include <fstream>

class User : public Unique {
    String firstName;
    String lastName;
    String passwordHash;
    unsigned id;
    unsigned points;

public:
    User();
    User(String firstName, String lastName, String passwordHash, unsigned points);
    friend std::ostream& operator<<(std::ostream& ofs, const User& user);
    friend std::istream& operator>>(std::istream& ifs, User& user);
    String getName()const;
    String getFullName()const;
    unsigned getId()const;
    void printUser() const;
    String shortUserInfo() const;
    bool isPasswordCorrect(const String& password) const;
    void vote();
};


