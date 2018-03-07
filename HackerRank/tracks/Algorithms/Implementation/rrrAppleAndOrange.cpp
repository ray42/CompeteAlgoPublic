/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// https://www.hackerrank.com/challenges/apple-and-orange/problem
#include<iostream>
using std::cout; using std::endl; using std::cin;

auto main(int argc, char *argv[])->int
{
  int houseStart,houseEnd; // s,t
  int AppleTree, OrangeTree; // a,b
  int numApples,numOrange; // m, n
  cin >> houseStart >> houseEnd 
      >> AppleTree >> OrangeTree
      >> numApples >> numOrange;

  // First do the apples
  decltype(numApples) nAppOnHouse{};
  decltype(AppleTree) d; // distance
  decltype(AppleTree) pos; // position from tree
  for(decltype(numApples) i=0; i != numApples; ++i)
  {
    cin >> d;
    pos=AppleTree+d;
    if((pos >= houseStart) && (pos <=houseEnd))
    {
      ++nAppOnHouse;
    }

  }

  // Now do oranges
  decltype(numOrange) nOragOnHouse{};
  for(decltype(numOrange) i=0; i!=numOrange; ++i)
  {
    cin >> d;
    pos=OrangeTree+d;
    if((pos >= houseStart)&&(pos <= houseEnd))
    {
      ++nOragOnHouse;
    }
  }

  cout << nAppOnHouse << "\n"<< nOragOnHouse << endl;

  return 0;
}
