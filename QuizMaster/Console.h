#pragma once
#include "String.h"
#include "Vector.hpp"

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

	static void printCommandsNoLogin();
	static void printCommandsAdmin();
	static void printCommandsPlayer();

	static void Start();

	static void printTrueFalseQuestion(const TrueOrFalseQuestion& tfQuestion);
	static bool answerTrueFalseQuestion();

	static void printSingleChoiceQuestion(const SingleChoiceQuestion& scQuestion);
	static unsigned answerSingleChoiceQuestion(const SingleChoiceQuestion& scQuestion);

	static void printMultipleChoiceQuestion(const MultipleChoiceQuestion& mcQuestion);
	static Vector<unsigned> answerMultipleChoiceQuestion(const MultipleChoiceQuestion& mcQuestion);

	static void printShortAnswerQuestion(const ShortAnswerQuestion& saQuestion);
	static String answerShortAnswerQuestion();

	static void printMatchingPairsQuestion(const MatchingPairsQuestion& mpQuestion);
	static Vector<unsigned> answerMatchingPairsQuestion(const MatchingPairsQuestion& mpQuestion);
};
