#pragma once
#include "User.h"

class Player : public User
{
private:
	unsigned points;
	unsigned level;

	void setPoints(unsigned points);
	void setPoints(const String& points);
	void setLevel(unsigned level);
	void setLevel(const String& level);

public:
	Player() = delete;
	Player(const String& firstName, const String& lastName, const String& username, const String& password);

	User* clone() const override;

	void write(std::ostream& os) const override;
	void read(std::istream& is) override;

	friend std::ostream& operator<<(std::ostream& os, const Player& player);
	friend std::istream& operator>>(std::istream& os, Player& player);
};
