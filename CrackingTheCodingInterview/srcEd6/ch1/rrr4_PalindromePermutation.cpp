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


// #include here


// Question here.
// 1.4 Palindrome Permutation: Given a string, write a function to check if 
// it is a permutation of a palindrome. A palindrome is a word or phrase 
// that is the same forwards and backwards. A permutation is a rearrangement
// of letters. The palindrome does not need to be limited to just dictionary
// words.
//
//EXAMPLE
//Input: Tact Coa
//Output: True (permutations: "taco cat", "atco cta", etc.)



// Implementation here
bool isPermutationOfPalin(std::string)
{
}

// Optimized
bool isPermutationOfPalinOpt(std::string)
{
}

bool isPermutationOfPalinBit(std::string)
{
}

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

