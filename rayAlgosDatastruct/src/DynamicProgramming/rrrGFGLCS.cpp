/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<algorithm>
using std::max;
#include<string>
using std::string;
#include<type_traits>
using std::common_type_t;
using std::remove_reference_t;
#include<tuple>
using std::make_tuple;

// http://www.geeksforgeeks.org/longest-common-subsequence/

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Function to find the longest common subsequence of two strings X and Y.
// of length m and n, respectively. Thus, X[0..m] and Y[0..n].
// Returns the length of the longest common substring found. This does not
// use DP.
auto lcs_length_recur(const string& X, const string& Y, 
                      decltype(X.size()) m, decltype(Y.size()) n)
  ->common_type_t<decltype(X.size()),decltype(Y.size())>
{
  // base case, if m or n equals 0, then we have no characters in one of
  // the substrings, which implies that the longest common subsequence in
  // this case is 0.
  if(m==0 || n == 0)
  {
    return 0;
  }
  // X[m-1]==Y[n-1] implies that this character is a part of the LCS. Thus
  // we know the LCS contains this character plus the LCS of the lower state
  // for X and Y. Note the difference in indices between how we index the
  // substrings X and Y and what we pass to the lcs function. That is, when
  // we pass m and n to lcs, the characters we're looking at in X and Y are
  // m-1 and n-1, respectively. Thus, when we want the lower states, we pass
  // m-1 and n-1 to lcs, instead of m-2 and n-1. This is correct since m and
  // n describes the length of the substrings, whilst indexing is from base
  // 0.
  else if(X[m-1] == Y[n-1])
  {
    return 1+lcs_length_recur(X,Y,m-1,n-1);
  }
  // Otherwise X[m-1]!=Y[n-1] implies either X[m-1] does not contribute to
  // the lcs and lcs is in (X[m-2],Y[n-1]) or Y[n-1] does not contribute to
  // the lcs and lsc is in (X[m-1],Y[n-2]). We want the max of this.
  else
  {
    return max(lcs_length_recur(X,Y,m,n-1),
               lcs_length_recur(X,Y,m-1,n));
  }
}

// Runs the above code
void run_lcs_length_recur(const string& str1, const string& str2)
{
  auto lcs = lcs_length_recur(str1,str2,str1.size(),str2.size());
  cout << "LCS(recur) for " << str1 << " and " << str2 << " is: " 
       << lcs << '\n';
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// LCS - DP with bottom up tabulation method.
// Returns the length of LCS.
auto lcs_length_tabulate(const string& X, const string& Y)
{
  using strsize_t = decltype(X.size());
  strsize_t m = X.size();
  strsize_t n = Y.size();

  vector<vector<int>>c(m+1,vector<int>(n+1,0));

  // Loop through the rows, starting from 1
  for(strsize_t i = 1; i != (m+1); ++i)
  {
    // Loop through the columns, starting from 1
    for(strsize_t j = 1; j != (n+1); ++j)
    {
      // These indices make sense, because range of X is X[0..n-1]
      // and i = 1..n.
      //
      // That is, c[i][j] contains the length of LCS of substrings of 
      // LENGTHS i and j. Indices of X and Y are: X[0..i-1] and Y[0..j-1].
      if(X[i-1] == Y[j-1])
        c[i][j] = c[i-1][j-1]+1;
      else
        c[i][j] = max(c[i-1][j], c[i][j-1]);
    }
  }
  return make_tuple(c[m][n],c);
}

template<typename S, typename T>
auto get_lcs(S& str1, S& str2, T c)
{
  // store the lcs characters, note: since we are using arrays, we do not
  // need the terminating character.
  auto m = str1.size();
  auto n = str2.size();

  vector<std::remove_cv_t<std::remove_reference_t<decltype(str1[0])> > > 
    lcs_chars(c[m][n]);
  auto i = m;
  auto j = n;
  auto lcs_index = c[m][n];

  while(i>0 && j>0)
  {
    if(str1[i-1] == str2[j-1])
    {
      lcs_chars[lcs_index-1] = str1[i-1];
      --i; --j; --lcs_index;
    }
    // move up? Note that we do NOt minus one from c[][] indices. Since this
    // array contains 0 at the upper left.
    else if(c[i-1][j]>c[i][j-1])
      --i;
    // move to the left
    else 
      --j;
  }

  return lcs_chars;
}

void run_lcs_length_tabulate(const string& str1, const string& str2)
{
  auto [lcs_len,c] = lcs_length_tabulate(str1,str2);
  cout << "LCS(tab) for " << str1 << " and " << str2 << " is: " 
       << lcs_len << '\n';

  auto lcs_chars = get_lcs(str1,str2,c);
  cout << "lcs chars are: ";
  for(auto i : lcs_chars)
  {
    cout << i << ' ';
  }
  cout << '\n';
}

// Note!!!: This code below does not work. It's a nice try though!
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// I also realised that I can find the LCS without recursion or DP, and is
// also O(mn). The key is to loop through each character of one string
// and match it with the other if possible.
auto lcs_iterative(const string& str1, const string& str2)
  -> decltype(str1.size())
{
  using strsize_t = decltype(str1.size());

  // lengths of the two strings.
  auto m = str1.size();
  auto n = str2.size();
  strsize_t lcs_len{0};

  // index of previously found lcs character in str2.
  // initially -1 since we need to check the first character at index 0 in
  // str2
  int prev_lcs_j = -1;
  for(strsize_t i = 0; i != m; ++i)
  {
//    cout << "i: " << i << endl;
    for(strsize_t j = (prev_lcs_j+1); j != n; ++j)
    {
//      cout << "j: " << j << endl;
      if(str1[i] == str2[j])
      {
//        cout << "match found for " << str1[i] << " " << str1[i] << endl;
        ++lcs_len;
        prev_lcs_j = j;
        break;
      }
    }
  }
  return lcs_len;
}
void run_lcs_iterative(const string& str1, const string& str2)
{
  auto lcs = lcs_iterative(str1,str2);
  cout << "LCS(iter) for " << str1 << " and " << str2 << " is: " 
       << lcs << '\n';
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
auto main()->int
{
  run_lcs_length_recur("ABCDGH","AEDFHR");
  run_lcs_length_recur("AGGTAB","GXTXAYB");
  run_lcs_length_tabulate("ABCDGH","AEDFHR");
  run_lcs_length_tabulate("AGGTAB","GXTXAYB");

//  run_lcs_iterative("ABCDGH","AEDFHR");
//  run_lcs_iterative("AGGTAB","GXTXAYB");

  return 0;
}

