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
#include<string>
using std::string;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';

// e.g. s = aabcccccaaa become a2b1c5a3
string strCompress(string s)
{
  if(s.empty())
    return "";

  s+="$";
  string compressed_str = "";
  int count = 0;
  int p1 = 0;
  int p2 = 0;
  while(p2 < s.size())
  {
    if(s[p1]==s[p2])
    {
      ++count;
      ++p2;
    }
    else
    {
      compressed_str+=s[p1]+std::to_string(count);
      p1 = p2;
      count = 0;
    }
  }
  // Remember that we added a sentinel at the end. Time to remove it.
  s.pop_back();
  return s.size() < compressed_str.size()? s : compressed_str;
}


TEST_CASE("Testing strCompress", "[strCompress]" )
{
  SECTION("Sec Testing strCompress")
  {
    {
    string s1{"aabcccccaaa"};
    string a1{"a2b1c5a3"};
    REQUIRE(strCompress(s1)==a1);
    }
    {
    string s1{""};
    string a1{""};
    REQUIRE(strCompress(s1)==a1);
    }
    {
    string s1{"a"};
    string a1{"a"};
    REQUIRE(strCompress(s1)==a1);
    }

  }
}

//auto main(int argc, char* argv[])->int
//{
//  return 0;
//}

