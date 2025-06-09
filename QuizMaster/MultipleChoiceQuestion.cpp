#include "MultipleChoiceQuestion.h"
#include "Console.h"

void MultipleChoiceQuestion::setAnswers(const Vector<String>& answers)
{
	if (answers.getSize() <= 1)
		throw std::invalid_argument("There must be at least two answers to the question!");

	for (size_t i = 0; i < answers.getSize(); i++)
	{
		this->answers.insert(i, answers[i]);
	}
}

void MultipleChoiceQuestion::setRightAnswers(const Vector<unsigned>& rightAnswers)
{
	if (answers.getSize() <= 1)
		throw std::invalid_argument("There must be at least two right answers to the question!");

	for (size_t i = 0; i < rightAnswers.getSize(); i++)
	{
		this->rightAnswers.insert(i, rightAnswers[i]);
	}
}

MultipleChoiceQuestion::MultipleChoiceQuestion(const String& question, double points, 
	const Vector<String>& answers, const Vector<unsigned>& rightAnswers) : Question(question, points)
{
	setAnswers(answers);
	setRightAnswers(rightAnswers);
}

Question* MultipleChoiceQuestion::clone() const
{
	return new MultipleChoiceQuestion(*this);
}

const Vector<String> MultipleChoiceQuestion::getAnswers() const
{
	return this->answers;
}

const Vector<unsigned> MultipleChoiceQuestion::getRightAnswers() const
{
	return this->rightAnswers;
}

double MultipleChoiceQuestion::answer() const
{
	unsigned points = 0;
	Vector<unsigned> givenAnswers = Console::answerMultipleChoiceQuestion(*this);
	double pointsPerRight = (double)this->getPoints() / this->getRightAnswers().getSize();
	for (size_t i = 0; i < givenAnswers.getSize(); i++)
	{
		if (this->getRightAnswers().contains(givenAnswers[i]))
			points += pointsPerRight;
	}

	if (points = this->getPoints() && givenAnswers.getSize() > this->getRightAnswers().getSize())
		points -= pointsPerRight * (this->getRightAnswers().getSize() - givenAnswers.getSize());

	if (points < 0)
		return 0;

	return points;
}
