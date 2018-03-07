/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//web
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

#include "./../leetcodeutility.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/*
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 
      2->1->4->3.

Your algorithm should use only constant space. You may not modify the values
in the list, only nodes itself can be changed.
*/
class Solution {
public:
  ListNode* swapPairs(ListNode* head)
  {
    ListNode* dummy = new ListNode{0};
    dummy->next = head;
    
    if(dummy->next == nullptr || dummy->next->next == nullptr)
      return head;

    ListNode* pre = dummy;
    ListNode* first = head;
    ListNode* second = head->next;
    while(first != nullptr && second != nullptr)
    {
      first->next = second->next;
      second->next = first;
      pre->next = second;

      // reset for next round.
      if(pre->next->next->next == nullptr || 
         pre->next->next->next->next == nullptr)
        break;

      second = pre->next->next->next->next;
      first = pre->next->next->next;
      pre = pre->next->next;
    }
    return dummy->next;
  }
};


TEST_CASE("Testing swapPairs", "[swapPairs]" )
{
  Solution s;
  
  SECTION("Sec Testing swapPairs")
  {
    ListNode* s1 = genList(vector<int>{1,2,3,4});
    ListNode* a1 = genList(vector<int>{2,1,4,3});
    REQUIRE(listToVec(s.swapPairs(s1))==listToVec(a1));
  }
}

//auto main()->int
//{
//  return 0;
//}















