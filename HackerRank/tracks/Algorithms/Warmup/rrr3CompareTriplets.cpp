/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// https://www.hackerrank.com/challenges/compare-the-triplets/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator> // istream_it
#include <string> // getline
#include <sstream> // stringstreams
#include <numeric> // accumulate

using namespace std;


int main(int argc, char* argv[])
{
  // Read input from cin and parse it.
  string line;

  // For A
  getline(cin,line);
  istringstream iss(line);
  vector<double>A((istream_iterator<double>{iss}),
                  (istream_iterator<double>()));

  // For B
  getline(cin,line);
  iss.clear();
  iss.str(line); // clear the error state
  vector<double>B((istream_iterator<double>{iss}),
                  (istream_iterator<double>()));

  int AScore{}, BScore{};
  for(decltype(A.size()) i=0; i< A.size();++i)
  {
    if(A[i]<B[i])
    {
      ++BScore;
    }
    else if(A[i]>B[i])
    {
      ++AScore;
    }
  }
  cout << AScore << " " << BScore << endl;
  return 0;
}

