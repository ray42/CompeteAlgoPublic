/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout;
#include<vector>
using std::vector;

#include<algorithm> // swap

#include "./../leetcodeutility.h"
#include "./../raymacro.h"

// https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
//
// https://www.geeksforgeeks.org/permutations-of-a-given-string-using-stl

// Writing my own swap for practice.
template<typename T>
void mySwap(T& t1, T& t2)
{
  T temp{};
  temp = t1;
  t1=t2;
  t2=temp;
}

template<typename C>
void myPrintCont(const C& cont)
{
  for(const auto ci : cont)
  {
    cout << ci << " ";
  }
  cout << '\n';
}

// left = 0, right=n-1
template<typename T>
void permute(T& vec, int left, int right)
{
  // There is one element left, no need to swap, just print.
  if(left==right)
  {
    myPrintCont(vec);
  }
  else
  {
    // We want to swap l with i = [l..r] inclusive, yes including the last 
    // one since it's to trigger the base case
    for(int i = left; i <= right; ++i)
    {
      mySwap(vec[left],vec[i]);
      permute(vec,left+1,right);
      mySwap(vec[left],vec[i]); // backtrack
    }
  }
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// With rotate

// http://en.cppreference.com/w/cpp/algorithm/rotate

// This returns first + (last - n_first), which is the position of first in
// the rotated. This makes sense since rotate is a left rotate, and so the
// first element is wrapped around left-wise and ends up being at position
// first+(last-n_first).
template<typename ForwardIt>
ForwardIt rotate(ForwardIt first, ForwardIt n_first, ForwardIt last)
{
  // first+(last-n_first)=first + (last - first) = last
  if(first == n_first) return last;

  // first+(last-n_first)=first + (last - last) = first
  if(n_first == last) return first;

  ForwardIt next = n_first;

  do{
    std::iter_swap(first, next);
    ++first;
    ++next;

    if(first == n_first) n_first = next;
  }
  while(next != last);


}

auto main()->int
{
  vector<int>v{1,2,3};
  permute(v,0,2);
  return 0;
}

