#pragma once
#include "User.h"
#include "Administrator.h"
#include "Player.h"
#include "Quiz.h"

class System
{
private:
	User* loggedUser;
	Vector<Quiz> quizzes;
	Vector<User*> users;
	Vector<Quiz> pending;
	System();

	void free();
	void copyFrom(const System& other);
	void moveFrom(System&& other);

public:
	System(const System& other);
	System(System&& other);
	System& operator=(const System& other);
	System& operator=(System&& other);
	~System();
	
	static System& getInstance();
	const Vector<Quiz>& getQuizzes() const;
	const Vector<Quiz>& getQuizzesByCreator(const String& creatorUsername) const;
	const Vector<Quiz>& getPending() const;

	void fillQuizzes();
	void fillUsers();
	void fillPending();
	System(const System&) = delete;
	void serializeQuizzes() const;
	void serializeUsers() const;

	const User* findUser(const String& username) const;
	size_t indexOf(const String& quizID) const;
	size_t indexOfPending(const String& quizID) const;

	void login(const String& username, const String& password);
	void logout();
	void quit();
	void signup(const String& firstName, const String& lastName, const String& username, const String& password1, const String& password2);
	void likeQuiz(const String& quizID);
	void unlikeQuiz(const String& quizID);
	void addToFavs(const String& quizID);
	void removeFromFavs(const String& quizID);
	void startQuiz(const String& quizID, bool isTest, bool isShuffled);
	void approveQuiz(const String& quizID);
	void rejectQuiz(const String& quizID);
	void removeQuiz(const String& quizID);
	void banPlayer(const String& username);

	const User* getLoggedUser() const;
};
