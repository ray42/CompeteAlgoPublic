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
#include<string>
#include<vector>
#include<unordered_map>

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

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

std::vector<int> buildCharFrequencyVec(const std::string&);
bool checkMaxOneOdd(const std::vector<int>&);

// Implementation here
bool isPermutationOfPalinVec(const std::string& phrase)
{
}

// Map each character to a number. a->0, b->1, c->2, etc...
// This is case insensitive. Non-letter characters map to -1.
int getCharNumber(char c)
{
}

std::vector<int> buildCharFrequencyVec(const std::string& str)
{
}

bool checkMaxOneOdd(const std::vector<int>& table)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

std::unordered_map<char,int> buildCharFrequencyMap(const std::string&);
bool checkMaxOneOdd(const std::unordered_map<char,int>&);

bool isPermutationOfPalinHash(const std::string& phrase)
{
}

std::unordered_map<char,int> buildCharFrequencyMap(const std::string& str)
{
}

bool checkMaxOneOdd(const std::unordered_map<char,int>& charfreq_map)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// Optimized - count number of odd as you loop through, as opposed to a 
// final loop at the end after constructing the table. Is it really more 
// optimal?
bool isPermutationOfPalinOpt(const std::string& phrase)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

int createBitVector(const std::string& phrase);
bool checkExactlyOneBitSet(int);

// Space optimization - using a bit vector.
bool isPermutationOfPalinBit(const std::string& phrase)
{
}


int toggle(int,int);

int createBitVector(const std::string& str)
{
}

int toggle(int bitvec, int index)
{
}

// Check that exactly one bit is set by subtracting one from the integer 
// and ANDing it with the original integer. E.g.
// 00010000 - 1 = 00001111
// 00010000 & 00001111 = 0, since there is no overlap between the new value
//                          and the original number
bool checkExactlyOneBitSet(int bitvec)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    REQUIRE(isPermutationOfPalinVec("")==true);
    REQUIRE(isPermutationOfPalinVec("a")==true);
    REQUIRE(isPermutationOfPalinVec("aa")==true);
    REQUIRE(isPermutationOfPalinVec("aaa")==true);
    REQUIRE(isPermutationOfPalinVec("ab")==false);
    REQUIRE(isPermutationOfPalinVec("abb")==true);
  }
//  SECTION("Sec Testing ")
//  {
//    REQUIRE(isPermutationOfPalinHash("")==true);
//    REQUIRE(isPermutationOfPalinHash("a")==true);
//    REQUIRE(isPermutationOfPalinHash("aa")==true);
//    REQUIRE(isPermutationOfPalinHash("aaa")==true);
//    REQUIRE(isPermutationOfPalinHash("ab")==false);
//    REQUIRE(isPermutationOfPalinHash("abb")==true);
//  }
//  SECTION("Sec Testing ")
//  {
//    REQUIRE(isPermutationOfPalinOpt("")==true);
//    REQUIRE(isPermutationOfPalinOpt("a")==true);
//    REQUIRE(isPermutationOfPalinOpt("aa")==true);
//    REQUIRE(isPermutationOfPalinOpt("aaa")==true);
//    REQUIRE(isPermutationOfPalinOpt("ab")==false);
//    REQUIRE(isPermutationOfPalinOpt("abb")==true);
//  }
//  SECTION("Sec Testing ")
//  {
//    REQUIRE(isPermutationOfPalinBit("")==true);
//    REQUIRE(isPermutationOfPalinBit("a")==true);
//    REQUIRE(isPermutationOfPalinBit("aa")==true);
//    REQUIRE(isPermutationOfPalinBit("aaa")==true);
//    REQUIRE(isPermutationOfPalinBit("ab")==false);
//    REQUIRE(isPermutationOfPalinBit("abb")==true);
//  }
}

//auto main()->int
//{
//  return 0;
//}

