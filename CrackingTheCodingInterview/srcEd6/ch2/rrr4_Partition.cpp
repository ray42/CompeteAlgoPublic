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
// 2.4: Partition: Write code to partition a linked list around a value x,
//      such that all nodes less than $x$ come before all nodes greater than
//      or equal to x. If x is contained within the list, the values of 
//      x only need to be after the elements less than x (see below). The 
//      partition element x can appear anywhere in the ``right partition'';
//      it does not need to appear between the left and right partitions.
//
// EXAMPLE:
// Input: 3->5->8-> 5 ->10->2->1 [partition = 5]
// Output:3->1->2->10->5 ->5->8

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
// We maintain two linked lists, one for elements <x and another for 
// elements >= x. Then afterwards, we concatenate the two linked lists.
ListNode* partition(ListNode* head, int x)
{
  // check for nullptr
  if(head == nullptr) return head;

  // I will have two dummy head, this will be used to connect the two lists
  // at the end. Using unique_ptr for these so that they will be 
  // automatically deleted once we return left_dummy->next
  std::unique_ptr<ListNode> left_dummy= std::make_unique<ListNode>(0);
  std::unique_ptr<ListNode> right_dummy= std::make_unique<ListNode>(0);

  // We need two more pointers which does the actual work, pointing to the
  // current node in the two linked lists. We point it to the dummy nodes
  // initially, since we need to add to them, which means to modify the next
  // pointer of the previous node.
  ListNode* left_node = left_dummy.get();   // used for return
  ListNode* right_node = right_dummy.get(); // used for attaching 

  // Now loop through the nodes of head, if it's less than x, attach it
  // to left_node, if it's equal to or greater than head, attach it to 
  // right_node. Remember to null the next pointer of right_node after the
  // loop, since it may point to a node in left_node.
  while(head)
  {
    if(head->data < x)
    {
      left_node->next = head;
      left_node = left_node->next;
    }
    else
    {
      right_node->next = head;
      right_node = right_node->next;
    }
    // increment the head.
    head = head->next;
  }

  // Now null the right_head->next to end the linked list.
  right_node->next = nullptr;

  // join the two linked lists, this involves attaching the 
  // left_node->next=right_dummy->next;
  left_node->next = right_dummy->next;

  // Now we need to return the left head, which is in left_dummy->next;
  return left_dummy->next;
}

// This is used to check the output of partition()
// Check if there is a partition such that once v[i]>= x, then all 
// subsequent v[i] is >= x.
bool check_partition(ListNode* head, int x)
{
  // If the head is null, always return true
  if(head == nullptr) return true;

  // This will trigger true if we have found a v[i] such that v[i]>=x
  bool rightFound = false;

  // Since we are not removing, it's okay to just condition for head, rather
  // than making a dummy node, and condition for dummy->next
  while(head)
  {
    if(rightFound)
    {
      if(head->data < x)
        return false;
    }
    else
    {
      if(head->data >= x)
        rightFound = true;
    }
    head = head->next;
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing check_partition")
  {
    {//1 - empty list
      ListNode* input = buildSinglyLinkedList({});
      REQUIRE(check_partition(input,42)==true);
    }
    {//2.1 - partition before all the list
      ListNode* input = buildSinglyLinkedList({42});
      REQUIRE(check_partition(input,40)==true);
    }
    {//2.2 - partition before all the list
      ListNode* input = buildSinglyLinkedList({42,56,76,100});
      REQUIRE(check_partition(input,40)==true);
    }
    {//2.3 - partition before all the list
      ListNode* input = buildSinglyLinkedList({42,56,76,100});
      REQUIRE(check_partition(input,42)==true); // changed to 42
    }
    {//3.1 - partition after all the list
      ListNode* input = buildSinglyLinkedList({42});
      REQUIRE(check_partition(input,45)==true);
    }
    {//3.2 - partition after all the list - partition being smallest element
      ListNode* input = buildSinglyLinkedList({42,20,30,22});
      REQUIRE(check_partition(input,45)==true);
    }
    {//3.3 - partition after all the list - partition being largest element
      ListNode* input = buildSinglyLinkedList({20,30,22,42});
      REQUIRE(check_partition(input,42)==true); // changed to 42
    }
    {//6.1 - partition in the middle - false
      ListNode* input = buildSinglyLinkedList({1,100,2,99,3,98,4,97});
      REQUIRE(check_partition(input,50)==false);
    }
    {//6.2 - partition in the middle - true
      ListNode* input = buildSinglyLinkedList({1,2,3,4,100,99,98,97});
      REQUIRE(check_partition(input,50)==true);
    }
  }

  SECTION("Sec Testing partition")
  {
    // First check edge cases:
    { // 1 - empty linked list
      int partition_point = 1;
      ListNode* input = buildSinglyLinkedList({});
      ListNode* res = partition(input,partition_point);
      
      REQUIRE(check_partition(res,partition_point));
    }
    { // 2 - one element, partition before the linked list
      int partition_point = 1;
      ListNode* input = buildSinglyLinkedList({3});
      ListNode* res = partition(input,partition_point);

      REQUIRE(check_partition(res,partition_point));
    }
    { // 3 - one element, partition after the linked list
      int partition_point = 5;
      ListNode* input = buildSinglyLinkedList({3});
      ListNode* res = partition(input,partition_point);

      REQUIRE(check_partition(res,partition_point));
    }
    { // 4 - partition in the middle of the linked list
      int partition_point = 5;
      ListNode* input = buildSinglyLinkedList({3,5,8,5,10,2,1});
      ListNode* res = partition(input,5);

      REQUIRE(check_partition(res,partition_point));
    }
  }
}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

