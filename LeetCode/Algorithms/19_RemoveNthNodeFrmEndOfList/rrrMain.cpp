/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// helper for testing, putting list values into a vector.
vector<int> toVec(ListNode* head)
{
  vector<int> v;
  while(head != NULL)
  {
    v.push_back(head->val);
    head = head->next;
  }
  return v;
}

class Solution {
public:

  // We use a one pass-two pointer solution.
  ListNode* removeNthFromEnd(ListNode* head, int n)
  {
    // if n=2, we have to delete number 4, which means our first pointer
    // needs to be at 3:
    // 1->2->3->4->5-null
    //       ^        ^
    //       1        2
    // thus, our two pointers need to be n+1=3 nodes apart (so there are
    // n nodes in between). Since n is always valid, this should always
    // work.

    // To delete the first node, we need a dummy node pointing to the 
    // head. That way, if we want to delete the 5th node from the end, 
    // we have:
    // D->1->2->3->4->5-null
    // ^                 ^
    // 1                 2
    // there are still n nodes in between, and the two pointers are n+1 
    // nodes apart.
    ListNode* dummy = new ListNode{0};
    dummy->next = head;

    // two pointers
    ListNode* p1 = dummy;
    ListNode* p2 = dummy;

    // Move p1 to n+1 node.
    for(int i=1; i <= n+1; ++i)
    {
      p2 = p2->next;
    }

    // Now move both p1 and p2 until p2 is null, maintaining the gap.
    while(p2 != nullptr)
    {
      p1=p1->next;
      p2=p2->next;
    }

    // Now delete
    p1->next = p1->next->next;

    // don't return the head as it may have been deleted.
    return dummy->next;
  }
};



TEST_CASE("Testing removeNthFromEnd", "[removeNthFromEnd]" )
{
  Solution s;
  
  SECTION("Sec Testing removeNthFromEnd")
  {
    ListNode* l1 = new ListNode{1};
    ListNode* l2 = new ListNode{2};
    ListNode* l3 = new ListNode{3};
    ListNode* l4 = new ListNode{4};
    ListNode* l5 = new ListNode{5};
    l1->next = l2; l2->next = l3; l3->next = l4; l4->next = l5;
    // testing my toVec function
    REQUIRE(toVec(l1)==vector<int>{1,2,3,4,5});
    REQUIRE(toVec(s.removeNthFromEnd(l1,2))==vector<int>{1,2,3,5});// n=2
//    REQUIRE(s.removeNthFromEnd()==vector<int>{1,2,3,4,5});//n=0
//    REQUIRE(s.removeNthFromEnd()==vector<int>{1,2,3,4});  // n=1
//    REQUIRE(s.removeNthFromEnd()==vector<int>{2,3,4,5});  // n=5
    
    // free memory
    delete l1; delete l2; delete l3; delete l4; delete l5;
  }
}

//auto main()->int
//{
//  return 0;
//}















