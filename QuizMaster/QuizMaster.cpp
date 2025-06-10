#include <iostream>
#include "Vector.hpp"
#include "TrueOrFalseQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "MatchingPairsQuestion.h"
#include "ShortAnswerQuestion.h"
#include "Console.h";

int main()
{
    TrueOrFalseQuestion tf = TrueOrFalseQuestion("Vqrno li e che gosho e debel?", 100, true);

    Vector<String> answers1;
    answers1.push_back(100);
    answers1.push_back(1000);
    answers1.push_back(10000);
    answers1.push_back("daje poveche");
    SingleChoiceQuestion sc = SingleChoiceQuestion("Kolko kila teji Gosho?", 100, answers1, 4);

    Vector<String> answers2;
    answers2.push_back("lqvata");
    answers2.push_back("dqsnata");
    answers2.push_back("nikoq");
    answers2.push_back("samo ednata");
    Vector<unsigned> rightAnswers2;
    rightAnswers2.push_back(1);
    rightAnswers2.push_back(2);
    MultipleChoiceQuestion mc = MultipleChoiceQuestion("Koq palaska na Gosho pada ot legloto dokato spi?", 100, answers2, rightAnswers2);

    ShortAnswerQuestion sa = ShortAnswerQuestion("Gosho e...", 100, "o4ilatko");

    Vector<String> firstCol;
    firstCol.push_back("purvo");
    firstCol.push_back("vtoro");
    firstCol.push_back("treto");
    Vector<String> secondCol;
    secondCol.push_back("debel");
    secondCol.push_back("grozen");
    secondCol.push_back("krasiv");
    secondCol.push_back("o4ilatko");
    Vector<unsigned> rightConnections;
    rightConnections.push_back(2);
    rightConnections.push_back(1);
    rightConnections.push_back(4);
    MatchingPairsQuestion mp = MatchingPairsQuestion("Svurjete po red", 100, firstCol, secondCol, rightConnections);

    unsigned points = 0;

    //points += tf.answer();
    //std::cout << points;
    //points += sc.answer();
    //std::cout << points;
    //points += mc.answer();
    //std::cout << points;
    //points += sa.answer();
    //std::cout << points;
    points += mp.answer();

    std::cout << points;
}