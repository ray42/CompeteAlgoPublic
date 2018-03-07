/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl;
#include<iomanip> // std::boolalpha

#include<vector>
using std::vector;

#include<string>
using std::string;

template<typename T>
void printVec(const vector<vector<T>>& v, string str = "")
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

class Solution {
public:

  // i and j are the l
  bool isMatchRecur(const string& s, const string& p, int ssize, int psize) 
  {
    // base case, if both ssize and psize == 0, we have matched everything
    // so return true
    if(ssize==0 && psize==0)
      return true;

    // we have string left but no pattern, => no match
    if(ssize>0 && psize==0)
      return false;

    // Otherwise we have three cases:
    // 1) if p[psize-1] == s[ssize-1], we match a single char, recur for
    //    (ssize-1,psize-1)
    // 
    // 2) if p[psize-1] == "." we can match anything in s, so recur for
    //    (ssize-1,psize-1)
    //
    // 3) if p[psize-1] == "*", then we need to check p[psize-2]:
    //      a) if ssize==0, we discard two from p and try match the next
    //         pattern, recur for (ssize,psize-2)
    //      b) if p[psize-2]==s[ssize-1] we have a*, try to match the next
    //         one in s by recurring (ssize-1,psize)
    //      c) if p[psize-2]==".", we can match anything, recur for
    //         (ssize-1,psize)
    //      d) if p[size-2]!=s[ssize-1], discard the current pattern
    //         (ssize,psize-2)

    if(p[psize-1]==s[ssize-1])
      return isMatchRecur(s,p,ssize-1,psize-1);
    if(p[psize-1]=='.')
      return isMatchRecur(s,p,ssize-1,psize-1);

    if(p[psize-1]=='*')
    {
      if(ssize==0)
        return isMatchRecur(s,p,ssize,psize-2);
      if(p[psize-2]==s[ssize-1])
        return isMatchRecur(s,p,ssize-1,psize);
      if(p[psize-2]=='.')
        return isMatchRecur(s,p,ssize-1,psize);
      if(p[psize-2]!=s[ssize-1])
        return isMatchRecur(s,p,ssize,psize-2);
    }
  }

  bool runIsMatchRecur(const string& s, const string& p)
  {
    return isMatchRecur(s,p,s.size(),p.size());
  }

