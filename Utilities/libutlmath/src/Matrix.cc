/**
********************************************************************************
** @file    Matrix.cc
**
** @brief   Utility to handle m x n matrix math
**
** @details The Matrix class allows the definition of an m x n matrix with m
**          rows and n columns. Mathematical operations can also be performed
**          with other conformable objects, such as a Matrix or Vector object.
**
** @author  $Format:%an$
**
** @date    $Format:%cD$
**
** @copyright Copyright 2015 by Benjamin Johnson\n
**            You can freely redistribute and/or modify the contents of this
**            file under the terms of the GNU General Public License version 3,
**            or any later versions.
********************************************************************************
*/

/*
********************************************************************************
**  Matrix.cc
**
**  (C) Copyright 2015 by Ben Johnson
**
**  This is free software: you can redistribute it and/or modify it under the
**  terms of the GNU General Public License as published by the Free Software
**  Foundation, either version 3 of the License, or (at your option) any later
**  version.
**
**  This is distributed in the hope that it will be useful, but WITHOUT ANY
**  WARRANTY; without even the implied warranty of MERCHANTIBILITY or FITNESS
**  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
**  details.
**
**  A copy of the license can be found at <http://www.gnu.org/licenses/>.
********************************************************************************
*/

/*------------------------------[Include Files]-------------------------------*/
#include <cstdio>
#include <cstdlib>

#include "Matrix.hh"

/*-------------------------------[Begin Code]---------------------------------*/
/**
********************************************************************************
** @details Matrix class constructor
** @param   m   Number of rows
** @param   n   Number of columns
********************************************************************************
*/
Matrix::Matrix(const UINT32& m, const UINT32& n)
{
    mrows = m;
    ncols = n;

    pMatrix = new double [mrows*ncols];

    for (UINT32 i = 0; i < mrows; i++)
    {
        for (UINT32 j = 0; j < ncols; j++)
        {
            pMatrix[i*ncols + j] = 0;
        }
    }
}

/**
********************************************************************************
** @details Matrix class constructor
** @param   matArray    Array of values to assign to the Matrix object
** @param   m           Number of rows
** @param   n           Number of columns
********************************************************************************
*/
Matrix::Matrix(const double* data, const UINT32& m, const UINT32& n)
{
    mrows = m;
    ncols = n;

    pMatrix = new double [mrows*ncols];

    for (UINT32 i = 0; i < mrows; i++)
    {
        for (UINT32 j = 0; j < ncols; j++)
        {
            pMatrix[i*ncols + j] = data[i*ncols + j];
        }
    }
}

/**
********************************************************************************
** @details Verify the number of rows and columns is greater than zero
** @param   m   Number of rows
** @param   n   Number of columns
********************************************************************************
*/
void Matrix::checkSize(const UINT32& m, const UINT32& n)
{
    checkRowInd(m);
    checkColInd(n);
}

/**
********************************************************************************
** @details Ensure the row index is not outside the accessible indices
** @param   m   Row index
********************************************************************************
*/
void Matrix::checkRowInd(const UINT32& m)
{
    if (m < 0 || m >= mrows)
    {
        printf("Error - Attempting to access matrix row index %d\n"
               "        Range of row indices: 0-%d\n",
               m,mrows-1);
        exit(EXIT_FAILURE);
    }
}

/**
********************************************************************************
** @details Ensure the column index is not outside the accessible indices
** @param   n   Column index
********************************************************************************
*/
void Matrix::checkColInd(const UINT32& n)
{
    if (n < 0 || n >= ncols)
    {
        printf("Error - Attempting to access matrix column index %d\n"
               "        Range of column indices: 0-%d\n",
               n,ncols-1);
        exit(EXIT_FAILURE);
    }
}

/**
********************************************************************************
** @details Access the specified Matrix row
** @param   index   Matrix row index
********************************************************************************
*/
MatrixRow Matrix::operator[](const UINT32& rowInd)
{
    checkRowInd(rowInd);

    return(MatrixRow(&pMatrix[rowInd*ncols],ncols));
}

/**
********************************************************************************
** @details MatrixRow class constructor
** @param   matRow  Pointer to data in a Matrix row
********************************************************************************
*/
MatrixRow::MatrixRow(const double* data,const UINT32& n)
{
    ncols = n;
    pRow = new double [ncols];

    for (UINT32 i = 0; i < ncols; i++)
    {
        pRow[i] = data[i];
    }
}

/**
********************************************************************************
** @details Ensure the MatrixRow index is not outside accessible indices
** @param   ind Column index
********************************************************************************
*/
void MatrixRow::checkInd(const UINT32& ind)
{
    if (ind < 0 || ind >= ncols)
    {
        printf("Error - Attempting to access MatrixRow column index %d\n"
               "        Range of column indices: 0-%d\n",
               ind,ncols-1);
        exit(EXIT_FAILURE);
    }
}

/**
********************************************************************************
** @details Verify the number of rows and columns is greater than zero
** @param   m   Number of rows
** @param   n   Number of columns
********************************************************************************
*/
double MatrixRow::operator[](const UINT32& index)
{
    checkInd(index);

    return(pRow[index]);
}









