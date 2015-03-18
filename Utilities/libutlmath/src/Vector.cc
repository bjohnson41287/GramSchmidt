/**
********************************************************************************
** @file    Vector.cc
**
** @brief   Utility to handle n-dimensional vector math
**
** @details The Vector class gives the capability of defining n-dimensional
**          vectors and performing mathematical operations with other vector
**          objects.
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
**  Vector.cc
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

#include "Vector.hh"

/*-------------------------------[Begin Code]---------------------------------*/
/**
********************************************************************************
** @details Default Vector class constructor
********************************************************************************
*/
Vector::Vector()
{
    /*
    ** Initialize members
    */
    ndims = 0;
    pVec = NULL;
}

/**
********************************************************************************
** @details Vector class constructor
** @param   n   Number of vector elements
********************************************************************************
*/
Vector::Vector(const UINT32& n)
{
    ndims = n;
    checkSize(ndims);

    pVec = new double [ndims];

    for (UINT32 i = 0; i < ndims; i++)
    {
        pVec[i] = 0;
    }
}

/**
********************************************************************************
** @details Vector class constructor
** @param   vals    Pointer to a 1-D array
** @param   n       Number of elements in vals
********************************************************************************
*/
Vector::Vector(const double* vals, const UINT32& n)
{
    ndims = 0;
    pVec = NULL;
    setVector(vals,n);
}

/**
********************************************************************************
** @details Vector copy constructor
** @param   vec Vector object
********************************************************************************
*/
Vector::Vector(const Vector& vec)
{
    ndims = vec.ndims;
    pVec = new double [ndims];

    for (UINT32 i = 0; i < ndims; i++)
    {
        pVec[i] = vec.pVec[i];
    }
}

/**
********************************************************************************
** @details Vector move constructor
** @param   vec Vector object rvalue reference
********************************************************************************
*/
Vector::Vector(Vector&& vec)
{
    pVec = vec.pVec;
    ndims = vec.ndims;

    vec.pVec = NULL;
    vec.ndims = 0;
}

/**
********************************************************************************
** @details Verify the dimension of the vector is greater than zero
** @param   n   Vector dimension
********************************************************************************
*/
void Vector::checkSize(const UINT32& n) const
{
    if (n < 1)
    {
        printf("Error - %s\n"
               "        Vector dimension (%u) is less than 1\n",
               __PRETTY_FUNCTION__,n);
        exit(EXIT_FAILURE);
    }
}

/**
********************************************************************************
** @details Check the dimensions of 2 vector objects before an overloaded
**          operator method uses them
** @param   n1  Dimension of first vector object
** @param   n2  Dimension of second vector object
********************************************************************************
*/
void Vector::checkOperatorSize(const UINT32& n1, const UINT32& n2) const
{
    if (0 == n1 || 0 == n2)
    {
        printf("Error - %s\n"
               "        Zero element vector not allowed in operations. Use\n"
               "        the setVector method or instantiate with a different\n"
               "        constructor.\n",__PRETTY_FUNCTION__);
        exit(EXIT_FAILURE);
    }
    else if (n1 != n2)
    {
        printf("Error - %s\n"
               "        Vector sizes are not equal\n",
               __PRETTY_FUNCTION__);
        exit(EXIT_FAILURE);
    }
}

/**
********************************************************************************
** @details Calculate the vector norm (magnitude)
** @return  Norm, or magnitude, of the vector
********************************************************************************
*/
double Vector::norm(void)
{
    return(sqrt(*this*(*this)));
}

/**
********************************************************************************
** @details Calculate the outer product of two vectors
** @param   rhs Vector object
** @return  Outer product matrix object
********************************************************************************
*/
Matrix Vector::outer(const Vector& rhs) const
{
    UINT32 matRows;
    UINT32 matCols;
    double* pMatrix;

    matRows = ndims;
    matCols = rhs.ndims;
    pMatrix = new double [matRows*matCols];

    for (UINT32 i = 0; i < matRows; i++)
    {
        for (UINT32 j = 0; j < matCols; j++)
        {
            pMatrix[i*matCols + j] = pVec[i]*rhs.pVec[j];
        }
    }

    return(Matrix(pMatrix,matRows,matCols));
}
/**
********************************************************************************
** @details Vector addition compound assignment
** @param   rhs     Vector object
** @return  *this   Calling object with added values
********************************************************************************
*/
Vector& Vector::operator+=(const Vector& rhs)
{
    checkOperatorSize(ndims,rhs.ndims);
    for (UINT32 i = 0; i < ndims; i++)
    {
        pVec[i] += rhs.pVec[i];
    }

    return(*this);
}

