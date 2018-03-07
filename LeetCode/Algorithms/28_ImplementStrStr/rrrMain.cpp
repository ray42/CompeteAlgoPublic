/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/implement-strstr
#include<iostream>
using std::cout; using std::endl;
#include<string>
using std::string;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

// https://www.geeksforgeeks.org/searching-for-patterns-set-2-kmp-algorithm/
// http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/

class Solution {
public:
  int strStr(const string& haystack, const string& needle)
  {
    // We do a simple naive approach, later I will come back and try KMP

    // Note that we only need to look for needle in haystack[0..n-m] 
    // inclusive.
    int n = haystack.size();
    int m = needle.size();
    for(int i = 0; i <= n-m; ++i)
    {
//      cout << "i="<< i << '\n';
      // Loop through needle chars
      int j = 0;
      for(;j<m;++j)
      {
        if(haystack[i+j] != needle[j])
        {
          break;
        }
      }
//      cout << "j=" << j << '\n';
      if (j==m) return i;
    }
    return -1;
  }
};


TEST_CASE("Testing strStr", "[strStr]" )
{
  Solution s;
  
  SECTION("Sec Testing strStr")
  {
    REQUIRE(s.strStr("hello","ll")==2);
    REQUIRE(s.strStr("aaaaa","bba")==-1);
  }
}

//auto main()->int
//{
//  return 0;
//}















