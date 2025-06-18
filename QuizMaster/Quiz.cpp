#include "Quiz.h"
#include "TrueOrFalseQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "ShortAnswerQuestion.h"
#include "MatchingPairsQuestion.h"
#include "System.h"
#include <cstdlib> 
#include <ctime>

void Quiz::setID(const String& ID)
{
	if (ID.getLen() == 0)
		throw std::invalid_argument("Quiz ID cannot be emtpy!");
	//if (file contains id)

	this->ID = ID;
}

void Quiz::setTitle(const String& title)
{
	if (title.getLen() == 0)
		throw std::invalid_argument("Quiz title cannot be empty!");

	this->title = title;
}

void Quiz::setQuestions(const Vector<Question*>& questions)
{
	if (questions.getSize() == 0)
		throw std::invalid_argument("There must be at least one question in the quiz!");

	this->questions = Vector<Question*>(questions.getCapacity());
	for (size_t i = 0; i < questions.getSize(); i++)
		this->questions.push_back(questions[i]->clone());
}

void Quiz::free()
{
	for (size_t i = 0; i < questions.getSize(); i++)
	{
		delete questions[i];
		questions[i] = nullptr;
	}
	ID = "";
	title = "";
	creatorUsername = "";
	timesPlayed = 0;
}

void Quiz::copyFrom(const Quiz& other)
{
	this->ID = other.ID;
	this->title = other.title;
	this->creatorUsername = other.creatorUsername;
	this->questions = Vector<Question*>(other.questions.getCapacity());
	for (size_t i = 0; i < other.questions.getSize(); i++)
	{
		this->questions.push_back(other.questions[i]->clone());
	}
	this->timesPlayed = other.timesPlayed;
	this->likes = other.likes;
}

void Quiz::moveFrom(Quiz&& other)
{
	this->ID = other.ID;
	this->title = other.title;
	this->creatorUsername = other.creatorUsername;
	this->questions = other.questions;
	this->timesPlayed = other.timesPlayed;
	this->likes = other.likes;

	for (size_t i = 0; i < other.questions.getSize(); i++)
	{
		other.questions[i] = nullptr;
	}
}

Quiz::Quiz()
{
	ID = "";
	title = "";
	creatorUsername = "";
	questions = Vector<Question*>();
	timesPlayed = 0;
	likes = Vector<String>();
}

Quiz::Quiz(const Quiz& other)
{
	copyFrom(other);
}

Quiz::Quiz(Quiz&& other) noexcept
{
	moveFrom(std::move(other));
}

