#ifndef DICEROLL_H
#define DICEROLL_H

#include <cstdlib>
#include <ctime>

class DiceRoller
{
    public:
        DiceRoller();
        ~DiceRoller();

        int rollDice(int dice);
        int rollDice(int dice, int modifier);
    private:
};

#endif