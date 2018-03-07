/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// https://www.hackerrank.com/challenges/plus-minus/problem
#include<iostream>
#include<iomanip>

using namespace std;

auto main(int argc, char* argv[])->int
{
  // size of array
  auto N=unsigned{};
  cin >> N;

  auto pos=unsigned{};
  auto neg=unsigned{};
  auto zero=unsigned{};

  auto i=int{};
  while(cin >> i)
  {
    if(i>0)
      ++pos;
    else if(i<0)
      ++neg;
    else
      ++zero;
  }
  cout << fixed << setprecision(6) 
       << static_cast<double>(pos)/N << "\n"
       << static_cast<double>(neg)/N << "\n"
       << static_cast<double>(zero)/N << endl;

  return 0;
}
