/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//web
#include<iostream>
using std::cout; using std::endl;
#include<algorithm> // max
#include<vector>
using std::vector;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;
#include "./../leetcodeutility.h"
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';


class Solution {
public:
  int maxSubArray(const vector<int>& nums) const
  {
    // For this, we use Kadane's algorithm.
    //            0 1  2 3  4 5 6  7 8
    // Example: [-2,1,-3,4,-1,2,1,-5,4]
    // This is sort of like dynamic programming. Say we have the maximum 
    // subarray ending at index i-1. What would be the maximum subarray
    // ending at i? Well, it would either 
    // 1) include the maximum subarray ending at i-1
    // 2) or it won't.
    //
    // This is because of the contiguous property, a subarray ending at 
    // i cannot skip past the entry located at i-1, so it must include that
    // entry. But we already worked out the max subarray ending at i-1, so
    // we can add it on if  a[i]+ max ending at i-1 > a[i].
    // Good description is here: 
    // https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm_(Algorithm_3:_Dynamic_Programming)
    // Don't read the geek for geeks website for this one, it's rubbish.
    
    // now, if we assume that there is at least one element in nums (like
    // the problem statement says), then we can initial:

    int max_ending_here = nums[0];
    int max_so_far = nums[0];

    // Now loop nums[1..n-1] and calculate the max_ending_here via dynamic
    // programming, then update max_so_far as required.
    for(int i = 1; i < static_cast<int>(nums.size()); ++i)
    {
      max_ending_here = std::max(max_ending_here+nums[i],nums[i]);
      max_so_far = std::max(max_so_far,max_ending_here);
    }
    return max_so_far;
  }
};


TEST_CASE("Testing maxSubArray", "[maxSubArray]" )
{
  Solution s;
  
  SECTION("Sec Testing maxSubArray")
  {
    REQUIRE(s.maxSubArray({-2,1,-3,4,-1,2,1,-5,4})==6);
  }
}

//auto main()->int
//{
//  return 0;
//}















