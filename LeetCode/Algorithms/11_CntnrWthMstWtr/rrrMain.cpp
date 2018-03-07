/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/container-with-most-water/description/
#include<iostream>
using std::cout; using std::endl;
#include<algorithm> // std::max
#include<vector>
using std::vector;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;


// NOTE: The solution to this is latex'd up. Look at my pdf. But I'll 
// briefly explain it here.
class Solution 
{
public:
  int maxArea(const vector<int>& height)
  {
    // initial area.
    int maxA = 0;

    // We start with two points at the outer-most lines
    int lefti=0; int rightj=height.size()-1;

    // while the left line in a position to the left of the right line 
    // (and they cannot be equal, since we cannot make an area that way)
    while(lefti<rightj)
    {
      // we calculate the area and update maxarea.
      maxA = std::max(maxA,
          std::min(height[lefti], height[rightj]) * (rightj-lefti));
      
//      rcout << "i= "<<lefti
//            <<", j= " << rightj 
//            << ", j-i= " << rightj-lefti 
//            << '\n';
      
      // The idea is that we move from the shorter line towards the longer
      // line. Let the shorter line be in position lefti, and the longer 
      // line be in position rightj. If we move from rightj (longer 
      // position) towards the shorter position, there is no way to improve
      // the area, since we have decreased the width, but the min height
      // is still the same (in position lefti). However, if we move lefti
      // towards rightj, we can hope to find a line long enough to offset
      // the reduced width.
      if(height[lefti]<height[rightj])
        ++lefti;
      else
        --rightj;
    }
    return maxA;
  }
};

TEST_CASE( "Testing maxArea", "[maxArea]" )
{
  Solution s;
  
  SECTION("Testing maxArea")
  {
    RAYDEBUG=true;
    REQUIRE(s.maxArea({1,2,1})==2);
    RAYDEBUG=false;
  }
}

//auto main()->int
//{
//  return 0;
//}















