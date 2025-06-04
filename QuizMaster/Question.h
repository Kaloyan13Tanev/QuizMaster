#pragma once

class Question
{
private:
	char* question;
	unsigned points;

	void setQuestion(char* question);
	void setPoints(unsigned points);

	void copyFrom(const Question& other);
	void moveFrom(Question&& other);
	void free();

public:
	Question() = delete;
	Question(const Question& other);
	Question(Question&& other) noexcept;
	Question& operator=(const Question& other);
	Question& operator=(Question && other) noexcept;
	virtual ~Question() = 0;

	virtual Question* clone() const = 0;

	Question(char* question, unsigned points);

	const char* getQuestion() const;
	const unsigned getPoints() const; 

	virtual unsigned answer() = 0;
};
