#pragma once
#include "Question.h"

class TrueOrFalseQuestion : public Question
{
private:
	bool rightAnswer;

public:
	TrueOrFalseQuestion() = delete;
	TrueOrFalseQuestion(char* question, unsigned points, bool answer);

	unsigned answer() override;
};
