/**
********************************************************************************
** @file    Vector.hh
**
** @brief   Declaration of the Vector class
**
** @details All members and methods of the Vector class are declared here.
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
**  Vector.hh
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

#ifndef _VECTOR_HH_
#define _VECTOR_HH_

/*------------------------------[Include Files]-------------------------------*/
#include "StdTypes.hh"
#include "Matrix.hh"


/*-------------------------------[Begin Code]---------------------------------*/
/**
********************************************************************************
** @class   Vector
** @brief   Incorporate n-dimensional vectors and vector math operations
** @details A class to implement general n-dimensional vectors and perform
**          various vector math operations.
********************************************************************************
*/
class Vector
{
    private:
        UINT32 ndims;   /* Number of dimensions (elements) in the vector */

        double* pVec;   /* Pointer to the vector elements */

    public:

        /*
        ** Default constructor
        */
        Vector();

        /*
        ** Constructor (one parameter)
        */
        Vector(const UINT32& n);

        /*
        ** Constructor (two parameters)
        */
        Vector(const double* vals, const UINT32& n);

        /*
        ** Default copy constructor
        */
        Vector(const Vector& vec);

        /*
        ** Default copy assignment
        */
        Vector& operator=(const Vector& rhs);

        /*
        ** Default move constructor
        */
        Vector(Vector&& vec);

        /*
        ** Default move assignment
        */
        Vector& operator=(Vector&& rhs);

        /**
        ** @brief Default destructor
        */
        ~Vector() = default;

        /*
        ** Check the vector dimension to ensure it is greater than zero
        */
        void checkSize(const UINT32& n) const;

        /*
        ** Check the sizes of both vector objects before an operation takes
        ** place with an overloaded operator
        */
        void checkOperatorSize(const UINT32& n1, const UINT32& n2) const;

        /*
        ** Vector norm (magnitude)
        */
        double norm(void);

        /*
        ** Outer product of two vectors
        */
        Matrix outer(const Vector& rhs) const;

        /*
        ** Operators
        */
        Vector& operator+=(const Vector& rhs);
        const Vector operator+(const Vector& rhs) const;
        double operator*(const Vector& rhs) const;
        double& operator[](const UINT32 i) const;
        double& operator[](const INT32 i) const;

        /*
        ** Print object information
        */
        void objPrint(void) const;

        /*
        ** Access methods
        */

        /*
        ** Set the size and elements of the vector from a column array
        */
        void setVector(const double* vals, const UINT32& n);

        /*
        ** Get the vector dimension
        */
        const UINT32& getSize(void) const;
};

#endif
