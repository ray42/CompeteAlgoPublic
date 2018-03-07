/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/longest-palindromic-substring/description/
#include<iostream>
using std::cout; using std::endl;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<algorithm> // std::max

static bool RayDebug=false;

// This is an incorrect attempt. I will now try to use a dp table, see below
void solveLPSRay(const string& str)
{
  vector<int> LPS(str.size(),1);
  LPS[0]=1;
  int maxLPSi = -1;
  int maxLPS = -1;
  for(int j = 1; j < static_cast<int>(str.size()); ++j)
  {
    cout << "j=" << j << '\n';
    if(j-LPS[j-1]-1 >= 0)
    {
      cout << "j-LPS[j-1]-1: " << j-LPS[j-1]-1 << '\n';
      if(str[j-LPS[j-1]-1] == str[j])
      {
        if(LPS[j-1]+2 >= maxLPS)
        {
          LPS[j] = LPS[j-1]+2;
          maxLPS = LPS[j];
          maxLPSi=j;
        }
      }
    }
  }
  cout << str << '\n';
  cout << "maxLPSi: " << maxLPSi << '\n';
  cout << "LPS[maxLPSi-LPS[maxLPSi-1]]: " << LPS[maxLPSi-LPS[maxLPSi-1]]
       << ", LPS[maxLPSi]: " << LPS[maxLPSi] << '\n';
  cout << str.substr(LPS[maxLPSi-LPS[maxLPSi-1]], LPS[maxLPSi]) << '\n';
}

template<typename T>
using Grid2d = vector<vector<int>>;

