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

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;
#include "./../leetcodeutility.h"
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';


class Solution {
public:
  bool hasCycle(ListNode *head)
  {
    // This is called Floyd's Cycle-Finding Algorithm
    // https://www.youtube.com/watch?v=Aup0kOWoMVg
    // We start with two pointers, both at the same position (the head).
    // The fast pointer moves 2 steps per iteration and the slow pointer
    // moves 1 step per iteration.
    // If they meet, it will be cause there is a cycle.
    ListNode* slow = head;
    ListNode* fast = head;

    // we need slow to not be null for us to be able to advance it.
    // To advance fast, we need both fast and it's next node to not be
    // null, so we can advance it by 2 steps.
    while(slow && fast && fast->next)
    {
      // Advance the pointers as described above.
      slow = slow->next;
      fast = fast->next->next;

      // Check if they are the same
      if(slow == fast)
        return true;
    }
    return false;
  }
};


TEST_CASE("Testing ", "[]" )
{
  Solution s;
  
  SECTION("Sec Testing ")
  {
    REQUIRE(s.FOO()==);
  }
}

//auto main()->int
//{
//  return 0;
//}















