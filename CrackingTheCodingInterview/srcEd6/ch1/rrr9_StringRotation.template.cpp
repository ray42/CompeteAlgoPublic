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
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Question here.
// 1.9 String Rotation: Assume you have a method isSubstring which checks if
//     one word is a substring of another. Given two strings, s1 and s2, 
//     write code to check if s2 is a rotation of s1 using only one call to 
//     isSubstring (e.g., "waterbottle" is a rotation of "erbottlewat").
//
// My own solutions:
//
// The brute force approach: would be to rotate s2 and compare with s1, and 
//   do that until we have a match or until we have done s2.size rotation, 
//   so it fails.
//
// Second attempt: We can pick a letter in s1, say s1[0]. Now we do a linear
//   search in s2 for s1[0]. If we have found the char in position j, we 
//   rotate s2[j] such that it is in position s2[0], we compare s1 and s2.
//
// Third attempt: We don't even need to rotate s2. If we have found s1[0] in
//   s2[j], we simply compare the characters, but make sure that we wrap 
//   around s2 by doing modulo.
//
// Hints:
//
// #34: If a string is a rotation of another, then it's a rotation at a
//      particular point. For example, a rotation of waterbottle at 
//      character 3 means cutting waterbottle at character 3 and putting the
//      right half (erbottle) before the left half (wat).
//
// #88: We are essentially asking if there's a way of splitting the first 
//      string into two parts, x and y, such that the first string is xy and
//      the second string is yx. For example, x=wat and y=erbottle. The 
//      first string is xy=waterbottle. The second string is yx=erbottlewat.
//
// #104: Think about the earlier hint. Then think about what happens when 
//       you concatenate erbottlewat to itself. You get 
//       erbottlewaterbottlewat. (xy is the original. yx is the rotated. 
//       yx concatenated to itself is yxyx, we have xy (the original) in
//       there. But I'll still need to know the rotation point to make any 
//       use of this. Hmmm....)

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here
#include<string>

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here

// The "provided" isSubstring(s1,s2) function, returns true if s1 is in s2.
bool isSubstring(const std::string s1, const std::string s2)
{
}

bool isRotation(const std::string s1, const std::string s2)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    REQUIRE(isRotation("water","erbottlewat")==false);
    REQUIRE(isRotation("","")==true);
    REQUIRE(isRotation("waterbottle","erbottlewat")==true);
    REQUIRE(isRotation("waterbottAA","erbottlewat")==false);
  }
}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

