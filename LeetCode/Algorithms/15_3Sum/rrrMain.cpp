/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/3sum/description/
#include<iostream>
using std::cout; using std::endl;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

#include<vector>
using std::vector;
#include<unordered_set>
using std::unordered_set;
#include<algorithm>
#include<map> // std::map

// Given an array S of n integers, are there elements a, b, c in S such that
// a+b+c=0? Find all unique triplets in the array which gives the sum of 
// zero.
// Note: The solution set must not contain duplicate triplets.
// 
// For example, given array S = [-1, 0, 1, 2, -1, -4],
// A solution set is:
// [
//   [-1, 0, 1],
//   [-1, -1, 2]
// ]

struct VectorHash {
  size_t operator()(const std::vector<int>& v) const
  {
    std::hash<int> hasher;
    size_t seed = 0;
    for (auto i : v) {
      seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }
    return seed;
  }
};

class Solution {
public:
  // This works but exceeded time limit.
  vector<vector<int>> threeSumBrute(const vector<int>& nums)
  {
    // First we try a brute force approach. For this, we work out all 
    // triplets then
    // 1) If their sum = 0, 
    // 2) check if they are unique by sorting and storing them in a set.
    // This is n choose 3, which is n!/(n-k)!k! = n(n-1)(n-2)/3! = O(n^3).
    auto nums_size = static_cast<int>(nums.size());
    
    unordered_set<vector<int>,VectorHash> triplet_set;

    for(int i = 0; i < nums_size; ++i)
    {
      for(int j = i+1; j < nums_size; ++j)
      {
        for(int k = j+1; k < nums_size; ++k)
        {
          if((nums[i]+nums[j]+nums[k]) == 0)
          {
            // sort and insert into the set
            vector<int> triplet{nums[i],nums[j],nums[k]};
            std::sort(triplet.begin(),triplet.end());
            triplet_set.emplace(std::move(triplet));
          }
        }
      }
    }
    return {triplet_set.begin(),triplet_set.end()};
  }

  // N^2 solution - Time still exceeded!!
  vector<vector<int>> threeSumWithTwoSumSolution(vector<int>& nums)
  {
    // now we attempt a n^2 solution. This is based on the observation that
    // the requirement a+b+c implies c = -(a+b). So we loop through nums,
    // and for each number, we find a *unique* pair such that -(a,b) is the
    // same as the first number.
    //
    // Another way to think about this is that we use the one-pass two-sums
    // solution, where we have to find two numbers in nums such that 
    // b+c=target. Instead, of target, we find two numbers b and c such that
    // c+b = -a., and we do not spot, we loop through the whole list.
    // Let's give this a go!

    // First let's sort the nums vector, this is so we do not have to sort
    // the triplets later, we can just insert in the order 
    // {nums[i],nums[j],nums[k]}
    std::sort(nums.begin(),nums.end());

    // number of numbers.
    auto nums_size = static_cast<int>(nums.size());

    vector<vector<int>> ret;

    // Loop through the first digit.
    for(int i = 0; i < nums_size; ++i)
    {
      // This check for **REPETITION** for the first element, the logic is
      // this, if find the set {c,b | b+c=-a}, then it would be the same set
      // for all ai=aj.
      if(i>0 && nums[i-1]==nums[i])
        continue;

      // Now, we know that the target is nums[i]. So we loop through nums
      // from j=i+1..<nums_size. For each one, we take the complement:
      // complement = target - nums[j], and see if the complement is in
      // a set, if it is not, then we add it in. If it is, then we know that
      // the triplet is {nums[i],nums[from map],nums[j]}.
      std::map<int,int>nums_to_index_map;
      for(int j=i+1; j < nums_size; ++j)
      {
        // target = b+c => -a = b+c =>
        // complement = target-nums[j] = -a-c
        auto complement = -nums[i]-nums[j];
        auto it = nums_to_index_map.find(complement);
        if(it!=nums_to_index_map.end())
        {
          ret.push_back({nums[i],nums[it->second],nums[j]});

          // Now we need to get rid of duplicates, we keep skipping the
          // next number until we're either at the end, or the next number
          // is not equal to this one.
          while(j+1<nums_size && nums[j]==nums[j+1])
            ++j; // GOD THIS IS SO BAD!!!
        }
        else
        {
          nums_to_index_map.emplace(nums[j],j);
        }
      }
    }
    return ret;
  }

