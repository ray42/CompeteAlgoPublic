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
#include<string>
using std::string;

#include<iomanip> // setw

// A utility function to check if (i,j) are valid indices
// for N*N chessboard
bool isLegal(const int x, const int y, const vector<vector<int>>& sol)
{
  auto N = static_cast<int>(sol.size());

  return ((x>=0) && (x<N) && (y>=0) && (y<N) &&
          (sol[x][y] == -1));
}

// A utility function to print a 2D vector
template<typename T>
void print2dVec(const vector<vector<T>>& vec, const string& str="")
{
  if(!str.empty())
  {
    cout << str;
  }

  for(const auto& row:vec)
  {
    for(const auto& val:row)
    {
      cout << std::setw(2) << val << ' ';
    }
    cout << '\n';
  }
}

// A recursive utility function to solve Knight Tour problem.
// curr_x and curr_y are the current x and y positions of the knight
// movei is a count of the current move number.
// sol contains the board.
// xMove and yMove are the new positions of the knight relative to current 
//   pos.
bool solveKTRecur(const int curr_x, const int curr_y, const int movei,
                  vector<vector<int>>& sol,
                  const vector<int>&xMove, const vector<int>&yMove)
{
  //cout << "Doing movei = " << movei << '\n';

  // Base case is when we have filled the whole board.
  // i.e. when movei == N*N
  auto N = static_cast<int>(sol.size());

  // The range of movei = [0..(N*N-1)]. However, for movei=N*N-1, we still
  // want to do the work (filling in the sol, if possible), so we test if
  // movei=N*N and return.
  if(movei == N*N) 
    return true;

  // Now loop through all the possibilities
  for(decltype(xMove.size()) i = 0; i < xMove.size(); ++i)
  {
    // create the next move
    int next_x = curr_x+xMove[i];
    int next_y = curr_y+yMove[i];

    // Check if this position is legal
    if(isLegal(next_x,next_y,sol))
    {
      // We know that we can place the next move here
      sol[next_x][next_y]=movei;

      // Now try every item from here.
      if(solveKTRecur(next_x,next_y,movei+1,
                      sol,xMove,yMove))
      {
        // we get here if we return true all the way down
        return true; 
      }
      else
      {
        // none of the 8 paths from here returns true. So we `backtrack'
        // this move/item and try the next of the 8 moves
        sol[next_x][next_y] = -1;
      }
    } // if legal
  } // for all items/moves

  // If we get here, it means that none of the items/moves worked. So we
  // return false.
  return false;
}

void runSolveKTRecur()
{
  // board size
  int N{8};
  
  // create the board and initialize with -1
  vector<vector<int>> board(N,vector<int>(N,-1));

  // start with the top left.
  int startx=0, starty=0;
  board[startx][starty]=0;

  // Create the eight moves in this order:
  //  2   1
  // 3     0
  //    x
  // 4     7
  //  5   6
  
  /* xMove[] and yMove[] define next move of Knight.
     xMove[] is for next value of x coordinate
     yMove[] is for next value of y coordinate */
  vector<int> xMove{2, 1, -1, -2, -2, -1,  1,  2};
  vector<int> yMove{1, 2,  2,  1, -1, -2, -2, -1};

  // If the solve returns true, it means there's a solution. Otherwise
  // there is no solution.
  if(solveKTRecur(startx,starty,1,board,xMove,yMove))
  {
    print2dVec(board, "Solution is:\n");
  }
  else
  {
    print2dVec(board, "No solution:\n");
    //cout << "Solution does not exist" << '\n';
  }

}

int main()
{
  runSolveKTRecur();

  return 0;
}

