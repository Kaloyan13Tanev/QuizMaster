#pragma once
#include "Question.h"

class TrueOrFalseQuestion : public Question
{
private:
	bool rightAnswer;

public:
	TrueOrFalseQuestion() = delete;
	TrueOrFalseQuestion(const String& question, double points, bool answer);

	Question* clone() const override;

	double answer() const override;
};
