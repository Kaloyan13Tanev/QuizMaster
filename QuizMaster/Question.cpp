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

Question::Question(std::istream& is, QuestionType type)
{
    this->deserialize(is);
    this->questionType = type;
}

Question::Question(const String& question, double points, QuestionType questionType)
{
    setPoints(points);
    setQuestion(question);
    this->questionType = questionType;
}

const String& Question::getQuestion() const
{
    return this->question;
}

const double Question::getPoints() const
{
    return this->points;
}

const QuestionType Question::getQuestionType() const
{
    return questionType;
}

void Question::serialize(std::ostream& os)
{
    int typeInt = (int)questionType;
    os.write((const char*)&typeInt, sizeof(typeInt));
    question.serialize(os);
    os.write((const char*)&points, sizeof(points));
}

void Question::deserialize(std::istream& is)
{
    question.deserialize(is);
    is.read((char*)&points, sizeof(points));
}
