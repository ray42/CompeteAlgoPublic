/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/generate-parentheses/description/
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<algorithm> // sort


// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

#include "./../leetcodeutility.h"

class Solution {
public:

  // check if a string of paren is valid.
  bool valid(const string& parens)
  {
    int balance = 0;
    for(const auto& c:parens)
    {
      if(c=='(')
        ++balance;
      if(c==')')
        --balance;
      
      if(balance < 0) return false;
    }
    return balance==0;
  }
  // Brute force approach: 
  // 1) Generate all 2^{2n}
  // 2) Check if each one if valid.
  // Why 2^{2n}? Because each n represents a pair of chars "(" and ")",
  // and each char can be either "(" or ")", so there are 2^{2n} 
  // combinations.
  //
  // How to check validity? Realise that for a combination to be valid, all
  // that matters is that there is an equal number of opening and closing 
  // parens. If we let "(" be 1 and ")" be -1, then if the partial sum is
  // ever <0, it's not a valid combination, or if there is the total sum of
  // greater than 0 (after adding them all), then it is not valid. 
  vector<string> generateParenthesisBruteIter(int n)
  {
    // First let's try and iterative approach using the technique we've
    // learnt from 17_LetterCombinatOfAPhoneNum

    // we use this as the prefix, and put the chars in here one by one.
    vector<string> all_combinations;
    all_combinations.push_back("");
    const string paren{"()"};

    // Loop through the number chars, there are 2*n chars in total.
    for(int char_i = 0; char_i < 2*n; ++char_i)
    {
      // Now we loop through the previously calculated prefixes
      vector<string> tmp;
      for(int prefix_j = 0; prefix_j < all_combinations.size(); ++prefix_j)
      {
        // Now loop through the number of different combinations i.e "(" or
        // ")" for this char_i and add it to the prefix, so we're 
        // multiplying the number of prefix by the different choices for 
        // this char_i
        for(int paren_choice_k = 0; paren_choice_k < paren.size(); 
            ++paren_choice_k)
        {
          // combine prefix with this choice
          tmp.push_back(all_combinations[prefix_j]+paren[paren_choice_k]);
        }
      }
      all_combinations.swap(tmp);
    }

    //printVec(all_combinations,"All combinations:\n");
    // Now loop through check one and check if it's valid.
    vector<string> valid_combinations;
    for(auto& str:all_combinations)
    {
      if(valid(str))
        valid_combinations.push_back(str);
    }
    return valid_combinations;
  } // generateParenthesisBruteIter

};


TEST_CASE("Testing generateParenthesis", "[generateParenthesis]" )
{
  Solution s;
  
  SECTION("Sec Testing generateParenthesisBrute")
  {
    RAYDEBUG=true;
    vector<string> sol1{"()"};
    vector<string> sol2{"(())","()()"};
    vector<string> sol3{"((()))",
                        "(()())",
                        "(())()",
                        "()(())",
                        "()()()"};
    auto ans1 = s.generateParenthesisBruteIter(1);
    std::sort(ans1.begin(),ans1.end());
    std::sort(sol1.begin(),sol1.end());
    REQUIRE(ans1==sol1);
//    auto ans2 = s.generateParenthesisBrute(2);
//    std::sort(ans2.begin(),ans2.end());
//    std::sort(sol2.begin(),sol2.end());
//    REQUIRE(ans2==sol2);
//    auto ans3 = s.generateParenthesisBrute(3);
//    std::sort(ans3.begin(),ans3.end());
//    std::sort(sol3.begin(),sol3.end());
//    REQUIRE(ans3==sol3);
  }
}

//auto main()->int
//{
//  return 0;
//}















