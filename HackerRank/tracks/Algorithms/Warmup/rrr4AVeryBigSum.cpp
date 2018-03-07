/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */

// https://www.hackerrank.com/challenges/a-very-big-sum/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string> // for getline
#include <iterator> // istream iterator
#include <numeric> // numeric
using namespace std;

int main(int argc, char* argv[])
{
  using llongint=long long int;

  string s;
  // throw away the first line, we don't need this input.
  getline(cin,s);

  llongint sum{};
  sum=std::accumulate(istream_iterator<llongint>{cin},
                      istream_iterator<llongint>{},
                      llongint{});
  cout << sum << endl;
  
  return 0;
}


