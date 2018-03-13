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
// 1.7 Rotate Matrix: Given an image represented by an NxN matrix, where 
//     each pixel in the image is 4 bytes, write a method to rotate the 
//     image by 90 degrees. Can you do this in place?
//
// Hints:
//
// #51: Try thinking about it layer by layer. Can you rotate a specific
//      layer?
// #100: Rotating a specific layer would just mean swapping the values in 
//       four arrays. If you were asked to swap the values in two arrays, 
//       could you do this? Can you then extend it to four arrays?
//
// My solution is to work from the outer layers, with base case sizes 2 and
// 1. Let's see what the book has before I code it up.

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here
#include<vector>

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here
template<typename T>
using Matrix = std::vector<std::vector<T> >;

void printMat(const Matrix<int>& mat)
{
  for(const auto& row : mat)
  {
    for(const auto& entry : row)
    {
      std::cout << entry << ' ';
    }
    std::cout << '\n';
  }
}


void rotateRight(Matrix<int>& mat)
{
}
// The key to the above algorithm is to work out the positions of 
// top/left/bottom and right.
// At each layer, we have the two points, first and last.
//
// First is where the layer starts.
// last is last element we loop to, this is n-1, but decreases by 1 per 
// layer, so we subtract the layer.
//
// Layer 0:
// First    last
// ^         ^
// 1 2 3 4 5 6  n=6, loop from [1..6)
//
// Layer 1:
//
//   F     L
//   ^     ^  
// 1 2 3 4 5 6  n=6, loop from [1..5)
//
// So, to reference the first column, we can use "first"
//     to reference the last column, we can use "last"
//
// Thus we have:
// top  = (first,i)
// left = (?    ,first)
// bot  = (last ,?)
// right= (i    ,last)
//
// What about the ?
// 
// If you draw out the matrix, you'll see that ? iterates from last to 1, 
// inclusively. Thus, we need last minus something. This something happens 
// to be offset = i-first, since i = first..<last.
//
// Putting this all together, we have
//
// top  = (first      ,i)
// left = (last-offset,first)
// bot  = (last       ,last-offset)
// right= (i          ,last)

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    // empty matrix
    Matrix<int> m1={{}};
    rotateRight(m1);
    Matrix<int> a1={{}};

    REQUIRE(m1==a1);
  }
  SECTION("Sec Testing ")
  {
    // empty matrix
    Matrix<int> m1={{1}};
    rotateRight(m1);
    Matrix<int> a1={{1}};

    REQUIRE(m1==a1);
  }
  SECTION("Sec Testing ")
  {
    // empty matrix
    Matrix<int> m1={{1,2},
                    {3,4}};
    rotateRight(m1);
    Matrix<int> a1={{3,1},
                    {4,2}};

    REQUIRE(m1==a1);
  }
  SECTION("Sec Testing ")
  {
    // empty matrix
    Matrix<int> m1={{1,2,3},
                    {4,5,6},
                    {7,8,9}};
    rotateRight(m1);
    Matrix<int> a1={{7,4,1},
                    {8,5,2},
                    {9,6,3}};

    REQUIRE(m1==a1);
  }
  SECTION("Sec Testing ")
  {
    // empty matrix
    Matrix<int> m1={{1, 2, 3, 4},
                    {5, 6, 7, 8},
                    {9, 10,11,12},
                    {13,14,15,16}};
    rotateRight(m1);
    Matrix<int> a1={{13,9,5,1},
                    {14,10,6,2},
                    {15,11,7,3},
                    {16,12,8,4}};

    REQUIRE(m1==a1);
  }
  SECTION("Sec Testing ")
  {
    // empty matrix
    Matrix<int> m1={{1, 2, 3, 4, 5},
                    {6, 7, 8, 9, 10},
                    {11,12,13,14,15},
                    {16,17,18,19,20},
                    {21,22,23,24,25}};
    rotateRight(m1);
    Matrix<int> a1={{21,16,11,6,1},
                    {22,17,12,7,2},
                    {23,18,13,8,3},
                    {24,19,14,9,4},
                    {25,20,15,10,5}};
    REQUIRE(m1==a1);
  }
}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

