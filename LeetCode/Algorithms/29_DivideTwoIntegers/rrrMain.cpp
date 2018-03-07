/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/divide-two-integers/description/
#include<iostream>
using std::cout; using std::endl;
#include<cstdlib> // llabs
#include<climits> // INT_MAX and INT_MIN

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;


// This is a good explanation of what I'm doing:
// https://leetcode.com/problems/divide-two-integers/discuss/13407
class Solution {
public:
  int divide(int dividend, int divisor)
  {
    // If the divisor is zero or...
    if(!divisor || (dividend == INT_MIN && divisor == -1))
      return INT_MAX;

    // RAYRAY come back to this.
    int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
    
    long long top = std::llabs(dividend);
    long long bot = std::llabs(divisor);
    int res = 0;
    while(top >= bot)
    {
      long long bot_temp = bot;
      long long multiple = 1;
      while(top >= bot_temp << 1)
      {
        bot_temp <<=1;
        multiple <<=1;
      }
      top = top-bot_temp;
      res+=multiple;
    }
    return sign == 1?res:-res;
  }
};


TEST_CASE("Testing divide", "[divide]" )
{
  Solution s;
  
  SECTION("Sec Testing divide")
  {
    REQUIRE(s.divide(15,3)==5);
  }
}

//auto main()->int
//{
//  return 0;
//}















