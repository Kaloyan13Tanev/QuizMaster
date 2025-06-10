#pragma once
#include "String.h"
#include "Vector.hpp"
#include "Quiz.h"
#include "Role.h"

class User
{
private:
	Role role;
	String firstName;
	String lastName;
	String username;
	String password;
	Vector<Quiz> favQuizes;

	void setFirstName(const String& firstName);
	void setLastName(const String& lastName);
	void setUsername(const String& username);
	void setPassword(const String& password);

public:
	User() = delete;
	User(String firstName, String lastName, String username, String password);

	const String& getFirstName() const;
	const String& getLastName() const;
	const String& getUsername() const;
};