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
#include<algorithm> // std::find
#include<string>
using std::string;


// https://www.geeksforgeeks.org/backtracking-set-7-suduku

// UNASSIGNED is used for empty cells in sudoku grid
static constexpr int UNASSIGNED{0};

// N is used for the size of the sudoku grid. Size will be NxN
static constexpr int GridSize{9};

template<typename T>
using Grid2d = vector<vector<T>>;

// A utility function to print grid
template<typename T>
void printGrid(const Grid2d<T>& grid, string str="")
{
  if(!str.empty()) cout << str;
  for(const auto& row:grid)
  {
    for(const auto& val:row)
      cout << val << " ";
    cout << '\n';
  }
}

// Searches the grid to find an entry that is still unassigned. If found, 
// the reference parameters row, col will be set to the location that is
// unassigned, and true is returned. If no assigned entries remain, false
// is returned.
bool FindUnassignedLocation(const Grid2d<int>& grid, int& row, int& col)
{
  for(row = 0; row < GridSize; ++row)
    for(col = 0; col < GridSize; ++col)
      if(grid[row][col] == UNASSIGNED)
        return true;
  return false;
}

// Functions to check if it's legal (isSafe), to do this, we need to check
// if the number is (1) used in the row, (2) used in the column, and (3)
// used in the box

// Returns a boolean which indicates whether any assigned entry in the 
// specified row matches the given number
bool UsedInRow(const Grid2d<int>& grid, const int row, const int num)
{
  return std::find(grid[row].begin(),grid[row].end(),num) != grid[row].end();
}

// Returns a boolean which determines whether any assigned entry in the
// specified column matches the give number.
bool UsedInCol(const Grid2d<int>& grid, const int col, const int num)
{
  // Loop through the rows of a given col
  for(int row = 0; row < GridSize; ++row)
    if(grid[row][col]==num)
      return true;
  return false;
}

// Returns a boolean which indicates whether any assigned entry within the
// specified 3x3 box matches the given number.
bool UsedInBox(const Grid2d<int>& grid, const int boxStartRow, 
               const int boxStartCol, const int num)
{
  for(int row=0; row < 3; ++row)
    for(int col=0; col < 3; ++col)
      if(grid[boxStartRow+row][boxStartCol+col] == num)
        return true;
  return false;
}

// Returns a boolean which indicates whether it will be legal to assign num
// to the given (row,col) location
bool isSafe(const Grid2d<int>& grid, const int row, const int col, 
            const int num)
{
  // Check if 'num' is not already placed in the current row, current 
  // column, and current 3x3 box
  return !UsedInRow(grid, row, num) &&
         !UsedInCol(grid, col, num) &&
         !UsedInBox(grid, row-row%3, col-col%3, num);
  // The last part makes sense, since, e.g.
  // 0, 1, 2 | 3, 4, 5 | 6, 7, 8
  //
  // Take the middle square, if we have 3, then:
  // 5-5%3 = 5-2=3 | 3(+2)-2=3
  // 4-4%3 = 4-1=3 | 3(+1)-1=3
  // 3-3%3 = 3-0=3 | 3(+0)-0=3
}

// Takes a partially filled-in grid and attempts to assign values to all 
// unassigned locations in such a way to meet the requirements for Sudoku
// solution (non-duplication across rows, columns, and boxes)
bool solveSudoku(Grid2d<int>& grid)
{
  int row, col;

  // base case, when we cannot find a free cell (unassigned location), we
  // are done.
  if(!FindUnassignedLocation(grid, row, col))
    return true;

  // Otherwise, we now have an unassigned cell in (row,col), and the items
  // are the numbers 1 to 9. The number 0 represents unassigned.
  for(int num = 1; num <= 9; ++num)
  {
    // See if we can fill this number in, and propagate the true back
    if(isSafe(grid, row, col, num))
    {
      // fill in this number
      grid[row][col]=num;
      
      // Go depth-first, try the next unassigned cell.
      if(solveSudoku(grid))
        return true;

      // Otherwise, we will backtrack, and try the next number.
      grid[row][col] = UNASSIGNED;
    }
  }

  // If none of the numbers work, we turn false. This triggers backtracking.
  return false;
}

// Driver program to test above functions
int main()
{
  // 0 means unassigned cells
  Grid2d<int> grid{
  {3, 0, 6, 5, 0, 8, 4, 0, 0},
  {5, 2, 0, 0, 0, 0, 0, 0, 0},
  {0, 8, 7, 0, 0, 0, 0, 3, 1},
  {0, 0, 3, 0, 1, 0, 0, 8, 0},
  {9, 0, 0, 8, 6, 3, 0, 0, 5},
  {0, 5, 0, 0, 9, 0, 6, 0, 0},
  {1, 3, 0, 0, 0, 0, 2, 5, 0},
  {0, 0, 0, 0, 0, 0, 0, 7, 4},
  {0, 0, 5, 2, 0, 6, 3, 0, 0}};

  if(solveSudoku(grid))
    printGrid(grid);
  else
    cout << "No solution exists\n";
  return 0;
}