  // Good blog: http://xiaohuiliucuriosity.blogspot.co.uk/2014/12/regular-expression-matching.html
  bool isMatch(string s, string p) 
  {
    auto ssize = s.size();
    auto psize = p.size();

    // +1 for the 0-th size
    vector<vector<bool>> dp(ssize+1,vector<bool>(psize+1,false));
//    printVec(dp, "initial dp:\n");

    // initial/boundary conditions:
    //  0 1 2 3 4 5 
    //  ----------- p
    //0|1 ? ? ? ? ?
    //1|0
    //2|0
    //3|0
    //4|0         X
    // s
    
    dp[0][0]=true;
    // what about if we have patterns but no string? Lets say we are at 
    // p.size()=psize, then we can only have a match if p[psize-1]='*'
    // AND the previous p[0..psize-3] pattern matches the empty string. That
    // is, dp[0,psize-2]==1. We know that dp[0,1] cannot match, since we
    // we have a pattern of size 1 and no strings, this also means that in 
    // this case, the pattern cannot be '*', since we only have pattern of
    // size 1.
    dp[0][1]=false;
    for(size_t pindex=2; pindex <= psize; ++pindex)
      dp[0][pindex] = p[pindex-1]=='*' && dp[0][pindex-2];

//    printVec(dp,"After conditions:\n");



    // Now loop through the dp table in row major order
    for(size_t sindex = 1; sindex <= ssize; ++sindex)
    {
      for(size_t pindex = 1; pindex <= psize; ++pindex)
      {
        if(p[pindex-1]==s[sindex-1])
          dp[sindex][pindex] = dp[sindex-1][pindex-1];

        if(p[pindex-1]=='.')
          dp[sindex][pindex] = dp[sindex-1][pindex-1];

        if(p[pindex-1]=='*')
        {

//          size_t ri = 1, rj=5;
          /*  
          dp[sindex][pindex] 
            = ((p[pindex-2]==s[sindex-1]) && dp[sindex-1][pindex]) ||
              ((p[pindex-2]=='.')         && dp[sindex-1][pindex]) ||
              dp[sindex][pindex - 2];
          // */

          // if p[pindex-1]=='*', there are 3 cases:
          // p[index-2]* does not match, so we recur for (i,j-2), i.e.
          // we ignore the pattern. Note that it also means that p[i-2] 
          // cannot be '.', since '.' matches everything.
          if( (p[pindex-2]!=s[sindex-1]) && (p[pindex-2]!='.'))
          {
//            if(sindex==ri && pindex==rj)
//            {
//              cout << "rrr discard\n";
//            }
            dp[sindex][pindex] = dp[sindex][pindex-2];
          }

          // If p[pindex-2]==s[sindex-1], we match

          //*
          if(p[pindex-2]==s[sindex-1])
          {
//            cout << "a*: " << "p[j-2]: " << p[pindex-2] 
//                           << ", s[i-1]: " << s[sindex-1] << '\n';
            // EDGE CASE - EVEN IF IT MATHCHES, WE MAY HAVE TO THROW IT AWAY
            // since we may have
            // s=aaa
            // p=aa*,
            // so a* will watch the last two aa, but 'a' will match the first
            // a
            dp[sindex][pindex] = dp[sindex-1][pindex] || dp[sindex][pindex-2];

//            if(sindex==ri && pindex==rj)
//            {
//              cout << "rrr doing a*\n";
//              cout << "dp[i-1][j] = " << dp[sindex-1][pindex] << '\n';
//              cout << "dp[i][j] = " << dp[sindex][pindex] << "\n\n";
//            }
          }
          
          if(p[pindex-2]=='.')
          {
//            if(sindex==ri && pindex==rj)
//            {
//              cout << "rrr doing .*\n";
//            }

            // EDGE CASE - EVEN IF IT MATHCHES, WE MAY HAVE TO THROW IT AWAY
            // since we may have
            // s=aaa
            // p=a.*,
            // so .* will watch the last two aa, but 'a' will match the first
            // a
            dp[sindex][pindex] = dp[sindex-1][pindex] || dp[sindex][pindex-2];
          }
          

          //*/

//          if(sindex==2 && pindex==5)
//          {
//            cout << "testing: " <<dp[sindex-1][pindex] << '\n';
//            cout << "testing: " <<dp[sindex][pindex] << '\n';
//          }
          
          
          // "aa",".*"
          /*
          if(p[pindex-2]==s[sindex-1])
            dp[sindex][pindex] = dp[sindex-1][pindex];
          
          else if(p[pindex-2]=='.')
            dp[sindex][pindex] = dp[sindex-1][pindex];

          else//(p[pindex-2]!=s[sindex-1])
            dp[sindex][pindex] = dp[sindex][pindex-2];
          //*/

        }
      }
    }

//    printVec(dp, "Ray\n");

    return dp[ssize][psize];
  }

//  bool isMatchTemp(string s, string p) {
//    /**
//     * f[i][j]: if s[0..i-1] matches p[0..j-1]
//     * if p[j - 1] != '*'
//     *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
//     * if p[j - 1] == '*', denote p[j - 2] with x
//     *      f[i][j] is true iff any of the following is true
//     *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
//     *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
//     * '.' matches any single character
//     */
//    int m = s.size(), n = p.size();
//    vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));
//    
//    f[0][0] = true;
//    for (int i = 1; i <= m; i++)
//        f[i][0] = false;
//    // p[0.., j - 3, j - 2, j - 1] matches empty iff p[j - 1] is '*' and p[0..j - 3] matches empty
//    for (int j = 1; j <= n; j++)
//    {
//      if(j==2)
//      {
//        cout <<"(j>1)"<< (j>1) << '\n';
//        cout <<"p[j-1]=='*'"<< ('*' == p[j - 1]) << '\n';
//        cout <<"f[0][j-2]"<< (f[0][j-2]) << '\n';
//      }
//      f[0][j] = (j > 1) && ('*' == p[j - 1]) && (f[0][j - 2]);
//    }
//
//    printVec(f);
//    
//    for (int i = 1; i <= m; i++)
//        for (int j = 1; j <= n; j++)
//            if (p[j - 1] != '*')
//                f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
//            else
//                // p[0] cannot be '*' so no need to check "j > 1" here
//                f[i][j] = f[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j];
//    
//    return f[m][n];
//  }

};

int main()
{
  Solution s;
  //std::cout << std::boolalpha;
//  cout << s.runIsMatchRecur("aa","a") << '\n';
//  cout << s.runIsMatchRecur("aa","aa") << '\n';
//  cout << s.runIsMatchRecur("aaa","aa") << '\n';
//  cout << s.runIsMatchRecur("aa","a*") << '\n';
//  cout << s.runIsMatchRecur("aa",".*") << '\n';
//  cout << s.runIsMatchRecur("ab",".*") << '\n';
//  cout << s.runIsMatchRecur("aab","c*a*b*") << '\n';

//  cout << s.isMatch("aa","a") << '\n';
//  cout << s.isMatch("aa","aa") << '\n';
//  cout << s.isMatch("aaa","aa") << '\n';
  cout << s.isMatch("aa","a*") << '\n';
  cout << s.isMatch("aa",".*") << '\n';
//  cout << s.runIsMatchRecur("aa",".*") << '\n';
//  cout << s.runIsMatchRecur("aaa","ab*a*c*a") << '\n';

  cout << s.isMatch("aaa","ab*a*c*a") << '\n'; // test this

//  cout << s.isMatch("ab",".*") << '\n';
//  cout << s.isMatch("aab","c*a*b*") << '\n';


  return 0;
}

