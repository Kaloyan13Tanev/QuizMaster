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
	MatchingPairsQuestion() = delete;
	MatchingPairsQuestion(const String& question, double points, const Vector<String>& firstCol, const Vector<String>& secondCol, const Vector<unsigned>& rightAnswers);

	Question* clone() const override;

	const Vector<String>& getFirstCol() const;
	const Vector<String>& getSecondCol() const;
	const Vector<unsigned>& getRightConnections() const;

	double answer() const override;
};
