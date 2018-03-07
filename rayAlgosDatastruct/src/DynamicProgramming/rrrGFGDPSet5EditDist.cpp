/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl;
#include<string>
using std::string;
#include<algorithm>
using std::min;
#include<type_traits>
#include<vector>
using std::vector;

//http://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance
template<typename T>
auto editDist(const T& s1, const T& s2, 
              decltype(s1.size()) s1_sz, decltype(s2.size()) s2_sz)
{
  // Insert all elements from s2 into s1, therefore number of edits
  // is the same as the number of chars left in s2.
  if(s1_sz == 0)
  {
    return s2_sz;
  }
  // If s2 is empty, then we remove all the chars left in s1. The number of
  // edits is the same as the number of chars in s1.
  if(s2_sz == 0)
  {
    return s1_sz;
  }
  
  // If the last character of the two strings are the same, we do not add
  // an edit. We just recur.
  if(s1[s1_sz-1]==s2[s2_sz-1])
    return editDist(s1,s2,s1_sz-1,s2_sz-1);

  // Last chars are different, so we use an edit (insert/remove/replace)
  // and recur.
  return 1 + min({editDist(s1,s2,s1_sz,s2_sz-1),    // insert
                  editDist(s1,s2,s1_sz-1,s2_sz),    // remove
                  editDist(s1,s2,s1_sz-1,s2_sz-1)});// replace
}
//template<typename T, std::enable_if_t<std::is_same<std::string,T>::value>>
void runEditDist(const string& s1, const string& s2)
{
  cout << "str1: " << s1 << ", str2: " << s2 << '\n';
  cout << "Min num of edits: " 
       << editDist(s1,s2,s1.size(),s2.size()) << '\n';
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// Now we do DP with tabulation (bottom up, starting with top left,
// i.e. i=0, j=0, and work to i=)
auto editDistTabulate(const string& s1, const string& s2)
{
  using strsz_t = decltype(s1.size());

  auto m = s1.size();
  auto n = s2.size();

  // minDist[i][j] contains the min edits for strs of length i and j,
  // where 0<=i<=m and 0<=j<=n
  // This is why we plus 1 to the sizes.
  vector<vector<strsz_t>>
    minDist(m+1,vector<strsz_t>(n+1,0));

  // Fill in minDist in bottom up manner, first loop through the rows.
  for(strsz_t i = 0; i != (m+1); ++i)
  {
    // Loop through each column.
    for(strsz_t j = 0; j != (n+1); ++j)
    {
      // If first string is empty, only option is to insert all chars of
      // second string
      if(i == 0) 
        minDist[i][j] = j; // Min. edits = j

      // If second string is empty, only option is to remove all chars of
      // the first string.
      else if(j==0) 
        minDist[i][j] = i; // Min. edits = i

      // If the last chars are the same, ignore last char (no edits 
      // required), and recur for remaining string.
      else if(s1[i]==s2[j])
        minDist[i][j] = minDist[i-1][j-1];

      // If last char are different, consider all possibilities and find
      // the minimum.
      else
        minDist[i][j] = 1+std::min({minDist[i][j-1],    // insert
                                    minDist[i-1][j],    // remove
                                    minDist[i-1][j-1]});// replace
    }
  }
  return minDist[m][n];
}
void runEditDistTab(const string& s1, const string& s2)
{
  cout << "str1: " << s1 << ", str2: " << s2 << '\n';
  cout << "Min num of edits: " 
       << editDistTabulate(s1,s2) << '\n';
}


int main()
{
  runEditDist("geek","gesek");
  runEditDist("cut","cat");
  runEditDist("sunday","saturday");

  runEditDistTab("geek","gesek");
  runEditDistTab("cut","cat");
  runEditDistTab("sunday","saturday");

  return 0;
}

