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
	User(const String& firstName, const String& lastName, const String& username, const String& password, Role role);

	virtual ~User() = default;

	virtual User* clone() const = 0;

	const String& getFirstName() const;
	const String& getLastName() const;
	const String& getUsername() const;
	const Role getRole() const;

	virtual void write(std::ostream& os) const;
	virtual void read(std::istream& is);

	friend std::ostream& operator<<(std::ostream& os, const User& user);
	friend std::istream& operator>>(std::istream& is, User& user);
};