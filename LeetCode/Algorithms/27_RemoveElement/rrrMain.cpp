/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/remove-element
#include<iostream>
using std::cout; using std::endl;
#include<algorithm> // remove, swap
#include<vector>
using std::vector;


// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

//#include "./../leetcodeutility.h"

class Solution{
public:
  int removeElement(vector<int>& nums, const int val)
  {
    // using STL:
    //return std::remove(nums.begin(),nums.end(),val)-nums.begin();

    // Plan is to move all occurences to val to the end.
    int fronti = 0;
    for(int backj = nums.size()-1; backj >=0; --backj)
    {
      if(fronti < backj && nums[backj]!=val)
      {
//        rcout << "i: " << fronti << ", j: " << backj << '\n';
//        rcout << "b4: a[i]: " << nums[fronti] << ", a[j]: "<< nums[backj] << '\n';
        std::swap(nums[fronti],nums[backj]);
//        rcout << "after: a[i]: " << nums[fronti] << ", a[j]: "<< nums[backj] << '\n';
//        printVec(nums,"nums:\n");
//        rcout << "\n\n\n";
        
        ++fronti;
      }
    }

//    printVec(nums,"AFTER: nums:\n");
    return ++fronti;
  }
};


TEST_CASE("Testing removeElement", "[removeElement]" )
{
  Solution s;
  
  SECTION("Sec Testing removeElement")
  {
    vector<int> in1{3,2,2,3};
    RAYDEBUG=true;
    REQUIRE(s.removeElement(in1,3)==2);
  }
}

//auto main()->int
//{
//  return 0;
//}















