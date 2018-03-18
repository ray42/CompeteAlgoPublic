/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), https://ray42.com
 * Contact: rayaxiom42 AT gmail DOT com
 * License: GNU AGPLv3
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
// 2.7: Intersection: Given two (singly) linked lists, determine if the two 
//      lists intersect. Return the intersecting node. Note that the 
//      intersection is defined based on reference, not value. That is, if 
//      the kth node of the first linked list is the exact same node (by
//      reference) as the jth node of the second linked list, then they are
//      intersecting.
//
// Hints:
//
// #20: You can do this in O(A+B) time and O(1) additional space. That is, 
//      you do not need a hash table (although you could do it with one).
//
// #45: Examples will help you. Draw a picture of intersecting linked lists 
//      and two equivalent linked lists (by value) that do not intersect.
//
// #55: Focus first on just identifying if there's an intersection.
//
// #65: Observe that two intersecting linked lists will always have the
//      same last node. Once they intersect, all the nodes after that will 
//      be equal.
//
// #76: You can determine if two linked lists intersect by traversing to the
//      end of each and comparing their tails.
//
// #93: Now, you need to find where the linked lists intersect. Suppose the
//      linked lists were the same length. How could you do this?
//
// #111: If the two linked lists were the same length, you could traverse 
//       forward in each until you found an element in common. Now, how do
//       you adjust this for lists of different lengths?
// 
// #120: Try using the difference between the lengths of the two linked 
//       lists.
// 
// #129: If you move a pointer in the longer linked list forward by the
//       difference in lengths, you can then apply a similar approach to the
//       scenario when the linked lists are equal.

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here
#include "./../rayheader.h"
//struct ListNode
//{
//  int data;
//  ListNode* prev;
//  ListNode* next;
//  ListNode(int d):data(d),prev(nullptr),next(nullptr)
//  {}
//};

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here

// We define an intersection as two singly linked lists sharing a node at
// one point. E.g.
//
// 3->1->5->9
//           \->7->2->1
//       4->6/
// Now we define edge cases: If l1 and l2 are null, then they do not share
// a node, thus false is returned. In fact, if either l1 or l2 is null, then
// they cannot share a node, thus false is returned.
//
// Also, the sizes (the in-out parameters l1size and l2size) are only
// reliable if the function returns true.
bool intersection_detection(ListNode* l1, int& l1size, 
                            ListNode* l2, int& l2size)
{
  if(l1==nullptr || l2==nullptr)
    return false;

  // Now both l1 and l2 are not null.

  // l1 and l2 intersecting at some point means that they share the same
  // last node. Thus we now loop through l1 and l2, keeping track of the 
  // size.
  
  // list l1: We start the size = 1, this is okay since we know we must have
  // at least one element. However, we MUST do this since we want to test
  // the l1->next in the while condition. We do this so we don't have to
  // keep track of the previous node when comparing the last node of each 
  // list. If we did not do this, and instead start l1size = 0 and test
  // while(l1), then when the loop ends, l1 is nullptr, and we have no way
  // to get the previous node to test against l2.
  l1size = 1;
  while(l1->next)
  {
    ++l1size;
    l1 = l1->next;
  }

  l2size = 1;
  while(l2->next)
  {
    ++l2size;
    l2 = l2->next;
  }

  // are the last nodes equal?
  return l1 == l2;
}

