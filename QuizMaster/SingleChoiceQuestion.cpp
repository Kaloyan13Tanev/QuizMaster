#include "SingleChoiceQuestion.h"
#include <iostream>

SingleChoiceQuestion::SingleChoiceQuestion(char* question, unsigned points, char answers[4][51], char rightAnswer) : Question(question, points)
{
	if (answers[0] == "" || answers[1] == "" || answers[2] == "" || answers[3] == "")
	{
		throw std::invalid_argument("Some of the given answers are empty!");
	}

	strcpy(this->answers[0], answers[0]);
	strcpy(this->answers[1], answers[1]);
	strcpy(this->answers[2], answers[2]);
	strcpy(this->answers[3], answers[3]);

	5
}
