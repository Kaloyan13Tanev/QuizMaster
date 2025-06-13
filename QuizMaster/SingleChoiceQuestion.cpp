#include "SingleChoiceQuestion.h"
#include "Console.h"
#include <iostream>

SingleChoiceQuestion::SingleChoiceQuestion(std::istream& is) : Question(is)
{
	this->deserialize(is);
}

SingleChoiceQuestion::SingleChoiceQuestion(const String& question, double points,
	const Vector<String>& answers, unsigned rightAnswer) : Question(question, points, QuestionType::SingleChoice)
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
	Console::printSingleChoiceQuestion(*this);

	if (Console::answerSingleChoiceQuestion(*this) == rightAnswer)
		return getPoints();

	return 0;
}

const String& SingleChoiceQuestion::rightAnswerToString() const
{
	return "Right answer: " + rightAnswer;
}

void SingleChoiceQuestion::serialize(std::ostream& os)
{
	Question::serialize(os);
	size_t size = this->answers.getSize();
	os.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		this->answers[i].serialize(os);
	}
	os.write((const char*)&rightAnswer, sizeof(rightAnswer));
}

void SingleChoiceQuestion::deserialize(std::istream& is)
{
	Question::deserialize(is);
	size_t size;
	is.read((char*)&size, sizeof(size));
	this->answers = Vector<String>(size);
	for (size_t i = 0; i < size; i++)
	{
		String answer;
		answer.deserialize(is);
		this->answers.push_back(answer);
	}
	unsigned rightAnswer;
	is.read((char*)&rightAnswer, sizeof(rightAnswer));
	this->rightAnswer = rightAnswer;
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
