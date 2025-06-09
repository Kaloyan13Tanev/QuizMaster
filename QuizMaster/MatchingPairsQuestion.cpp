#include "MatchingPairsQuestion.h"

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

MatchingPairsQuestion::MatchingPairsQuestion(const String& question, double points, const Vector<String>& firstCol, const Vector<String>& secondCol) : Question(question, points)
{
	setFirstCol(firstCol);
	setSecondCol(secondCol);
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

double MatchingPairsQuestion::answer() const
{
	return 0.0;
}
