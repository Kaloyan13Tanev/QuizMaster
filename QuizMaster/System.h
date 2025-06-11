#pragma once
#include "User.h"
#include "Administrator.h"
#include "Player.h"

class System
{
private:
	User* loggedUser;

	System();

public:
	static System& getInstance();
	System(const System&) = delete;

	void login(const String& username, const String& password);
	void logout();
	void quit();
	void signup(const String& firstName, const String& lastName, const String& username, const String& password1, const String& password2);

	const User* getLoggedUser() const;
};
