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

void rotateRight(Matrix<int>& mat)
{
  if(mat.size() == 0 || mat[0].size() != mat.size())
  {
    return ;
  }
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
//  SECTION("Sec Testing ")
//  {
//    // empty matrix
//    Matrix<int> m1={{}};
//    rotateRight(m1);
//    Matrix<int> a1={{}};
//
//    REQUIRE(m1==a1);
//  }
//  SECTION("Sec Testing ")
//  {
//    // empty matrix
//    Matrix<int> m1={{1}};
//    rotateRight(m1);
//    Matrix<int> a1={{1}};
//
//    REQUIRE(m1==a1);
//  }
//  SECTION("Sec Testing ")
//  {
//    // empty matrix
//    Matrix<int> m1={{1,2},
//                    {3,4}};
//    rotateRight(m1);
//    Matrix<int> a1={{}};
//
//    REQUIRE(m1==a1);
//  }
//  SECTION("Sec Testing ")
//  {
//    // empty matrix
//    Matrix<int> m1={{1,2,3},
//                    {4,5,6},
//                    {7,8,9}};
//    rotateRight(m1);
//    Matrix<int> a1={{}};
//
//    REQUIRE(m1==a1);
//  }
  SECTION("Sec Testing ")
  {
    // empty matrix
    Matrix<int> m1={{1,2,3,4},
                    {5,6,7,8},
                    {9,10,11,12},
                    {13,14,15,16}};
    cout << m1[3][1] << '\n';
    rotateRight(m1);
    Matrix<int> a1={{}};

    REQUIRE(m1==a1);
  }

}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

