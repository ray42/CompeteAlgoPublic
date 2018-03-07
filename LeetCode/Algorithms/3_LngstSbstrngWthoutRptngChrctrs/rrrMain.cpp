/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl;
#include<unordered_set>
using std::unordered_set;
#include<string>
using std::string;
#include<type_traits>
using std::remove_reference;

// https://leetcode.com/problems/longest-substring-without-repeating-characters
// Given a string, find the length of the longest substring without 
// repeating characters.
//
// Examples:
// 
// Given "abcabcbb", the answer is "abc", which the length is 3.
// 
// Given "bbbbb", the answer is "b", with the length of 1.
// 
// Given "pwwkew", the answer is "wke", with the length of 3. Note that the
// answer must be a substring, "pwke" is a subsequence and not a substring.
class Solution {
public:
  int lengthOfLongestSubstring(string s)
  {
    // start at 0 for empty string.
    decltype(s.size()) maxlen = 0;
    auto currentmaxlen = maxlen;

    for(decltype(s.size()) i = 0; i != s.size(); ++i)
    {
      // if we get in here, we have at least one char.
      currentmaxlen = 1;
      std::unordered_set<remove_reference<decltype(s[0])>::type> dups{s[i]};

      for(auto j = i+1; j != s.size(); ++j)
      {
        auto ret = dups.emplace(s[j]);
        if(!ret.second) break;
        ++currentmaxlen;
      }
      maxlen = (currentmaxlen>maxlen) ? currentmaxlen:maxlen;
    }
    return maxlen;
  }
};

auto main(int, char* [])-> int
{
  cout << Solution{}.lengthOfLongestSubstring("abcabcbb") << '\n';
  cout << Solution{}.lengthOfLongestSubstring("bbbbb") << '\n';
  cout << Solution{}.lengthOfLongestSubstring("pwwkew") << '\n';
  return 0;
}

