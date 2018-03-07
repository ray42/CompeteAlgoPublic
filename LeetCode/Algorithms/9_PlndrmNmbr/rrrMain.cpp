/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/palindrome-number/description/
#include<iostream>
using std::cout; using std::endl;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;


class Solution {
public:
  bool isPalindrome(int x)
  {
    // Edge cases:
    // 1) all negative numbers is not a palindrome, since you cannot match 
    // '-' on the left with a number on the right.
    // 2) If the right-most digit is zero, the number must be zero, since
    // we need to match zero on the left-most number, the only number which
    // matches this description is 0.
    if(x<0 || (x%10==0 && x != 0))
    {
      return false;
    }

    int reversedNum=0;
    while(x>reversedNum)
    {
      reversedNum = reversedNum*10 + x%10;
      x/=10;
    }
    // Try with numbers:
    // x=1234567=> x=123, r=7654
    // x=123456 => x=123, r=654
    // x=987654 => x=98,  r=4567
    // x=12321  => x=12,  r=123
    // x=123321 => x=123, r=123
//    rcout << "x: " << x << '\n';
//    rcout << "r: " << reversedNum << '\n';
//    rcout << '\n';

    return x==reversedNum || x==(reversedNum/10);
  }

};


TEST_CASE( "Testing isPalindrome", "[isPalindrome]" )
{
  Solution s;
  
  SECTION("Testing isPalindrome")
  {
    RAYDEBUG=true;
    REQUIRE(s.isPalindrome(1234567)==false);
    REQUIRE(s.isPalindrome(123456)==false);
    REQUIRE(s.isPalindrome(987654)==false);
    REQUIRE(s.isPalindrome(220)==false);
    REQUIRE(s.isPalindrome(0)==true);
    REQUIRE(s.isPalindrome(12321)==true);
    REQUIRE(s.isPalindrome(123321)==true);
    REQUIRE(s.isPalindrome(-123321)==false);
    RAYDEBUG=false;
  }
}

//auto main()->int
//{
//  return 0;
//}















