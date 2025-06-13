#pragma once
#include "Question.h"
#include "String.h"

class ShortAnswerQuestion : public Question
{
private:
	String rightAnswer;

	void setRightAnswer(const String& rightAnswer);

public:
	ShortAnswerQuestion(std::istream& is);
	ShortAnswerQuestion(const String& question, double points, const String& rightAnswer);

	Question* clone() const override;

	const String& getRightAnswer() const;

	double answer() const override;
	const String& rightAnswerToString() const override;

	void serialize(std::ostream& os);
	void deserialize(std::istream& is);
};
