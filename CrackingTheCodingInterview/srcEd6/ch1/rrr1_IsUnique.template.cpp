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

// 1.1 Is Unique: Implement an algorithm to determine if a string has all 
// unique characters. What if you cannot use additional data structures?
bool is_unique_hashtable(const std::string& str)
{
  // Can also do: - but this will insert EVERY element.
  //unordered_set<char> sset(s.begin(),s.end());
  //return sset.size()==s.size();
}

// Assume ASCII, 0-128 chars. But confirm with interviewer
bool is_unique_bool(std::string const & str)
{
}

// inplace
bool is_unique_vector(std::string& str)
{
}

TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    REQUIRE(is_unique_hashtable("qwer")==true);
    REQUIRE(is_unique_hashtable("")==true);
    REQUIRE(is_unique_hashtable("qq")==false);
  }
  SECTION("Sec Testing ")
  {
    REQUIRE(is_unique_bool("qwer")==true);
    REQUIRE(is_unique_bool("")==true);
    REQUIRE(is_unique_bool("qq")==false);
  }
  SECTION("Sec Testing ")
  {
    std::string s1{"qwer"}; 
    std::string s2{""}; 
    std::string s3{"qq"}; 
    REQUIRE(is_unique_vector(s1)==true);
    REQUIRE(is_unique_vector(s2)==true);
    REQUIRE(is_unique_vector(s3)==false);
  }

}

//auto main()->int
//{
//  return 0;
//}

