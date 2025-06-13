#include "Quiz.h"
#include "TrueOrFalseQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "ShortAnswerQuestion.h"
#include "MatchingPairsQuestion.h"
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

void Quiz::setQuestions(const Vector<Question*> questions)
{
	if (questions.getSize() == 0)
		throw std::invalid_argument("There must be at least one question in the quiz!");

	this->questions = Vector<Question*>(questions.getCapacity());
	for (size_t i = 0; i < questions.getSize(); i++)
		this->questions.push_back(questions[i]->clone());
}

Quiz::Quiz(std::istream& is)
{
	deserialize(is);
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
}

void Quiz::playQuizShuffled()
{
	size_t size = questions.getSize();

	std::srand(static_cast<unsigned>(std::time(nullptr)));

	Vector<size_t> numbers(size);
	for (size_t i = 0; i < size; ++i)
		numbers[i] = i;

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
		numbers[i] = i;

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

void Quiz::serialize(std::ostream& os) const
{
	ID.serialize(os);
	title.serialize(os);
	creatorUsername.serialize(os);
	size_t size = this->questions.getSize();
	os.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		this->questions[i]->clone()->serialize(os);
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
	size_t size;
	is.read((char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		QuestionType questionType;
		is.read((char*)&questionType, sizeof(size));

		if (questionType == QuestionType::TrueOrFalse)
		{
			TrueOrFalseQuestion tf = TrueOrFalseQuestion(is);
			this->questions.push_back(tf.clone());
		}
		else if (questionType == QuestionType::SingleChoice)
		{
			SingleChoiceQuestion sc = SingleChoiceQuestion(is);
			this->questions.push_back(sc.clone());
		}
		else if (questionType == QuestionType::MultipleChoice)
		{
			MultipleChoiceQuestion mc = MultipleChoiceQuestion(is);
			this->questions.push_back(mc.clone());
		}
		else if (questionType == QuestionType::ShortAnswer)
		{
			ShortAnswerQuestion sa = ShortAnswerQuestion(is);
			this->questions.push_back(sa.clone());
		}
		else if (questionType == QuestionType::MatchingPairs)
		{
			MatchingPairsQuestion mp = MatchingPairsQuestion(is);
			this->questions.push_back(mp.clone());
		}
	}

	is.read((char*)&this->timesPlayed, sizeof(this->timesPlayed));

	is.read((char*)&size, sizeof(size));
	this->likes = Vector<String>(size);
	for (size_t i = 0; i < size; i++)
	{
		this->likes[i].deserialize(is);
	}
}

void operator<<(std::ostream& os, const Quiz& quiz)
{
	os << quiz.title << " " << quiz.ID << "\nby " << quiz.creatorUsername
		<< " " << quiz.timesPlayed << " times played " << quiz.likes.getSize() << " likes";
}
