/**
********************************************************************************
** @file    StdTypes.hh
**
** @brief   Definition of variable types and standard macros
**
** @details All C++ variable types are defined using typedef, along with boolean
**          true and false values and the NULL macro.
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
**  StdTypes.hh
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

#ifndef _STD_TYPES_HH_
#define _STD_TYPES_HH_

/*------------------------------[Include Files]-------------------------------*/
#include "Macros.hh"

/*-------------------------------[Begin Code]---------------------------------*/
/**
********************************************************************************
** @def   true
** @brief Boolean type definition for true if the compiler does not define it
**
** @def   false
** @brief Boolean type definition for false if the compiler does not define it
**
** @def   NULL
** @brief Defined value for NULL if the compiler does not define it
**
********************************************************************************
*/

/*
** Type define each standard C++ variable type for a 64-bit processor
*/
#ifdef CPU_64_BIT
    typedef unsigned char      UINT8;   /**< 8-bit unsigned variable for 64-bit
                                        **   CPU */
    typedef unsigned short int UINT16;  /**< 16-bit unsigned variable for 64-bit
                                        **   CPU */
    typedef unsigned int       UINT32;  /**< 32-bit unsigned variable for 64-bit
                                        **   CPU */
    typedef unsigned long int  UINT64;  /**< 64-bit unsigned variable for 64-bit
                                        **   CPU */

    typedef signed char      INT8;      /**< 8-bit signed variable for 64-bit
                                        **   CPU */
    typedef signed short int INT16;     /**< 16-bit signed variable for 64-bit
                                        **   CPU */
    typedef signed int       INT32;     /**< 32-bit signed variable for 64-bit
                                        **   CPU */
    typedef signed long int  INT64;     /**< 64-bit signed variable for 64-bit
                                        **   CPU */
#endif

/*
** Type define each standard C++ variable type for a 32-bit processor
*/
#ifdef CPU_32_BIT
    typedef unsigned char          UINT8;   /**< 8-bit unsigned variable for
                                            **   32-bit CPU */
    typedef unsigned short int     UINT16;  /**< 16-bit unsigned variable for
                                            **   32-bit CPU */
    typedef unsigned int           UINT32;  /**< 32-bit unsigned variable for
                                            **   32-bit CPU */
    typedef unsigned long long int UINT64;  /**< 64-bit unsigned variable for
                                            **   32-bit CPU */

    typedef signed char          INT8;  /**< 8-bit signed variable for 32-bit
                                        **   CPU */
    typedef signed short int     INT16; /**< 16-bit signed variable for 32-bit
                                        **   CPU */
    typedef signed int           INT32; /**< 32-bit signed variable for 32-bit
                                        **   CPU */
    typedef signed long long int INT64; /**< 64-bit signed variable for 32-bit
                                        **   CPU */
#endif

/*
** Define the boolean keyword, along with true and false, if they are not
** already defined
*/
#ifndef __cplusplus
typedef UINT32 bool;    /**< Boolean data type, if not defined */

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#endif

#ifndef NULL
#define NULL 0
#endif

/*
** Floating point variables are defined according to the IEEE 754 standard and
** do not need to be defined.
*/
#endif
