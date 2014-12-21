/**
********************************************************************************
** @file    GramSchmidt.cc
**
** @brief   Starting point for the Gram-Schmidt algorithm
**
** @details The Gram-Schmidt process generates an orthonormal set of n basis
**          vectors, given a non-orthogonal set of n vectors that span the
**          n-dimensional space.
**
** @author  Ben Johnson
**
** @date    Sunday October 19, 2014
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
**  GramSchmidt is free software: you can redistribute it and/or modify it under
**  the terms of the GNU General Public License as published by the Free
**  Software Foundation, either version 3 of the License, or (at your option)
**  any later version.
**
**  GramSchmidt is distributed in the hope that it will be useful, but WITHOUT
**  ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
**  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License in the
**  GPL_V3 file for more details.
**
**  You should have received a copy of the GNU General Public License in the
**  GPL_V3 file along with GramSchmidt.
**  If not, see <http://www.gnu.org/licenses/>.
********************************************************************************
*/

/*------------------------------[Include Files]-------------------------------*/
#include <stdio.h>

#include "StdTypes.hh"
#include "Vector.hh"

/*-------------------------------[Begin Code]---------------------------------*/
/**
********************************************************************************
** @details This is the main() function for the start of the GramSchmidt C++
**          program.
** @param   argc    Number of program input arguments
** @param   argv[]  Array of char pointers to the input arguments
** @return  int
********************************************************************************
*/
int main(int argc, char* argv[])
{
    printf("This is the GramSchmidt program.\n");
#if defined(CPU_64_BIT)
    printf("64-bit CPU\n");
#elif defined(CPU_32_BIT)
    printf("32-bit CPU\n");
#endif
    printf("Size of char: %ld\n",sizeof(char));
    printf("Size of short int: %ld\n",sizeof(short));
    printf("Size of int: %ld\n",sizeof(int));
    printf("Size of long: %ld\n",sizeof(long));
    printf("Size of long long: %ld\n",sizeof(long long));
}
