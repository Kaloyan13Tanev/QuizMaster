#pragma once
#include "Question.h"
#include "Vector.hpp"

class MatchingPairsQuestion : public Question
{
private:
	Vector<String> firstCol;
	Vector<String> secondCol;

	void setFirstCol(const Vector<String>& firstCol);
	void setSecondCol(const Vector<String>& secondCol);

public:
	MatchingPairsQuestion() = delete;
	MatchingPairsQuestion(const String& question, double points, const Vector<String>& firstCol, const Vector<String>& secondCol);

	Question* clone() const override;

	const Vector<String>& getFirstCol() const;
	const Vector<String>& getSecondCol() const;

	double answer() const override;
};
