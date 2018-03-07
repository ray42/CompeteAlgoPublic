/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/single-number
#include<iostream>
using std::cout; using std::endl;
#include<unordered_map>
using std::unordered_map;
#include<unordered_set>
using std::unordered_set;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;
#include "./../leetcodeutility.h"
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';


class Solution {
public:
  int singleNumber(const vector<int>& nums) const
  {
    // We need to keep a count for each elements in nums, then search for
    // the element with a count of 1. HOWEVER, since every element appears
    // twice except for one, we can keep a sum. Now we iterate through nums,
    // and insert it into a set, if it's possible, we add it to the count,
    // if it's not possible, we take it away from sum. We will end up with
    // the single singular element.
    unordered_set<int> intset;
    int sum=0;
    for(const auto& val:nums)
    {
      auto piter = intset.insert(val);
      if(piter.second)
      {
        sum+=val;
      }
      else
      {
        sum-=val;
      }
    }
    return sum;
  }
};


TEST_CASE("Testing singleNumber", "[singleNumber]" )
{
  Solution s;
  
  SECTION("Sec Testing singleNumber")
  {
    REQUIRE(s.singleNumber()==);
  }
}

//auto main()->int
//{
//  return 0;
//}















