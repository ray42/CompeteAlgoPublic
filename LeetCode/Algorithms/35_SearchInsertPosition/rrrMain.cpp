/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/search-insert-position
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;
#include "./../leetcodeutility.h"
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';


class Solution {
public:
  int searchInsert(const vector<int>& nums, int target)
  {

    // We use binary search to find the index. Note that in binary search,
    // when the loop condition while(low <= high) is false, then low == mid,
    // we can use this fact to determine where to put the number.

    int numsize = nums.size();
    int low = 0;
    int high =  numsize-1;

    // This is the trick. We need to keep track of which, low or high,
    // we last incremented before we terminated.
    // Then we take the opposite of this. I just realised that I could have
    // used mid, let's try that now.
    bool last_increment_low = false;

    
    // Okay, using mid works. No need to keep track of last_increment_low.
    // But I will keep it in here for future reference
    int mid = 0;
    while(low <= high)
    {
      mid = low+(high-low)/2;

      cout << "Before It:\n";
      RDEBUG(low);
      RDEBUG(high);
      RDEBUG(mid);
      if(nums[mid]==target)
        return mid;

      // Remember to do the right first, I've learnt from my mistake in
      // P33 - Search in Rotated Sorted Array.
      if(nums[mid] < target)
      {
        low = mid+1;
        last_increment_low = true;
      }
      else
      {
        high = mid-1;
        last_increment_low = false;
      }
      cout << "After It:\n";
      RDEBUG(low);
      RDEBUG(high);
      RDEBUG(mid);
      cout << '\n';

    }

    // since we may have advanced low above high, we need the smaller one.
//    int ret = low<high?low:high;
    int ret = mid;
//    if(last_increment_low)
//      ret = high;
//    else
//      ret = low;

    RDEBUG(ret);

    if(target < nums[ret])
    {
      cout << "Target is less, returning low" << std::endl;
      return ret;
    }
    else
    {
      cout << "Target is HIGH, returning low+1" << std::endl;
      return ret+1;
    }
  }
};


TEST_CASE("Testing searchInsert", "[searchInsert]" )
{
  Solution s;
  
  SECTION("Sec Testing searchInsert")
  {
    vector<int> v1{1,3,5,6};
    int t1{5};
    REQUIRE(s.searchInsert(v1,t1)==2);

    vector<int> v2{1,3,5,6};
    int t2{2};
    REQUIRE(s.searchInsert(v2,t2)==1);

    vector<int> v3{1,3,5,6};
    int t3{7};
    //cout << "RAYRAYRAY: " << s.searchInsert(v3,t3) << std::endl;
    REQUIRE(s.searchInsert(v3,t3)==4);

    vector<int> v4{1,3,5,6};
    int t4{0};
    REQUIRE(s.searchInsert(v4,t4)==0);

    vector<int> v5{-5000,-4999,-4998,-4996,-4994,-4992,-4988};
    int t5{-5365};
    REQUIRE(s.searchInsert(v5,t5)==0);
  }
}

//auto main()->int
//{
//  return 0;
//}















