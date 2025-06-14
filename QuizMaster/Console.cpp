#include "Console.h"
#include "StringHelpers.h"
#include "TrueOrFalseQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "ShortAnswerQuestion.h"
#include "MatchingPairsQuestion.h"
#include "Role.h"
#include "System.h"
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

;void Console::printCommandsNoLogin()
{
	std::cout << "\nAvailable commands:\n";
	std::cout << "- logout\n";
	std::cout << "- quit\n";
	std::cout << "- signup <first-name> <last-name> <username> <password1> <password2>\n\n";
}

void Console::printCommandsAdmin()
{
	std::cout << "\nAvailable commands:\n";
	std::cout << "- logout\n";
	std::cout << "- quit\n";
	std::cout << "- pending\n";
	std::cout << "- approve-quiz <quiz-id>\n";
	std::cout << "- reject-quiz <quiz-id> <reason>\n";
	std::cout << "- remove-quiz <quiz-id> <reason>\n";
	std::cout << "- view-reports\n";
	std::cout << "- ban <username>\n\n";
}

void Console::printCommandsPlayer()
{
	std::cout << "\nAvailable commands:\n";
	std::cout << "- login <username> <password>\n";
	std::cout << "- quit\n";
	std::cout << "- view-profile\n";
	std::cout << "- view-challenges\n";
	std::cout << "- view-finished-challenges\n";
	std::cout << "- view <username>\n";
	std::cout << "- messages\n";
	std::cout << "- create-quiz\n";
	std::cout << "- quizzes\n";
	std::cout << "- quizzes <username>\n";
	std::cout << "- like-quiz <quiz-id>\n";
	std::cout << "- unlike-quiz <quiz-id>\n";
	std::cout << "- add-to-favs <quiz-id>\n";
	std::cout << "- remove-from-favs <quiz-id>\n";
	std::cout << "- start-quiz <quiz-id> test|normal (shuffle)\n";
	std::cout << "- save-quiz <quiz-id> <filepath>\n";
	std::cout << "- report-quiz <quiz-id> <reason>\n\n";
}