  // N^2 solution - final attempt, we work with a sliding window.
  vector<vector<int>> threeSum(vector<int>& nums)
  {
    // In this attempt, we first sort nums, this is nlogn, operation.
    std::sort(nums.begin(),nums.end());

    // Now that it's in sorted order, denote a = nums. We know that 
    // a0 <= a1 <= ... <= a[n-1]. Now, we traverse a from i=0..n-1
    // the window will be from j=(i+1)..(k=n-1).
    // 
    // 1) if (ai) + (aj+ak)>0, we should move k to the left, since a is
    //    sorted and we want to reduce the sum.
    // 2) else if ai + (aj+ak)<0, we should increase j, to increase the sum.
    // 3) else this means ai+aj+ak=0
    //     To prevent dupes:
    //       we decrease k while(j<k && nums[k-1]==nums[k])
    //          increase j while(j<k && nums[j]==nums[j+1])
    vector<vector<int>> ret;
    int nums_size = nums.size();
    for(int i = 0; i < nums_size; ++i)
    {
      // skip over repeated i's
      if(i>0 && nums[i-1]==nums[i]) continue;

      int lo = i+1;        // j
      int hi = nums_size-1;// k
      while(lo<hi)
      {
        int sum = nums[i]+nums[lo]+nums[hi];
        if(sum>0) --hi;
        else if(sum<0)++lo;
        else
        {
          //rcout << "Inserting: i="<<i <<", lo="<<lo<<", hi=" << hi << '\n';
          ret.push_back(vector<int>{nums[i],nums[lo],nums[hi]});
          
          // Get rid of duplicates
          while(lo<hi && nums[lo]==nums[lo+1])++lo;
          while(lo<hi && nums[hi-1]==nums[hi])--hi;
          // Move past the last ones which are the same
          ++lo;--hi;
        }
      }
    }
    return ret;
  }
};


TEST_CASE("Testing threeSum", "[threeSum]" )
{
  Solution s;
  
//  // Time limit exceeded!
//  SECTION("Sec Testing threeSumBrute")
//  {
//    vector<int> input1{-1,0,1,2,-1,-4};
//    vector<vector<int>>output1{{-1,-1,2},{-1,0,1}};
//    REQUIRE(s.threeSumBrute(input1)==output1);
//  }
//  // Time limit STILL exceeded!
//  SECTION("Sec Testing threeSumWithTwoSumSolution")
//  {
//    vector<int> input1{0,0,0,0};
//    vector<vector<int>>output1{{0,0,0}};
//    vector<int> input2{-1,0,1,2,-1,-4};
//    vector<vector<int>>output2{{-1,0,1},{-1,-1,2}};
//    REQUIRE(s.threeSumWithTwoSumSolution(input1)==output1);
//    REQUIRE(s.threeSumWithTwoSumSolution(input2)==output2);
//  }
  // 
  SECTION("Sec Testing threeSum")
  {
    RAYDEBUG=true;
    vector<int> input1{0,0,0,0};
    vector<vector<int>>output1{{0,0,0}};
    vector<int> input2{-1,0,1,2,-1,-4};
    vector<vector<int>>output2{{-1,-1,2},{-1,0,1}};
    //                 0 1  2  3
    vector<int> input3{1,2,-2,-1};
    vector<vector<int>>output3;

    REQUIRE(s.threeSum(input1)==output1);
    REQUIRE(s.threeSum(input2)==output2);
    REQUIRE(s.threeSum(input3)==output3);
  }

}

//auto main()->int
//{
//  return 0;
//}















