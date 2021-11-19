#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

#pragma once

/**
 * @brief Splits a string into parts based on a delimiter
 *
 *      For example the string: "2.d.12" would be turned into 
 *      a vector => ["2","d","12"] and returned
 * 
 * @param s 
 * @param delimiter 
 * @return vector<string> 
 */
vector<string> tokenize(string s,string delimiter){
    size_t pos = 0;
    vector<string> tokens;
    while ((pos = s.find(delimiter)) != string::npos) {
        tokens.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}

json getRandomWeapon(json Weapons){
    int r = rand() % Weapons.size();
    return Weapons[r];
}

json getRandomWeaponType(json Weapons,string wtype){
  json tempWeapons = json::array();

  for(int i=0;i<Weapons.size();i++){
    if(Weapons[i]["Type"] == wtype){
      tempWeapons.push_back(Weapons[i]);
    }
  }
  return getRandomWeapon(tempWeapons);
}

string getRandomName(vector<string> &names)
{
  int r = rand() % names.size();
  return names[r];
}