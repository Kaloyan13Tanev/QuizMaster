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

MultipleChoiceQuestion::MultipleChoiceQuestion(std::istream& is) : Question(is, QuestionType::MultipleChoice)
{
	this->deserialize(is);
}

MultipleChoiceQuestion::MultipleChoiceQuestion(const String& question, double points, const Vector<String>& answers,
	const Vector<unsigned>& rightAnswers) : Question(question, points, QuestionType::MultipleChoice)
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
	Console::printMultipleChoiceQuestion(*this);

	unsigned points = 0;
	Vector<unsigned> givenAnswers = Console::answerMultipleChoiceQuestion(*this);
	double pointsPerRight = (double)this->getPoints() / this->getRightAnswers().getSize();
	for (size_t i = 0; i < givenAnswers.getSize(); i++)
	{
		if (this->getRightAnswers().contains(givenAnswers[i]))
			points += pointsPerRight;
	}

	if (points - this->getPoints() < 0.0000001 && givenAnswers.getSize() > this->getRightAnswers().getSize())
		points -= pointsPerRight * (this->getRightAnswers().getSize() - givenAnswers.getSize());

	if (points < 0)
		return 0;

	return points;
}

String MultipleChoiceQuestion::rightAnswerToString() const
{
	String answer = "Right answers: ";
	for (size_t i = 0; i < rightAnswers.getSize(); i++)
	{
		answer += String((char)('a' + rightAnswers[i] - 1));
		if (i != rightAnswers.getSize() - 1)
			answer += ", ";
	}
	return answer + "\n";
}

void MultipleChoiceQuestion::serialize(std::ostream& os)
{
	Question::serialize(os);
	size_t size = this->answers.getSize();
	os.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		this->answers[i].serialize(os);
	}
	size = this->rightAnswers.getSize();
	os.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		os.write((const char*)&this->rightAnswers[i], sizeof(this->rightAnswers[i]));
	}
}

void MultipleChoiceQuestion::deserialize(std::istream& is)
{
	size_t size = 0;
	is.read((char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		String a;
		a.deserialize(is);
		this->answers.push_back(a);
	}
	size = 0;
	is.read((char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		unsigned u;
		is.read((char*)&u, sizeof(u));
		this->rightAnswers.push_back(u);
	}
}
