#include "Question.h"
#pragma warning(disable:4996)
#include <iostream>

void Question::setQuestion(const String& question)
{
    if (question.getLen() == 0)
        throw std::invalid_argument("Question shouldn't be empty!");

    this->question = question;
}

void Question::setPoints(double points)
{
    if (points <= 0)
        throw std::invalid_argument("A question cannot be 0 points or less!");

    this->points = points;
}

Question::Question(const String& question, double points)
{
    setPoints(points);
    setQuestion(question);
}

const String& Question::getQuestion() const
{
    return this->question;
}

const double Question::getPoints() const
{
    return this->points;
}