// return a node which is the intersection of l1 and l2, in the below 
// example, it will return the node corresponding to value 7. Is no 
// intersection exists, then nullptr is returned.
// 3->1->5->9
//           \->7->2->1
//       4->6/
ListNode* get_intersection(ListNode* l1, ListNode* l2)
{
  // check if there is an intersection, if there is, we need the size.
  int l1size = 0; 
  int l2size = 0;
  if(!intersection_detection(l1,l1size,l2,l2size))
  {
    return nullptr;
  }

  // Now we know that there is a intersection, and we have the lengths, 
  // we find the difference and the longer one, then advance through the
  // longer one. See the book for more details.

  // which is longer? l1 or l2?
  ListNode* longer = nullptr;
  ListNode* shorter = nullptr;
  if(l1size > l2size)
  {
    longer = l1;
    shorter = l2;
  }
  else
  {
    longer = l2;
    shorter = l1;
  }

  // How many nodes to advance through the longer?
  int nnodes_to_adv = (l1size > l2size) ? l1size-l2size:l2size-l1size;

  // advance through the longer one.
  while(nnodes_to_adv > 0)
  {
    longer = longer->next;
    --nnodes_to_adv;
  }

  // Iterate through longer and shorter and return the equal node.
  while(longer != shorter)
  {
    longer = longer->next;
    shorter = shorter->next;
  }

  // They are the same now.
  return longer;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
SECTION("Sec Testing intersection_detection")
{
{//1.1 both l1==l2==null
  ListNode* l1 = nullptr;
  ListNode* l2 = nullptr;
  int l1size = 0;
  int l2size = 0;
  REQUIRE(intersection_detection(l1,l1size,l2,l2size)==false);
}
{//1.2 both l1==null and l2!=null
  ListNode* l1 = nullptr;
  ListNode* l2 = new ListNode{3};
  int l1size = 0;
  int l2size = 0;
  REQUIRE(intersection_detection(l1,l1size,l2,l2size)==false);
}
{//1.3 both l1==null and l2!=null
  ListNode* l1 = new ListNode{3};
  ListNode* l2 = nullptr;
  int l1size = 0;
  int l2size = 0;
  REQUIRE(intersection_detection(l1,l1size,l2,l2size)==false);
}
{//2.1 one node, not equal
  ListNode* l1 = new ListNode{3};
  ListNode* l2 = new ListNode{3};
  int l1size = 0;
  int l2size = 0;
  REQUIRE(intersection_detection(l1,l1size,l2,l2size)==false);
}
{//2.1 one node, equal (intersect on one node)
  ListNode* l1 = new ListNode{3};
  ListNode* l2 = l1;
  int l1size = 0;
  int l2size = 0;
  REQUIRE(intersection_detection(l1,l1size,l2,l2size)==true);
  REQUIRE(l1size==1);
  REQUIRE(l2size==1);
}
{//2.2 general, from the CTCI book example:
  // 11 12 13 14
  // 3->1->5->9   15 16 17
  //           \->7->2->1
  //       4->6/
  ListNode* l11 = new ListNode{3};
  ListNode* l12 = new ListNode{1};
  ListNode* l13 = new ListNode{5};
  ListNode* l14 = new ListNode{9};
  ListNode* l15 = new ListNode{15};
  ListNode* l16 = new ListNode{16};
  ListNode* l17 = new ListNode{17};
  // link them
  l11->next = l12;
  l12->next = l13;
  l13->next = l14;
  l14->next = l15;
  l15->next = l16;
  l16->next = l17;

  ListNode* l21 = new ListNode{4};
  ListNode* l22 = new ListNode{6};
  l21->next = l22;
  l22->next = l15; // link back to l1

  int l1size = 0;
  int l2size = 0;
  REQUIRE(intersection_detection(l11,l1size,l21,l2size)==true);
  REQUIRE(l1size==7);
  REQUIRE(l2size==5);
}
}// end section

SECTION("Sec Testing get_intersection")
{
{//1.1 both l1==l2==null
  ListNode* l1 = nullptr;
  ListNode* l2 = nullptr;
  REQUIRE(get_intersection(l1,l2)==nullptr);
}
{//1.2 both l1==null and l2!=null
  ListNode* l1 = nullptr;
  ListNode* l2 = new ListNode{3};
  REQUIRE(get_intersection(l1,l2)==nullptr);
}
{//1.3 both l1==null and l2!=null
  ListNode* l1 = new ListNode{3};
  ListNode* l2 = nullptr;
  REQUIRE(get_intersection(l1,l2)==nullptr);
}
{//2.1 one node, not equal
  ListNode* l1 = new ListNode{3};
  ListNode* l2 = new ListNode{3};
  REQUIRE(get_intersection(l1,l2)==nullptr);
}
{//2.1 one node, equal (intersect on one node)
  ListNode* l1 = new ListNode{3};
  ListNode* l2 = l1;
  REQUIRE(get_intersection(l1,l2)==l1);
}
{//2.2 general, from the CTCI book example:
  // 11 12 13 14
  // 3->1->5->9   15 16 17
  //           \->7->2->1
  //       4->6/
  //
  // We do three variations:
  // 1) intersection in the middle as the above example.
  // 2) intersect l2 with the first node in l1
  // 3) intersect l2 with the last node in l1
  ListNode* l11 = new ListNode{3};
  ListNode* l12 = new ListNode{1};
  ListNode* l13 = new ListNode{5};
  ListNode* l14 = new ListNode{9};
  ListNode* l15 = new ListNode{15};
  ListNode* l16 = new ListNode{16};
  ListNode* l17 = new ListNode{17};
  // link them
  l11->next = l12;
  l12->next = l13;
  l13->next = l14;
  l14->next = l15;
  l15->next = l16;
  l16->next = l17;

  ListNode* l21 = new ListNode{4};
  ListNode* l22 = new ListNode{6};
  l21->next = l22;
  l22->next = l15; // link back to l1

  // intersection at l15
  REQUIRE(get_intersection(l11,l21)==l15);
}
{//2.2 general, from the CTCI book example:
  // 11 12 13 14
  // 3->1->5->9   15 16 17
  //           \->7->2->1
  //       4->6/
  //
  // We do three variations:
  // 1) intersection in the middle as the above example.
  // 2) intersect l2 with the first node in l1
  // 3) intersect l2 with the last node in l1
  ListNode* l11 = new ListNode{3};
  ListNode* l12 = new ListNode{1};
  ListNode* l13 = new ListNode{5};
  ListNode* l14 = new ListNode{9};
  ListNode* l15 = new ListNode{15};
  ListNode* l16 = new ListNode{16};
  ListNode* l17 = new ListNode{17};
  // link them
  l11->next = l12;
  l12->next = l13;
  l13->next = l14;
  l14->next = l15;
  l15->next = l16;
  l16->next = l17;

  ListNode* l21 = new ListNode{4};
  ListNode* l22 = new ListNode{6};
  l21->next = l22;
  l22->next = l11; // link back to l1

  // intersection is at first node in l1: l11
  REQUIRE(get_intersection(l11,l21)==l11);
}
{//2.2 general, from the CTCI book example:
  // 11 12 13 14
  // 3->1->5->9   15 16 17
  //           \->7->2->1
  //       4->6/
  //
  // We do three variations:
  // 1) intersection in the middle as the above example.
  // 2) intersect l2 with the first node in l1
  // 3) intersect l2 with the last node in l1 <- THIS
  ListNode* l11 = new ListNode{3};
  ListNode* l12 = new ListNode{1};
  ListNode* l13 = new ListNode{5};
  ListNode* l14 = new ListNode{9};
  ListNode* l15 = new ListNode{15};
  ListNode* l16 = new ListNode{16};
  ListNode* l17 = new ListNode{17};
  // link them
  l11->next = l12;
  l12->next = l13;
  l13->next = l14;
  l14->next = l15;
  l15->next = l16;
  l16->next = l17;

  ListNode* l21 = new ListNode{4};
  ListNode* l22 = new ListNode{6};
  l21->next = l22;
  l22->next = l17; // link back to l1

  // intersection is at last node in l1: l17
  REQUIRE(get_intersection(l11,l21)==l17);
}
{//3 general, NO INTERSECTION:
  ListNode* l11 = new ListNode{3};
  ListNode* l12 = new ListNode{1};
  ListNode* l13 = new ListNode{5};
  ListNode* l14 = new ListNode{9};
  ListNode* l15 = new ListNode{15};
  ListNode* l16 = new ListNode{16};
  ListNode* l17 = new ListNode{17};
  // link them
  l11->next = l12;
  l12->next = l13;
  l13->next = l14;
  l14->next = l15;
  l15->next = l16;
  l16->next = l17;

  ListNode* l21 = new ListNode{4};
  ListNode* l22 = new ListNode{6};
  l21->next = l22;

  REQUIRE(get_intersection(l11,l21)==nullptr);
}

}// end section

} // end test case

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

