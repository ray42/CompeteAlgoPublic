/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl; using std::cin;

int main()
{
  // Enter in terminal/stdin:
  // 1 2 3 4 5
  int i{};
  cin >> i; // 1
  cout << "First i: "<<i << "\n";
  cin.ignore(2); // ignore 2,3
//  cin.ignore(3); 
  cin >> i; // Why is this not 4??
  cout << "Second i: "<<i << "\n"; // It is three!

  // In fact, I get the same output if I do cin.ignore(3) instead of 
  // cin.ignore(2) (see the line commented out). What gives?


  return 0;
}

