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

template<typename T>
using Grid2d = vector<vector<T>>;

template<typename T>
void printGrid2d(const Grid2d<T>& grid, const string& str = "",
                 const int prec = 0)
{
  if(!str.empty())
    cout << str;

  for(const auto& row:grid)
  {
    for(const auto& val:row)
      cout << std::setw(prec) << val << ' ';
    cout << '\n';
  }
}

bool isLegal(const int x, const int y, const Grid2d<int>& maze)
{
  // size of the maze
  auto N = static_cast<int>(maze.size());

  return ((x >= 0)&&(x<N)&&(y>=0)&&(y<N)&&(maze[x][y] != 0));
}

bool solveMazeRecur(const int curr_x, const int curr_y,
                    const Grid2d<int>& maze,
                    const vector<int>& xmoves, const vector<int>& ymoves,
                    Grid2d<int>& sol)
{
  // size of the maze
  auto N = static_cast<int>(maze.size());

  // base case - solution found!
  if((curr_x == (N-1)) && (curr_y==(N-1)))
    return true;

  // Loop through the items and try each one.
  for(decltype(xmoves.size()) k = 0; k < xmoves.size(); ++k)
  {
    // Get the next position
    int next_x = curr_x + xmoves[k];
    int next_y = curr_y + ymoves[k];

    if(isLegal(next_x,next_y,maze))
    {
      // travel into the next path and ...
      sol[next_x][next_y] = 1;

      // ... try all paths from there
      if(solveMazeRecur(next_x,next_y,maze,xmoves,ymoves,sol))
      {
        return true;
      }
      else
      {
        // un-travel this item `backtracking' and try the next item
        sol[next_x][next_y] = 0;
      }
    }
  }

  // If none of the above child items returns true, then return false, 
  // indicating that this path should not be taken.
  return false;
}

void runSolveMazeRecur()
{
  Grid2d<int>maze{{1, 0, 0, 0},
                  {1, 1, 0, 1},
                  {0, 1, 0, 0},
                  {1, 1, 1, 1}};

  // Solution grid, initialized to 0
  auto N = maze.size();
  Grid2d<int>sol(N,vector<int>(N,0));

  // move vectors (the items), only right and down.
  vector<int> xmoves{1,0};
  vector<int> ymoves{0,1};

  // starting positions: top left.
  int start_x = 0, start_y = 0;
  sol[start_x][start_y] = 1;

  if(solveMazeRecur(start_x,start_y,maze,xmoves,ymoves,sol))
  {
    printGrid2d(sol,"Solution is:\n");
  }
  else
  {
    cout << "No solution.\n";
  }
}
int main()
{
  runSolveMazeRecur();
  return 0;
}

