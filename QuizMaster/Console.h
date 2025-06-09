#pragma once

class TrueOrFalseQuestion;
class SingleChoiceQuestion;
class MultipleChoiceQuestion;
class ShortAnswerQuestion;
class MatchingPairsQuestion;

class Console
{
public:
	Console() = delete;
	static String readLine(); 
	static bool answerTrueFalseQuestion();
	static unsigned answerSingleChoiceQuestion(const SingleChoiceQuestion& scQuestion);
	static Vector<unsigned> answerMultipleChoiceQuestion(const MultipleChoiceQuestion& mcQuestion);
	static String answerShortAnswerQuestion();
	static Vector<unsigned> answerMatchingPairsQuestion(const MatchingPairsQuestion& mpQuestion);
};
