/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//http here
#include<iostream>
using std::cout; using std::endl;
#include<cctype>
#include<string>
using std::string;
#include<climits>


static bool RayDebug=false;
#define rcout if(RayDebug) cout 


class Solution {
public:
  // Let's list the cases to take care of:
  // leading whitespace
  // minus sign (if any)
  // iterator through numbers until first none number.
  int myAtoi(string str)
  {
//    rcout << "init str: " << str << '\n';
    long long int str_index=0;
    // First get rid of whitespace
    while(isspace(str[str_index]))
      ++str_index;
//    rcout << "str_index after whitespace: " << str_index << '\n';

    // Now check if is negative and save it.
    // Apparently, we have to take care of cases like -1, +1, -+1, ++1, --1,
    // etc... so we'll loop through all the + and -, and increment and 
    // change the sign accordingly.
    long long int sign = 1;
    // We can do not +-1, so we get rid of minuses first, then pluses, then
    // if we have +-, we would have gotten rid of the plus, not leave the -,
    // resulting in a zero return.
    if(str[str_index]=='-' || str[str_index]=='+')
    {
      if(str[str_index]=='-')
      {
        sign*=-1;
      }
      ++str_index;
    }

//    rcout << "sign is: " << sign << '\n';

    // Now loop through all numbers in str and add it to the result.
    long long int res = 0;

//    rcout << "RRR 0 is: " << ((int)'0') << '\n';
//    rcout << "RRR 9 is: " << ((int)'9') << '\n';
//    rcout << "RRR   is: " << ((int)' ') << '\n';
    while(str_index < str.size() &&
          (str[str_index]>='0' && str[str_index]<='9'))
    {
      long long int ichar = str[str_index]-'0';
      res += ichar;
      res*=10;
//      rcout << "In while, str[i]: " << str[str_index] 
//            << ", ichar: " << ichar
//            << ", res: " << res
//            << '\n';

      // Since the string can represent arbitrarily big numbers, we add a 
      // check in here.
      if((res*sign)/10>INT_MAX)
        return INT_MAX;
      if((res*sign)/10<INT_MIN)
        return INT_MIN;

      ++str_index;
    }
    res = (res*sign)/10;
//    rcout << "final res: "<< res<<", INT_MIN is: " << INT_MIN<<  '\n';
   
    // double check just to make sure 
    if(res>INT_MAX)
      res=INT_MAX;
    if(res<INT_MIN)
      res=INT_MIN;

    return res;
  }
};


TEST_CASE( "atoi", "[atoi]" )
{
  Solution s;
  
  SECTION("Testing C++ atoi")
  {
    REQUIRE(s.myAtoi("123")==123); // first a
    REQUIRE(s.myAtoi(" 123")==123); // first a
    REQUIRE(s.myAtoi(" 123 p")==123); // first a
    REQUIRE(s.myAtoi(" -123 p")==-123); // first a
    REQUIRE(s.myAtoi("p  123 p")==0); // first a
    REQUIRE(s.myAtoi("p  -123p ")==0); // first a
    REQUIRE(s.myAtoi("+1")==1);
    REQUIRE(s.myAtoi("-+1")==0);
    REQUIRE(s.myAtoi("+-1")==0);
    REQUIRE(s.myAtoi("2147483647")==2147483647);
    REQUIRE(s.myAtoi("-2147483647")==-2147483647);
    REQUIRE(s.myAtoi("2147483648")==2147483647);
    REQUIRE(s.myAtoi("-2147483648")==-2147483648);
    REQUIRE(s.myAtoi("9223372036854775809")==2147483647);
  }
}

//auto main()->int
//{
//  return 0;
//}















