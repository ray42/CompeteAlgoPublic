/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/merge-two-sorted-lists/description/
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<string>
using std::string;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

#include"./../leetcodeutility.h"

class Solution {
public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
  {
    ListNode* dummy = new ListNode{0};
    ListNode* tmp = dummy;

    while(l1!=nullptr && l2 != nullptr)
    {
      if(l1->val < l2->val)
      {
        tmp->next = l1;
        tmp = tmp->next;
        l1 = l1->next;
      }
      else
      {
        tmp->next = l2;
        tmp = tmp->next;
        l2 = l2->next;
      }
    }
    if(l1 != nullptr)
    {
      tmp->next = l1;
    }
    if(l2 != nullptr)
    {
      tmp->next = l2;
    }
    return dummy->next;
  }
};


TEST_CASE("Testing mergeTwoLists", "[mergeTwoLists]" )
{
  Solution s;
  
  SECTION("Sec Testing mergeTwoLists")
  {
    RAYDEBUG=true;
    // Input: 1->2->4, 1->3->4
    // Output: 1->1->2->3->4->4
    ListNode* l1 = genList(vector<int>{1,2,4});
    ListNode* l2 = genList(vector<int>{1,3,4});
    REQUIRE(listToVec(s.mergeTwoLists(l1,l2))==vector<int>{1,1,2,3,4,4});
  }
}

//auto main()->int
//{
//  return 0;
//}















