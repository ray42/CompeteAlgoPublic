/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */

//https://www.hackerrank.com/challenges/diagonal-difference/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib> // for abs.

using namespace std;

auto main(int argc, char* argv[]) -> int
{
  int msize{};
  cin >> msize;

  vector<int> m;
  decltype(m)::value_type ii{};
  // read in the matrix
  while(cin >> ii)
  {
    m.push_back(ii);
  }

  // calculate diagonal sums
  decltype(m)::value_type diagsum{};
  decltype(m)::value_type antidiagsum{};
  for(decltype(msize) i=0; i< msize; ++i)
  {
    // i and j are the same for a diagonal value
    decltype(msize) j=i;

    // index of the diagonal in the vector
    decltype(msize) d=i*msize+j;
    diagsum+=m[d];

    // For the secondary diagonal:
    // i = size-1..0
    // j = 0..size-1
    decltype(msize) ii=msize-1-i;
    d=ii*msize+j;
    antidiagsum+=m[d];
  }
  cout << abs(diagsum-antidiagsum) << endl;
  return 0;
}
