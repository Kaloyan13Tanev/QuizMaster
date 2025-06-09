#include "ShortAnswerQuestion.h"
#include "Console.h"

void ShortAnswerQuestion::setRightAnswer(const String& rightAnswer)
{
	if (rightAnswer.getLen() == 0)
		throw std::invalid_argument("The right answer shouldn't be empty!");

	this->rightAnswer = rightAnswer;
}

ShortAnswerQuestion::ShortAnswerQuestion(const String& question, double points, const String& rightAnswer) : Question(question, points)
{
	this->setRightAnswer(rightAnswer);	
}

Question* ShortAnswerQuestion::clone() const
{
	return new ShortAnswerQuestion(*this);
}

const String& ShortAnswerQuestion::getRightAnswer() const
{
	return rightAnswer;
}

double ShortAnswerQuestion::answer() const
{
	String answer = Console::answerShortAnswerQuestion();
	if (answer == this->getRightAnswer())
		return this->getPoints();

	return 0;
}
