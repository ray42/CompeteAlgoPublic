/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

// https://leetcode.com/problems/remove-duplicates-from-sorted-array/
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<algorithm>
using std::unique;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

class Solution {
public:
  int removeDuplicates(vector<int>& nums)
  {
    // Note: This works:
    //return std::unique(nums.begin(),nums.end())-nums.begin();
    //But I think that the whole point is to implement std::unique.
    
    // Since we're pointing with two pointers, we check if size is greater
    // than 1.
    auto nums_size = static_cast<int>(nums.size());
    if(nums_size<=1)
      return nums_size;

    // There are at least two elements.
    int firsti = 0;
    int secondj = 1;
    while(secondj < nums_size)
    {
      // firsti always points to the last unique item.
      while(secondj<nums_size && nums[firsti]==nums[secondj])
        ++secondj;

      if(secondj == nums_size)
        break;

      nums[firsti+1] = nums[secondj];
      ++firsti;
      ++secondj;
    }
    return ++firsti;
  }
};


TEST_CASE("Testing removeDuplicates", "[removeDuplicates]" )
{
  Solution s;
  
  SECTION("Sec Testing removeDuplicates")
  {
    vector<int> a1{1,1,2};
    REQUIRE(s.removeDuplicates(a1)==2);
    vector<int> a2{1,1};
    REQUIRE(s.removeDuplicates(a2)==1);
  }
}

//auto main()->int
//{
//  return 0;
//}















