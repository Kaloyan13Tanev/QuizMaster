#pragma once
#include "String.h"
#include "QuestionType.h"

class Question
{
private:
	QuestionType questionType;
	String question;
	double points;

	void setQuestion(const String& question);
	void setPoints(double points);

public:
	Question(std::istream& is);
	virtual ~Question() = default;

	virtual Question* clone() const = 0;

	Question(const String& question, double points, QuestionType questionType);

	const String& getQuestion() const;
	const double getPoints() const; 
	const QuestionType getQuestionType() const;

	virtual double answer() const = 0;
	virtual const String& rightAnswerToString() const = 0;

	virtual void serialize(std::ostream& os);
	virtual void deserialize(std::istream& is);
};
