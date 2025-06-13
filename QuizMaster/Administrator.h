#pragma once
#include "User.h"

class Admin : public User
{
public:
	Admin();
	Admin(const String& firstName, const String& lastName, const String& username, const String& password);

	User* clone() const override;
};
