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
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';

#include<string>
using std::string;
#include<unordered_set>
using std::unordered_set;
#include<vector>
using std::vector;
#include<algorithm> // sort
#include<unordered_set>

#include "./../rayheader.h"



TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    {
//    ListNode* n0 = buildSinglyLinkedList({0,1,2,3,4,5,6});
//    vector<int> sol0{0,1,2,3,4,5,6};
//    ListNode* res0 = removeDups(n0);
//    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
  }
}

//auto main(int argc, char* argv[])->int
//{
//  return 0;
//}















