#include "SingleChoiceQuestion.h"
#include "Console.h"
#include <iostream>

SingleChoiceQuestion::SingleChoiceQuestion(const String& question, double points, 
	const Vector<String>& answers, unsigned rightAnswer) : Question(question, points)
{
	setAnswers(answers);
	setRightAnswer(rightAnswer);
}

const Vector<String>& SingleChoiceQuestion::getAnswers() const
{
	return this->answers;
}

const unsigned SingleChoiceQuestion::getRightAnswer() const
{
	return this->rightAnswer;
}

double SingleChoiceQuestion::answer() const
{
	if (Console::answerSingleChoiceQuestion(*this) == rightAnswer)
		return getPoints();

	return 0;
}

Question* SingleChoiceQuestion::clone() const
{
	return new SingleChoiceQuestion(*this);
}

void SingleChoiceQuestion::setAnswers(const Vector<String>& answers)
{
	if (answers.getSize() <= 1)
		throw std::invalid_argument("There must be at least two answers to the question!");

	for (size_t i = 0; i < answers.getSize(); i++)
	{
		this->answers.insert(i, answers[i]);
	}
}

void SingleChoiceQuestion::setRightAnswer(unsigned rightAnswer)
{
	if (rightAnswer == 0 || rightAnswer > getAnswers().getSize())
	{
		String message = "The right answer should be between 1 and " + getAnswers().getSize();
		message += "!";
		throw std::invalid_argument(message.c_str());
	}

	this->rightAnswer = rightAnswer;
}
