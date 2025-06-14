#include "QuestionFactory.h"
#include "Console.h"

TrueOrFalseQuestion* QuestionFactory::createTrueOrFalseQuestion()
{
	std::cout << "Question: ";
	String question;
	question = Console::readLine();

	std::cout << "Answer (true/false): ";
	String answer;
	answer = Console::readLine();
	answer.makeLower();

	if (answer != 'true' && answer != "false")
		throw std::invalid_argument("Answer should be 'true' or 'false'!");

	std::cout << "Points: ";
	String pointsString;
	pointsString = Console::readLine();
	unsigned points = pointsString.toUnsigned();

	if (answer == "true")
	{
		TrueOrFalseQuestion tf(question, points, true);
		return &tf;
	}
	else
	{
		TrueOrFalseQuestion tf(question, points, false);
		return &tf;
	}
}

SingleChoiceQuestion* QuestionFactory::createSingleChoiceQuestion()
{
	std::cout << "Question: ";
	String question = Console::readLine();
	
	std::cout << "Answers: ";
	Vector<String> answers = Console::readLine().split(' ');

	std::cout << "Right answer number: ";
	unsigned rightAnswer = Console::readLine().toUnsigned();

	std::cout << "Points: ";
	unsigned points = Console::readLine().toUnsigned();

	SingleChoiceQuestion sc(question, points, answers, rightAnswer);
	return &sc;
}

MultipleChoiceQuestion* QuestionFactory::createMultipleChoiceQuestion()
{
	std::cout << "Question: ";
	String question = Console::readLine();

	std::cout << "Answers: ";
	Vector<String> answers = Console::readLine().split(' ');

	std::cout << "Right answers numbers: ";
	Vector<String> rightAnswersStr = Console::readLine().split(' ');
	Vector<unsigned> rightAnswers = Vector<unsigned>(rightAnswersStr.getSize());
	for (size_t i = 0; i < rightAnswersStr.getSize(); i++)
	{
		rightAnswers.push_back(rightAnswersStr[i].toUnsigned());
	}

	std::cout << "Points: ";
	unsigned points = Console::readLine().toUnsigned();

	MultipleChoiceQuestion mc(question, points, answers, rightAnswers);
	return &mc;
}

MatchingPairsQuestion* QuestionFactory::createMatchingPairsQuestion()
{
	std::cout << "Question: ";
	String question = Console::readLine();

	std::cout << "First column: ";
	Vector<String> firstCol = Console::readLine().split(' ');
	
	std::cout << "Second column: ";
	Vector<String> secondCol = Console::readLine().split(' ');

	std::cout << "Connections (<number>.<character>): ";
	Vector<unsigned> rightAnswers;
	for (size_t i = 0; i < firstCol.getSize(); i++)
	{
		std::cout << i + 1 << '.';
		String letter = Console::readLine();

		if (letter.getLen() != 1)
			throw std::invalid_argument("Input should be a character!");

		rightAnswers.push_back(letter[0] - 'a' + 1);
	}

	std::cout << "Points: ";
	unsigned points = Console::readLine().toUnsigned();

	MatchingPairsQuestion mp(question, points, firstCol, secondCol, rightAnswers);
	return &mp;
}

ShortAnswerQuestion* QuestionFactory::createShortAnswerQuestion()
{
	std::cout << "Question: ";
	String question = Console::readLine();

	std::cout << "Answer: ";
	String answer = Console::readLine();

	std::cout << "Points: ";
	unsigned points = Console::readLine().toUnsigned();

	ShortAnswerQuestion sa(question, points, answer);
	return &sa;
}

Question* QuestionFactory::createQuestion()
{
	std::cout << "Question type (TF, SC, MC, SA, MP): ";
	String type = Console::readLine().makeLower();

	if (type == "tf")
		return createTrueOrFalseQuestion();
	else if (type == "sc")
		return createSingleChoiceQuestion();
	else if (type == "mc")
		return createMultipleChoiceQuestion();
	else if (type == "mp")
		return createMatchingPairsQuestion();
	else if (type == "sa")
		return createShortAnswerQuestion();
	else
		throw std::invalid_argument("No such type of question!");
}
