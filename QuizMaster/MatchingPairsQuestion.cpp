#include "MatchingPairsQuestion.h"
#include "Console.h"

MatchingPairsQuestion::MatchingPairsQuestion(std::istream& is) : Question(is, QuestionType::MatchingPairs)
{
	this->deserialize(is);
}

void MatchingPairsQuestion::setFirstCol(const Vector<String>& firstCol)
{
	if (firstCol.getSize() <= 1)
		throw std::invalid_argument("First column should have at least 2 parameters!");

	for (size_t i = 0; i < firstCol.getSize(); i++)
	{
		if (firstCol[i].getLen() == 0)
			throw std::invalid_argument("Parameters in the first column cannot be empty!");

		this->firstCol.push_back(firstCol[i]);
	}
}

void MatchingPairsQuestion::setSecondCol(const Vector<String>& secondCol)
{
	if (secondCol.getSize() <= 1)
		throw std::invalid_argument("Second column should have at least 2 parameters!");

	for (size_t i = 0; i < secondCol.getSize(); i++)
	{
		if (secondCol[i].getLen() == 0)
			throw std::invalid_argument("Parameters in the second column cannot be empty!");

		this->secondCol.push_back(secondCol[i]);
	}
}

void MatchingPairsQuestion::setRightConnections(const Vector<unsigned>& rightConnections)
{
	if (rightConnections.getSize() != this->getFirstCol().getSize())
		throw std::invalid_argument("The number of connections is different from what it should be!");

	for (size_t i = 0; i < this->getFirstCol().getSize(); i++)
		this->rightConnections.push_back(rightConnections[i]);
}


MatchingPairsQuestion::MatchingPairsQuestion(const String& question, double points, const Vector<String>& firstCol,
	const Vector<String>& secondCol, const Vector<unsigned>& rightAnswers) : Question(question, points, QuestionType::MatchingPairs)
{
	setFirstCol(firstCol);
	setSecondCol(secondCol);
	setRightConnections(rightAnswers);
}

Question* MatchingPairsQuestion::clone() const
{
	return new MatchingPairsQuestion(*this);
}

const Vector<String>& MatchingPairsQuestion::getFirstCol() const
{
	return this->firstCol;
}

const Vector<String>& MatchingPairsQuestion::getSecondCol() const
{
	return this->secondCol;
}

const Vector<unsigned>& MatchingPairsQuestion::getRightConnections() const
{
	return this->rightConnections;
}

double MatchingPairsQuestion::answer() const
{
	Console::printMatchingPairsQuestion(*this);
	Vector<unsigned> givenAnswers = Console::answerMatchingPairsQuestion(*this);
	for (size_t i = 0; i < this->getRightConnections().getSize(); i++)
	{
		if (this->getRightConnections()[i] != givenAnswers[i])
			return 0;
	}

	return this->getPoints();
}

String MatchingPairsQuestion::rightAnswerToString() const
{
	String string = "Right answers: ";
	for (size_t i = 1; i <= firstCol.getSize(); i++)
	{
		string += String(i);
		string += '.';
		string += 'a' + rightConnections[i - 1] - 1;
		if (i != firstCol.getSize())
			string += ', ';
	}
	return string + "\n";
}

void MatchingPairsQuestion::serialize(std::ostream& os)
{
	Question::serialize(os);
	size_t size = this->firstCol.getSize();
	os.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		this->firstCol[i].serialize(os);
	}
	size = this->secondCol.getSize();
	os.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		this->secondCol[i].serialize(os);
	}
	size = this->rightConnections.getSize();
	os.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		os.write((const char*)&this->rightConnections[i], sizeof(this->rightConnections[i]));
	}
}

void MatchingPairsQuestion::deserialize(std::istream& is)
{
	size_t size = 0;
	is.read((char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		String fc;
		fc.deserialize(is);
		this->firstCol.push_back(fc);
	}
	size = 0;
	is.read((char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		String sc;
		sc.deserialize(is);
		this->secondCol.push_back(sc);
	}
	size = 0;
	is.read((char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		unsigned u;
		is.read((char*)&u, sizeof(u));
		this->rightConnections.push_back(u);
	}
}
