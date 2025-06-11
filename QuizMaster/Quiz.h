#pragma once
#include "Question.h"
#include "Vector.hpp"
#include "Player.h"

class Quiz
{
private:
	String ID;
	String title;
	String creatorUsername;
	Vector<Question*> questions;
	unsigned timesPlayed;
	Vector<Player> likes;

	void free();
	void copyFrom(const Quiz& other);
	void moveFrom(Quiz&& other);

	void setID(const String& ID);
	void setTitle(const String& title);
	void setQuestions(const Vector<Question*> questions);

public:
	Quiz() = delete;
	Quiz(const Quiz& other);
	Quiz(Quiz&& other);
	Quiz& operator=(const Quiz& other);
	Quiz& operator=(Quiz&& other);
	~Quiz();

	Quiz(const String& ID, const String& title, const String& creatorUsername, const Vector<Question*> question);

	unsigned getTimesPlayed();
	void updateTimesPlayed();
	const String& getID() const;
	const String& getTitle() const;
	const String& getCreator() const;
	const Vector<const Question*>& getQuestions() const;
	const unsigned getTimesPlayed() const;
	const Vector<Player>& getLikes() const;
};
