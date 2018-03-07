/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl; using std::cin;

#include<string>
using std::string;

#include<cctype> // to toupper

#include<algorithm> // std::all_of

#include<iterator> // std::begin std::end

#include<vector>
using std::vector;

//10
//LLZOSYAMQRMBTZXTQMQcKGLR
//LLZOSYAMBTZXMQKLR
//MGYXKOVSMAHKOLAZZKWXKS
//MGXKOVSAHKOLZKKDP
//VLKHNlpsrlrvfxftslslrrh
//VLKHN
//OQSVONTNZMDJAVRZAZCVPKh
//OSVONTNZMDJAVRZAZCVPK
//AXbosoh
//AX
//EYONDOCHNZYYlBZXPGzX
//EYONDOCHNZYYBZXPGXOG
//BJAFXKGENMFUvdsvcptrp
//BJAFXKGENMFU
//UBUFOOSIXXsdtfmeyongkhehq
//UBUFOOSIXX
//PWBIJLCOIAXGJGUXUZOutgic
//PWBIJLCOIAXGJGUXUZO
//EOWZEOHWYOJTBNMcefdsp
//EOWZEOHWYOJTBNM
//NO
//NO
//YES
//NO
//YES
//NO
//YES
//YES
//YES
//YES

//10
//XXVVnDEFYgYeMXzWINQYHAQKKOZEYgSRCzLZAmUYGUGILjMDET
//XXVVDEFYYMXWINQYHAQKKOZEYSRCLZAUYGUGILMDETQVWU
//PVJSNVBDXABZYYGIGFYDICWTFUEJMDXADhqcbzva
//PVJSNVBDXABZYYGIGFYDICWTFUEJMDXAD
//QOTLYiFECLAGIEWRQMWPSMWIOQSEBEOAuhuvo
//QOTLYFECLAGIEWRQMWPSMWIOQSEBEOA
//DRFNLZZVHLPZWIupjwdmqafmgkg
//DRFNLZZVHLPZWI
//SLIHGCUOXOPQYUNEPSYVDaEZKNEYZJUHFXUIL
//SLIHCUOXOPQYNPSYVDEZKEZJUHFXUIHMGFP
//RYASPJNZEFHEORROXWZFOVDWQCFGRZLWWXJVMTLGGnscruaa
//RYASPJNZEFHEORROXWZFOVDWQCFGRZLWWXJVMTLGG
//AVECtLVOXKPHIViTZViLKZCZAXZUZRYZDSTIHuCKNykdduywb
//AVECLVOXKPHIVTZVLKZCZAXZUZRYZDSTIHCKN
//wZPRSZwGIMUAKONSVAUBUgSVPBWRSTJZECxMTQXXA
//ZPRSZGIMUAKONSVAUBUSVPBWRSTJZECMTQXXA
//SYIHDDSMREKXOKRFDQAOZJQXRIDWXPYINFZCEFYyxu
//SYIHDDSMREKXOKRFDQAOZJQXRIDWXPYINFZCEFY
//EIZGAWWDCSJBBZPBYVNKRDEWVZnSSWZIw
//EIZGAWWDCSJBBZPBYVNKRDEWVZSSWZI
//NO
//YES
//YES
//YES
//NO
//YES
//YES
//YES
//YES
//YES

void printVec(const vector<vector<int>> v, const string& str="")
{
  if(!str.empty())
  {
    cout << str;
  }

  for(const auto& row:v)
  {
    for(const auto& val:row)
    {
      cout << val << " ";
    }
    cout << '\n';
  }
}

bool abbre_recur(const string& a, const string& b, 
           const int asize, const int bsize)
{
  // If chars in a are used up, and still chars in b, always false
  if(asize==0 && bsize>0) 
  {
//    cout << "asize==0 and bsize>0, return false\n";
    return false;
  }
  
  if(asize==0 && bsize==0)
  {
//    cout << "asize==0 and bsize==0, return true\n";
    return true;
  }

  if(asize>0 && bsize==0) 
  {
    if(std::all_of(std::begin(a), std::begin(a)+asize,
                   [](char c)
                   {
                     return islower(c);
                   }))
    {
//      cout << "checking if rest of a is lower, TRUE\n";
      return true;
    }
    else
    {
//      cout << "checking if rest of a is lower, FALSE\n";
      return false;

    }
  }

  //  if it's lower case:
  //    if can be capitalised to b, we can either use recur (i-1,j-1)
  //                                       or not use recur (i-1,j)
  //    else if it cannot be cap to b, recur (i-1,j)
  //  else if it's upper case:
  //    here we must use it so if it's not equal, return false.
  //    If equal, recur (i-1,j-1)
  if(islower(a[asize-1]))
  {
    if(toupper(a[asize-1])==b[bsize-1])
      return (abbre_recur(a,b,asize-1,bsize-1) || abbre_recur(a,b,asize-1,bsize));
    else
      return abbre_recur(a,b,asize-1,bsize);
  }
  else
  {
    if(a[asize-1]==b[bsize-1])
      return abbre_recur(a,b,asize-1,bsize-1);
    else
      return false;
  }
}

bool abbreDP(const string& a, const string& b)
{
  // create the DP table and set the boundary conditions
  auto aN = a.size();
  auto bN = b.size();

  // Need +1 to account for 0-sized strings.
  // So dp[i][j] represents if a of length i can be converted to b of 
  // length j.
  vector<vector<int>> dp(aN+1,vector<int>(bN+1,0));
  
  // Set the boundary condition according to the base cases:
  //   0 1 2 3 4 5 b
  // 0 1 0 0 0 0 0
  // 1 ?
  // 2 ?
  // 3 ?
  // 4 ?
  // a
  // where ? is the base case:
  //if(asize>0 && bsize==0) 
  //{
  //  if(std::all_of(std::begin(a), std::begin(a)+asize,
  //                 [](char c)
  //                 {
  //                   return islower(c);
  //                 }))
  //    return true;
  //  else
  //    return false;
  //}
  // first we do along the row
  dp[0][0] = 1;
  for(decltype(bN) j=1; j<=bN; ++j)
    dp[0][j]=0;

  // Now we go down. Check if a is not empty, then fill in the first one.
  if(aN>0)// 
    dp[1][0] = static_cast<bool>(islower(a[0]));

  // Fill in the rest
  for(decltype(aN) i = 2; i <= aN; ++i)
    dp[i][0] = static_cast<bool>(dp[i-1][0] && islower(a[i-1]));


  // Loop in row major order, we start from 1, see the dp table with init/
  // boundary conditions filled in.
  for(decltype(aN) i = 1; i <= aN; ++i)
  {
    for(decltype(bN) j = 1; j <= bN; ++j)
    {
      if(islower(a[i-1]))
      {
        if(toupper(a[i-1])==b[j-1])
          dp[i][j] = (dp[i-1][j-1] || dp[i-1][j]);
        else
          dp[i][j] = dp[i-1][j];
      }
      else
      {
        if(a[i-1]==b[j-1])
        {
          dp[i][j]=dp[i-1][j-1];
        }
        else
          dp[i][j]=0;
      }
    }
  }

  return dp[aN][bN];
}

auto main()->int
{
  string a,b;
  std::getline(cin,a); // ignore first line

//  while(std::getline(cin,a))
//  {
//    std::getline(cin,b);
//    if(abbre_recur(a,b,a.size(),b.size())) cout << "YES\n";
//    else cout << "NO\n";
//  }

  while(std::getline(cin,a))
  {
    std::getline(cin,b);
    if(abbreDP(a,b)) cout << "YES\n";
    else cout << "NO\n";
  }

  return 0;
}

