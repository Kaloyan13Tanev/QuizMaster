#pragma once
#include "Question.h"
#include "Vector.hpp"

class Quiz
{
private:
	String ID;
	String title;
	Vector<Question*> questions;
	bool isNormalMode;
	unsigned timesPlayed;
	unsigned likes;
};
