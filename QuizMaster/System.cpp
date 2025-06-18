#include "System.h"
#include "QuestionFactory.h"
#include <fstream>

System& System::getInstance()
{
	static System instance;
	return instance;
}

const Vector<Quiz>& System::getQuizzes() const
{
	return quizzes;
}

Vector<Quiz> System::getQuizzesByCreator(const String& creatorUsername) const
{
	Vector<Quiz> quizzesByCreator;
	for (size_t i = 0; i < quizzes.getSize(); i++)
	{
		if (quizzes[i].getCreator() == creatorUsername)
			quizzesByCreator.push_back(quizzes[i]);
	}

	return quizzesByCreator;
}

const Vector<Quiz>& System::getPending() const
{
	return pending;
}

void System::fillQuizzes()
{
	std::ifstream quizzes("Quizzes.bin", std::ios::binary);

	/*if (!quizzes.is_open())
		throw std::*/

	size_t size = 0;
	quizzes.read((char*)&size, sizeof(size));
	this->quizzes = Vector<Quiz>(size);
	
	for (size_t i = 0; i < size; i++)
	{
		Quiz quiz(quizzes);
		this->quizzes.push_back(quiz);
	}
	quizzes.close();
}

void System::fillUsers()
{
	std::ifstream users("Users.bin", std::ios::binary);

	/*if (!users.is_open())
		throw std::*/

	size_t size = 0;
	users.read((char*)&size, sizeof(size));
	this->users = Vector<User*>(size);
	for (size_t i = 0; i < size; i++)
	{
		int roleInt = 0;
		users.read((char*)&roleInt, sizeof(roleInt));
		if ((Role)roleInt == Role::Player)
		{
			Player player;
			player.deserialize(users);

			this->users.push_back(player.clone());
		}
		else
		{
			Admin admin;
			admin.deserialize(users);

			this->users.push_back(admin.clone());
		}
	}
	users.close();
}

void System::fillPending()
{
	std::ifstream pending("Pending.bin", std::ios::binary);

	/*if (!pending.is_open())
		throw std::*/

	size_t size = 0;
	pending.read((char*)&size, sizeof(size));
	this->pending = Vector<Quiz>(size);
	for (size_t i = 0; i < size; i++)
	{
		this->pending.push_back(Quiz(pending));
	}
	pending.close();
}

void System::login(const String& username, const String& password)
{
	size_t size = users.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (users[i]->getUsername() == username &&
			users[i]->correctPassword(password))
		{
			this->loggedUser = users[i]->clone();
		}
	}

	if (loggedUser == nullptr)
		throw std::invalid_argument("Username or password is incorrect!");
}

void System::logout()
{
	if (loggedUser == nullptr)
		throw std::invalid_argument("No profile logged in!");

	serializeQuizzes();
	serializeUsers();
	serializePending();
	loggedUser = nullptr;
}

void System::quit()
{
	if (loggedUser != nullptr)
	{
		logout();
	}
}

void System::signup(const String& firstName, const String& lastName, const String& username, const String& password1, const String& password2)
{
	if (loggedUser != nullptr)
		throw std::invalid_argument("Profile already logged in!\n");

	if (password1 != password2)
		throw std::invalid_argument("The password is not typed correctly!\n");

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getUsername() == username)
			throw std::invalid_argument("Username already taken!\n");
	}

	Player player = Player(firstName, lastName, username, password1);
	users.push_back(player.clone());
	loggedUser = player.clone();
}

void System::likeQuiz(const String& quizID)
{
	if (!loggedUser)
		throw std::logic_error("No user is logged in!");
	else if (loggedUser->getRole() == Role::Admin)
		throw std::logic_error("Admins cannot like quizzes!");

	for (size_t i = 0; i < quizzes.getSize(); i++)
	{
		if (quizzes[i].getID() != quizID)
		{
			continue;
		}

		quizzes[i].addLike(loggedUser->getUsername());
		return;
	}

	throw std::invalid_argument("Quiz not found!");
}

void System::unlikeQuiz(const String& quizID)
{
	if (!loggedUser)
		throw std::logic_error("No user is logged in!");
	else if (loggedUser->getRole() == Role::Admin)
		throw std::logic_error("Admins cannot like quizzes!");

	for (size_t i = 0; i < quizzes.getSize(); i++)
	{
		if (quizzes[i].getID() != quizID)
			continue;

		quizzes[i].removeLike(loggedUser->getUsername());
		return;
	}

	throw std::invalid_argument("Quiz not found!");
}

