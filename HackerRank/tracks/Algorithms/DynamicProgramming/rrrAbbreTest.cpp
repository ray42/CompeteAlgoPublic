#include<iostream>
using std::cout; using std::endl; using std::cin;

#include<string>
using std::string;

#include<cctype> // to toupper

#include<algorithm> // std::all_of

#include<iterator> // std::begin std::end

#include<vector>
using std::vector;

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
        //cout << "Before char compare, ";
        //cout << "i = " << i << ", j = " << j << '\n';
        if(a[i-1]==b[j-1])
        {
          //cout << "Done char compare\n";
          dp[i][j]=dp[i-1][j-1];
        }
        else
          dp[i][j]=0;
      }
    }
  }

  cout << "about to return" << endl;
  cout << dp[aN][bN] << '\n';

  return 0;
  //return dp[aN][bN];
}

int main()
{
  cout << "Before abbreDP call\n";
  abbreDP("LLZOSYAMQRMBTZXTQMQcKGLR","LLZOSYAMBTZXMQKLR");
  cout << "AFTER abbreDP call\n";

  return 0;
}

