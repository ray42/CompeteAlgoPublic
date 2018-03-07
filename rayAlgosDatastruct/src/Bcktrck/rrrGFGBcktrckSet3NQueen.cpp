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

template<typename T>
using Grid2d = vector<vector<T>>;

template<typename T>
void printGrid2d(const Grid2d<T>& board)
{
  for(const auto& row:board)
  {
    for(const auto& val:row)
    {
      cout << val << ' ';
    }
    cout << '\n';
  }
}

// Check to see if x and y are within the board (0<=x,y<N-1) and 
// 1) Check left horizontally
// 2) Check up diagonal
// 3) Check down diagonal
bool isLegal(const int x, const int y, const Grid2d<int>& board)
{
  // First check if x and y are in range
  auto N = static_cast<int>(board.size());
  if(x < 0 || x>=N || y<0 || y>= N)
  {
    return false;
  }

  // Check if to the left, so only column changes
  for(int yi = 0; yi < y; ++yi)
    if(board[x][yi] == 1)
      return false;

  // Check if up diag, both row and col indices reduce by 1 at each 
  // iteration
  for(int xi = x, yi = y; xi >= 0 && yi >= 0; xi--, yi--)
    if(board[xi][yi]==1)
      return false;

  // Check if down diag, row increases by 1, col decreases by 1
  for(int xi = x, yi = y; xi < N && yi >= 0; ++xi, --yi)
    if(board[xi][yi]==1)
      return false;

  return true;
}

bool solveNQueenRecur(const int col, Grid2d<int>& board)
{
  // We try to place the col-th queen in the col-th column. 
  // If col == board.size(), then we know that we have already placed all 
  // the N queens in the 0..N-1 columns
  auto N = static_cast<int>(board.size());
  if(col == N)
    return true;

  // Try to place the queen in the col-th column by looping through the rows
  for(int row = 0; row < N; ++row)
  {
    if(isLegal(row,col,board))
    {
      // Found a legal square, so we set the queen here
      board[row][col] = 1;
      
      // Now try for the next column. We go deeper, depth-first,
      // recursively placing the remaining queens, and propagate true back
      // to the caller of this function if the base case is reached.
      if(solveNQueenRecur(col+1,board))
        return true;
      else
        // backtrack by resetting (row,col) to zero, so we can try a 
        // different row.
        board[row][col] = 0;
    }
  }

  // If none of the rows work=>none of the path of items , return false
  return false;
}

void runSolveNQueens()
{
  constexpr size_t N = 100;
  Grid2d<int> board(N,vector<int>(N,0));
  solveNQueenRecur(0,board);
  printGrid2d(board);
}

int main()
{
  runSolveNQueens();
  return 0;
}