void System::addToFavs(const String& quizID)
{
	if (!loggedUser)
		throw std::logic_error("No user is logged in!");

	loggedUser->addToFavs(quizID);
}

void System::removeFromFavs(const String& quizID)
{
	if (!loggedUser)
		throw std::logic_error("No user is logged in!");

	loggedUser->removeFromFavs(quizID);
}

void System::startQuiz(const String& quizID, bool isTest, bool isShuffled)
{
	if (!loggedUser)
		throw std::logic_error("No user is logged in!");

	size_t i = indexOf(quizID);
	if (isTest)
	{
		if (isShuffled)
			quizzes[i].playQuizTestShuffled();
		else 
			quizzes[i].playQuizTest();
	}
	else
	{
		if (isShuffled)
			quizzes[i].playQuizShuffled();
		else
			quizzes[i].playQuiz();
	}
}

void System::approveQuiz(const String& quizID)
{
	if (!loggedUser || loggedUser->getRole() == Role::Player)
		throw std::logic_error("Cannot approve quiz!");

	size_t i = indexOfPending(quizID);
	quizzes.push_back(pending[i]);
	pending.removeAt(i);
}

void System::rejectQuiz(const String& quizID)
{
	if (!loggedUser || loggedUser->getRole() == Role::Player)
		throw std::logic_error("Cannot reject quiz!");

	pending.removeAt(indexOfPending(quizID));
}

void System::removeQuiz(const String& quizID)
{
	if (!loggedUser || loggedUser->getRole() == Role::Player)
		throw std::logic_error("Cannot remove quiz!");

	quizzes.removeAt(indexOf(quizID));
}

void System::banPlayer(const String& username)
{
	if (!loggedUser || loggedUser->getRole() == Role::Player)
		throw std::logic_error("Cannot ban player!");

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getUsername() == username)
		{
			if (users[i]->getRole() == Role::Admin)
				throw std::invalid_argument("Cannot ban administrator!");

			users.remove(users[i]);
			return;
		}
	}
	throw std::invalid_argument("User not found!");
}

void System::createQuiz()
{
	if (!loggedUser || loggedUser->getRole() == Role::Admin)
		throw std::logic_error("Cannot create quiz!");

	String title = Console::readQuizTitle();
	size_t size = Console::readQuizNumberOfQuestions();
	Vector<Question*> questions;
	for (size_t i = 0; i < size; i++)
	{
		questions.push_back(QuestionFactory::createQuestion());
	}
	String ID = Quiz::generateID();
	pending.push_back(Quiz(ID, title, System::loggedUser->getUsername(), questions));
}

const User* System::getLoggedUser() const
{
	return this->loggedUser;
}

System::System()
{
	loggedUser = nullptr;
	fillQuizzes();
	fillPending();
	fillUsers();
}

void System::free()
{
	loggedUser = nullptr;
	for (size_t i = 0; i < users.getSize(); i++)
	{
		delete users[i];
		users[i] = nullptr;
	}
}

void System::serializeQuizzes() const
{
	std::ofstream saveQuizzes("Quizzes.bin", std::ios::binary);
	size_t size = quizzes.getSize();
	saveQuizzes.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		quizzes[i].serialize(saveQuizzes);
	}
	//saveQuizzes.close();
}

void System::serializeUsers() const
{
	std::ofstream saveUsers("Users.bin", std::ios::binary);
	size_t size = users.getSize();
	saveUsers.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		users[i]->serialize(saveUsers);
	}
	//saveUsers.close();
}

void System::serializePending() const
{
	std::ofstream savePending("Pending.bin", std::ios::binary);
	size_t size = pending.getSize();
	savePending.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		pending[i].serialize(savePending);
	}
	//savePending.close();
}

const User* System::findUser(const String& username) const
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getUsername() == username)
			return users[i];
	}

	throw std::invalid_argument("User not found!");
}

size_t System::indexOf(const String& quizID) const
{
	for (size_t i = 0; i < quizzes.getSize(); i++)
	{
		if (quizzes[i].getID() == quizID)
			return i;
	}

	throw std::invalid_argument("Quiz not found!");
}

size_t System::indexOfPending(const String& quizID) const
{
	for (size_t i = 0; i < pending.getSize(); i++)
	{
		if (pending[i].getID() == quizID)
			return i;
	}

	throw std::invalid_argument("Quiz not found in pending!");
}

System::~System()
{
	free();
}