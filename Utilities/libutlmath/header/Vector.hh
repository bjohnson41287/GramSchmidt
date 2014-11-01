/**
********************************************************************************
** @file    Vector.hh
**
** @brief   Declaration of the Vector class
**
** @details All members of methods of the Vector class are declared here.
**
** @author  Ben Johnson
**
**          Date Created: Monday October 20, 2014
** @date    Tuesday October 28, 2014
**
** @copyright Copyright 2014 by Benjamin Johnson\n
**            You can freely redistribute and/or modify the contents of this
**            file under the terms of the GNU General Public License version 3,
**            or any later versions.
********************************************************************************
*/

/*
********************************************************************************
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
**
**
**
********************************************************************************
*/
class Vector
{
    private:
        unsigned int ndims;   /* Number of dimensions (elements) in the vector */

        double* pVec;         /* Pointer to the vector elements */

    public:

        /*
        ** Default constructor (disabled)
        */
        Vector() = delete;

        /*
        ** Constructor (one parameter)
        */
        Vector(unsigned int n);

        /*
        ** Default copy constructor (disabled)
        */
        Vector(const Vector&) = delete;

        /*
        ** Default copy assignment (disabled)
        */
        Vector& operator=(const Vector&) = delete;

        /*
        ** Default move constructor
        **
        */
        Vector(Vector&&) = default;

        /*
        ** Default move assignment
        */
        Vector& operator=(Vector&&) = default;

        /*
        ** Default destructor (disabled)
        */
        ~Vector();


};








#endif
