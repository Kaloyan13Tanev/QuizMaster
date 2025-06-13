#include "Administrator.h"

Admin::Admin() : User()
{
}

Admin::Admin(const String& firstName, const String& lastName, const String& username, const String& password) :
	User(firstName, lastName, username, password, Role::Admin)
{

}

User* Admin::clone() const
{
	return new Admin(*this);
}
