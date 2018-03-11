/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */

// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

#include<iostream>
using std::cout; using std::endl;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) std::cout 
static bool RAYDEBUG=false;
#define RDEBUG(x) std::cout << '>' << #x << ':' << x << '\n';


// #include here
#include<string>
#include<cstddef>


// Question here.
// 1.3 URLify: Write a method to replace all spaces in a string with '\%20'.
// You may assume that the string has sufficient space at the end to hold 
// the additional characters, and that you are given the ``true'' length of
// the string (the true length of the string includes the spaces in between 
// words, but excluding the extra spaces at the end). (Note: If implementing 
// in Java, please use a character array so that you can perform this 
// operation in place.)
//
// EXAMPLE
//         1234567.....13
// Input: "Mr John Smith   ", 13
// Output: "Mr%20John%20Smith"

// Implementation here
void replaceSpaces(std::string& str, int trueLength)
{
}

TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    std::string s1 = "Mr John Smith    ";
    std::size_t tl1 = 13;
    std::string a1 = "Mr%20John%20Smith";
    replaceSpaces(s1,tl1);
    REQUIRE(s1==a1);
  }
}

//auto main()->int
//{
//  return 0;
//}

