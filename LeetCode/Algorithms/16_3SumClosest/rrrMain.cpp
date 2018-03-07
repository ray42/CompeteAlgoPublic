/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/3sum-closest/description/
#include<iostream>
using std::cout; using std::endl;
#include<limits> // numeric_limits
#include<cmath> // abs
#include<vector>
using std::vector;
#include<numeric> // accumulate
#include<algorithm> // sort

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;


// Given an array S of n integers, find three integers in S such that the 
// sum is closest to a given number, target. Return the sum of the three
// integers. You may assume that each input would have exactly one solution.
//
//    For example, given array S = {-1 2 1 -4}, and target = 1.
//
//    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
class Solution {
public:
  // Brute force solution, because it's good to practice this.
  int threeSumClosestBrute(vector<int>& nums, int target)
  {
    // We work out every possible combination of triplets, and for each one,
    // we take the distance (abs) between the sum of the triplets and the
    // target. If this is smaller than a previously found distance, then we
    // update the distance.

    // Number of values to consider.
    int nums_size = nums.size();

    // Edge case, if there is less than or equal to 3 numbers, we simply 
    // return the sum.
    if(nums_size <= 3)
      return std::accumulate(nums.begin(),nums.end(),0);

    // Sum to return
    int minSum = 0;

    // Min distance found so far from target to sum
    int minDistance = std::numeric_limits<int>::max();

    for(int i = 0; i < nums_size; ++i)
    {
      for(int j=i+1; j < nums_size; ++j)
      {
        for(int k = j+1; k < nums_size; ++k)
        {
          int sum = nums[i]+nums[j]+nums[k];
          int maybeMinDist = std::abs(target-sum);
          if(maybeMinDist < minDistance)
          {
            minDistance = maybeMinDist;
            minSum = sum;
          }
        }
      }
    }
    return minSum;
  }

  // Optimized version, based on 3Sum, where i fix the first value, and 
  // use a sliding window technique to get the other two.
  int threeSumClosest(vector<int>& nums, int target)
  {
    int nums_size = nums.size();
    // Edge case, if there is less than or equal to 3 numbers, we simply 
    // return the sum.
    if(nums_size <= 3)
      return std::accumulate(nums.begin(),nums.end(),0);
   

    // First we sort nums, this is nlogn
    std::sort(nums.begin(),nums.end());
    
    // Now we traverse nums from i=[0..nums_size-1], for each i:
    // lo points to i+1, hi points to nums_size-1
    // let sumi = nums[i]+nums[lo]+nums[hi]
    // let disti = abs(target-sumi)
    // compare disti with the one formed by 
    // ++lo, --hi
    // while(lo<hi)
    // if (target - (nums[i]+nums[lo]+nums[hi]) < disti

    int minDist = std::numeric_limits<int>::max();
    int minDistSum = 0;
    for(int i = 0; i < nums_size; ++i)
    {
      int lo = i+1, hi = nums_size-1;
      while(lo<hi)
      {
        int sum = nums[i]+nums[lo]+nums[hi];
//        rcout << "i: " << i << ", lo: " << lo << ", hi: " << hi 
//              << ", sum: " << sum << '\n';

        // update if we have found a smaller distance
        int temp_min_dist = std::abs(target-sum);
        if(temp_min_dist < minDist)
        {
//          rcout << "abs(t-s): " << std::abs(target-sum)
//                << ", minDist: " << minDist << '\n';
          minDistSum = sum;
          minDist = temp_min_dist;

          // optimize: if the sum is equal to the target, then we have a 
          // distance of zero, so we can return immediately.
          if(sum==target) return sum;
        }

        // Now, we have to make the sum=nums[i]+nums[j]+nums[k] close to the
        // target. Since nums is sorted, is sum>target, we get a smaller sum
        // by --hi; if sum < target, we get a bigger sum by ++lo.
        (sum>target) ? --hi : ++lo;
      }
    }
    return minDistSum;
  }
};


TEST_CASE("Testing threeSumClosest", "[threeSumClosest]" )
{
  Solution s;
  
  SECTION("Sec Testing threeSumClosestBrute")
  {
    vector<int> v1{-1,2,1,-4};
    int out1 = 2;
    REQUIRE(s.threeSumClosestBrute(v1,1)==out1);
  }

  SECTION("Sec Testing threeSumClosest")
  {
    RAYDEBUG=true;
    vector<int> v1{-1,2,1,-4};
    int out1 = 2;
    vector<int> v2{1,1,1,0};
    int out2 = 2;

    REQUIRE(s.threeSumClosest(v1,1)==out1);
    REQUIRE(s.threeSumClosest(v2,-100)==out2);
  }

}

//auto main()->int
//{
//  return 0;
//}















