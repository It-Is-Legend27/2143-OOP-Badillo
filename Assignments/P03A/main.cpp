/*****************************************************************************
*                    
*  Author:           Angel Badillo
*  Email:            badilloa022402@gmail.com
*  Label:            P03A
*  Title:            Rock Paper Scissors Lizard Spock
*  Course:           CMPS 2143
*  Semester:         Fall 2021
* 
*  Description:
*        This program is a game of RPSLS (Rock Paper Scissors Lizard Spock)
*        where two players are generated with two random, but distinct weapons 
*        each (meaning a player cannot have 2 of the same weapon). The 
*        "weapons" are "hands", which are emojis representing rock, paper, 
*        scissors, lizard, and spock. The rules are:
*           - Scissors cuts Paper
*           - Paper covers Rock
*           - Rock crushes Lizard
*           - Lizard poisons Spock
*           - Spock smashes Scissors
*           - Scissors decapitates Lizard
*           - Lizard eats Paper
*           - Paper disproves Spock
*           - Spock vaporizes Rock
*           - Rock crushes Scissors
*       The p1's first weapon gets compared to p2's second weapon,
*       if their weapons are not they same (they don't "throw" the same hand)
*       the game is over and a winner is declared. If they have the same weapon,
*       there is a second match, and their weapons will be compared, but if for
*       any reason they have the same weapon again, the game is over and declared a tie.
*        
*  Usage:
*       - g++ main.cpp -o main && ./main
*       - You just compile and run it.
* 
*  Files:     
*       main.cpp        : driver program
*       RPSLS.hpp       : header file with definition and implementation of "game"
*       output.txt      : output of program
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include "RPSLS.hpp"

using namespace std;

int main()
{
    ofstream outfile("output.txt");
    outfile << "CMPS-2143-101\n"
            << "PO3A\n"
            << "Angel Badillo\n\n";

    // Running 30 instances of the battle of p1 vs p2
    for (int i = 1; i <= 30; i++)
    {
        cout << "Instance " << i << '\n';
        outfile << "Instance " << i << '\n';

        Player p1; // Player 1 with random weapons
        Player p2; // Player 2 with random weapons

        battle(cout, p1, p2);    // Prints "battle" outcome to standard output
        battle(outfile, p1, p2); // Prints "battle" outcome to output file
    }
    return 0;
}