#pragma once
#include "String.h"

class Question
{
private:
	String question;
	double points;

	void setQuestion(const String& question);
	void setPoints(double points);

public:
	Question() = delete;
	virtual ~Question() = default;

	virtual Question* clone() const = 0;

	Question(const String& question, double points);

	const String& getQuestion() const;
	const double getPoints() const; 

	virtual double answer() const = 0;
};
