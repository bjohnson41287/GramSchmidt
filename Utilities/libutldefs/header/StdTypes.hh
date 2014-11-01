/**
********************************************************************************
** @file    StdTypes.hh
**
** @brief   Definition of variable types and standard macros
**
** @details All C++ variable types are defined using typedef, along with boolean
**          true and false values and the NULL macro.
**
** @author  Ben Johnson
**
**          Date Created: Sunday October 26, 2014
** @date    Monday October 27, 2014
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

#ifndef _STD_TYPES_HH_
#define _STD_TYPES_HH_

/*------------------------------[Include Files]-------------------------------*/
#include <stdio.h>

#include "Macros.hh"

/*-------------------------------[Begin Code]---------------------------------*/
/**
********************************************************************************
** ADD DOXYGEN COMMENTS HERE!!!! -> Describe the typedef use for each variable!
**
**
**
********************************************************************************
*/

/*
** Type define each standard C++ variable type for a 64-bit processor
*/
#if defined(CPU_64_BIT)
    typedef unsigned char      UINT8;
    typedef unsigned short int UINT16;
    typedef unsigned int       UINT32;
    typedef unsigned long int  UINT64;

    typedef signed char      INT8;
    typedef signed short int INT16;
    typedef signed int       INT32;
    typedef signed long int  INT64;
#elif defined(CPU_32_BIT)
    //printf("I'm a 32-bit computer!\n");
#endif

/*
** Define the true and false boolean keywords if they are not defined
*/
#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

/*
** TALK ABOUT WHY FLOATING POINT VARIABLES ARE NOT TYPE DEFINED!!!! -> DUE TO IEEE STANDARD
*/













#endif
