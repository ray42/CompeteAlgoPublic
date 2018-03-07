/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// https://www.hackerrank.com/challenges/mini-max-sum/problem

#include<iostream>
using std::cout; using std::endl; using std::cin;
#include<iterator>
using std::istream_iterator;
#include<vector>
using std::vector;
#include<algorithm>
using std::sort;
#include<numeric>
using std::accumulate;

auto main(int argc, char* argv[])->int
{
  using llu=long long unsigned;

  llu sum=0;
  llu i;
  llu max=0, min=1e10;
  while(cin >> i)
  {
    sum+=i;
    if(i>max) max=i;
    if(i<min) min=i;
  }
  cout << sum-max << " " << sum-min << endl;

  return 0;
}