Quiz& Quiz::operator=(const Quiz& other)
{
	if (&other != this)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Quiz& Quiz::operator=(Quiz&& other) noexcept
{
	if (&other != this)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Quiz::~Quiz()
{
	free();
}

Quiz::Quiz(std::istream& is)
{
	deserialize(is);
}

Quiz::Quiz(const String& ID, const String& title, const String& creatorUsername, const Vector<Question*>& questions)
{
	setID(ID);
	setTitle(title);
	this->creatorUsername = creatorUsername;
	setQuestions(questions);
	timesPlayed = 0;
}

unsigned Quiz::getTimesPlayed()
{
	return this->timesPlayed;
}

void Quiz::updateTimesPlayed()
{
	timesPlayed++;
}

const String& Quiz::getID() const
{
	return this->ID;
}

const String& Quiz::getTitle() const
{
	return this->title;
}

const String& Quiz::getCreator() const
{
	return this->creatorUsername;
}

const Vector<const Question*>& Quiz::getQuestions() const
{
	Vector<const Question*> constQuestions = Vector<const Question*>(this->questions.getCapacity());
	for (size_t i = 0; i < this->questions.getSize(); i++)
	{
		constQuestions.push_back(questions[i]->clone());
	}
	return constQuestions;
}

const unsigned Quiz::getTimesPlayed() const
{
	return this->timesPlayed;
}

const Vector<String>& Quiz::getLikes() const
{
	return this->getLikes();
}

void Quiz::addLike(const String& username)
{
	if (likes.contains(username))
		throw std::invalid_argument("Quiz already liked!");

	likes.push_back(username);
}

void Quiz::removeLike(const String& username)
{
	if (!likes.contains(username))
		throw std::invalid_argument("Quiz not liked!");

	likes.remove(username);
}

void Quiz::playQuiz()
{
	double accPoints = 0;
	double maxPoints = 0;
	for (size_t i = 0; i < questions.getSize(); i++)
	{
		accPoints += questions[i]->answer();
		maxPoints += questions[i]->getPoints();
	}
	Console::printQuizResult(accPoints, maxPoints);
	timesPlayed++;
}

void Quiz::playQuizShuffled()
{
	size_t size = questions.getSize();

	std::srand(static_cast<unsigned>(std::time(nullptr)));

	Vector<size_t> numbers(size);
	for (size_t i = 0; i < size; ++i)
		numbers.push_back(i);

	for (size_t i = size - 1; i > 0; --i)
	{
		size_t j = rand() % (i + 1);
		std::swap(numbers[i], numbers[j]);
	}

	double accPoints = 0, maxPoints = 0;
	for (size_t i = 0; i < size; i++)
	{
		accPoints += questions[numbers[i]]->answer();
		maxPoints += questions[numbers[i]]->getPoints();
	}

	Console::printQuizResult(accPoints, maxPoints);
}

void Quiz::playQuizTest()
{
	for (size_t i = 0; i < questions.getSize(); i++)
	{
		questions[i]->answer();
		Console::printRightAnswers(questions[i]);
	}
}

void Quiz::playQuizTestShuffled()
{
	size_t size = questions.getSize();

	std::srand(static_cast<unsigned>(std::time(nullptr)));

	Vector<size_t> numbers(size);
	for (size_t i = 0; i < size; ++i)
		numbers.push_back(i);

	for (size_t i = size - 1; i > 0; --i)
	{
		size_t j = rand() % (i + 1);
		std::swap(numbers[i], numbers[j]);
	}

	for (size_t i = 0; i < size; i++)
	{
		questions[numbers[i]]->answer();
		Console::printRightAnswers(questions[numbers[i]]);
	}
}

String Quiz::generateID()
{
	size_t length = 5;
	const char charset[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	const size_t charsetSize = sizeof(charset) - 1;

	String result;

	static bool seeded = false;
	if (!seeded) {
		std::srand(static_cast<unsigned>(std::time(nullptr)));
		seeded = true;
	}

	for (size_t i = 0; i < length; ++i) {
		char randomChar = charset[rand() % charsetSize];
		result += randomChar;
	}

	for (size_t i = 0; i < System::getInstance().getQuizzes().getSize(); i++)
	{
		if (System::getInstance().getQuizzes()[i].ID == result)
			return generateID();
	}
	for (size_t i = 0; i < System::getInstance().getPending().getSize(); i++)
	{
		if (System::getInstance().getPending()[i].ID == result)
			return generateID();
	}
	return result;
}

void Quiz::serialize(std::ostream& os) const
{
	ID.serialize(os);
	title.serialize(os);
	creatorUsername.serialize(os);
	size_t size = this->questions.getSize();
	os.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		this->questions[i]->serialize(os);
	}
	os.write((const char*)&timesPlayed, sizeof(timesPlayed));
	size = this->likes.getSize();
	os.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		this->likes[i].serialize(os);
	}
}

void Quiz::deserialize(std::istream& is)
{
	ID.deserialize(is);
	title.deserialize(is);
	creatorUsername.deserialize(is);
	size_t size = 0;
	is.read((char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		int typeInt = 0;
		is.read((char*)&typeInt, sizeof(typeInt));
		QuestionType type = (QuestionType)typeInt;

		Question* current = nullptr;
		switch (type) {
		case QuestionType::TrueOrFalse:
			current = new TrueOrFalseQuestion(is);
			break;
		case QuestionType::MatchingPairs:
			current = new MatchingPairsQuestion(is);
			break;
		case QuestionType::MultipleChoice:
			current = new MultipleChoiceQuestion(is);
			break;
		case QuestionType::ShortAnswer:
			current = new ShortAnswerQuestion(is);
			break;
		case QuestionType::SingleChoice:
			current = new SingleChoiceQuestion(is);
			break;
		default: throw std::invalid_argument("Invalid question type!");
		}
		this->questions.push_back(current);
	}

	is.read((char*)&this->timesPlayed, sizeof(this->timesPlayed));

	size = 0;
	is.read((char*)&size, sizeof(size));
	this->likes = Vector<String>(size);
	for (size_t i = 0; i < size; i++)
	{
		String like;
		like.deserialize(is);
		this->likes.push_back(like);
	}
}

void operator<<(std::ostream& os, const Quiz& quiz)
{
	os << quiz.title << " " << quiz.ID << "\nby " << quiz.creatorUsername
		<< " " << quiz.timesPlayed << " times played " << quiz.likes.getSize() << " likes";
}
