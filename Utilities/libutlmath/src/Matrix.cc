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
#include <cmath>

#include "Matrix.hh"
#include "Vector.hh"

/*-------------------------------[Begin Code]---------------------------------*/
/*-----------------------------[Matrix Methods]-------------------------------*/
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
    
    checkSize(mrows,ncols);
    pMatrix = new double [mrows*ncols];

    for (UINT32 i = 0; i < mrows*ncols; i++)
    {
        pMatrix[i] = 0;
    }
}

/**
********************************************************************************
** @details Matrix class constructor
** @param   data    Array of values to assign to the Matrix object
** @param   m       Number of rows
** @param   n       Number of columns
********************************************************************************
*/
Matrix::Matrix(const double* data, const UINT32& m, const UINT32& n)
{
    mrows = m;
    ncols = n;

    checkSize(mrows,ncols);
    pMatrix = new double [mrows*ncols];

    for (UINT32 i = 0; i < mrows*ncols; i++)
    {
        pMatrix[i] = data[i];
    }
}

/**
********************************************************************************
** @details Matrix copy constructor
** @param   rhs Matrix object
********************************************************************************
*/
Matrix::Matrix(const Matrix& rhs)
{
    mrows = rhs.mrows;
    ncols = rhs.ncols;
    pMatrix = new double [mrows*ncols];

    for (UINT32 i = 0; i < mrows*ncols; i++)
    {
        pMatrix[i] = rhs.pMatrix[i];
    }
}

/**
********************************************************************************
** @details Matrix move constructor
** @param   rhs Matrix object lvalue reference
********************************************************************************
*/
Matrix::Matrix(Matrix&& rhs)
{
    pMatrix = rhs.pMatrix;
    mrows = rhs.mrows;
    ncols = rhs.ncols;

    rhs.pMatrix = NULL;
    rhs.mrows = 0;
    rhs.ncols = 0;
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
    if (m <= 0)
    {
        printf("Error - %s\n"
               "        Matrix object with %d rows\n",
               __PRETTY_FUNCTION__,m);
        exit(EXIT_FAILURE);
    }
    else if (n <= 0)
    {
        printf("Error - %s\n"
               "        Matrix object with %d columns\n",
               __PRETTY_FUNCTION__,n);
        exit(EXIT_FAILURE);
    }
}

/**
********************************************************************************
** @details Verify the dimensions of two matrices are equal
** @param   m1  Number of rows in the first matrix
** @param   n1  Number of columns in the first matrix
** @param   m2  Number of rows in the second matrix
** @param   n2  Number of columns in the second matrix
********************************************************************************
*/
void Matrix::checkEqualSize(const UINT32& m1, const UINT32& n1,
                            const UINT32& m2, const UINT32& n2)
{
    if (m1 != m2 || n1 != n2)
    {
        printf("Error - %s\n"
               "        Matrix dimensions are not equal\n",__PRETTY_FUNCTION__);
        exit(EXIT_FAILURE);
    }
}

