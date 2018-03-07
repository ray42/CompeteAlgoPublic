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

bool is_unique_hashtable(const string& s)
{
  unordered_set<char> sset(s.begin(),s.end());
  return sset.size()==s.size();
}

// No extra space used, treating s as a vector.
bool is_unique_vector(string& s)
{
  std::sort(s.begin(),s.end());
  for(int i  = 1; i < s.size(); ++i)
  {
    if(s[i-1]==s[i])
      return false;
  }
  return true;
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
    string s1{"qwer"}; 
    string s2{""}; 
    string s3{"qq"}; 
    REQUIRE(is_unique_vector(s1)==true);
    REQUIRE(is_unique_vector(s2)==true);
    REQUIRE(is_unique_vector(s3)==false);
  }

}

//auto main(int argc, char* argv[])->int
//{
//  return 0;
//}















