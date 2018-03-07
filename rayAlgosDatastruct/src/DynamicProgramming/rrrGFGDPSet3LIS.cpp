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
#include<limits>

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
auto longestIncreSubseq(const vector<T>& A)
{
  using vecSz_t = decltype(A.size());
  auto n = A.size();

  vector<T> lis(n,0);
  
  // base case: lis of first number is 1
  lis[0] = 1;

  // Loop for lis[i], i=1..n-1
  for(vecSz_t i = 1; i < n; ++i)
  {
    // There is always a LIS of length at least 1 ending in A[i] 
    // (the element already in there!)
    lis[i] = 1;
    // Consider each previous lis[j], j<i
    for(vecSz_t j = 0; j<i; ++j)
    {
      // We need to plus one to account for the element ending at A[i].
      // So if lis[j]+A[i] is a valid subsequence (A[j]<A[i]),
      // then it must be of length lis[j]+1, we compare if this is greater
      // than what's currently calculated for lis[i].
      if((lis[j]+1)>lis[i] && A[j]<A[i])
      {
        lis[i] = lis[j]+1;
      }
    }
  }

  return lis;
}

int main()
{
  auto lis = longestIncreSubseq<int>({50,3,10,7,40,80});
  printSeqCon(lis, "lis: ");
  return 0;
}
