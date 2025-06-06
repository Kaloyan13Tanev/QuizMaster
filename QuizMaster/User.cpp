#include "User.h"

void User::setFirstName(const String& firstName)
{
    if (firstName.getLen() == 0)
        throw std::invalid_argument("First name cannot be empty!");
}

void User::setLastName(const String& lastName)
{
    if (lastName.getLen() == 0)
        throw std::invalid_argument("Last name cannot be empty!");
}

void User::setUsername(const String& username)
{
    if (username.getLen() == 0)
        throw std::invalid_argument("Username cannot be empty!");
}

User::User(String firstName, String lastName, String username)
{
}

const String& User::getFirstName() const
{
    return firstName;
}

const String& User::getLastName() const
{
    return lastName;
}

const String& User::getUsername() const
{
    return username;
}

