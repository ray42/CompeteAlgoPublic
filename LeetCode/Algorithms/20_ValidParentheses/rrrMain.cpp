/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/valid-parentheses/description
#include<iostream>
using std::cout; using std::endl;
#include<stack>
using std::stack;
#include<string>
using std::string;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;


class Solution
{
public:
  bool isValid(const string& s)
  {
    // Use a stack, put all opening parens in, if we meet a closing paren,
    // we pop and hope it matches the corresponding opening paren.
    stack<char> paren;

    for(const auto& c:s)
    {
      if(c=='(' || c=='[' || c=='{')
      {
        paren.push(c);
      }
      else // it is a closing paren, we see if it matches
      {
        // If this is already empty, return false, since we must match each
        // closing paren with an opening paren, this means we do not have 
        // enough closing parens.
        if(paren.empty()) return false;

        // Match each opening with a closing.
        if(c == ')' && paren.top() != '(')
          return false;
        else if(c == '}' && paren.top() != '{')
          return false;
        else if(c == ']' && paren.top() != '[')
          return false;
        else
          paren.pop();
      }
    }

    // finally, all open parens should be popped out (i.e. matched with a 
    // closing paren).
    return paren.empty();
  }
};


TEST_CASE("Testing isValid", "[isValid]" )
{
  Solution s;
  
  SECTION("Sec Testing isValid")
  {
    RAYDEBUG=true;
    REQUIRE(s.isValid("")==true);
    REQUIRE(s.isValid("()")==true);
    REQUIRE(s.isValid("()[]{}")==true);
    REQUIRE(s.isValid("{[()]}")==true);
    REQUIRE(s.isValid("(]")==false);
    REQUIRE(s.isValid("([)]")==false);
    REQUIRE(s.isValid("((")==false);
    REQUIRE(s.isValid("]")==false);
  }
}

//auto main()->int
//{
//  return 0;
//}