/**
********************************************************************************
** @details Verify two matrices are conformable for multiplication
** @param   n1  Number of columns in the first matrix
** @param   m2  Number of rows in the second matrix
********************************************************************************
*/
void Matrix::checkConformable(const UINT32& n1, const UINT32& m2)
{
    if (n1 != m2)
    {
        printf("Error - %s\n"
               "        Matrices are not conformable\n",
               __PRETTY_FUNCTION__);
        exit(EXIT_FAILURE);
    }
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
** @details Calculate the rank of the matrix from the QR decomposition with a
**          Householder Transformation
** @return  Rank of the matrix
********************************************************************************
*/
UINT32 Matrix::rank(void)
{
    UINT32 matRank;
    double det;

    /*
    ** Use the QR decomposition to calculate the rank of the matrix. This will
    ** also calculate the determinant if the matrix is square.
    */
    QRdecomp(MATRIX_DECOMP_RANK,det,matRank);

    return(matRank);
}

/**
********************************************************************************
** @details Calculate the determinant of a square matrix using the QR
**          decomposition with a Householder Transformation
** @return  Determinant of a square matrix
********************************************************************************
*/
double Matrix::determinant(void)
{
    UINT32 matRank;
    double det;

    /*
    ** Use the QR decomposition to calculate the rank and determinant of the
    ** matrix if the matrix is square
    */
    if (mrows != ncols)
    {
        printf("Error - %s\n"
               "        Determinant undefined for a non-square matrix\n",
               __PRETTY_FUNCTION__);
        exit(EXIT_FAILURE);
    }

    QRdecomp(MATRIX_DECOMP_DET,det,matRank);

    return(det);
}

/**
********************************************************************************
** @details Calculate the QR decomposition using the Householder Transformation
**          to return the determinant of a square matrix or the rank of any
**          matrix
** @param   decompFlag  Flag indicating if the determinant or rank is returned
** @param   det         Reference for the determinant, if a square matrix
** @param   matrixRank  Reference for the rank
********************************************************************************
*/
void Matrix::QRdecomp(INT32 decompFlag, double& det, UINT32& matrixRank)
{
    UINT32 n;
    UINT32 newARows;
    UINT32 newACols;
    UINT32 matRank;

    double kVal;
    double matDet;
    double subIdent[(mrows-1)*mrows];
    double vecData[mrows];

    double* pNewA;

    matRank = 0;
    matDet = 1;

    /*
    ** Find the smaller matrix dimension
    */
    n = MIN(mrows,ncols);

    /*
    ** If there is only one row or column in the matrix, then look for nonzero
    ** values. If any are found, then return a rank of 1. If the matrix only has
    ** one element, then set the determinant equal to that element.
    */
    if (1 == n)
    {
        for (UINT32 i = 0; i < n; i++)
        {
            if (fabs(pMatrix[i]) >= FLOAT_TOL)
            {
                matRank++;
                break;
            }
        }

        if (mrows == ncols)
        {
            det = pMatrix[0];
        }
        matrixRank = matRank;

        return;
    }

    newARows = mrows;
    newACols = ncols;

    pNewA = pMatrix;

    /*
    ** Instantiate an (mrows-1) x mrows identity matrix, which is just an
    ** mrows x mrows identity matrix without the first row. For each loop
    ** through the n-1 columns or rows of the matrix object, successive top rows
    ** and left columns will not be used from this sub identity matrix to form
    ** the sub matrix of the Householder Transformation matrix.
    */
    for (UINT32 i = 0; i < mrows-1; i++)
    {
        for (UINT32 j = 0; j < mrows; j++)
        {
            if (i+1 == j)
            {
                subIdent[i*mrows + j] = 1;
            }
            else
            {
                subIdent[i*mrows + j] = 0;
            }
        }
    }

    Matrix subIdentity(subIdent,mrows-1,mrows);

    /*
    ** Loop through the smaller dimension n-1 times if n > 1
    */
    for (UINT32 i = 0; i < n-1; i++)
    {
        /*
        ** Store the first column of the A' matrix in a Vector object
        */
        for (UINT32 j = 0; j < newARows; j++)
        {
            vecData[j] = pNewA[j*newACols];
        }

        Vector colVec(vecData,newARows);

        /*
        ** Calculate the vector norm and check if it is considered to be zero
        */
        kVal = colVec.mag();
        if (fabs(kVal) < FLOAT_TOL)
        {
            if (mrows == ncols)
            {
                matDet = 0;
            }

            if (MATRIX_DECOMP_DET == decompFlag)
            {
                det = matDet;
                return;
            }

            /*
            ** When kVal = 0, then the column vector is already full of zeros
            ** and the loop will just continue to the next submatrix column
            */
            for (UINT32 j = 0; j < newARows-1; j++)
            {
                for (UINT32 k = 0; k < newACols-1; k++)
                {
                    pNewA[j*(newACols-1) + k] = pNewA[(j+1)*newACols + (k+1)];
                }
            }
            newARows--;
            newACols--;
            continue;
        }

        /*
        ** Set the correct sign for kVal to avoid numerical instability and
        ** calculate the elements of the v hat vector. Also calculate the
        ** determinant for a square matrix and increment the rank counter.
        */
        kVal = -sgn(colVec[0])*kVal;

        if (mrows == ncols)
        {
            matDet *= kVal;
        }
        matRank++;

        vecData[0] = sqrt((kVal - colVec[0])/(2*kVal));

        for (UINT32 j = 1; j < newARows; j++)
        {
            vecData[j] = -colVec[j]/(2*kVal*vecData[0]);
        }

        Vector vHat(vecData,newARows);
        Vector vHatSub(vecData+1,newARows-1);

        /*
        ** Form the identity matrix from row 2 to the end and use it to
        ** calculate the Householder Transformation matrix from row 2 to the end
        */
        Matrix newA(pNewA,newARows,newACols);
        Matrix hhSub(vHatSub.getSize(),vHat.getSize());
        Matrix identSub(vHatSub.getSize(),vHat.getSize());

        identSub = subIdentity.getSubMatrix(i,i,subIdentity.getRows()-1,
                                            subIdentity.getCols()-1);
        hhSub = identSub - 2*vHatSub.outer(vHat);

        /*
        ** Calculate the new A' matrix for the next loop iteration and store the
        ** matrix data pointer
        */
        pNewA = (hhSub*newA.getSubMatrix(0,1,newARows-1,newACols-1)).pMatrix;
        
        newARows--;
        newACols--;
    }

    /*
    ** Evaluate the determinant for a square matrix and the final rank counter
    */
    kVal = 0;
    for (UINT32 i = 0; i < newARows*newACols; i++)
    {
        kVal += pNewA[i]*pNewA[i];
    }

    kVal = sqrt(kVal);
    if (fabs(kVal) >= FLOAT_TOL)
    {
        if (mrows == ncols)
        {
            matDet *= pNewA[0];
            if ((ncols-1) % 2)
            {
                matDet *= -1;
            }
        }
        matRank++;
    }
    else if (mrows == ncols)
    {
        matDet = 0;
    }

    det = matDet;
    matrixRank = matRank;
}

/**
********************************************************************************
** @details Matrix subtraction compound assignment
** @param   rhs Matrix object
** @return  Calling object with subtracted values
********************************************************************************
*/
Matrix& Matrix::operator-=(const Matrix& rhs)
{
    checkEqualSize(mrows,ncols,rhs.mrows,rhs.ncols);
    for (UINT32 i = 0; i < mrows*ncols; i++)
    {
        pMatrix[i] -= rhs.pMatrix[i];
    }

    return(*this);
}

/**
********************************************************************************
** @details Matrix multiplied by a double compound assignment
** @param   rhs double data type
** @return  Calling object with every element multiplied by rhs
********************************************************************************
*/
Matrix& Matrix::operator*=(const double& rhs)
{
    for (UINT32 i = 0; i < mrows*ncols; i++)
    {
        pMatrix[i] *= rhs;
    }

    return(*this);
}

/**
********************************************************************************
** @details Matrix subtraction with another Matrix object
** @param   rhs Matrix object
** @return  New Matrix object with subtraction of elements
********************************************************************************
*/
const Matrix Matrix::operator-(const Matrix& rhs) const
{
    Matrix result(*this);
    result -= rhs;

    return(result);
}

/**
********************************************************************************
** @details Matrix A multiplied by a matrix B
** @param   rhs Matrix object B
** @return  New Matrix object C = A*B
********************************************************************************
*/
const Matrix Matrix::operator*(const Matrix& rhs)
{
    checkConformable(ncols,rhs.mrows);
    double multMat[mrows*rhs.ncols];

    for (UINT32 i = 0; i < mrows; i++)
    {
        for (UINT32 j = 0; j < rhs.ncols; j++)
        {
            multMat[i*rhs.ncols + j] = 0;

            for (UINT32 k = 0; k < ncols; k++)
            {
                multMat[i*rhs.ncols + j] += pMatrix[i*ncols + k]*
                                            rhs.pMatrix[k*rhs.ncols + j];
            }
        }
    }

    Matrix result(multMat,mrows,rhs.ncols);

    return(result);
}

/**
********************************************************************************
** @details Double multiplied by a matrix
** @param   lhs double data type
** @param   rhs Matrix object
** @return  New Matrix object with every element multiplied by lhs
********************************************************************************
*/
Matrix operator*(const double& lhs, const Matrix& rhs)
{
    Matrix result(rhs);
    result *= lhs;

    return(result);
}

/**
********************************************************************************
** @details Matrix multiplied by a double
** @param   lhs Matrix object
** @param   rhs double data type
** @return  Matrix object with every element multiplied by rhs
********************************************************************************
*/
Matrix operator*(const Matrix& lhs, const double& rhs)
{
    return(rhs*lhs);
}

/**
********************************************************************************
** @details Access the specified Matrix row
** @param   rowInd  Matrix row index
** @return  MatrixRow object
********************************************************************************
*/
MatrixRow Matrix::operator[](const UINT32& rowInd)
{
    checkRowInd(rowInd);

    return(MatrixRow(pMatrix + rowInd*ncols,ncols));
}

/**
********************************************************************************
** @details Matrix copy assignment operator
** @param   rhs Matrix lvalue reference object
** @return  Calling object with rhs values
********************************************************************************
*/
Matrix& Matrix::operator=(const Matrix& rhs)
{
    checkEqualSize(mrows,ncols,rhs.mrows,rhs.ncols);

    for (UINT32 i = 0; i < mrows*ncols; i++)
    {
        pMatrix[i] = rhs.pMatrix[i];
    }

    return(*this);
}

/**
********************************************************************************
** @details Matrix move assignment operator
** @param   rhs Matrix rvalue reference object
** @return  Calling object with temporary's values
********************************************************************************
*/
Matrix& Matrix::operator=(Matrix&& rhs)
{
    if (this != &rhs)
    {
        checkEqualSize(mrows,ncols,rhs.mrows,rhs.ncols);

        delete[] pMatrix;
        pMatrix = rhs.pMatrix;
        mrows = rhs.mrows;
        ncols = rhs.ncols;

        rhs.pMatrix = NULL;
        rhs.mrows = 0;
        rhs.ncols = 0;
    }

    return(*this);
}

/**
********************************************************************************
** @details Print the number of rows and columns in the matrix object, along
**          with the matrix elements
********************************************************************************
*/
void Matrix::objPrint(void) const
{
    printf("Matrix size: %d x %d\n",mrows,ncols);

    if (1 == mrows*ncols)
    {
        printf("Matrix element\n");
    }
    else
    {
        printf("Matrix elements\n");
    }

    for (UINT32 i = 0; i < mrows; i++)
    {
        for (UINT32 j = 0; j < ncols; j++)
        {
            printf(" %12.3f",pMatrix[i*ncols + j]);
        }
        printf("\n");
    }
}

/**
********************************************************************************
** @details Extract a sub matrix from the current matrix object
** @param   startRow    First row index of the matrix to extract (0 indexed)
** @param   startCol    First column index of the matrix to extract (0 indexed)
** @param   endRow      Last row indes of the matrix to extract (0 indexed)
** @param   endCol      Last column index of the matrix to extract (0 indexed)
** @return  Extracted sub matrix
********************************************************************************
*/
Matrix Matrix::getSubMatrix(const UINT32& startRow, const UINT32& startCol,
                            const UINT32& endRow, const UINT32& endCol) const
{
    UINT32  subMatRows;
    UINT32  subMatCols;

    double* pSubMatrix;

    subMatRows = endRow - startRow + 1;
    subMatCols = endCol - startCol + 1;

    /*
    ** Ensure the indices given exist in the current matrix and that the ending
    ** indices are the same as or greater than the corresponding starting
    ** indices
    */
    if (startRow < 0 || startRow >= mrows)
    {
        printf("Error - Extracting sub matrix starting at row (%d)\n"
               "        Range of row indices: 0-%d\n",
               startRow,mrows);
        exit(EXIT_FAILURE);
    }
    else if (startCol < 0 || startCol >= ncols)
    {
        printf("Error - Extracting sub matrix starting at column (%d)\n"
               "        Range of column indices: 0-%d\n",
               startCol,ncols);
        exit(EXIT_FAILURE);

    }
    else if (endRow < 0 || endRow >= mrows)
    {
        printf("Error - Extracting sub matrix ending at row (%d)\n"
               "        Range of allowable row indices: %d-%d\n",
               endRow,startRow,mrows);
        exit(EXIT_FAILURE);
    }
    else if (endCol < 0 || endCol >= ncols)
    {
        printf("Error - Extracting sub matrix ending at column (%d)\n"
               "        Range of allowable column indices: %d-%d\n",
               endCol,startCol,ncols);
        exit(EXIT_FAILURE);
    }
    else if (subMatRows <= 0)
    {
        printf("Error - %s\n"
               "        Value of endRow (%d) is less than startRow (%d)\n",
               __PRETTY_FUNCTION__,endRow,startRow);
        exit(EXIT_FAILURE);
    }
    else if (subMatCols <= 0)
    {
        printf("Error - %s\n"
               "        Value of endCol (%d) is less than startCol (%d)\n",
               __PRETTY_FUNCTION__,endCol,startCol);
        exit(EXIT_FAILURE);
    }

    /*
    ** Extract the sub matrix
    */
    pSubMatrix = new double [subMatRows*subMatCols];

    for (UINT32 i = 0; i < subMatRows; i++)
    {
        for (UINT32 j = 0; j < subMatCols; j++)
        {
            pSubMatrix[i*subMatCols + j] =
                pMatrix[(startRow+i)*ncols + (startCol+j)];
        }
    }

    return(Matrix(pSubMatrix,subMatRows,subMatCols));
}

/**
********************************************************************************
** @details Return the number of rows in the matrix
** @return  Number of rows in the matrix
********************************************************************************
*/
UINT32 Matrix::getRows(void) const
{
    return(mrows);
}

/**
********************************************************************************
** @details Return the number of columns in the matrix
** @return  Number of columns in the matrix
********************************************************************************
*/
UINT32 Matrix::getCols(void) const
{
    return(ncols);
}

/*----------------------------[MatrixRow Methods]-----------------------------*/
/**
********************************************************************************
** @details MatrixRow class constructor
** @param   rowData Pointer to data in a Matrix row
** @param   n       Number of columns in the Matrix row
********************************************************************************
*/
MatrixRow::MatrixRow(double* rowData,const UINT32& n)
{
    ncols = n;
    pRow = rowData;
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
** @details Access the specified MatrixRow element
** @param   index   MatrixRow index
** @return  Specified MatrixRow element
********************************************************************************
*/
double& MatrixRow::operator[](const UINT32& index)
{
    checkInd(index);

    return(pRow[index]);
}
