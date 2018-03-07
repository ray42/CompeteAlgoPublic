/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/next-permutation
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;

#include<algorithm> // swap

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';

#include "./../leetcodeutility.h"


class Solution {
public:
  void nextPermutation(vector<int>& nums)
  {
    // First we search from the RHS for a[i-1], a[i] such that 
    // a[i-1] < a[i], draw out the graph of values to make it clearer.
    auto numsize = nums.size();

    int index = 0;
    int indexMinusOne = 0;

    // Go from numsize-1 to 1, since we need to read the i-1 value.
    for(int i = numsize-1; i >= 1; --i)
    {
      if(nums[i-1]<nums[i])
      {
        index = i;
        indexMinusOne = i-1;
        break;
      }
    }

//    RDEBUG(index);
//    RDEBUG(indexMinusOne);
    // If i is found such that a[i-1]<a[i], then it must be that i>=1, by 
    // the loop above, otherwise it is 0 and we simply reverse the vector.
    if(index==0)
    {
//      cout << "Index is 0, reversing\n";
//      printCont(nums,"Before: ");
      reverse(nums,0,numsize-1);
//      printCont(nums,"After: ");
    }
    else
    {
      // since we know that a[i-1]<a[i], we need to find a[j], starting from
      // the right, such that a[j] is just bigger than a[i-1]. But we know
      // that everything to the right of a[i-1] is in descending order.
      // And we know that at least one value to the right of a[i-1] is
      // greater than it. Namely, a[i]. So we just loop from the right
      // and test:
      int j = numsize-1;
      while(j>=0 && nums[j] <= nums[indexMinusOne])
      {
        --j;
      }

      // Now we know that we can swap a[i-1] and  a[j]
      std::swap(nums[indexMinusOne],nums[j]);

      // Now we have to reverse a[index..numsize-1] to make it a small list
      reverse(nums,index,numsize-1);
    }
  }

  void reverse(vector<int>& nums, int left, int right)
  {
    // number of elements to reverse divided by 2:
    int ndiv2 = (right-left+1)/2;

    // Loop through and reverse
    for(int i = 0; i < ndiv2; ++i)
    {
      std::swap(nums[left+i], nums[right-i]);
    }
  }
};


TEST_CASE("Testing nextPermutation", "[nextPermutation]" )
{
  Solution s;
  
  SECTION("Sec Testing nextPermutation")
  {
    // testing even number of numbers
    vector<int> r1{0,1,2,3,4,5,6,7,8};
    vector<int> ra1{0,1,5,4,3,2,6,7,8};
    s.reverse(r1,2,5);
    REQUIRE(r1==ra1);

    // testing odd number of numbers
    vector<int> r2{0,1,2,3,4,5,6,7,8};
    vector<int> ra2{0,1,6,5,4,3,2,7,8};
    s.reverse(r2,2,6);
    REQUIRE(r2==ra2);

    vector<int> in1{1,2,3};
    s.nextPermutation(in1);
    vector<int> out1{1,3,2};
    REQUIRE(in1==out1);

    vector<int> in2{3,2,1};
    s.nextPermutation(in2);
    vector<int> out2{1,2,3};
    REQUIRE(in2==out2);

    vector<int> in3{1,1,5};
    s.nextPermutation(in3);
    vector<int> out3{1,5,1};
    REQUIRE(in3==out3);
  }
}

//auto main()->int
//{
//  return 0;
//}















