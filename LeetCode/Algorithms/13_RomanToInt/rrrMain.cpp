/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/roman-to-integer/description
#include<iostream>
using std::cout; using std::endl;
#include<string>
using std::string;
#include<map>

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;


class Solution {
public:
  int romanToInt(string s)
  {
    // Map of roman numerals to ints
    std::map<char,int>rtoi{{'I',1},

                         //{"IV",4},  // V-1
                           {'V',5},

                         //{"IX",9},  // X-1
                           {'X',10},

                         //{"XL",40}, // L-10
                           {'L',50},

                         //{"XC",90}, // C-10
                           {'C',100},

                         //{"CD",400},// D-100
                           {'D',500},

                         //{"CM",900}, // M-100
                           {'M',1000}};

    // Note how, except for the first line ("I",1), every two lines form a
    // pair. Second note, and most importantly, is to see that going from 
    // right to left, the numbers should increase. e.g. VII, going from 
    // right to left, you have 1, 1, 5. If the number goes down, i.e. IV, we
    // have 5, 1, it means we subtract the 1. So for each roman number we 
    // scan from right to left, we can compare it with the previous number,
    // if it's equal to or greater than the previous number, we add it. If 
    // it's lower, we subtract it.
    //
    // We start with a previous roman value of 0, which means we always add
    // the first character we come across, which is what we want!
    int pre_val=0;
    int curr_val=0;
    int sum=0;
    for(int s_index = s.size()-1; s_index >=0; --s_index)
    {
      curr_val=rtoi[s[s_index]];
      if(curr_val>=pre_val) sum+=curr_val;
      else sum-=curr_val;

      // Now record the new pre_val
      pre_val = curr_val;
    }

    return sum;
  }
};


TEST_CASE( "Testing romanToInt", "[romanToInt]" )
{
  Solution s;
  
  SECTION("Sec Testing romanToInt")
  {
    RAYDEBUG=true;
    REQUIRE(s.romanToInt("MMMDXLIX")==3549);
    REQUIRE(s.romanToInt("MCMXCIV")==1994);
    REQUIRE(s.romanToInt("CMI")==901);
    REQUIRE(s.romanToInt("DCCCXXXII")==832);
    REQUIRE(s.romanToInt("DCCC")==800);
    REQUIRE(s.romanToInt("I")==1);
    REQUIRE(s.romanToInt("II")==2);
    REQUIRE(s.romanToInt("III")==3);
    REQUIRE(s.romanToInt("IV")==4);
    REQUIRE(s.romanToInt("V")==5);
    REQUIRE(s.romanToInt("VI")==6);
    REQUIRE(s.romanToInt("VII")==7);
    REQUIRE(s.romanToInt("VIII")==8);
    REQUIRE(s.romanToInt("IX")==9);
    REQUIRE(s.romanToInt("X")==10);
  }
}

//auto main()->int
//{
//  return 0;
//}



























