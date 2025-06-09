#pragma once
#include "Question.h"
#include "String.h"

class ShortAnswerQuestion : public Question
{
private:
	String rightAnswer;

	void setRightAnswer(const String& rightAnswer);

public:
	ShortAnswerQuestion() = delete;
	ShortAnswerQuestion(const String& question, double points, const String& rightAnswer);

	Question* clone() const override;

	const String& getRightAnswer() const;

	double answer() const override;
};
