#include "Administrator.h"

Admin::Admin(const String& firstName, const String& lastName, const String& username, const String& password) :
	User(firstName, lastName, username, password, Role::Admin)
{

}
