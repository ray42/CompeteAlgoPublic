/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/4sum/description
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<algorithm> // accumulate, sort

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

// To use bruteforce, we simply do 4 loops, and check each quadruplet
// nums[i]+nums[j]+nums[k]+nums[l] to see if it's equal to target.
//
// We'll skip that and go straight to the most efficient solution I can
// think of. Problem:
// Given an array S of n integers, are there elements a, b, c, and d in S 
// such that a + b + c + d = target? Find all *unique* quadruplets in the 
// array which gives the sum of target.
//
// We'll base our solution on the 3Sum algorithm. In the solution to 3Sums,
// the target is 0, and we fix the first number (indexed by i, 
// which is iterated through), for each nums[i], we check if the 
// sum=nums[i]+nums[lo]+nums[hi] is greater than the target. If so, we 
// decrease hi and try again, and it's lower than the target, then we 
// increase lo and try again, else, it should be equal, so we add it. We do
// this until lo>=hi (end of this iteration). (Look at the 3Sum code in 
// folder 15_3Sum, it'll become more clear.)
//
// How do we adapt this for 4 sum? Easy, we "fix" the first two nums, 
// nums[i] and nums[j]. Then we we use lo, hi for the last two, starting at
// the ends and move inwards until lo>=hi.
//
// this is a really good guide to what I'm doing:
// https://leetcode.com/problems/4sum/discuss/8714/
class Solution {
public:
  vector<vector<int>> fourSum(vector<int>& nums, int target) const
  {
    // return vector of vector of ints.
    vector<vector<int>> ret;

    // Edge case, if there are less than 4 elements, we return an empty 
    // vector of vectors of int, since it is impossible to have a quadruplet
    // which sums to target.
    int nums_size = nums.size();
    if(nums.size()< 4)
      return ret;

    // Now sort nums for the two-pointer lo/hi approach to work.
    std::sort(nums.begin(),nums.end());

    for(int i = 0; i < nums_size; ++i)
    {
      // target for 3sum approach
      auto target3 = target - nums[i];
      for(int j = i+1; j < nums_size; ++j)
      {
        auto target2 = target3 - nums[j];

        // Now check the lo and hi.
        int lo = j+1;
        int hi = nums_size-1;
        while(lo < hi)
        {
          int twoSum = nums[lo]+nums[hi];
          if(twoSum > target2)      --hi;
          else if(twoSum < target2) ++lo;
          else
          {
            // we found a quadruplet!
            // save lo and hi nums for dupes check later.
            int loNum = nums[lo];
            int hiNum = nums[hi];
            ret.push_back(vector<int>{nums[i],nums[j],loNum,hiNum});
            
            // now let's check if there are others by passing by same lo 
            // and hi
            while(lo < hi && nums[lo]==loNum) ++lo;
            while(lo < hi && nums[hi]==hiNum) --hi;
          }
        }
        // Note: we use a different approach from the 3sum one, where we 
        // check at the start of the loop. In the 3sum solution, we always
        // use the first element, and we check if i>0. Since we also need to
        // use the first number for j, even if it's the same as i, we need a 
        // different approach.
        // skip over the next j if it matches this one.
        while(j+1 < nums_size && nums[j]==nums[j+1]) ++j;
      }

      // Checking dupes at the end for consistency with the j loop.
      // skip over the next i if it's the same as this one.
      // process dupes for number 1
      while(i+1 < nums_size && nums[i]==nums[i+1]) ++i;
    }
    return ret;
  }
};


TEST_CASE("Testing fourSum", "[fourSum]" )
{
  Solution s;
  
  SECTION("Sec Testing fourSum")
  {
    // Test case 1
    vector<int>v1{1, 0, -1, 0, -2, 2};
    int t1 = 0;
    vector<vector<int>>sol1{{-1,0,0,1},{-2,-1,1,2},{-2,0,0,2}};
    auto ans1 = s.fourSum(v1,t1);
    std::sort(ans1.begin(),ans1.end());
    std::sort(sol1.begin(),sol1.end());
    REQUIRE(ans1==sol1);
  }
}

//auto main()->int
//{
//  return 0;
//}