void Console::Start()
{
	std::cout << "Welcome to QuizMaster!" << std::endl;
	std::cout << "Type \"help\" for commands." << std::endl;
	bool cont = true;

	while (cont)
	{
		std::cout << "> ";
		Vector<String> input = readLine().split(' ');
		if (input.isEmpty())
			throw std::invalid_argument("Command shouldn't be empty!");

		if (input[0] == "login")
		{
			if (input.getSize() != 3)
				throw std::invalid_argument("Error: Unknown command!\nUsage: login <username> <password>");

			System::getInstance().login(input[1], input[2]);
		}
		else if (input[0] == "help")
		{
			if (input.getSize() != 1)
				throw std::invalid_argument("Error: Unknown command!\nUsage: help");

			if (System::getInstance().getLoggedUser() == nullptr)
				printCommandsNoLogin();
			else if (System::getInstance().getLoggedUser()->getRole() == Role::Admin)
				printCommandsAdmin();
			else
				printCommandsPlayer();
		}
		else if (input[0] == "logout")
		{
			if (input.getSize() != 1)
				throw std::invalid_argument("Error: Unknown command!\nUsage: logout");

			System::getInstance().logout();
		}
		else if (input[0] == "quit")
		{
			if (input.getSize() != 1)
				throw std::invalid_argument("Error: Unknown command!\nUsage: quit");

			System::getInstance().quit();
			cont = false;
		}
		else if (input[0] == "signup")
		{
			if (input.getSize() != 6)
				throw std::invalid_argument("Error: Unknown command!\nUsage: signup <first-name> <last-name> <username> <password1> <password2>");

			System::getInstance().signup(input[1], input[2], input[3], input[4], input[5]);
		}
		else if (input[0] == "view-profile")
		{
			if (input.getSize() != 1)
				throw std::invalid_argument("Error: Unknown command!\nUsage: view-profile");

			std::cout << System::getInstance().getLoggedUser();
		}
		else if (input[0] == "view-challenges")
		{
			if (input.getSize() != 1)
				throw std::invalid_argument("Error: Unknown command!\nUsage: view-challenges");
			//add challenges to player
		}
		else if (input[0] == "view-finished-challenges")
		{
			if (input.getSize() != 1)
				throw std::invalid_argument("Error: Unknown command!\nUsage: view-finished-challenges");

			//add challenges to player
		}
		else if (input[0] == "view")
		{
			if (input.getSize() != 2)
				throw std::invalid_argument("Error: Unknown command!\nUsage: view <username>");

			std::cout << System::getInstance().findUser(input[1]);
		}
		else if (input[0] == "messages")
		{
			if (input.getSize() != 1)
				throw std::invalid_argument("Error: Unknown command!\nUsage: messages");

			//make messages for player Vector<String> 
		}
		else if (input[0] == "create-quiz")
		{
			if (input.getSize() != 1)
				throw std::invalid_argument("Error: Unknown command!\nUsage: create-quiz");

			//createQuiz();
		}
		else if (input[0] == "quizzes")
		{
			if (input.getSize() == 1)
			{
				for (size_t i = 0; i < System::getInstance().getQuizzes().getSize(); i++)
				{
					std::cout << System::getInstance().getQuizzes()[i];
				}
			}
			else if (input.getSize() == 2)
			{
				Vector<Quiz> quizzesByUser = System::getInstance().getQuizzesByCreator(input[1]);

				if (quizzesByUser.getSize() == 0)
					std::cout << "This user has not created any quizzes!";
				else
				{
					for (size_t i = 0; i < quizzesByUser.getSize(); i++)
					{
						std::cout << quizzesByUser[i];
					}
				}
			}
			else
				throw std::invalid_argument("Error: Unknown command!\nUsage: quizzes | quizzes <username>");
		}
		else if (input[0] == "like-quiz")
		{
			if (input.getSize() != 2)
				throw std::invalid_argument("Error: Unknown command!\nUsage: like-quiz <quiz-id>");

			System::getInstance().likeQuiz(input[1]);
		}
		else if (input[0] == "unlike-quiz")
		{
			if (input.getSize() != 2)
				throw std::invalid_argument("Error: Unknown command!\nUsage: unlike-quiz <quiz-id>");

			System::getInstance().unlikeQuiz(input[1]);
		}
		else if (input[0] == "add-to-favs")
		{
			if (input.getSize() != 2)
				throw std::invalid_argument("Error: Unknown command!\nUsage: add-to-favs <quiz-id>");

			System::getInstance().addToFavs(input[1]);
		}
		else if (input[0] == "remove-from-favs")
		{
			if (input.getSize() != 2)
				throw std::invalid_argument("Error: Unknown command!\nUsage: remove-from-favs <quiz-id>");

			System::getInstance().removeFromFavs(input[1]);
		}
		else if (input[0] == "start-quiz")
		{
			bool isValid = input.getSize() == 3 || input.getSize() == 4;
			if (isValid)
				isValid = (input[2] == "test" || input[2] == "normal");
			if (input.getSize() == 4)
				isValid = (input[3] == "shuffle");

			if (!isValid)
				throw std::invalid_argument("Error: Unknown command!\nUsage: start-quiz <quiz-id> test|normal (shuffle)");

			if (input[2] == "normal")
			{
				if (input.getSize() == 3)
					System::getInstance().startQuiz(input[1], false, false);
				else
					System::getInstance().startQuiz(input[1], false, true);
			}
			else
			{
				if (input.getSize() == 3)
					System::getInstance().startQuiz(input[1], true, false);
				else
					System::getInstance().startQuiz(input[1], true, true);
			}
		}
		else if (input[0] == "report-quiz")
		{
			if (input.getSize() != 3)
				throw std::invalid_argument("Error: Unknown command!\nUsage: report-quiz <quiz-id> <reason>");

			//reportQuiz();
		}
		else if (input[0] == "pending")
		{
			if (input.getSize() != 1)
				throw std::invalid_argument("Error: Unknown command!\nUsage: pending");

			if (!System::getInstance().getLoggedUser() || System::getInstance().getLoggedUser()->getRole() == Role::Player)
				throw std::logic_error("Can't access pending quizzes!");

			for (size_t i = 0; i < System::getInstance().getPending().getSize(); i++)
			{
				std::cout << System::getInstance().getPending()[i];
			}
		}
		else if (input[0] == "approve-quiz")
		{
			if (input.getSize() != 2)
				throw std::invalid_argument("Error: Unknown command!\nUsage: approve-quiz <quiz-id>");

			System::getInstance().approveQuiz(input[1]);
		}
		else if (input[0] == "reject-quiz")
		{
			if (input.getSize() != 3)
				throw std::invalid_argument("Error: Unknown command!\nUsage: reject-quiz <quiz-id> <reason>");

			System::getInstance().rejectQuiz(input[1]);
		}
		else if (input[0] == "view-reports")
		{
			if (input.getSize() != 1)
				throw std::invalid_argument("Error: Unknown command!\nUsage: view-reports");

			//viewReports();
		}
		else if (input[0] == "remove-quiz")
		{
			if (input.getSize() != 3)
				throw std::invalid_argument("Error: Unknown command!\nUsage: remove-quiz <quiz-id> <reason>");

			System::getInstance().removeQuiz(input[1]);
		}
		else if (input[0] == "ban")
		{
			if (input.getSize() != 2)
				throw std::invalid_argument("Error: Unknown command!\nUsage: ban <username>");

			System::getInstance().banPlayer(input[1]);
		}
	}
}

void Console::printTrueFalseQuestion(const TrueOrFalseQuestion& tfQuestion)
{
	std::cout << tfQuestion.getQuestion() << std::endl;
}

bool Console::answerTrueFalseQuestion()
{
	String givenA;
	std::cout << "Answer with 'T' or 'F': ";
	givenA = Console::readLine();
	if (givenA != "T" && givenA != "F")
		throw std::invalid_argument("You should answer with 'T' or 'F'!");

	if (givenA == "T")
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

	char maxChar = 'a' + scQuestion.getAnswers().getSize() - 1;
	if (answer.getLen() > 1 || answer < 'a' || answer > maxChar)
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

void Console::printQuizResult(double accPoints, double maxPoints)
{
	std::cout << "Result: " << accPoints << '\\' << maxPoints << "points";
}

void Console::printRightAnswers(const Question* question)
{
	std::cout << question->rightAnswerToString();
}

const String& Console::readQuizTitle()
{
	std::cout << "Quiz title: ";
	return Console::readLine();
}

const size_t Console::readQuizNumberOfQuestions()
{
	std::cout << "Number of questions: ";
	return Console::readLine().toUnsigned();
}
