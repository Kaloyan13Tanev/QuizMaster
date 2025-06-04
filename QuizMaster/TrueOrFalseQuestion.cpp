#include "TrueOrFalseQuestion.h"
#include <iostream>

TrueOrFalseQuestion::TrueOrFalseQuestion(char* question, unsigned points, bool answer) : Question(question, points)
{
	this->rightAnswer = answer;
}

unsigned TrueOrFalseQuestion::answer()
{
	bool givenAnswer;
	char givenA;
	std::cout << "Answer with 'T' or 'F': ";/////////////////////инпут въпрос
	std::cin >> givenA;						/////////////////////инпут въпрос
	if (givenA != 'T' && givenA != 'F')
		throw std::invalid_argument("You should answer with 'T' or 'F'!");
	
	if (givenA == 'T')
		givenAnswer = 1;
	else
		givenAnswer = 0;

	if (givenAnswer == rightAnswer)
		return getPoints();
}
