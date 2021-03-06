/**
********************************************************************************
** @file    Matrix.hh
**
** @brief   Declaration of the Matrix and MatrixRow classes
**
** @details All members and methods of the Matrix and MatrixRow classes are
**          declared here.
**
** @author  $Format:%an$
**
** @date    $Format:%cD$
**
** @copyright Copyright 2015 by Ben Johnson\n
**            You can freely redistribute and/or modify the contents of this
**            file under the terms of the GNU General Public License version 3,
**            or any later versions.
********************************************************************************
*/

/*
********************************************************************************
**  Matrix.hh
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

#ifndef _MATRIX_HH_
#define _MATRIX_HH_

/*------------------------------[Include Files]-------------------------------*/
#include "StdTypes.hh"


/*-------------------------------[Begin Code]---------------------------------*/
/**
********************************************************************************
** @class   MatrixRow
** @brief   Storage class for Matrix rows
** @details To effectively access the Matrix elements, a storage class is needed
**          to store a row of a Matrix object. This allows direct access to the
**          columns within a particular row.
********************************************************************************
*/
class MatrixRow
{
    private:
        UINT32 ncols;   /* Number of elements in the matrix row */

        double* pRow;   /* Pointer to the elements in a matrix row */

    public:

        /**
        ** @brief Default constructor (disabled)
        */
        MatrixRow();

        /*
        ** Constructor (two parameters)
        */
        MatrixRow(double* rowData, const UINT32& n);

        /**
        ** @brief Default destructor
        */
        ~MatrixRow() = default;

        /*
        ** Check the index to ensure it is within the accessible range
        */
        void checkInd(const UINT32& ind);

        /*
        ** Operator
        */
        double& operator[](const UINT32& index);
};

/**
********************************************************************************
** @class   Matrix
** @brief   Incorporate m x n matrix math
** @details A class to implement general m x n matrices and perform various math
**          operations with other Matrix or Vector objects.
********************************************************************************
*/
class Matrix
{
    private:
        UINT32 mrows;       /* Number of rows */
        UINT32 ncols;       /* Number of columns */

        double* pMatrix;    /* Pointer to the matrix elements */

        /*
        ** Enumerations for use when performing matrix decompositions
        */
        enum {MATRIX_DECOMP_RANK,
              MATRIX_DECOMP_DET};

    public:

        /**
        ** @brief Default constructor (disabled)
        */
        Matrix();

        /*
        ** Constructor (two parameters)
        */
        Matrix(const UINT32& m, const UINT32& n);

        /*
        ** Constructor (three parameters)
        */
        Matrix(const double* matArray, const UINT32& m, const UINT32& n);

        /*
        ** Default copy constructor
        */
        Matrix(const Matrix& rhs);

        /*
        ** Default copy assignment
        */
        Matrix& operator=(const Matrix& rhs);

        /*
        ** Default move constructor
        */
        Matrix(Matrix&& rhs);

        /*
        ** Default move assignment
        */
        Matrix& operator=(Matrix&& rhs);

        /**
        ** @brief Default destructor
        */
        ~Matrix() = default;

        /*
        ** Check the matrix dimensions to ensure the number of rows and columns
        ** are both greater than zero
        */
        void checkSize(const UINT32& m, const UINT32& n);

        /*
        ** Check two matrices to ensure they are the same size
        */
        void checkEqualSize(const UINT32& m1, const UINT32& n1,
                            const UINT32& m2, const UINT32& n2);

        /*
        ** Check two matrices to ensure they are conformable for multiplication
        */
        void checkConformable(const UINT32& n1, const UINT32& m2);

        /*
        ** Check the matrix row index to ensure it is within the accessible
        ** range
        */
        void checkRowInd(const UINT32& m);

        /*
        ** Check the matrix column index to ensure it is within the accessible
        ** range
        */
        void checkColInd(const UINT32& n);

        /*
        ** Calculate the rank of the matrix
        */
        UINT32 rank(void);

        /*
        ** Calculate the determinant of a square matrix
        */
        double determinant(void);

        /*
        ** Calculate the QR decomposition of the matrix
        */
        void QRdecomp(INT32 decompFlag, double& det, UINT32& matRank);

        /*
        ** Operators
        */
        Matrix& operator-=(const Matrix& rhs);
        Matrix& operator*=(const double& rhs);
        const Matrix operator-(const Matrix& rhs) const;
        const Matrix operator*(const Matrix& rhs);
        MatrixRow operator[](const UINT32& rowInd);

        friend Matrix operator*(const double& lhs, const Matrix& rhs);
        friend Matrix operator*(const Matrix& lhs, const double& rhs);

        /*
        ** Print object information
        */
        void objPrint(void) const;

        /*
        ** Access methods
        */

        /*
        ** Return a sub matrix from the current matrix object
        */
        Matrix getSubMatrix(const UINT32& startRow, const UINT32& startCol,
                            const UINT32& endRow, const UINT32& endCol) const;

        /*
        ** Return the number of rows in the matrix
        */
        UINT32 getRows(void) const;

        /*
        ** Return the number of columns in the matrix
        */
        UINT32 getCols(void) const;

};

#endif
