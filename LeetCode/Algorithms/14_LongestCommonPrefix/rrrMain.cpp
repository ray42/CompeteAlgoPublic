/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/longest-common-prefix/description/
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<limits>

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;


class Solution {
public:
  string longestCommonPrefix(const vector<string>& strs)
  {
    // We will do vertical scanning of the strs. For this, we first work out
    // the min length of all the strings, then scan from index 0 to 
    // minlength-1 chars. For each char, we go down from strs[0] to 
    // strs[strs.size()-1], and see if we get a mismatch. If we do, we know
    // the index of the char before it represents the LCP.

    // Number of strs to consider
    auto num_strs = static_cast<int>(strs.size());
    
    // Edge cases:
    // If there are no strings, just return empty immediately.
    if(num_strs == 0) return "";
    // If there is only one string, just return the string.
    else if(num_strs==1) return strs[0];

    // Otherwise, get the smallest number of chars in all strings.
    int min_chars = std::numeric_limits<int>::max();
    for(int strs_index = 0; strs_index < num_strs; ++strs_index)
    {
      min_chars = min_chars>strs[strs_index].size()?
                    strs[strs_index].size():min_chars;
    }
    //rcout << "min_chars: " << min_chars << '\n';
    
    // Another edge case is that if the min chars is 0, it means we can
    // immediately return ""
    if(min_chars == 0) return "";
    
    // Now loop through the chars, then the strs and see if they're all 
    // equal
    int lcp_index = -1; // minus 1 to indicate that it has not been found.

    for(int char_index = 0; char_index < min_chars; ++char_index)
    {
      // Get the char to compare from the first string. Thanks to the edge 
      // case, we know there is at least two strings.
      char curr_char=strs[0][char_index];
      //rcout << "doing char: " << curr_char <<", at index: " << char_index << '\n';

      // Keep track of if all the chars are the same so far.
      bool same_so_far = true; 

      // Start the comparison from the second string.
      for(int strs_index = 1; strs_index < num_strs; ++strs_index)
      {
        if(strs[strs_index][char_index] != curr_char)
        {
          //rcout << "not same as " << strs[strs_index][char_index] << '\n';
          same_so_far = false;
          break;
        }
      }
      // If we get here, we have either compared all the strs of this 
      // curr_char, or it broke off. We test this.
      if(same_so_far)
      {
        lcp_index=char_index;
      }
      else break;
    }

    //rcout << "lcp_index: " << lcp_index << '\n';

    if(lcp_index == -1)
      return "";

    // When it broke off, we are working in base 0, so it broke off WITHOUT
    // assigning when we reached two chars which are not the same. This 
    // means that the number of chars of the lcp is actually lcp_index+1
    return strs[0].substr(0,lcp_index+1);
  }
};

TEST_CASE( "Testing longestCommonPrefix", "[longestCommonPrefix]" )
{
  Solution s;

  vector<string>strs1{"0123qqq",
                      "0123www",
                      "0123eee"};
 
  vector<string>strs2{"0123",
                      "0123www",
                      "0123eee"};
 
  vector<string>strs3{"0123",
                      "0123www",
                      ""};
  vector<string>strs4{"0123",
                      "qqqqqq",
                      "wwwwwww"};
  vector<string>strs5{"0123"};
  vector<string>strs6;

  SECTION("Sec Testing longestCommonPrefix")
  {
    RAYDEBUG=true;
    REQUIRE(s.longestCommonPrefix(strs1)=="0123");
    REQUIRE(s.longestCommonPrefix(strs2)=="0123");
    REQUIRE(s.longestCommonPrefix(strs3)=="");
    REQUIRE(s.longestCommonPrefix(strs4)=="");
    REQUIRE(s.longestCommonPrefix(strs5)=="0123");
    REQUIRE(s.longestCommonPrefix(strs6)=="");
  }
}

//auto main()->int
//{
//  return 0;
//}















