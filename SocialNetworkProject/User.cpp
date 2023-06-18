#include "User.h"
#include "HelperFunctions.h"
User::User(String firstName, String lastName, String passwordHash, unsigned points) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->passwordHash = passwordHash;
    this->points = points;
    this->id = genetateId();
}
User::User() :firstName("unknown"), lastName("unknown"), passwordHash("password"), id(0), points(0) {}
String User::getName() const {
    return firstName;
}
String User::getFullName() const {
    return firstName + " " + lastName;
}
unsigned User::getId() const {
    return id;
}

std::ostream& operator<<(std::ostream& ofs, const User& user) {
    ofs << user.id << " ";
    ofs << user.firstName.length() << " " << user.firstName << " ";
    ofs << user.lastName.length() << " " << user.lastName << " ";
    ofs << user.passwordHash.length() << " " << user.passwordHash << " ";
    ofs<< user.points << '\n';
    return ofs;
}
std::istream& operator>>(std::istream& ifs, User& user) {
    ifs >> user.id;
    readString(ifs, user.firstName);
    readString(ifs, user.lastName);
    readString(ifs, user.passwordHash);
    ifs >> user.points;
    return ifs;
}

String User::shortUserInfo() const
{
    String res = firstName;
    res += String(" ") + lastName;
    res += String(" {id: ");
    res += String(intToString(id)) + String( "}");
    return res;
}
void User::printUser() const
{
    std::cout << "User: " << firstName << " " << lastName << std::endl;
    std::cout << "User has " << points << " points!" << std::endl;
}
bool User::isPasswordCorrect(const String& passwordHash) const
{
    return this->passwordHash == passwordHash;
}

void User::vote()
{
    points++;
}
