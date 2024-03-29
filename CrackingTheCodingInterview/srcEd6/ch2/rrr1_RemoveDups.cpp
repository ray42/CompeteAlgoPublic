/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */

// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

#include<iostream>
using std::cout; using std::endl;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Question here.
// 2.1: Remove Dups: Write code to remove duplicates from an unsorted
//      linked list.
//
//FOLLOW UP
//
//How would you solve this problem if a temporary buffer is not allowed?
//
// I would loop through the linked list and place each entry in a hash set. 
// If I cannot insert it into the linked list, then I would delete it.
//
// I don't know what to do if a temporary buffer is not allowed. (See the
// solution below. My mind was trying to do it in O(N), but they sacrifice 
// time for space, so it becomes O(N^2).)
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Hints:
//
// #9: Have you tried a hash table? You should be able to do this in a
//     single pass of the linked list.
// #40: Without extra space, you'll need O(N^2) time. Try using two 
//      pointers, where the second one searches ahead of the first one.

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here
#include "./../rayheader.h"
#include<unordered_set>
#include<memory>

// Def of ListNode: (make sure to write this for practice, then comment it 
// out)
//struct ListNode{
//  int data;
//  ListNode* next;
//  ListNode* prev;
//
//  ListNode(int d):data(d), next(nullptr), prev(nullptr)
//  {}
//};

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here
ListNode* deleteDups(ListNode* head)
{
  // Edge case: If this is an empty linkedlist, just return
  if(head==nullptr)
    return head;

  // Otherwise, there is at least one node. We use a dummy head node so 
  // things are easier to work with.
  std::unique_ptr<ListNode> dummy = std::make_unique<ListNode>(0);
  dummy->next = head;

  // Now we create a hashset, unordered_set, and put in the data, if the 
  // data exists, then we simply delete the node.
  
  std::unordered_set<int> dataset;

  // Insert the first one, which we know exists, then the loop keeps trying 
  // to insert the next one.
  dataset.insert(head->data);

  // A common thing to do with singly linked lists is that we hold the 
  // previous node whilst dealing with the next node, since some operations
  // require access to the previous node, like deleting.
  while(head->next)
  {
    // Try to insert the next value
    const auto& p = dataset.insert(head->next->data);

    // If it is not inserted, then it's a duplicate.
    if(!p.second)
    {
      // To delete the next node, we must reset the head->next pointer. We 
      // know that the next node must exist (since we checked it's data), 
      // and the head->next->next node may exist, or it may be a nullptr. 
      // Thus, the following code works:
      
      // Store the next node for deletion.
      ListNode* tmp = head->next;

      // Hop over the next node:
      head->next = head->next->next;

      // Now free up memory.
      delete tmp; tmp = nullptr;
    }
    else
    {
      // advance the head
      head = head->next;
    }

  }

  // dummy automatically gets deleted.
  return dummy->next;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// This implementation is in-place, but uses two pointers and is O(N^2) time 
// instead of O(N).
ListNode* deleteDupsInplace(ListNode* head)
{
  // First check for empty list
  if(head == nullptr)
    return head;

  // Dummy head
  std::unique_ptr<ListNode> dummy = std::make_unique<ListNode>(0);
  dummy->next = head;

  // First observer pointer. This needs to point to the current one which
  // we need to compare against, which is the head at the moment.
  ListNode* current = head;
  while(current)
  {
    // Get the data to compare
    int data = current->data;

    // For the runner pointer, we need to compare the values after current
    // to delete. But recall that to delete a node in a singly linked list,
    // we need the previous node. Thus we point this to current.
    ListNode* runner = current;

    // while there is a next node to scan
    while(runner->next)
    {
      if(runner->next->data == current->data)
      {
        // Delete the next node
        ListNode* tmp = runner->next;
        runner->next = runner->next->next;
        delete tmp; tmp = 0;
      }
      else
      {
        runner = runner->next;
      }
    }

    current = current->next;
  }

  return dummy->next;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    // First check edge cases: (1) empty linked list and (2) one element:
    { // 1
      ListNode* n0 = buildSinglyLinkedList({});
      std::vector<int> sol0{};
      ListNode* res0 = deleteDups(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    { // 2
      ListNode* n0 = buildSinglyLinkedList({0});
      std::vector<int> sol0{0};
      ListNode* res0 = deleteDups(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    // More edge cases, duplicates at the (3) beginning and at the (4) end
    { // 3
      ListNode* n0 = buildSinglyLinkedList({1,1,1,2,3,4});
      std::vector<int> sol0{1,2,3,4};
      ListNode* res0 = deleteDups(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    { // 4
      ListNode* n0 = buildSinglyLinkedList({1,2,3,4,4,4,4});
      std::vector<int> sol0{1,2,3,4};
      ListNode* res0 = deleteDups(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    // General case - no deletion
    { // 5
      ListNode* n0 = buildSinglyLinkedList({1,2,3,4,5,6,7});
      std::vector<int> sol0{1,2,3,4,5,6,7};
      ListNode* res0 = deleteDups(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    // General case - delete every other element.
    { // 6
      ListNode* n0 = buildSinglyLinkedList({1,1,2,2,3,3,4,4,5,5,6,6});
      std::vector<int> sol0{1,2,3,4,5,6};
      ListNode* res0 = deleteDups(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // in-place two-pointer algo test:
  //////////////////////////////////////////////////////////////////////////
  SECTION("Sec Testing ")
  {
    // First check edge cases: (1) empty linked list and (2) one element:
    { // 1
      ListNode* n0 = buildSinglyLinkedList({});
      std::vector<int> sol0{};
      ListNode* res0 = deleteDupsInplace(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    { // 2
      ListNode* n0 = buildSinglyLinkedList({0});
      std::vector<int> sol0{0};
      ListNode* res0 = deleteDupsInplace(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    // More edge cases, duplicates at the (3) beginning and at the (4) end
    { // 3
      ListNode* n0 = buildSinglyLinkedList({1,1,1,2,3,4});
      std::vector<int> sol0{1,2,3,4};
      ListNode* res0 = deleteDupsInplace(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    { // 4
      ListNode* n0 = buildSinglyLinkedList({1,2,3,4,4,4,4});
      std::vector<int> sol0{1,2,3,4};
      ListNode* res0 = deleteDupsInplace(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    // General case - no deletion
    { // 5
      ListNode* n0 = buildSinglyLinkedList({1,2,3,4,5,6,7});
      std::vector<int> sol0{1,2,3,4,5,6,7};
      ListNode* res0 = deleteDupsInplace(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    // General case - delete every other element.
    { // 6
      ListNode* n0 = buildSinglyLinkedList({1,1,2,2,3,3,4,4,5,5,6,6});
      std::vector<int> sol0{1,2,3,4,5,6};
      ListNode* res0 = deleteDupsInplace(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
  }
}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

