#include "Console.h"
#include "StringHelpers.h"
#include "TrueOrFalseQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "ShortAnswerQuestion.h"
#include "MatchingPairsQuestion.h"
#include <iostream>

String Console::readLine()
{
	String res;
	std::cin >> std::ws;

	char temp;
	while (std::cin.get(temp) && temp != '\n')
	{
		res += temp;
	}
	return res;
}

void Console::printTrueFalseQuestion(const TrueOrFalseQuestion& tfQuestion)
{
	std::cout << tfQuestion.getQuestion() << std::endl;
}

bool Console::answerTrueFalseQuestion()
{
	char givenA;
	std::cout << "Answer with 'T' or 'F': ";
	std::cin >> givenA;
	if (givenA != 'T' && givenA != 'F')
		throw std::invalid_argument("You should answer with 'T' or 'F'!");

	if (givenA == 'T')
		return 1;
	else
		return 0;
}

void Console::printSingleChoiceQuestion(const SingleChoiceQuestion& scQuestion)
{
	std::cout << scQuestion.getQuestion() << std::endl;
	for (size_t i = 0; i < scQuestion.getAnswers().getSize(); i++)
	{
		std::cout << (char)('a' + i) << '.' << scQuestion.getAnswers()[i] << ' ';
	}
	std::cout << std::endl;
}

unsigned Console::answerSingleChoiceQuestion(const SingleChoiceQuestion& scQuestion)
{
	String answer;
	std::cout << "Choose the letter of the right answer: ";
	answer = Console::readLine();

	if (answer.getLen() > 1 || answer < 'a' || answer > 'a' + scQuestion.getAnswers().getSize() - 1)
	{
		String message = "the answer should be a letter between 'a' and " + (char)('a' + scQuestion.getAnswers().getSize());
		message += "!";
		throw std::invalid_argument(message.c_str());
	}

	return answer[0] - 'a' + 1;
}

void Console::printMultipleChoiceQuestion(const MultipleChoiceQuestion& mcQuestion)
{
	std::cout << mcQuestion.getQuestion() << std::endl;
	for (size_t i = 0; i < mcQuestion.getAnswers().getSize(); i++)
	{
		std::cout << (char)('a' + i) << '.' << mcQuestion.getAnswers()[i] << ' ';
	}
	std::cout << std::endl;
}

Vector<unsigned> Console::answerMultipleChoiceQuestion(const MultipleChoiceQuestion& mcQuestion)
{
	String answers;
	std::cout << "Write the letters of the right answers separated by a space: ";
	answers = readLine();
	answers.makeLower();
	Vector<String> answersVec = answers.split(' ');
	for (size_t i = 0; i < answersVec.getSize(); i++)
	{
		std::cout << answersVec[i];
	}
	if (answersVec.getSize() > mcQuestion.getAnswers().getSize()
		|| answersVec.getSize() <= 1)
	{
		throw std::invalid_argument("There are missing or extra answers!");
	}

	Vector<unsigned> numAnswers = Vector<unsigned>();
	for (size_t i = 0; i < answersVec.getSize(); i++)
	{
		char maxAnswer = 'a' + mcQuestion.getAnswers().getSize() - 1;
		if (answersVec[i].getLen() != 1 || answersVec[i] < 'a' || answersVec[i] > maxAnswer)
			throw std::invalid_argument("You have given an answer which is either not a letter or is unavailable!");

		if (!numAnswers.contains(answersVec[i][0] - 'a' + 1))
			numAnswers.push_back(answersVec[i][0] - 'a' + 1);
	}

	return numAnswers;
}

void Console::printShortAnswerQuestion(const ShortAnswerQuestion& saQuestion)
{
	std::cout << saQuestion.getQuestion();
}

String Console::answerShortAnswerQuestion()
{
	String answer;
	std::cout << "Your short answer: ";
	answer = readLine();
	return std::move(answer.makeLower());
}

void Console::printMatchingPairsQuestion(const MatchingPairsQuestion& mpQuestion)
{
	size_t firstColSize = mpQuestion.getFirstCol().getSize();
	size_t secondColSize = mpQuestion.getSecondCol().getSize();
	size_t length = std::max(firstColSize, secondColSize);
	for (size_t i = 0; i < length; i++)
	{
		if (i < firstColSize)
			std::cout << i + 1 << ". " << mpQuestion.getFirstCol()[i];

		if (i < secondColSize)
			std::cout << '\t' << '\t' << (char)('a' + i) << ". " << mpQuestion.getSecondCol()[i] << std::endl;
	}
}

Vector<unsigned> Console::answerMatchingPairsQuestion(const MatchingPairsQuestion& mpQuestion)
{
	Vector<unsigned> answers = Vector<unsigned>();
	std::cout << "Choose the corresponding letter from the second column for each number from the first:" << std::endl;

	size_t max = mpQuestion.getSecondCol().getSize();
	char maxChar = 'a' + max;
	for (size_t i = 1; i <= mpQuestion.getFirstCol().getSize(); i++)
	{
		std::cout << i << '.';

		String c;
		c = Console::readLine();
		c.makeLower();

		if (c.getLen() > 1 || c < 'a' || c > maxChar)
		{
			throw std::invalid_argument("There is no such row in the second column!");
		}

		answers.push_back(c[0] - 'a' + 1);
	}

	return answers;
}
