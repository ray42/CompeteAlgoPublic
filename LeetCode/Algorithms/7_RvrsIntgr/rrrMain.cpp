/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//http here
#include<iostream>
using std::cout; using std::endl;
#include<climits>


#define rcout if(RayDebug) cout 


static bool RayDebug=false;

class Solution {
public:
  int reverse(int x) {

    // Check sign and make x positive
    // since if either x, y (in x%y) is negative, the remainder is 
    // implementation dependent.
    int sign=1;
    if(x<0)
    {
      sign=-1;
      x*=-1;
    }

    // Define the result as long int, so we can check for overflow
    long long int res = 0;
    while(x != 0)
    {
      int remainder = x%10;
      x=(x-remainder)/10;
      res+=remainder;
      res*=10;
    }
    
    // Put the sign back and divide by 10
    //cout << "res is: " << res;
    //cout << "sign is: " << sign;
    res = (res*sign)/10;

    if(res < INT_MIN || res > INT_MAX)
      return 0;

    //cout <<"final res is: "<< res;
    return res;
  }
};


TEST_CASE( "reverse", "[reverse]" )
{
  Solution s;
  
  SECTION("Testing reversing an integer")
  {
    REQUIRE(s.reverse(123)==321); // From LC
    REQUIRE(s.reverse(-123)==-321); // From LC
    REQUIRE(s.reverse(120)==21); // From LC
  }
}

//auto main()->int
//{
//  return 0;
//}















