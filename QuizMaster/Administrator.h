#pragma once
#include "User.h"

class Admin : public User
{
public:
	Admin() = delete;
	Admin(const String& firstName, const String& lastName, const String& username, const String& password);
};
