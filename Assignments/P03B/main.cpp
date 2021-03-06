/*
 *
 *  Author:           Angel Badillo
 *  Email:            badilloa022402@gmail.com
 *  Label:            P03B
 *  Title:            BoliNverse Fight Club
 *  Course:           CMPS 2143
 *  Semester:         Fall 2021
 *
 *   This program is the randomized "battle simulation" where a number of attackers are fighting a small group of defenders (1 defender of each type per 100 attackers).
 *   E.g: 1000 attackers vs. 10 defenders. The program is fairly balanced so neither side wins too frequently. The point of this program is to demonstrate run-time
 *   polymorphism using BaseFighter points that point to an instance of any of BaseFighter's subclasses.
 *
 * Files
 *
 *|   #   | File                                 | Description                                                                                     |
 *| :---: | ------------------------------------ | ----------------------------------------------------------------------------------------------- |
 *|   1   | [main.cpp](main.cpp)                 | Main driver for program                                                                         |
 *|   2   | [fighter.hpp](fighter.hpp)           | Header for fighter classes                                                                      |
 *|   3   | [fighterData.json](fighterData.json) | Data to be used with fighter classes                                                            |
 *|   4   | [weapon.hpp](weapon.hpp)             | Header for weapon class                                                                         |
 *|   5   | [weapons.json](weapons.json)         | Data to be used with  weapon class                                                              |
 *|   6   | [helpers.hpp](helpers.hpp)           | Helper functions for dice and randomization of data                                             |
 *|   7   | [dice.hpp](dice.hpp)                 | Header for die and dice classes                                                                 |
 *|   8   | [json.hpp](json.hpp)                 | Header for using JSON in C++, credit to the creator(s) (https://github.com/nlohmann/json)       |
 *|   9   | [attackers.txt](attackers.txt)       | Data file used for generating specified amount of attackers                                     |
 *|  10   | [banner.txt](banner.txt)             | Banner for this Program                                                                         |
 *
 * Instructions
 *
 * - Just compile and run the program.
 *
 * - Example Command:
 *  - g++ main.cpp -o main
 *  - ./main
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "helpers.hpp"
#include "weapon.hpp"
#include "fighter.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main()
{
  ifstream infile;
  ofstream outfile;
  infile.open("attackers.txt"); // Names for fighters
  outfile.open("P03B.txt");     // Results will go to file
  int numAttackers = 0;         // Number of Attackers
  int numDefenders = 0;         // Number of Defenders
  
  infile >> numAttackers;

  // Counters for attackers
  int warCount = 0;
  int wizCount = 0;
  int archCount = 0;
  int elfCount = 0;
  int dragCount = 0;
  int roundCount = 0;

  // Counts the number of attackers of each type
  for (int i = 0; i < numAttackers; i++)
  {
    string fighterType;
    infile >> fighterType;

    if (fighterType == "warrior")
    {
      warCount++;
    }
    else if (fighterType == "wizard")
    {
      wizCount++;
    }
    else if (fighterType == "archer")
    {
      archCount++;
    }
    else if (fighterType == "elf")
    {
      elfCount++;
    }
    else
    {
      dragCount++;
    }
  }

  srand(time(0));
  // Attackers and Defender vectors
  vector<BaseFighter *> Attackers;
  vector<BaseFighter *> Defenders;

  // Captains of the teams
  BaseFighter *CaptAttacker;
  BaseFighter *CaptDefender;

  // Pushes all the attackers to the vector
  for (int i = 0; i < warCount; i++)
    Attackers.push_back(new Warrior("attacker"));

  for (int i = 0; i < wizCount; i++)
    Attackers.push_back(new Wizard("attacker"));

  for (int i = 0; i < archCount; i++)
    Attackers.push_back(new Archer("attacker"));

  for (int i = 0; i < elfCount; i++)
    Attackers.push_back(new Elf("attacker"));

  for (int i = 0; i < dragCount; i++)
    Attackers.push_back(new DragonBorn("attacker"));

  // Pushes Defenders to vector, following guideline of 1 fighter of each type for 100 attackers
  for (int i = 0; i < Attackers.size() / 100; i++)
  {
      Defenders.push_back(new Warrior("defender"));
      Defenders.push_back(new Wizard("defender"));
      Defenders.push_back(new Archer("defender"));
      Defenders.push_back(new Elf("defender"));
      Defenders.push_back(new DragonBorn("defender"));
      numDefenders+=5;
  }

  // GAME LOOP
  while (Attackers.size() && Defenders.size())
  {
    roundCount++; // Counting rounds
    for (int i = 0; i < Defenders.size(); i++)
      if (i < 0)
        Defenders[i]->regen();
    CaptAttacker = Attackers.back();
    CaptDefender = Defenders.back();

    // sub game loop
    while (CaptAttacker->alive() && CaptDefender->alive())
    {
      this_thread::sleep_for(chrono::milliseconds(1));
      system("clear");
      cout << "Defenders v Attackers\n";
      cout << Defenders.size() << " v " << Attackers.size() << endl;
      CaptAttacker->attack(CaptDefender);
      CaptDefender->attack(CaptAttacker);
    }
    if (!Attackers.back()->alive())
    {
      Attackers.pop_back();
    }
    if (!Defenders.back()->alive())
    {
      Defenders.pop_back();
    }
  }
  
  outfile << "Angel Badillo\nProgram 3B: Bolinverse Fight Club\n";
  if(Attackers.size() == 0)
  {
    cout << "Defenders won!" << '\n';
    outfile << "Defenders won!" << '\n';
  }
  else
  {
    cout << "Attackers won!" << '\n';
    outfile << "Attackers won!" << '\n';
  }
  cout << "Number of Defenders: " << numDefenders << '\n';
  outfile << "Number of Defenders: " << numDefenders << '\n';

  cout << "Amount of Defenders left: " << Defenders.size() << '\n';
  outfile << "Amount of Defenders left: " << Defenders.size() << '\n';

  cout << "Number of Attackers: " << numAttackers << '\n';
  outfile << "Number of Attackers: " << numAttackers << '\n';

  cout << "Amount of Attackers left: " << Attackers.size() << '\n';
  outfile << "Amount of Attackers left: " << Attackers.size() << '\n';

  cout << "Number of rounds fought: " << roundCount << '\n';
  outfile << "Number of rounds fought: " << roundCount << '\n';
  outfile.close();
}