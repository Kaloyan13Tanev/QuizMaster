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

void User::setPassword(const String& password)
{
    if (password.getLen() < 8)
        throw std::invalid_argument("Password should be at least 8 characters long!");
}

User::User(const String& firstName, const String& lastName, const String& username, const String& password, Role role)
{
    setUsername(username);
    setFirstName(firstName);
    setLastName(lastName);
    setPassword(password);
    this->role = role;
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

const Role User::getRole() const
{
    return this->role;
}

void User::write(std::ostream& os) const
{
    os << "@" << this->username << " " << this->firstName << " " << this->lastName;
}

void User::read(std::istream& is)
{
    is >> this->username >> this->firstName >> this->lastName;
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
    user.write(os);
    return os;
}

std::istream& operator>>(std::istream& is, User& user)
{
    user.read(is);
    return is;
}
