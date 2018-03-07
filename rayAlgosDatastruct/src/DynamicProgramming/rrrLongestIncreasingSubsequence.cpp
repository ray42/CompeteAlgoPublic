/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<string>
using std::string;

template<typename T>
void printSeqCon(const T& v, string str = "")
{
  if(!str.empty())
  {
    cout << str;
  }
  for(const auto& i : v)
  {
    cout << i << " ";
  }
  cout << '\n';
}

template<typename T>
auto longestIncreasingSubsequence(vector<T> A)
{
  vector<T> lis(A.size(),0);
  
  // base case: lis of first number is 1
  lis[0] = 1;

  for(decltype(A.size()) i = 1; i < A.size(); ++i)
    lis[i] = (A[i-1]< A[i]) ? lis[i-1]+1 : lis[i-1];

  return lis;
}

int main()
{
  auto lis = longestIncreasingSubsequence<int>({10,22,9,33,21,50,41,60,80});
  printSeqCon(lis, "lis: ");
  return 0;
}
