#pragma once
#include "Question.h"

class TrueOrFalseQuestion : public Question
{
private:
	bool rightAnswer;

public:
	TrueOrFalseQuestion(std::istream& is);
	TrueOrFalseQuestion(const String& question, double points, bool answer);

	Question* clone() const override;

	double answer() const override;
	const String& rightAnswerToString() const override;

	void serialize(std::ostream& os);
	void deserialize(std::istream& is);
};	