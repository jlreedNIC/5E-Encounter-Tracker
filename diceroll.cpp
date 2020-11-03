#include "diceroll.h"

DiceRoller::DiceRoller()
{
    std::srand(time(nullptr));
}

DiceRoller::~DiceRoller()
{
    //destructor
}

int DiceRoller::rollDice(int dice)
{
    return (rand() % dice) + 1;
}

int DiceRoller::rollDice(int dice, int modifier)
{
    return rollDice(dice) + modifier;
}