/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/search-in-rotated-sorted-array/
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
  int search(vector<int>& nums, int target)
  {
    // 0 1 2 3 4 5 6 7 8
    // 4 5 6 7 8 9 0 1 2
    int numsize = nums.size();
    int low = 0;
    int high = numsize - 1;

//    RDEBUG(low);
//    RDEBUG(high);
//    RDEBUG(mid);
    
    while(low <= high)
    {
      cout << "BEGIN It\n";

      int mid = low + (high-low)/2;
  
      RDEBUG(low);
      RDEBUG(high);
      RDEBUG(mid);

      // If we found the correct mid, we return
      if(nums[mid] == target)
        return mid;

      // How do I determine if target is in the left half or right half?
      // First we deal with the left half, the right half will mirror it.
      //
      //We know that the left half can either be sorted => a[low] < a[mid-1]
      //or not: a[low] >= a[mid-1]
      //
      //Either left half or right half or both must be sorted.
      
      // If the left half is sorted
      // Must be less than or equal to in case there is only one number on
      // the left.
      //
      // NOTE IMPORTANT: This code kept failing when the if statement was
      // if(nums[low] < nums[mid-1])
      // This is because we calculate mid by rounding (high-low)/2 DOWN.
      // This means there is a possibility that low = mid, so when we
      // index mid-1, it makes no sense since we are going out of bounds.
      if(nums[mid+1] <= nums[high])
      {

  //             0 1
//  vector<int> v2{3,1};
        cout << "RIGHT half sorted\n";
        // So we use the sorted right half to determine if it's in the
        // right half or not. Again, we need to test if it's in the range.
        // For the right hand side, we check inclusive,
        // since we can add 1 to mid (since mid is rounded down, never up)
        if((nums[mid+1] <= target) && (target <= nums[high]))
        {
          cout << "Moving to the RIGHT\n";
          low = mid+1;
        }
        else // it's in the unsorted left half
        {
          cout << "Moving to the LEFT\n";
          high = mid-1;
        }
      }
      else
        // right half is sorted
      {
  //             0 1 2 3 4 5 6 7
//  vector<int> v4{3,4,5,6,7,8,1,2};
        cout << "LEFT half sorted\n";
        // we compare with the sorted left half, we need to know that target
        // is in the RANGE of the left half, since it may be shifted, just
        // checking against the midpoint is not good enough.
        // NOTE: Here we cannot check target < nums[mid-1] since it may be
        // that low = mid, so we are indexing out of bounds if we use 
        // mid-1.
        if((nums[low] <= target) && (target < nums[mid]))
        {
          cout << "Moving to the LEFT\n";
          high = mid-1;
        }
        else // we know it's in unsorted right half
        {
          cout << "Moving to the RIGHT\n";
          low = mid+1;
        }
      }
      cout << "END It\n";
      RDEBUG(low);
      RDEBUG(high);

      cout << '\n';
    }
    return -1;
  }
};


TEST_CASE("Testing search", "[search]" )
{
  Solution s;
  //             0 1 2 3 4 5 6 7 8
  vector<int> v1{4,5,6,7,8,9,0,1,2};
  
  //             0 1
  vector<int> v2{3,1};

  //             0 1 2 3 4 5 6 7 8
  vector<int> v3{2,3,4,5,6,7,8,9,1};

  //             0 1 2 3 4 5 6 7
  vector<int> v4{3,4,5,6,7,8,1,2};
  
  SECTION("Sec Testing search")
  {
    REQUIRE(s.search(v1,1)==7);
    REQUIRE(s.search(v2,1)==1);
    REQUIRE(s.search(v3,9)==7);
    REQUIRE(s.search(v4,2)==7);
  }
}

//auto main()->int
//{
//  return 0;
//}















