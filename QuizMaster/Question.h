#pragma once
#include "String.h"

class Question
{
private:
	String question;
	unsigned points;

	void setQuestion(const String& question);
	void setPoints(unsigned points);

public:
	Question() = delete;
	virtual ~Question() = 0;

	virtual Question* clone() const = 0;

	Question(const String& question, unsigned points);

	const String& getQuestion() const;
	const unsigned getPoints() const; 

	virtual unsigned answer() = 0;
};
