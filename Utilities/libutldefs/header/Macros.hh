/**
********************************************************************************
** @file    Macros.hh
**
** @brief   Define common macros
**
** @details Many C++ programs use a common set of preprocessor macros as
**          constants, flags, functions, or for other purposes. This file
**          defines common macros that are used throughout this program.
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
**  Macros.hh
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

#ifndef _MACROS_HH_
#define _MACROS_HH_

/*-------------------------------[Begin Code]---------------------------------*/
/**
********************************************************************************
** @def   CPU_64_BIT
** @brief A macro that is set if the user's computer is 64-bit.
**
** @def   CPU_32_BIT
** @brief A macro that is set if the user's computer is 32-bit.
********************************************************************************
*/
#if defined(__x86_64__) || defined(_M_x64)
    #define CPU_64_BIT
#else
    #define CPU_32_BIT
#endif

/**
********************************************************************************
** @def   FLT_TOL
** @brief Smallest precision for a floating point variable.
********************************************************************************
*/
#define FLT_TOL 1E-6

/**
********************************************************************************
** @def   sgn(x)
** @brief Signum function to find the sign of a number
********************************************************************************
*/
#define sgn(x) ((x > 0) - (x < 0))

/*
********************************************************************************
** Documentation macros for doxygen use
********************************************************************************
*/
#ifdef DOXYGEN_ONLY
    #ifndef CPU_64_BIT
    #define CPU_64_BIT
    #endif

    #ifndef CPU_32_BIT
    #define CPU_32_BIT
    #endif
#endif

#endif
