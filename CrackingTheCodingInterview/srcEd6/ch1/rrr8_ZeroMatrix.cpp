/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */

// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

#include<iostream>
using std::cout; using std::endl;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Question here.
// 1.8 Zero Matrix: Write an algorithm such that if an element in an MxN 
//          matrix is 0, its entire row and column are set to 0.
//
// 
// How I'd do it is to keep a vector of columns which needs to be zero and 
// the same for rows. After analyzing the matrix to find the zero entries
// O(N^2), we simply loop through these two vectors and zero the 
// rows/columns.
//
// This needs O(N) space. 
//
// Hints:
//
// #17: If you just cleared the rows and columns as you found $0$s, you'd
//      likely wind up clearing the whole matrix. Try finding the cells with
//      zeros first before making any changes to the matrix.
// 
// #74: Can you use O(N) additional space instead of O(N^2)? What 
//      information do you really need from the list of cells that are zero?
//
// #102: You probably need some data storage to maintain a list of the rows 
//       and columns that need to be zeroed. Can you reduce the additional
//       space usage to a O(1) by using the matrix itself for data storage?

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here
#include<vector>
#include<unordered_set>

template<typename T>
using Matrix = std::vector<std::vector<T> >;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here

void nullifyRow(Matrix<int>& mat, int row);

void nullifyColumn(Matrix<int>& mat, int col);

void setZero(Matrix<int>& mat)
{
  // Check for zero matrix
  if(mat.size() == 0 || mat[0].size()==0)
    return ;

  // set of rows/cols which contains zeros.
  std::unordered_set<int> rowsToZero{};
  std::unordered_set<int> colsToZero{};

  // Store the row and column index with value zero.
  for(int i = 0; i < (int)mat.size(); ++i)
  {
    for(int j = 0; j < (int)mat[0].size(); ++j)
    {
      if(mat[i][j] == 0)
      {
        rowsToZero.insert(i);
        colsToZero.insert(j);
      }
    }
  }

  // Loop through the rowsToZero set, and nullify the rows.
  for(const auto& rowi : rowsToZero)
  {
    nullifyRow(mat,rowi);
  }

  // Loop through the colsToZero set, and nullify the columns
  for(const auto& coli : colsToZero)
  {
    nullifyColumn(mat,coli);
  }
}

void nullifyRow(Matrix<int>& mat, int row)
{
  // Loop through the columns to nullify this row
  for(int coli = 0; coli < (int)mat[0].size(); ++coli)
  {
    mat[row][coli]=0;
  }
}

void nullifyColumn(Matrix<int>& mat, int col)
{
  // Loop through the rows to nullify this column
  for(int rowi = 0; rowi < (int)mat.size(); ++rowi)
  {
    mat[rowi][col]=0;
  }
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// For the inplace version, we use the first row and first column to zero a 
// 0, indicating the rows/columns we have to nullify. However, during this 
// process, we add zeros to the first column/row, which means we also 
// nullify them, which is incorrect! So, we first check if the first row and
// column needs to be nullified, before we put zeros in there.
void setZeroInplace(Matrix<int>& mat)
{
  // Check for empty matrix
  if(mat.size()==0 || mat[0].size()==0)
    return ;

  // Flags to check if the first row/column has zero entries
  bool firstRowHasZero = false;
  bool firstColHasZero = false;

  // Number of rows and columns
  const int nrow = static_cast<int>(mat.size());
  const int ncol = static_cast<int>(mat[0].size()); // There is at least 
                                                    // one row

  // Check if first row has a zero, loop over columns
  for(int coli = 0; coli < ncol; coli++)
  {
    if(mat[0][coli]==0)
    {
      firstRowHasZero = true;
      break;
    }
  }

  // Check if the first column has zero, loop over the rows
  for(int rowi = 0; rowi < nrow; ++rowi)
  {
    if(mat[rowi][0]==0)
    {
      firstColHasZero = true;
      break;
    }
  }

  // Loop over the entries, if mat[i][j]==0, set mat[0,j]==0, mat[i][0]==0
  // Note that we start from 1, since the first row/column has already been
  // scanned.
  for(int rowi=1; rowi < nrow; ++rowi)
  {
    for(int coli=1; coli < ncol; ++coli)
    {
      if(mat[rowi][coli]==0)
      {
        mat[0][coli] = 0;
        mat[rowi][0] = 0;
      }
    }
  }

  // Nullify columns:
  // Scan the first row (loop through cols) and set the col to zero
  for(int coli = 1; coli < ncol; ++coli)
  {
    if(mat[0][coli]==0)
    {
      nullifyColumn(mat,coli);
    }
  }

  // Nullify rows:
  // Scan the first column (loop through rows) and set the row to zero
  for(int rowi = 1; rowi < nrow; ++rowi)
  {
    if(mat[rowi][0]==0)
    {
      nullifyRow(mat,rowi);
    }
  }

  // Nullify first row if required
  if(firstRowHasZero)
  {
    nullifyRow(mat,0);
  }

  // Nullify first column if required
  if(firstColHasZero)
  {
    nullifyColumn(mat,0);
  }
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    Matrix<int> m1{{}};
    setZero(m1);
    Matrix<int> a1{{}};
    REQUIRE(m1==a1);
  }

  SECTION("Sec Testing ")
  {
    Matrix<int> m1{{0}};
    setZero(m1);
    Matrix<int> a1{{0}};
    REQUIRE(m1==a1);
  }

  SECTION("Sec Testing ")
  {
    Matrix<int> m1{{1}};
    setZero(m1);
    Matrix<int> a1{{1}};
    REQUIRE(m1==a1);
  }

  SECTION("Sec Testing ")
  {
    Matrix<int> m1{{1,2,3},
                   {4,0,6},
                   {7,8,9}};
    setZero(m1);
    Matrix<int> a1{{1,0,3},
                   {0,0,0},
                   {7,0,9}};   
    REQUIRE(m1==a1);
  }

  ///////////////////////////////
  ///////////////////////////////
  // in-place version
  SECTION("Sec Testing ")
  {
    Matrix<int> m1{{}};
    setZeroInplace(m1);
    Matrix<int> a1{{}};
    REQUIRE(m1==a1);
  }

  SECTION("Sec Testing ")
  {
    Matrix<int> m1{{0}};
    setZeroInplace(m1);
    Matrix<int> a1{{0}};
    REQUIRE(m1==a1);
  }

  SECTION("Sec Testing ")
  {
    Matrix<int> m1{{1}};
    setZeroInplace(m1);
    Matrix<int> a1{{1}};
    REQUIRE(m1==a1);
  }

  SECTION("Sec Testing ")
  {
    Matrix<int> m1{{1,2,3},
                   {4,0,6},
                   {7,8,9}};
    setZeroInplace(m1);
    Matrix<int> a1{{1,0,3},
                   {0,0,0},
                   {7,0,9}};   
    REQUIRE(m1==a1);
  }
}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

