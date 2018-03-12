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


// #include here




// Implementation here




TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    REQUIRE(func("","")==true);
  }
}

//auto main()->int
//{
//  return 0;
//}

