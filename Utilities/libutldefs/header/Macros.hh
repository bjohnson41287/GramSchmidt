/**
********************************************************************************
** @file    Macros.hh
**
** @brief   Define common macros
**
** @details Many C++ programs use a common set of preprocessor macros as
**          constants, flags, functions, or for other purposes. This file
**          defines the macros that are used throughout this program.
**
** @author  Ben Johnson
**
**          Date Created: Monday October 27, 2014
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

#ifndef _MACROS_HH_
#define _MACROS_HH_

/*-------------------------------[Begin Code]---------------------------------*/
/**
********************************************************************************
** ADD DOXYGEN COMMENTS HERE, IF NEEDED!!!!
**
**
**
********************************************************************************
*/
#if defined(__x86_64__) || defined(_M_x64)
    #define CPU_64_BIT
#else
    #define CPU_32_BIT
#endif

#endif
