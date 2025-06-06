#pragma once
#include "String.h"

class User
{
private:
	String firstName;
	String lastName;
	String username;

	void setFirstName(const String& firstName);
	void setLastName(const String& lastName);
	void setUsername(const String& username);

public:
	User() = delete;
	User(String firstName, String lastName, String username);

	const String& getFirstName() const;
	const String& getLastName() const;
	const String& getUsername() const;
};