void printGrid(Grid2d<int>& g, const string& str="")
{
  if(!str.empty()) cout << str;

  for(const auto& r:g)
  {
    for(const auto& i:r)
    {
      cout << i << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}

void solveLPSDP(const string& str)
{
  auto N = static_cast<int>(str.size());
  Grid2d<int> grid(N,vector<int>(N,0));

  // base case when one char
  for(int i = 0; i < N; ++i)
    grid[i][i]=1;

  int maxLPSLen=1;
  int maxi=0;
  int maxj=0;
  // Start at length l = 2
  for(int l=2; l < N; ++l)
  {
    // Loop through rows, i=0..N-l
    for(int i = 0; i < (N-l); ++i)
    {
      // calculate j
      int j = l-i+1;

      // if l=2, check if palindrome
      if(l==2 && str[i]==str[j])
      {
        grid[i][j]=2;
      }
      else
      {
        if(str[i]==str[j] && grid[i+1][j-1] > 0)
        {
          grid[i][j]= 2+grid[i+1][j-1];
        }
      }

      // Update if LPS.
      if(grid[i][j]>maxLPSLen)
      {
        maxLPSLen=grid[i][j];
        maxi = i; maxj = j;
      }
    }
  }
  cout << str.substr(maxi, maxj) << '\n';
}


class Solution {
public:
  string longestPalindrome(string s)
  {
    auto N = static_cast<int>(s.size());
    Grid2d<int> grid(N,vector<int>(N,0));

    // base case when one char
    for(int i = 0; i < N; ++i)
      grid[i][i]=1;

//    printGrid(grid, "Init:\n");
  
    int maxLPSLen=1;
    int maxi=0;
    int maxj=0;
    //cout << "N: " << N << '\n';
    // Start at length l = 2
    for(int l=2; l <= N; ++l)
    {
      // Loop through rows, i=0..N-l
      for(int i = 0; i < (N-l+1); ++i)
      {
        // calculate j
        int j = l+i-1;
        
//        cout << "Doing for l=" << l << ", i=" << i << ", j=" << j << '\n';
  
        // if l=2, check if palindrome
        if(l==2 && s[i]==s[j])
        {
          grid[i][j]=2;
        }
        else
        {
          if(s[i]==s[j] && grid[i+1][j-1] > 0)
          {
            grid[i][j]= 2+grid[i+1][j-1];
          }
        }
  
        // Update if LPS.
        if(grid[i][j]>maxLPSLen)
        {
          maxLPSLen=grid[i][j];
          maxi = i; maxj = j;
        }
      }
    }

//    printGrid(grid, "After:\n");
//    cout << "maxi: " << maxi << ", maxj: " << maxj << '\n';
    return s.substr(maxi, (maxj-maxi+1));
  }

  // output the longest palindromic substring using O(1) space (instead of)
  // O(N^2) space. The idea is to expand around the center of each 
  // palindrome. Each char is a palindrome of length 1.
  // E.g. if we have a string s=[abbc], then we can expand about 
  // 0  1   2  3   4  5   6
  // a, ab, b, bb, b, bc, c
  //
  // we can think of this as putting splits in the string:
  // 0123456
  // a#b#b#c
  //
  // Thus there are n (num single chars) + n-1 (number of in-betweens)= 2n-1
  // centres.
  //
  // For each centre, we expand left and right, testing if the chars are the
  // same. First we write the expand function, it will return the length of
  // the palindrome about a center.
  int expandAroundCentre(const string& s, int lefti, int rightj)
  {
    // Length of s
    auto N = static_cast<int>(s.size());

//    cout << "s: " << s 
//         << ", N: "<<N<<", i: " << lefti << ", j: " << rightj << '\n';

    // Only do this if rightj < N, we may end up with rightj=N for the last
    // call of expandAroundCentre
    if(lefti >=0 && rightj<N)
    {
      // Function to find the length of the palindrome expanded around ij.
      // if i==j, then we are expanding around a single char, if j=i+1, when
      // we are expanding around 2 chars.
      //
      // For the two cases, if lefti==rightj, then we can simply expand:
      if(lefti==rightj)
      {
//        cout << "Got in lefti==rightj\n";
        while(lefti>=0 && rightj<N && s[lefti]==s[rightj])
        {
          --lefti; // move left
          ++rightj; // move right
        }
//        cout << "After, i: " << lefti << ", j: " << rightj << '\n';
//        cout << "rightj-lefti+1 = " << rightj-lefti+1 <<'\n';
        // the range [lefti,rightj] (INCLUSIVE) is a palindrome. However, 
        // when the algorithm ends, we actually have [lefti-1,rightj+1] 
        // (since we expand until the first invalid two indices), that is, 
        // we have 2 more than we need. So instead of rightj-lefti+1, we do
        // rightj-lefti+1-2=rightj-lefti-1
        return rightj-lefti-1;
      }
      // Otherwise, if we expand around, say bb, then we're okay. However,
      // expanding about ab should return 0.
      else if(s[lefti]==s[rightj])
      {
        while(lefti>=0 && rightj<N && s[lefti]==s[rightj])
        {
          --lefti; // move left
          ++rightj; // move right
        }
        // the range [lefti,rightj] (INCLUSIVE) is a palindrome. However, when
        // the algorithm ends, we actually have [lefti-1,rightj+1] 
        // (since we expand until the first invalid two indices), that is, we
        // have 2 more than we need. So instead of rightj-lefti+1, we do
        // rightj-lefti+1-2=rightj-lefti-1
        return rightj-lefti-1;
      }
      else
      {
        return 0;
      }
    }
    return -1;
  }

  string longestPalindrome1Space(string s)
  {
    // Size of the string
    int N = static_cast<int>(s.size());

    // Now we need to loop through the chars in s and generate...
    // 0123456  0123
    // a#b#b#c  abbc
    // ... and generate 0, 01, 1, 12, 2, 23, 3
    // What we can do is loop from [0..3], and within each loop, we call
    // expandAroundCentre for i,i and i,i+1. This of course would mean that
    // the last time we call expandAroundCentre, we use (3,4), which is out
    // of bounds, but the expandAroundCentre function will return 2... to
    // fix this, we wrap up the functionality of expandAroundCentre to 
    // return -1 for out of bounds.

    // indices to store the range [i..j] of the palindrome
    int starti=0; // First letter
    int endj=0;   // First letter
    int maxlen=1; // length 1

    // Now we can loop through the indices of s without worry.
    for(int k = 0; k<N; ++k)
    {
      int len1 = expandAroundCentre(s,k,k); // single char
      int len2 = expandAroundCentre(s,k,k+1); // double char/inbetween
      int len = std::max(len1,len2);

//      if(RayDebug)
//      cout << "k: " << k << "len1: " << len1 << "len2: " << len2 << '\n';
      
      // Calculate the indices
      if(len>maxlen)
      {
//        cout << "maxlen: " << 
        // case 1:
        //        i    k    j
        //        0 1  2  3 4
        // len=5, a b |a| b a
        //
        // case 2:
        //        i    k k+1  j
        //        0 1  2 3  4 5
        // len=6, a a |a a| a a
        //
        // For case 1, we have to go left and right by 2, i.e. len/2=5/4=2.
        // For case 2, we need to go left and right by 2 from k and k+1.
        //             but 6/2=3, not 2. So we can either do len/2-1, that
        //             means we have to determine if we have
        starti = k-(len-1)/2;
        endj = k+len/2; // k+1 len/2-1 works for both case1 and case2
        maxlen=len;
      }
    }
    return s.substr(starti, endj-starti+1);
  }
};

//TEST_CASE( "LPS", "[lps]" )
//{
//  Solution s;
//  REQUIRE(s.longestPalindrome("babad")=="bab");
//  REQUIRE(s.longestPalindrome("bb")=="bb");
//  REQUIRE(s.longestPalindrome("cbbd")=="bb");
//  REQUIRE(s.longestPalindrome("abcda")=="a");
//}

TEST_CASE( "Expanding around centres of palindrome", "[expand]" )
{
  Solution s;
  
  SECTION("Testing expand function")
  {
    REQUIRE(s.expandAroundCentre("abcda",0,0)==1); // first a
    REQUIRE(s.expandAroundCentre("abcda",1,1)==1); // b
    REQUIRE(s.expandAroundCentre("abcda",2,2)==1); // c
    REQUIRE(s.expandAroundCentre("abcda",3,3)==1); // d
    REQUIRE(s.expandAroundCentre("abcda",4,4)==1); // a
    REQUIRE(s.expandAroundCentre("abcda",-1,-1)==-1); // out of bounds
    REQUIRE(s.expandAroundCentre("abcda",5,5)==-1); // out of bounds

    // Repeat above but with palindrome
    REQUIRE(s.expandAroundCentre("abcba",0,0)==1); // first a
    REQUIRE(s.expandAroundCentre("abcba",1,1)==1); // b
    REQUIRE(s.expandAroundCentre("abcba",2,2)==5); // c
    REQUIRE(s.expandAroundCentre("abcba",3,3)==1); // d
    REQUIRE(s.expandAroundCentre("abcba",4,4)==1); // a
    REQUIRE(s.expandAroundCentre("abcba",-1,-1)==-1); // out of bounds
    REQUIRE(s.expandAroundCentre("abcba",5,5)==-1); // out of bounds
  }

  SECTION("Actual palindrome1space function")
  {
    RayDebug=true;
    REQUIRE(s.longestPalindrome1Space("babad")=="bab");
    RayDebug=false;
    REQUIRE(s.longestPalindrome1Space("bb")=="bb");
    REQUIRE(s.longestPalindrome1Space("cbbd")=="bb");
    REQUIRE(s.longestPalindrome1Space("abcda")=="a");
  }

}

//auto main()->int
//{
////  solveLPSRay("babad");
////  cout << '\n';
////  solveLPSRay("cbbd");
//
////  solveLPSDP("babad");
////  cout << '\n';
////  solveLPSDP("cbbd");
//
//  Solution s;
//  cout << s.longestPalindrome("babad")<<'\n';
//  cout << s.longestPalindrome("bb")<<'\n';
//  cout << s.longestPalindrome("cbbd") << '\n';
//  cout << s.longestPalindrome("abcda") << '\n';
//
//  return 0;
//}















