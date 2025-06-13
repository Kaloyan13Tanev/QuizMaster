#include "Player.h"

void Player::setPoints(unsigned points)
{
	if (level >= 1 && level <= 10 && points >= 1000)
		throw std::invalid_argument("Points cannot be 1000 or more for levels 1-10!");
	else if (level >= 11 && level <= 20 && points >= 2000)
		throw std::invalid_argument("Points cannot be 2000 or more for levels 11-20!");
	else if (level >= 21 && level <= 30 && points >= 3000)
		throw std::invalid_argument("Points cannot be 3000 or more for levels 21-30!");
	else if (level >= 31 && points >= 4000)
		throw std::invalid_argument("Points cannot be 4000 or more for levels above 31!");

	this->points = points;
}

void Player::setPoints(const String& pointsString)
{
	setPoints(pointsString.toUnsigned());
}

void Player::setLevel(unsigned level)
{
	this->level = level;
}

void Player::setLevel(const String& level)
{
	setLevel(level.toUnsigned());
}

Player::Player() : User()
{
	level = 0;
	points = 0;
}

Player::Player(const String& firstName, const String& lastName, const String& username, const String& password) :
	User(firstName, lastName, username, password, Role::Player)
{
	level = 0;
	points = 0;
}

User* Player::clone() const
{
	return new Player(*this);
}

void Player::write(std::ostream& os) const
{
	User::write(os);
	os << level << " level " << points << "points";
}

void Player::read(std::istream& is)
{
	User::read(is);
	String level;
	is >> level;
	setLevel(level);
	String points;
	is >> points;
	setPoints(points);
}

void Player::serialize(std::ostream& os) const
{
	User::serialize(os);
	os.write((const char*)level, sizeof(level));
	os.write((const char*)points, sizeof(points));
}

void Player::deserialize(std::istream& is)
{
	User::deserialize(is);
	unsigned level = 0;
	is.read((char*)level, sizeof(level));
	this->setLevel(level);
	unsigned points = 0;
	is.read((char*)points, sizeof(points));
	this->setPoints(points);
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	player.write(os);
	return os;
}

std::istream& operator>>(std::istream& is, Player& player)
{
	player.read(is);
	return is;
}
