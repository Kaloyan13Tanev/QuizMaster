#include "ShortAnswerQuestion.h"
#include "Console.h"

void ShortAnswerQuestion::setRightAnswer(const String& rightAnswer)
{
	if (rightAnswer.getLen() == 0)
		throw std::invalid_argument("The right answer shouldn't be empty!");

	this->rightAnswer = rightAnswer;
}

ShortAnswerQuestion::ShortAnswerQuestion(std::istream& is) : Question(is)
{
	this->deserialize(is);
}

ShortAnswerQuestion::ShortAnswerQuestion(const String& question, double points, const String& rightAnswer)
	: Question(question, points, QuestionType::ShortAnswer)
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
	Console::printShortAnswerQuestion(*this);

	String answer = Console::answerShortAnswerQuestion();
	if (answer == this->getRightAnswer())
		return this->getPoints();

	return 0;
}

const String& ShortAnswerQuestion::rightAnswerToString() const
{
	return "Right answer: " + rightAnswer;
}

void ShortAnswerQuestion::serialize(std::ostream& os)
{
	Question::serialize(os);
	rightAnswer.serialize(os);
}

void ShortAnswerQuestion::deserialize(std::istream& is)
{
	Question::deserialize(is);
	rightAnswer.deserialize(is);
}
