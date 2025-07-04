#pragma once
#include "Question.h"
#include "Vector.hpp"
#include "Console.h"

class Quiz
{
private:
	String ID;
	String title;
	String creatorUsername;
	Vector<Question*> questions;
	unsigned timesPlayed;
	Vector<String> likes;

	void setID(const String& ID);
	void setTitle(const String& title);
	void setQuestions(const Vector<Question*>& questions);

	void free();
	void copyFrom(const Quiz& other);
	void moveFrom(Quiz&& other);

public:
	Quiz();
	Quiz(const Quiz& other);
	Quiz(Quiz&& other) noexcept;
	Quiz& operator=(const Quiz& other);
	Quiz& operator=(Quiz&& other) noexcept;
	~Quiz();

	Quiz(std::istream& is);
	Quiz(const String& ID, const String& title, const String& creatorUsername, const Vector<Question*>& question);

	unsigned getTimesPlayed();
	void updateTimesPlayed();
	const String& getID() const;
	const String& getTitle() const;
	const String& getCreator() const;
	const Vector<const Question*>& getQuestions() const;
	const unsigned getTimesPlayed() const;
	const Vector<String>& getLikes() const;
	void addLike(const String& username);
	void removeLike(const String& username);

	void playQuiz();
	void playQuizShuffled();
	void playQuizTest();
	void playQuizTestShuffled();

	static String generateID();

	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);

	friend void operator<<(std::ostream& os, const Quiz& quiz);
};
