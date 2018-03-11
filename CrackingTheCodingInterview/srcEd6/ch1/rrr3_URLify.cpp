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
  // Two scan approach. First count the number of spaces. Then we triple 
  // this value to find out how many extra characters we need in the final
  // string.
  //
  // The second pass, which is done in reverse order, we actually edit the 
  // string. When we see a space, we replace it with %20, if there are no 
  // space, then we copy the original character.

  // Count the number of spaces
  int spaceCount = 0;
  for(int i = 0; i < trueLength; ++i)
  {
    if(str[i]==' ')
      ++spaceCount;
  }

  // Now we loop from the end of the string we plan to construct.
  int index = trueLength + spaceCount*2;

  // Now, there may be more spaces than we need at the end. That is
  // Input: "Mr John Smith           ", 13
  //        "Mr%20John%20Smith     " <- to much space
  // In this case, we end the string with a null value.
  if(index < str.size()) str[index] = '\0'; // End the array

  // Now loop through the length the true length of the string in reverse 
  // order.
  // Note that index is trueLength+spaceCount*2 (the extra spaces required)
  // But since we use base zero, we have to decrement this to begin with.
  --index;
  for(int i = trueLength -1; i >=0; --i)
  {
    std::cout << "i: " << i << ", str[i]: " << str[i] 
              << ", index: " << index << '\n'; 

    // If we find a space, we insert %20 backwards.
    if(str[i] == ' ')
    {
      str[index]   = '0';
      str[index-1] = '2';
      str[index-2] = '%';
      index-=3;
      
      std::cout << "got in if: " << str << '\n';
    }
    else
    // just copy the value over
    {
      str[index] = str[i];
      --index;
      
      std::cout << "got in else: " << str << '\n';
    }
  }
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

