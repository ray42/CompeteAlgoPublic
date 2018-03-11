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

#include<string>
#include<algorithm>
#include<cstddef> // size_t
#include<unordered_map>

// 1.2 Check Permutation: Given two strings, write a method to decide if one
// is a permutation of the other.

// What assumptions are made? About case sensitivity and whitespace?
// What the time and space complexity of each algo?
// What are the advantages f each algo?

bool is_permutation_sort(std::string s1, std::string s2)
{
}

bool is_permutation_vec(const std::string& s1, const std::string& s2)
{
}

bool is_permutation_hash(const std::string& s1, const std::string& s2)
{
}

TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    REQUIRE(is_permutation_sort("","")==true);
    REQUIRE(is_permutation_sort("","q")==false);
    REQUIRE(is_permutation_sort("q","")==false);
    REQUIRE(is_permutation_sort("q","q")==true);
    REQUIRE(is_permutation_sort("qq","q")==false);
    REQUIRE(is_permutation_sort("q","qq")==false);
    REQUIRE(is_permutation_sort("qq","qq")==true);
    REQUIRE(is_permutation_sort("qw","qw")==true);
    REQUIRE(is_permutation_sort("qw","wq")==true);
    REQUIRE(is_permutation_sort("qw","wqw")==false);
  }
  SECTION("Sec Testing ")
  {
    REQUIRE(is_permutation_vec("","")==true);
    REQUIRE(is_permutation_vec("","q")==false);
    REQUIRE(is_permutation_vec("q","")==false);
    REQUIRE(is_permutation_vec("q","q")==true);
    REQUIRE(is_permutation_vec("qq","q")==false);
    REQUIRE(is_permutation_vec("q","qq")==false);
    REQUIRE(is_permutation_vec("qq","qq")==true);
    REQUIRE(is_permutation_vec("qw","qw")==true);
    REQUIRE(is_permutation_vec("qw","wq")==true);
    REQUIRE(is_permutation_vec("qw","wqw")==false);
  }
  SECTION("Sec Testing ")
  {
    REQUIRE(is_permutation_hash("","")==true);
    REQUIRE(is_permutation_hash("","q")==false);
    REQUIRE(is_permutation_hash("q","")==false);
    REQUIRE(is_permutation_hash("q","q")==true);
    REQUIRE(is_permutation_hash("qq","q")==false);
    REQUIRE(is_permutation_hash("q","qq")==false);
    REQUIRE(is_permutation_hash("qq","qq")==true);
    REQUIRE(is_permutation_hash("qw","qw")==true);
    REQUIRE(is_permutation_hash("qw","wq")==true);
    REQUIRE(is_permutation_hash("qw","wqw")==false);
  }
}

//auto main()->int
//{
//
//  return 0;
//}

