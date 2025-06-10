#include "TrueOrFalseQuestion.h"
#include "Console.h";
#include <iostream>

TrueOrFalseQuestion::TrueOrFalseQuestion(const String& question, double points, bool answer) : Question(question, points)
{
	this->rightAnswer = answer;
}

Question* TrueOrFalseQuestion::clone() const
{
	return new TrueOrFalseQuestion(*this);
}

double TrueOrFalseQuestion::answer() const
{
	Console::printTrueFalseQuestion(*this);

	if (Console::answerTrueFalseQuestion() == rightAnswer)
		return getPoints();

	return 0;
}