/**
********************************************************************************
** @details Vector addition with another Vector object
** @param   rhs     Vector object
** @return  result  Vector object with addition of elements
********************************************************************************
*/
const Vector Vector::operator+(const Vector& rhs) const
{
    Vector result(*this);
    result += rhs;

    return(result);
}

/**
********************************************************************************
** @details Vector inner(dot) product
** @param   rhs Conformable Vector object
** @return  dotProd Vector dot product
********************************************************************************
*/
double Vector::operator*(const Vector& rhs) const
{
    double dotProd = 0;

    checkOperatorSize(ndims,rhs.ndims);
    for (UINT32 i = 0; i < ndims; i++)
    {
        dotProd += pVec[i]*rhs.pVec[i];
    }

    return(dotProd);
}

/**
********************************************************************************
** @details Vector element operator for UINT32 index
** @param   i       UINT32 vector index
** @return  pVec[i] Vector element
********************************************************************************
*/
double& Vector::operator[](const UINT32 i) const
{
    if (i > ndims-1)
    {
        printf("Error - %s\n"
               "        Vector index out of bounds: %d\n"
               "        Max Vector index: %u\n",
               __PRETTY_FUNCTION__,i,ndims-1);
        exit(EXIT_FAILURE);
    }

    return(pVec[i]);
}

/**
********************************************************************************
** @details Vector element operator for INT32 index
** @param   i       INT32 vector index
** @return  pVec[i] Vector element
********************************************************************************
*/
double& Vector::operator[](const INT32 i) const
{
    if (i < 0)
    {
        printf("Error - %s\n"
               "        Invalid vector index: %d\n",
               __PRETTY_FUNCTION__,i);
        exit(EXIT_FAILURE);
    }
    else if (i > (INT32)(ndims-1))
    {
        printf("Error - %s\n"
               "        Vector index out of bounds: %d\n"
               "        Max vector index: %u\n",
               __PRETTY_FUNCTION__,i,ndims-1);
        exit(EXIT_FAILURE);
    }

    return(pVec[i]);
}

/**
********************************************************************************
** @details Vector copy assignment operator
** @param   rhs     Vector lvalue reference object
** @return  *this   Calling object with rhs values
********************************************************************************
*/
Vector& Vector::operator=(const Vector& rhs)
{
    checkOperatorSize(ndims,rhs.ndims);

    for (UINT32 i = 0; i < ndims; i++)
    {
        pVec[i] = rhs.pVec[i];
    }

    return(*this);
}

/**
********************************************************************************
** @details Vector move assignment operator
** @param   rhs     Vector rvalue reference object
** @return  *this   Calling object with temporary's values
********************************************************************************
*/
Vector& Vector::operator=(Vector&& rhs)
{
    if (this != &rhs)
    {
        checkOperatorSize(ndims,rhs.ndims);

        delete[] pVec;
        pVec = rhs.pVec;
        ndims = rhs.ndims;

        rhs.pVec = NULL;
        rhs.ndims = 0;
    }

    return(*this);
}

/**
********************************************************************************
** @details Print the vector dimension and the elements
********************************************************************************
*/
void Vector::objPrint(void) const
{
    checkSize(ndims);
    printf("Vector dimension: %d\n",ndims);

    if (1 == ndims)
    {
        printf("Vector element\n");
    }
    else
    {
        printf("Vector elements\n");
    }

    for (UINT32 i = 0; i < ndims; i++)
    {
        printf(" %12.3f\n",pVec[i]);
    }
}

/**
********************************************************************************
** @details Set the elements of a vector from a 1-D array of doubles
** @param   vals    Pointer to a 1-D array
** @param   n       Number of elements in vals
********************************************************************************
*/
void Vector::setVector(const double* vals, const UINT32& n)
{
    if (ndims != 0 && ndims != n)
    {
        printf("Error - %s\n"
               "        Attempting to reset vector dimension from %u to %u\n",
               __PRETTY_FUNCTION__,ndims,n);
        exit(EXIT_FAILURE);
    }

    /*
    ** Set the vector dimension and ensure it is greater than zero
    */
    ndims = n;
    checkSize(ndims);

    if (NULL == pVec)
    {
        pVec = new double [ndims];
    }

    for (UINT32 i = 0; i < ndims; i++)
    {
        pVec[i] = vals[i];
    }
}

/**
********************************************************************************
** @details Return the vector dimension
** @return  ndims   Vector dimension
********************************************************************************
*/
const UINT32& Vector::getSize(void) const
{
    return(ndims);
}
