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
#include<string>
#include<cstdlib> // abs
#include<cmath>   // abs

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
  // They are the same length
  if(str1.size() == str2.size())
  {
    // Can only make one the same as the other with replacement.
    return oneEditReplace(str1,str2);
  }
  // str1 is one shorter than str2
  else if(str1.size() + 1 == str2.size())
  {
    // Insert into str1
    return oneEditInsert(str1,str2);
  }
  // str1 is one longer than str2, so we insert into str2
  else if(str1.size() - 1 == str2.size())
  {
    // Insert into str2 to try make it the same as str1.
    return oneEditInsert(str2,str1);
  }

  // We get here if the two strings do not differ in size by at most 1.
  return false;
}

bool oneEditReplace(const std::string& s1, const std::string& s2)
{
  bool foundDifference = false;

  // Loop through the chars in s1 and s2, and check that there is only one 
  // difference. We can do this with a single bool, since if they are 
  // different, we trigger the bool on. If we see a difference again, we can
  // first check if the bool has been previously triggered on.
  for(int i = 0; i < static_cast<int>(s1.size()); ++i)
  {
    if(s1[i]!=s2[i])
    {
      // Check if there was a previous difference, if so, return false 
      // immediately.
      if(foundDifference)
        return false;

      // Set the flag since this is the first time.
      foundDifference = true;
    }
  }

  // If we make it here, we know that there is at most one difference.
  return true;
}

// Check if you can insert  char into the shorter s1 to make s2.
bool oneEditInsert(const std::string& s1, const std::string& s2)
{
  int index1 = s1.size()-1;
  int index2 = s2.size()-1;

  bool inserted = false;

  // Loop through the chars of both strings, from right to left
  while(index1 >= 0 && index2 >= 0)
  {
    // If the chars are the  same
    if(s1[index1] == s2[index2])
    {
      --index1;
      --index2;
    }
    // If it's not the same, we "insert" into s1 by decreasing the index of 
    // s2.
    else
    {
      // First we check if this is the first insert.
      if(inserted) 
        return false;

      --index2;
      inserted = true;
    }
  }

  // If we get here, it means there is at most on insert to turn s1 into s2.
  return true;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// We combine both replace and insert in one loop
bool oneEditAwayV2(const std::string& str1, const std::string& str2)
{
  // Check that the length differ by at most one
  if(abs(str1.size()-str2.size())>1)
    return false;

  // Get the shorter (s1) and longer (s2) string.
  std::string s1 = str1.size() < str2.size() ? str1 : str2;
  std::string s2 = str1.size() < str2.size() ? str2 : str1;

  // indices to loop through the strings from right to left.
  int index1 = s1.size()-1;
  int index2 = s2.size()-1;

  // Flag to trigger when first found.
  bool foundDifference = false;

  // Note: We know that s1 is shorter than s2 by AT MOST one.
  while(index1 >=0 && index2 >=0)
  {
    // if they are the same, we decrement both indices.
    if(s1[index1] == s2[index2])
    {
      --index1;
      --index2;
    }
    // They are not the same
    else
    {
      // first check if this is the first difference found.
      if(foundDifference) return false;

      // set the foundDifference
      foundDifference = true;

      // Check if s1 and s2 has the same length, if so, we perform a 
      // "replace", by decrementing both index1 and index2.
      if(s1.size() == s2.size())
      {
        --index1;
        --index2;
      }
      // Otherwise, we "insert" into s1 by decrementing s2 only.
      else
      {
        --index2;
      }
    }
  }

  // If we get here, then it's true.
  return true;
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

