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
** @author  Ben Johnson
**
**          DateCreated: Monday October 20, 2014
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

/*------------------------------[Include Files]-------------------------------*/
#include <cstdio>
#include <cstdlib>

#include "Vector.hh"


/*-------------------------------[Begin Code]---------------------------------*/
/**
********************************************************************************
** FUNCTION DEFINITIONS GO HERE!!!!
**
**
**
********************************************************************************
*/
Vector::Vector(unsigned int n)
{
    ndims = n;

    /*
    ** Ensure the number of vector elements is at least 1
    */
    if (ndims < 1 )
    {
        printf("ERROR: PUT SOMETHING INFORMATIVE HERE!!!!\n");
        exit(EXIT_FAILURE);
    }

    pVec = new double [ndims];

    /*
    ** Initialize all vector elements to zero
    */
    for (UINT32 i = 0; i < ndims; i++)
    {
        pVec[i] = 0.0;
    }
}



