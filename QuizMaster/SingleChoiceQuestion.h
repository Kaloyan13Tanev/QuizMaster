#pragma once
#include "Question.h"
#include "Vector.hpp"
#include "String.h"

class SingleChoiceQuestion : public Question
{
private:
	Vector<String> answers;
	unsigned rightAnswer;

	void setAnswers(const Vector<String>& answers);
	void setRightAnswer(unsigned rightAnswer);

public:
	SingleChoiceQuestion(std::istream& is);
	SingleChoiceQuestion(const String& question, double points, const Vector<String>& answers, unsigned rightAnswer);

	Question* clone() const override;

	const Vector<String>& getAnswers() const;
	const unsigned getRightAnswer() const;

	double answer() const override;
	String rightAnswerToString() const override;

	void serialize(std::ostream& os);
	void deserialize(std::istream& is);
};
