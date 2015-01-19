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
** @copyright Copyright 2014 by Ben Johnson\n
**            You can freely redistribute and/or modify the contents of this
**            file under the terms of the GNU General Public License version 3,
**            or any later versions.
********************************************************************************
*/

/*
********************************************************************************
**  Vector.hh
**
**  (C) Copyright 2014 by Ben Johnson
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

        /**
        ** @brief Default constructor (disabled)
        */
        Vector() = delete;

        /*
        ** Constructor (one parameter)
        */
        Vector(UINT32 n);

        /**
        ** @brief Default copy constructor (disabled)
        */
        Vector(const Vector&) = delete;

        /**
        ** @brief Default copy assignment (disabled)
        */
        Vector& operator=(const Vector&) = delete;

        /**
        ** @brief TODO: MOVE DOCUMENTATION Default move constructor
        */
        Vector(Vector&&) = default;

        /**
        ** @brief TODO: MOVE DOCUMENTATION Default move assignment
        */
        Vector& operator=(Vector&&) = default;

        /**
        ** @brief TODO: MOVE DOCUMENTATION Default destructor (disabled)
        */
        ~Vector() = default;

        /*
        ** Operators
        */
        Vector& operator=(const double*);


};








#endif
