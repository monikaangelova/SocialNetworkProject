#include "UserSystem.h"

UserSystem::UserSystem() {
    std::ifstream fin(usersFilename.c_str());
    if (fin.is_open()) {
        users = Vector<User>();
        User user;
        while (fin >> user)
        {
            users.pushBack(user);
        }
        fin.close();
    }
}

bool UserSystem::login(const String& firstName, const String& passwordHash) {
    size_t size = users.getSize();
    for (size_t i = 0; i < size; i++)
    {
        if (firstName == users[i].getName() && users[i].isPasswordCorrect(passwordHash))
        {
            loggedUser = &users[i];
            return true;
        }
    }
    loggedUser = nullptr;
    return false;
}
bool UserSystem::signup(String firstName, String lastName, String passwordHash, unsigned points) {

    if (loggedUser != nullptr)
        return false;
    User newUser(firstName, lastName, passwordHash, points);
    users.pushBack(newUser);
    return true;
}
User* UserSystem::logout() {
    if (loggedUser == nullptr)
        return nullptr;
    User* res = loggedUser;
    loggedUser = nullptr;
    return res;
}
User* UserSystem::getLoggedUser() const {
    return loggedUser;
}
UserSystem::~UserSystem() {
    std::ofstream ofs(usersFilename.c_str());
    if (!ofs.is_open()) {
        return;
    }
    size_t size = users.getSize();
    for (size_t i = 0; i < size; i++) {
        ofs << users[i];
    }
    loggedUser = nullptr;
    ofs.close();
}