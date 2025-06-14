#pragma once
#include "Question.h"
#include "TrueOrFalseQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "MatchingPairsQuestion.h"
#include "ShortAnswerQuestion.h"

class QuestionFactory
{
private:
	static TrueOrFalseQuestion* createTrueOrFalseQuestion();
	static SingleChoiceQuestion* createSingleChoiceQuestion();
	static MultipleChoiceQuestion* createMultipleChoiceQuestion();
	static MatchingPairsQuestion* createMatchingPairsQuestion();
	static ShortAnswerQuestion* createShortAnswerQuestion();

public:
	static Question* createQuestion();
};
