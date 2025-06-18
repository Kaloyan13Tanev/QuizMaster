#pragma once
#include "Question.h"
#include "String.h"
#include "Vector.hpp"

class MultipleChoiceQuestion : public Question
{
private:
	Vector<String> answers;
	Vector<unsigned> rightAnswers;

	void setAnswers(const Vector<String>& answers);
	void setRightAnswers(const Vector<unsigned>& rightAnswers);

public:
	MultipleChoiceQuestion(std::istream& is);
	MultipleChoiceQuestion(const String& question, double points,
		const Vector<String>& answers, const Vector<unsigned>& rightAnswers);

	Question* clone() const override;

	const Vector<String> getAnswers() const;
	const Vector<unsigned> getRightAnswers() const;

	double answer() const override;
	String rightAnswerToString() const override;

	void serialize(std::ostream& os);
	void deserialize(std::istream& is);
};
