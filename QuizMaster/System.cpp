#include "System.h"

System& System::getInstance()
{
    static System instance;
    return instance;
}

void System::login(const String& username, const String& password)
{
    //check for username in file
    //check if password is the same
}

void System::logout()
{
    if (loggedUser == nullptr)
        throw std::invalid_argument("No profile logged in!");

    //update in file
    loggedUser = nullptr;
}

void System::quit()
{
    if (loggedUser != nullptr)
        bool quit; //update in file
}

void System::signup(const String& firstName, const String& lastName, const String& username, const String& password1, const String& password2)
{
    if (loggedUser != nullptr)
        throw std::invalid_argument("Profile already logged in!");

    //check file for username
    if (password1 != password2)
        throw std::invalid_argument("The password is not typed correctly!");

    Player player = Player(firstName, lastName, username, password1);
    //save in file
}

const User* System::getLoggedUser() const
{
    return this->loggedUser;
}
