#include "TrueOrFalseQuestion.h"
#include "Console.h";
#include <iostream>

TrueOrFalseQuestion::TrueOrFalseQuestion(std::istream& is) : Question(is, QuestionType::TrueOrFalse)
{
	this->deserialize(is);
}

TrueOrFalseQuestion::TrueOrFalseQuestion(const String& question, double points, bool answer) : Question(question, points, QuestionType::TrueOrFalse)
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

String TrueOrFalseQuestion::rightAnswerToString() const
{
	if (rightAnswer == true)
		return "Right answer: True\n";
	
	return "Right answer: False\n";
}

void TrueOrFalseQuestion::serialize(std::ostream& os)
{
	Question::serialize(os);
	os.write((const char*)&rightAnswer, sizeof(rightAnswer));
}

void TrueOrFalseQuestion::deserialize(std::istream& is)
{
	bool rightAnswer;
	is.read((char*)&rightAnswer, sizeof(rightAnswer));
	this->rightAnswer = rightAnswer;
}
