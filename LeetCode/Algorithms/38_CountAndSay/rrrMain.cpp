/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/count-and-say
//https://www.geeksforgeeks.org/look-and-say-sequence
#include<iostream>
using std::cout; using std::endl;
#include<string>
using std::string;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;
#include "./../leetcodeutility.h"
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';


class Solution {
public:
  string countAndSay(int n)
  {
    // base case, if n=0, we let that be 1.
    if(n==0) return "1";
    if(n==1) return "1";
    if(n==2) return "11";

    // Now we loop through the previous sequence, counting the number of 
    // times a number appears consecutively.
    string prev_seq = "11";
    
    for(int seqi = 3; seqi <= n; ++seqi)
    {
      // Initialize the ith sequence
      string current_seq = "";

      // In the below loop, the previous character is processed in the 
      // current iteration. That is why a dummy character is added to make
      // sure that loop runs one extra iteration, to account for the last
      // character in the actual prev_seq
      prev_seq += '$';

      // generate the ith sequence by looping through the prev_seq string
      int count = 1;
      for(int chari = 1; chari < prev_seq.size(); ++chari)
      {
        if(prev_seq[chari-1] != prev_seq[chari])
        {
          // Form the current sequence
          current_seq += std::to_string(count) + prev_seq[chari-1];
          // reset counter
          count = 1;
        }
        else
        {
          ++count;
        }
      }

      // update the prev_seq
      prev_seq = current_seq;
    } // for [i..n]
    return prev_seq;
  }
};


TEST_CASE("Testing countAndSay", "[countAndSay]" )
{
  Solution s;
  
  SECTION("Sec Testing countAndSay")
  {
    REQUIRE(s.countAndSay(1)=="1");
    REQUIRE(s.countAndSay(2)=="11");
    REQUIRE(s.countAndSay(3)=="21");
    REQUIRE(s.countAndSay(4)=="1211");
    REQUIRE(s.countAndSay(5)=="111221");
  }
}

//auto main()->int
//{
//  return 0;
//}















