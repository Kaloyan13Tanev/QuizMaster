#include "Question.h"
#pragma warning(disable:4996)
#include <iostream>

void Question::setQuestion(char* question)
{
    if (question == nullptr)
        throw std::invalid_argument("Question shouldn't be empty!");

    this->question = new char[strlen(question) + 1] {};
    strcpy(this->question, question);
}

void Question::setPoints(unsigned points)
{
    if (points == 0)
        throw std::invalid_argument("A question cannot be 0 points!");

    this->points = points;
}

void Question::copyFrom(const Question& other)
{
    this->question = new char[strlen(other.question) + 1] {};
    strcpy(this->question, other.question);
    this->points = other.points;
}

void Question::moveFrom(Question&& other) noexcept
{
    this->question = other.question;
    this->points = other.points;

    other.question = nullptr;
}

void Question::free()
{
    delete[] this->question;
    this->question = nullptr;
    this->points = 0;
}

Question::Question(const Question& other)
{
    copyFrom(other);
}

Question::Question(Question&& other) noexcept
{
    moveFrom(std::move(other));
}

Question& Question::operator=(const Question& other)
{
    if (&other != this)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

Question& Question::operator=(Question&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Question::~Question()
{
    free();
}

Question::Question(char* question, unsigned points)
{
    setPoints(points);
    setQuestion(question);
}

const char* Question::getQuestion() const
{
    return this->question;
}

const unsigned Question::getPoints() const
{
    return this->points;
}
