#pragma once
#include "Question.h"
#include "Vector.hpp"

class MatchingPairsQuestion : public Question
{
private:
	Vector<String> firstCol;
	Vector<String> secondCol;
	Vector<unsigned> rightConnections;

	void setFirstCol(const Vector<String>& firstCol);
	void setSecondCol(const Vector<String>& secondCol);
	void setRightConnections(const Vector<unsigned>& rightConnections);

public:
	MatchingPairsQuestion(std::istream& is);
	MatchingPairsQuestion(const String& question, double points, const Vector<String>& firstCol, const Vector<String>& secondCol, const Vector<unsigned>& rightAnswers);

	Question* clone() const override;

	const Vector<String>& getFirstCol() const;
	const Vector<String>& getSecondCol() const;
	const Vector<unsigned>& getRightConnections() const;

	double answer() const override;
	const String& rightAnswerToString() const override;

	void serialize(std::ostream& os);
	void deserialize(std::istream& is);
};
