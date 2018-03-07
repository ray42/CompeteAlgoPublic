/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// https://www.hackerrank.com/challenges/staircase/problem

#include<iostream>
using std::cin; using std::cout; using std::endl;
#include<string>
using std::string;

auto main(int argc, char* argv[])->int
{
  auto N=unsigned{};
  cin >> N;
  for(decltype(N) i=0; i!=N; ++i)
  {
    // How many space?
    string space(N-i-1,' ');
    string hash(i+1,'#');
    cout << space << hash << endl;
  }
  return 0;
}
