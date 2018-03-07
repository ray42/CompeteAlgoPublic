/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<map> // map

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

// Given a digit string, return all possible letter combinations that the
// number could represent.
//
// A mapping of digit to letters (just like on the telephone buttons) is 
// given below.
//           2: abc | 3: def
// 4: ghi  | 5: jkl | 6: mno
// 7: pqrs | 8: tuv | 9: wxyz
//
// Input:Digit string "23"
// Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
// Note:
// Although the above answer is in lexicographical order, your answer could
// be in any order you want.
//
// Good explanation of solution here:
// https://leetcode.com/problems/letter-combinations-of-a-phone-number/discuss/8090/
// (Although I did come up with it myself by considering cases for 2, 23, 
// 234, etc...)
class Solution
{
public:
  // Brute force approach. Loop through digits, for each one, we choose 1
  // of the letters it could represent.
  vector<string> letterCombinationsBrute(const string& digits)
  {
    // Edge case, if digits is empty, return an empty vector.
    // The below will always have a vector of 1 string which is empty.
    if(digits.empty()) return vector<string>{};

//    std::map<string,string>{             {"2","abc"},{"3","def"},
//                            {"4","ghi"}, {"5","jkl"},{"6","mno"},
//                            {"7","pqrs"},{"8","tuv"},{"9","wxyz"}};

    // Instead, we can just just use a vector and index it via 
    // digits[i]-'0'. This means that the first two entries of this vector
    // needs to be "", for 0 and 1.
    static const vector<string> digit_to_chars{ "","","abc","def",
                                                  "ghi","jkl","mno",
                                                 "pqrs","tuv","wxyz"};

    // Think of it like this, if we have "2", then result is:
    // [a,b,c]
    // If we have [2,3], result is:
    // [ad,ae,af, bd,be,bf, cd,ce,cf]
    // So we can use the previous array elements as a prefix, adding the
    // letters represented by the new digit at each iteration.

    vector<string> ret;
    // populate it with an empty string to start off the prefix, since then 
    // we have ""+a, ""+b, ""+c = [a,b,c].
    ret.push_back("");

    // Loop through the digits
    for(int digits_i = 0; digits_i < digits.size(); ++digits_i)
    {
      int single_dig = digits[digits_i]-'0';
      // check validity, if this is not a digit, we discontinue
      if(single_dig < 0 || single_dig >9) break;

      // temp vec to store the new prefix
      vector<string> tmp_prefix;
      // Loop through the current prefix in ret and loop through all chars
      // represented by single_dig, and concatenate them, pushing them into
      // tmp_prefix.
      for(int ret_i = 0; ret_i < ret.size(); ++ret_i)
      {
        string chars = digit_to_chars[single_dig];
        for(int char_i = 0; char_i < chars.size(); ++char_i)
        {
          tmp_prefix.push_back(ret[ret_i]+chars[char_i]);
        }
      }
      ret.swap(tmp_prefix);
    }
    return ret;
  }

  vector<string> letterCombinations(const string& digits)
  {
    cout << "hi: " << digits << endl;

    return vector<string>{};
  }
};


TEST_CASE("Testing letterCombinations", "[letterCombinations]" )
{
  Solution s;
  
  SECTION("Sec Testing letterCombinationsBrute")
  {
    string in1{"23"};
    vector<string>out1{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
    REQUIRE(s.letterCombinationsBrute(in1)==out1);
  }
}

//auto main()->int
//{
//  return 0;
//}















