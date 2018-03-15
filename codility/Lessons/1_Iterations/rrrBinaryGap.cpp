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
// A binary gap within a positive integer N is any maximal sequence of 
// consecutive zeros that is surrounded by ones at both ends in the binary
// representation of N.
//
// For example, number 9 has binary representation 1001 and contains a 
// binary gap of length 2. The number 529 has binary representation 
// 1000010001 and contains two binary gaps: one of length 4 and one of 
// length 3. The number 20 has binary representation 10100 and contains one
// binary gap of length 1. The number 15 has binary representation 1111 and
// has no binary gaps.
// 
// Write a function:
//   int solution(int N);
//
// that, given a positive integer N, returns the length of its longest 
// binary gap. The function should return 0 if N doesn't contain a binary 
// gap.
// 
// For example, given N = 1041 the function should return 5, because N has
// binary representation 10000010001 and so its longest binary gap is of
// length 5.
//
// Assume that:
// N is an integer within the range [1..2,147,483,647].
// 
// Complexity:
// expected worst-case time complexity is O(log(N));
// expected worst-case space complexity is O(1).

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    REQUIRE(func("","")==true);
  }
}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

