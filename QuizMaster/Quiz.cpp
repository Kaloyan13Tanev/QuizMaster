#include "Quiz.h"

void Quiz::free()
{
	for (size_t i = 0; i < questions.getSize(); i++)
	{
		delete questions[i];
		questions[i] = nullptr;
	}
	this->ID = "";
	this->title = "";
	this->timesPlayed = 0;
	this->questions = 0;
	this->likes = 0;
}

void Quiz::copyFrom(const Quiz& other)
{
	this->ID = other.ID;
	this->title = other.title;
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
	this->timesPlayed = other.timesPlayed;
	this->likes = other.likes;
	this->questions = other.questions;

	for (size_t i = 0; i < other.questions.getSize(); i++)
		other.questions[i] = nullptr;
}

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

void Quiz::setQuestions(const Vector<Question*> questions)
{
	if (questions.getSize() == 0)
		throw std::invalid_argument("There must be at least one question in the quiz!");

	this->questions = Vector<Question*>(questions.getCapacity());
	for (size_t i = 0; i < questions.getSize(); i++)
		this->questions.push_back(questions[i]->clone());
}

Quiz::Quiz(const Quiz& other)
{
	copyFrom(other);
}

Quiz::Quiz(Quiz&& other)
{
	moveFrom(std::move(other));
}

Quiz& Quiz::operator=(const Quiz& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Quiz& Quiz::operator=(Quiz&& other)
{
	if (this != &other)
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

Quiz::Quiz(const String& ID, const String& title, const String& creatorUsername, const Vector<Question*> question)
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

const Vector<Player>& Quiz::getLikes() const
{
	return this->getLikes();
}
