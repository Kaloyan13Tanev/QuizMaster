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

	System(System&& other) = delete;
	System& operator=(const System& other) = delete;
	System& operator=(System&& other) = delete;
	System(const System&) = delete;

	void free();

public:
	~System();
	
	static System& getInstance();
	const Vector<Quiz>& getQuizzes() const;
	Vector<Quiz> getQuizzesByCreator(const String& creatorUsername) const;
	const Vector<Quiz>& getPending() const;

	void fillQuizzes();
	void fillUsers();
	void fillPending();
	void serializeQuizzes() const;
	void serializeUsers() const;
	void serializePending() const;

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
	void createQuiz();

	const User* getLoggedUser() const;
};
