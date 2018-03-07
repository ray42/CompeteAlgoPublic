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

#include<tuple>
using std::tuple;

#include<cstddef>
using std::size_t;

#include<numeric>
using std::accumulate;

#include<iterator>
using std::reverse_iterator;
using std::distance;
using std::advance;
using std::prev;
using std::next;

#include<limits>
using std::numeric_limits;

// Brute force maximum subarray problem
template<typename InputIt, typename T>
auto maximum_subarray_bruteforce(InputIt first, InputIt last, T init)
  ->tuple<InputIt,InputIt,T>
{
  InputIt left;
  InputIt right;
  T maxSum{};
  T maxSumPerRow{};

  for(InputIt i = first; i != last; ++i)
  {
    maxSumPerRow = T{};
    for(InputIt j = i; j != last; ++j)
    {
      maxSumPerRow+= *j;
      if(maxSumPerRow > maxSum)
      {
        maxSum = maxSumPerRow;
        left = i;
        right= j+1;
      }
    }
  }
  return {left,right,maxSum};
}

template<typename InputIt>
auto find_max_crossing_subarray(InputIt low, InputIt mid, 
                                InputIt high)
  ->tuple<InputIt,InputIt,typename InputIt::value_type>
{

  using RIter = reverse_iterator<InputIt>;
  RIter rmid{mid};
  RIter rlow{low};

  auto leftSum = 
    numeric_limits<typename InputIt::value_type>::lowest();

  InputIt leftIndex;

  auto sum = typename InputIt::value_type{};
  for(;rmid != rlow; ++rmid)
  {
    sum+=*rmid;
    if(sum > leftSum)
    {
      leftSum = sum;
      leftIndex = prev(rmid.base());
    }
  }

  //////
  sum = typename InputIt::value_type{};
  auto rightSum = 
    numeric_limits<typename InputIt::value_type>::lowest();
  InputIt rightIndex;
  for(InputIt it = mid; it != high; ++it)
  {
    sum+=*it;
    if(sum > rightSum)
    {
      rightSum = sum;
      rightIndex = next(it);
    }
  }

  return {leftIndex,rightIndex,leftSum+rightSum};
}

template<typename InputIt>
auto find_maximum_subarray(InputIt lowIt, InputIt highIt)
  -> tuple<InputIt,InputIt,typename InputIt::value_type>
{
  if(highIt==lowIt)
  {
    cout << "highIt==lowIt" << endl;
    exit(0);
  }
  else if(distance(lowIt,highIt) == 1)
  {
    return {lowIt, highIt,*lowIt};
  }
  else
  {
    auto midIt = lowIt;
    advance(midIt,distance(lowIt,highIt)/2);

    auto[leftLowIt,leftHighIt,leftSum]=
      find_maximum_subarray(lowIt,midIt);
    auto[rightLowIt,rightHighIt,rightSum]=
      find_maximum_subarray(midIt,highIt);
    auto[crossLowIt,crossHighIt,crossSum]=
      find_max_crossing_subarray(lowIt,midIt,highIt);

    if(leftSum >= rightSum && leftSum >= crossSum)
    {
      return {leftLowIt,leftHighIt,leftSum};
    }
    else if(rightSum >= leftSum && rightSum >= crossSum)
    {
      return {rightLowIt, rightHighIt, rightSum};
    }
    else
    {
      return {crossLowIt,crossHighIt,crossSum};
    }
  }
}

auto main(int, char* [])->int
{
  //              begin       mid       end
  //                0  1 2  3  4 5 6  7  8
  vector<double> v{-2,-3,4,-1,-2,1,5,-3,-4};

//  ////////////////////////////////////////////////////////////////////////
//
//  auto[low1,high1,sum1] = 
//    maximum_subarray_bruteforce(v.cbegin(),v.cend(),
//                                decltype(v)::value_type{});
//  cout << "low: " << *low1
//       << ", high: " << *high1
//       << ", sum: " << sum1 << "\n\n" << endl;
//
//  ////////////////////////////////////////////////////////////////////////
//
//  cout << "Testing midcross" << endl;
//  auto mid2 = v.cbegin();
//  advance(mid2,distance(v.cbegin(),v.cend())/2);
//
//  auto[low2,high2,sum2]=
//    find_max_crossing_subarray(v.cbegin(),mid2,v.cend());
//  cout << *low2 << endl;
//  cout << *high2 << endl;
//  cout << sum2 << endl;
//
//  ////////////////////////////////////////////////////////////////////////

  auto[low3,high3,sum3]=
    find_maximum_subarray(v.cbegin(),v.cend());
  cout << *low3 << " " << *high3 << " " << sum3 << endl;


  return 0;
}
