/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// https://www.codechef.com/NOV17/problems/PERPALIN
#include<iostream>
using std::cout; using std::cin;
#include<string>
using std::string;

auto main()->int
{
  cin.ignore();
  long int N,P;
  while(cin >> N >> P)
  {
    if((P==1) || (P==2))
    {
      cout << "impossible"<<"\n";
    }
    else
    {
      // Create palindrome of length p.
      auto floorHalfP=P/2;
      string palinss(P,'a'); // Start with a's and slot in b's.
      decltype(P) i=1;
      do{
        palinss[i]='b';
        palinss[P-i-1]='b';
        i+=2;
      }while(i <=floorHalfP);

      // concatenate the periods.
      auto nPeriod=N/P;
      decltype(palinss) outstr="";
      for(decltype(nPeriod) j =0; j!=nPeriod; ++j)
      {
        outstr+=palinss;
      }
      cout << outstr << "\n";
    }
  }
  return 0;
}
