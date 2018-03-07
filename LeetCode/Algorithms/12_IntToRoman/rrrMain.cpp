/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/integer-to-roman/description/
#include<iostream>
using std::cout; using std::endl;
#include<string>
using std::string;
#include<array>

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

void appendString(size_t n, const string& str_to_add, string& s)
{
  for(size_t i=0; i<n; ++i)
  {
    s+=str_to_add;
  }
}

class Solution {
public:
  string intToRoman(int num)
  {
    string ret{};

    while(num!=0)
    {
      if(num>=1000)
      {
        ret.append(num/1000,'M');
        num%=1000;
      }
      else if(num >= 900)
      {
        appendString(num/900,"CM",ret);
        num%=900;
      }
      else if(num >= 500)
      {
        ret.append(num/500,'D');
        num%=500;
      }
      else if(num >= 400)
      {
        appendString(num/400,"CD",ret);
        num%=400;
      }
      else if(num >= 100)
      {
        ret.append(num/100,'C');
        num%=100;
      }
      else if(num >= 90)
      {
        appendString(num/90,"XC",ret);
        num%=90;
      }
      else if(num >= 50)
      {
        ret.append(num/50,'L');
        num%=50;
      }
      else if(num >= 40)
      {
        appendString(num/40,"XL",ret);
        num%=40;
      }
      else if(num >= 10)
      {
        ret.append(num/10,'X');
        num%=10;
      }
      else if(num >=9)
      {
        appendString(num/9,"IX",ret);
        num%=9;
      }
      else if(num >= 5)
      {
        ret.append(num/5,'V');
        num%=5;
      }
      else if(num >= 4)
      {
        // If I get here, it must be equal to 4, so just append IV and set
        // num = 0
        appendString(1,"IV",ret);
        num=0;
      }
      else
      {
        // Get here if only it is 3 or less, so no need to take mod or 
        // anything else.
        ret.append(num,'I');
        num = 0;
      }
    }
    return ret;
  }

  // Trying again with a more elegant approach.
  // See: https://www.geeksforgeeks.org/converting-decimal-number-lying-between-1-to-3999-to-roman-numerals/
  // Another Approach:
  // In this approach we have to first observe the problem. The number 
  // given in problem statement can be maximum of 4 digits. The idea to 
  // solve this problem is:
  // 
  // 1) Divide the given number into digits at different places like unit's, 
  //    ten's, hundred's or thousand's.
  // 2) Starting from the thousand's place print the corresponding roman 
  //    value. For example, if the digit at thousand's place is 3 then print
  //    the roman equivalent of 3000, which is MMM.
  // 3) Repeat the second step until we reach one's place.
  // Example:
  // Suppose the input number is 3549. So, starting from thousand's place we
  // will start printing the roman equivalent. In this case we will print in
  // the order as given below:
  // 
  // First: Roman equivalent of 3000: MMM
  // Second: Roman equivalent of 500: D
  // Third: Roman equivalent of 40: XL
  // Fourth: Roman equivalent of 9: IX
  // So, the output will be: MMMDXLIX
  string intToRomanAgain(int num)
  {
    // thousands: 0000, 1000, 2000, 3000
    const std::array<string,4> m{"","M","MM","MMM"};
    // hundreds: 000, 100, 200, 300, 400, 500, 600, 700, 800, 900
    const std::array<string,10>c{"","C","CC","CCC","CD","D","DC","DCC",
                                 "DCCC","CM"};
    // tens: 00, 10, 20, 30, 40, 50, 60, 70, 80, 90
    const std::array<string,10>x{"","X","XX","XXX","XL","L","LX","LXX",
                                 "LXXX","XC"};
    // units: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    const std::array<string,10>i{"","I","II","III","IV","V","VI","VII",
                                 "VIII","IX"};

    // This is correct, but I'll put it all in the return statement,
    // maybe it's more efficient.
//    // convert to roman numerals, first see how many thousands there are:
//    string thou = m[num/1000];
//    // Now get the remainder div by 1000 and see how many 100s
//    string hund = c[(num%1000)/100];
//    // Now we want to see how many 10s there are. To do that, we first have
//    // to get the remainder by 100, hence the %100, then divide this by 10
//    // to get how many tens.
//    string tens = x[(num%100)/10];
//    // to get how many 1s, we simply mod 10, no need to divide by 1.
//    string ones = i[num%10];
//
//    string ret = thou+hund+tens+ones;
//    return ret;
    return m[num/1000]+c[(num%1000)/100]+x[(num%100)/10]+i[num%10];
  }
};


TEST_CASE( "Testing intToRoman", "[intToRoman]" )
{
  Solution s;
  
  SECTION("Sec Testing intToRoman")
  {
    RAYDEBUG=true;
    REQUIRE(s.intToRoman(3549)=="MMMDXLIX");
    REQUIRE(s.intToRoman(1994)=="MCMXCIV");
    REQUIRE(s.intToRoman(901)=="CMI");
    REQUIRE(s.intToRoman(832)=="DCCCXXXII");
    REQUIRE(s.intToRoman(800)=="DCCC");
    REQUIRE(s.intToRoman(1)=="I");
    REQUIRE(s.intToRoman(2)=="II");
    REQUIRE(s.intToRoman(3)=="III");
    REQUIRE(s.intToRoman(4)=="IV");
    REQUIRE(s.intToRoman(5)=="V");
    REQUIRE(s.intToRoman(6)=="VI");
    REQUIRE(s.intToRoman(7)=="VII");
    REQUIRE(s.intToRoman(8)=="VIII");
    REQUIRE(s.intToRoman(9)=="IX");
    REQUIRE(s.intToRoman(10)=="X");
  }
  
  SECTION("Sec Testing intToRomanAgain")
  {
    RAYDEBUG=true;
    REQUIRE(s.intToRomanAgain(3549)=="MMMDXLIX");
    REQUIRE(s.intToRomanAgain(1994)=="MCMXCIV");
    REQUIRE(s.intToRomanAgain(901)=="CMI");
    REQUIRE(s.intToRomanAgain(832)=="DCCCXXXII");
    REQUIRE(s.intToRomanAgain(800)=="DCCC");
    REQUIRE(s.intToRomanAgain(1)=="I");
    REQUIRE(s.intToRomanAgain(2)=="II");
    REQUIRE(s.intToRomanAgain(3)=="III");
    REQUIRE(s.intToRomanAgain(4)=="IV");
    REQUIRE(s.intToRomanAgain(5)=="V");
    REQUIRE(s.intToRomanAgain(6)=="VI");
    REQUIRE(s.intToRomanAgain(7)=="VII");
    REQUIRE(s.intToRomanAgain(8)=="VIII");
    REQUIRE(s.intToRomanAgain(9)=="IX");
    REQUIRE(s.intToRomanAgain(10)=="X");
  }

}

//auto main()->int
//{
//  return 0;
//}















