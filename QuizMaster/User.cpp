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

User::User()
{
    firstName = "";
    lastName = "";
    username = "";
    password = "";
}

User::User(const String& firstName, const String& lastName, const String& username, const String& password, Role role)
{
    setUsername(username);
    setFirstName(firstName);
    setLastName(lastName);
    setPassword(password);
    this->role = role;
}

User::User(const String& firstName, const String& lastName, const String& username, const String& password, Role role, Vector<String> favQuizzes)
{
    setUsername(username);
    setFirstName(firstName);
    setLastName(lastName);
    setPassword(password);
    this->role = role;
    this->favQuizes = Vector<String>(favQuizzes);
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

const Vector<String>& User::getFavQuizzes() const
{
    return this->favQuizes;
}

const bool User::correctPassword(const String& passwordInput) const
{
    return this->password == passwordInput;
}

void User::addToFavs(const String& quizID)
{
    if (favQuizes.contains(quizID))
        throw std::invalid_argument("Quiz already added to favourites!");

    favQuizes.push_back(quizID);
}

void User::removeFromFavs(const String& quizID)
{
    if (!favQuizes.contains(quizID))
        throw std::invalid_argument("Quiz is not in favourites!");

    favQuizes.remove(quizID);
}

void User::write(std::ostream& os) const
{
    os << "@" << this->username << " " << this->firstName << " " << this->lastName;
}

void User::read(std::istream& is)
{
    is >> this->username >> this->firstName >> this->lastName;
}

void User::serialize(std::ostream& os) const
{
    os.write((const char*)&role, sizeof(role));
    username.serialize(os);
    password.serialize(os);
    firstName.serialize(os);
    lastName.serialize(os);
    size_t size = this->favQuizes.getSize();
    os.write((const char*)&size, sizeof(size));
    for (size_t i = 0; i < size; i++)
        this->favQuizes[i].serialize(os);
}

void User::deserialize(std::istream& is)
{
    String username, password, firstName, lastName;
    Vector<String> favQuizzes;
    username.deserialize(is);
    password.deserialize(is);
    firstName.deserialize(is);
    lastName.deserialize(is);
    size_t size = 0;
    is.read((char*)size, sizeof(size));
    favQuizes = Vector<String>(size);
    for (size_t i = 0; i < size; i++)
    {
        String quizID;
        quizID.deserialize(is);
        favQuizzes.push_back(quizID);
    }
    this->username = username;
    this->password = password;
    this->firstName = firstName;
    this->lastName = lastName;
    this->role = role;
    this->favQuizes = Vector<String>(favQuizzes);
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
