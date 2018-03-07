/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */

#include<iostream>
using std::cin; using std::cout; using std::endl;
#include<string>
using std::getline; using std::string;


auto main(int argc, char* argv[])->int
{
  string TimeString;
  getline(cin,TimeString);

  //0123456789
  //07:05:45PM

  int h1=TimeString[0]-'0';
  int h2=TimeString[1]-'0';
  int hh=h1*10+h2;
//  cout <<"h1: " <<h1<< ", h2: " << h2 << ", hh: "<< hh << endl;

  // AM
  if(TimeString[8]=='A')
  {
    if(hh==12)
    {
      cout << "00";
      for(int i=2; i!=8;++i)
        cout << TimeString[i];
      cout << endl;
    }
    else
    {
      for(int i=0; i!=8;++i)
        cout << TimeString[i];
      cout << endl;
    }
  }
  else // PM
  {
    if(hh==12)
    {
      for(int i=0; i!=8; ++i)
        cout << TimeString[i];
      cout << endl;
    }
    else
    {
      hh+=12;
      cout << hh;
      for(int i=2; i!=8; ++i)
        cout << TimeString[i];
      cout << endl;
    }
  }

  return 0;
}
