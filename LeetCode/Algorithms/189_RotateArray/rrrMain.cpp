/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/rotate-array
#include<iostream>
using std::cout;
#include<vector>
using std::vector;
#include<algorithm> // swap

#include "./../leetcodeutility.h"

#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

class Solution {
public:
  void rotate(vector<int>& nums, int k)
  {
    auto size = nums.size();
    k = k%size;
    RDEBUG(k);
    leftRotate(nums,0,size-k,size);
  }

  void leftRotate(vector<int>& nums, int first, int middle, int last)
  {
    middle = middle % nums.size();
    //if(middle == 0 || middle ==)
    int next = middle;
    while(first != next)
    {
      std::swap(nums[first++],nums[next++]);

      if(next == last)
      {
        // Move it back to the middle
        next = middle;
      }
      else if(first == middle)
      {
        // since next is not last, we can advance it to next.
        middle = next;
      }
    }
  }

//  void leftRotate(vector<int>& nums, int first, int middle, int last)
//  {
//    int next = middle;
//
//    // Start
//    cout << "Start: \n";
//    printCont(nums,">nums:");
//    RDEBUG(first);
//    RDEBUG(middle);
//    RDEBUG(last);
//    RDEBUG(next);
//    cout <<'\n';
//    
//    while(first != next)
//    {
//      std::swap(nums[first],nums[next]);
//      ++first;
//      ++next;
//
//      if(next == last)
//      {
//        cout << "RRRIF next==last, set next=middle\n";
//        next=middle;
//      }
//      else if(first==middle)
//      {
//        cout << "RRRELSE IF first==middle, set middle=next\n";
//        middle = next;
//      }
//
//      printCont(nums,">nums:");
//      RDEBUG(first);
//      RDEBUG(middle);
//      RDEBUG(last);
//      RDEBUG(next);
//      cout <<'\n';
//    }
//  }
};


TEST_CASE("Testing rotate", "[rotate]" )
{
  Solution s;
  
  SECTION("Sec Testing rotate")
  {
//    vector<int> v1{1,2,3,4,5,6,7};
//    vector<int> a1{5,6,7,1,2,3,4};
//    int k1 = 3;
//    s.rotate(v1,k1);
//    REQUIRE(v1==a1);

    vector<int> v2{1};
    vector<int> a2{1};
    int k2=0;
    s.rotate(v2,k2);
    REQUIRE(v2==a2);

    vector<int> v3{-1};
    vector<int> a3{-1};
    int k3=2;
    s.rotate(v3,k3);
    REQUIRE(v3==a3);

  }
}

//auto main()->int
//{
//  Solution s;
//  vector<int> v1{0,1,2,3,4,5,6,7};
//  s.leftRotate(v1,0,8-3,v1.size());
//  printCont(v1,"v1AFTER:");
//  return 0;
//}















