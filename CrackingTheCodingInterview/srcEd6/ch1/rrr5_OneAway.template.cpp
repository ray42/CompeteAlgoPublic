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
// 1.5 One Away: There are three types of edits that can be performed on 
// strings: 
// 1) insert a character,
// 2) remove a character, or
// 3) replace a character.
//
//Given two strings, write a function to check if they are one edit (or zero
//edits) away.
//
//EXAMPLE
//pale,  ple   -> true
//pales, pale  -> true
//pale,  bale  -> true
//pale,  bake  -> false
//
//Hints:
// #23: Start with the easy thing. Can you check each of the conditions
//  separately?
// #97: What is the relationship between the ``insert character'' option
//  and the ``remove character'' option? Do these need to be two separate
//  checks?
// #130: Can you do all three checks in a single pass?
//
//The only way I know how to check this is via dynamic programming:
//https://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here

// There will be at most one difference.
bool oneEditReplace(const std::string& str1, const std::string& str2);

// Check if you can insert a char into s1 to make s2.
bool oneEditInsert(const std::string& str1, const std::string& str2);


bool oneEditAway(const std::string& str1, const std::string& str2)
{
}

bool oneEditReplace(const std::string& s1, const std::string& s2)
{
}

// Check if you can insert  char into the shorter s1 to make s2.
bool oneEditInsert(const std::string& s1, const std::string& s2)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// We combine both replace and insert in one loop
bool oneEditAwayV2(const std::string& str1, const std::string& str2)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    REQUIRE(oneEditAway("pale","ple")==true);
    REQUIRE(oneEditAway("pales","pale")==true);
    REQUIRE(oneEditAway("pale","bale")==true);
    REQUIRE(oneEditAway("pale","bake")==false);
  }
  SECTION("Sec Testing ")
  {
    REQUIRE(oneEditAwayV2("pale","ple")==true);
    REQUIRE(oneEditAwayV2("pales","pale")==true);
    REQUIRE(oneEditAwayV2("pale","bale")==true);
    REQUIRE(oneEditAwayV2("pale","bake")==false);
  }
}

//auto main()->int
//{
//  return 0;
//}

