#pragma once
#include "Question.h"

class SingleChoiceQuestion : public Question
{
private:


	char answers[4][51]{};
	char rightAnswer;

public:
	SingleChoiceQuestion() = delete;
	SingleChoiceQuestion(char* question, unsigned points, char answers[4][51], char rightAnswer);

	unsigned answer() override;
};
