#include "Question.h"
#pragma warning(disable:4996)
#include <iostream>

void Question::setQuestion(const String& question)
{
    if (question.getLen() == 0)
        throw std::invalid_argument("Question shouldn't be empty!");

    this->question = question;
}

void Question::setPoints(unsigned points)
{
    if (points == 0)
        throw std::invalid_argument("A question cannot be 0 points!");

    this->points = points;
}

Question::Question(const String& question, unsigned points)
{
    setPoints(points);
    setQuestion(question);
}

const String& Question::getQuestion() const
{
    return this->question;
}

const unsigned Question::getPoints() const
{
    return this->points;
}
