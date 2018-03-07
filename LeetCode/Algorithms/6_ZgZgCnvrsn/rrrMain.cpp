/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/zigzag-conversion/description/
#include<iostream>
using std::cout; using std::endl;
#include<string>
using std::string;


static bool RayDebug=false;


// NOTE: The majority of my workings out is on paper. I'll need to scan this
// into the folder or type it up.
class Solution {
public:
  string convert(string s, int numRows)
  {
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13
    // 0 1 2 3 4 5 6 7 8 9 q  w  e  r
    //
    //N=3
    //0   4   8     12
    // 1 3 5 7 9  11  13
    //  2   6   10
    //row 0  : 2(N-1)*k (from looking at the top row)
    //row n-1: N-1
    //
    //N=4
    // 0     6      12
    //  1   5 7   11  13
    //   2 4   8 10
    //    3     9
    //
    //row 0  : 2(N-1)*k (from looking at the top row)
    //row n-1: 
    if(numRows==1) return s;

    string ret="";
    // Loop through the rows 
    for(int rowi = 0; rowi<numRows; ++rowi)
    {
//      cout << "rowi: " << rowi << '\n';
      int k=0;
      while(true)
      {
//        cout << "in while, rowi = " << rowi <<'\n';
        int s_index=0;
        if(rowi==0)
        {
//          cout << "rowi=0, BREAK\n";
//          break;
          s_index = 2*(numRows-1)*k+rowi;
//          cout << "if(rowi==0), s_index = " << s_index << '\n';
          if(s_index >= s.size()) break;
          ret+=s[s_index];
//          cout << s[s_index] <<'\n';
          ++k;
        }

        if(rowi==(numRows-1)){
//          cout << "rowi= numRows-1, BREAK\n";
//          break;
          s_index = 2*(numRows-1)*k+rowi;
//          cout << "if(rowi==numRows-1), s_index = " << s_index << '\n';
          if(s_index >= s.size()) break;
          ret+=s[s_index];

//          cout << s[s_index] << '\n';
          ++k;
        }

        if(rowi>=1 && rowi <=numRows-2)
        {
          // first char
          s_index = 2*(numRows-1)*k+rowi;
//          cout << "1char s_index: " << s_index << '\n';
          if(s_index >= s.size())
          {
//            cout << "BREAKING\n";
            break;
          }
//          cout << s[s_index] << '\n';
          ret+=s[s_index];

          // 2nd char
          s_index = 2*(numRows-1)*(k+1)-rowi;
//          cout << "2char s_index: " << s_index << '\n';
          if(s_index >= s.size())
          {
//            cout << "BREAKING\n";
            break;
          }
          ret+=s[s_index];
//          cout << s[s_index] << '\n';

          ++k;
        }
      } // while(true)
//      cout << '\n';
    }
    
    return ret;
  }
};


TEST_CASE( "Test convert", "[convert]" )
{
  Solution s;
  
  SECTION("Testing convert")
  {
    REQUIRE(s.convert("PAYPALISHIRING",3)=="PAHNAPLSIIGYIR"); // From GFG
    REQUIRE(s.convert("0123456789qwer",1)=="0123456789qwer"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",2)=="02468qe13579wr"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",3)=="048e13579wr26q"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",4)=="06e157wr248q39"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",5)=="0817926q35wr4e"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",6)=="0q19w28e37r465"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",7)=="0e1wr2q3948576"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",8)=="01r2e3w4q59687"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",9)=="0123r4e5w6q798"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",10)=="012345r6e7w8q9"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",11)=="01234567r8e9wq"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",12)=="0123456789rqew"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",13)=="0123456789qwre"); // From spreadsheet
    REQUIRE(s.convert("0123456789qwer",14)=="0123456789qwer"); // From spreadsheet
  }
}

//auto main()->int
//{
//  return 0;
//}















