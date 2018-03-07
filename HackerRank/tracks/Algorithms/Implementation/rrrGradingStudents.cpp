/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// https://www.hackerrank.com/challenges/grading/problem

#include<iostream>
using std::cin; using std::cout; using std::endl;

auto main(int argc, char* argv[])->int
{
  int foo{};
  cin >> foo; // ignore first item.
  
  while(cin >> foo)
  {
    if(foo > 37)
    {
      int remainder=foo%5;
      if(remainder > 2)
        cout << foo+5-remainder << endl;
      else
        cout << foo << endl;
    }
    else
    {
      cout << foo << endl;
    }
  }

  return 0;
}
