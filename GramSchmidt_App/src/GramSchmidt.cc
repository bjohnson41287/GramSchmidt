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
**  GramSchmidt.cc
**
**  (C) Copyright 2015 by Ben Johnson
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
#include "Matrix.hh"

/*-------------------------------[Begin Code]---------------------------------*/
/**
********************************************************************************
** @details This is the entry point for the GramSchmidt C++ program.
** @param   argc    Number of program input arguments
** @param   argv[]  Array of char pointers to the input arguments
** @return  int
********************************************************************************
*/
int main(int argc, char* argv[])
{
    /*
    ** Define needed variables
    */
    UINT32 noOfVecs = 3;
    UINT32 ndims = 4;
    //UINT32 gramRank;
    double gramDet;

    double vecSet[noOfVecs][ndims];
    double matArray[noOfVecs*noOfVecs];

    Vector vec[noOfVecs];

    /*
    ** Instantiate each vector in the set and define their values
    */
    vecSet[0][0] = 1;
    vecSet[0][1] = 2;
    vecSet[0][2] = 3;
    vecSet[0][3] = 4;

    vecSet[1][0] = -1;
    vecSet[1][1] = 2;
    vecSet[1][2] = 4;
    vecSet[1][3] = 1;

    vecSet[2][0] = 2;
    vecSet[2][1] = 0;
    vecSet[2][2] = 5;
    vecSet[2][3] = -7;

    for (UINT32 i = 0; i < noOfVecs; i++)
    {
        vec[i].setVector(vecSet[i],ndims);
    }

    /*
    ** Calculate the Grammian matrix and determine it's rank
    */
    for (UINT32 i = 0; i < noOfVecs; i++)
    {
        for (UINT32 j = 0; j < noOfVecs; j++)
        {
            matArray[i*noOfVecs + j] = vec[i]*vec[j];
        }
    }

    Matrix grammian(matArray,noOfVecs,noOfVecs);

    gramDet = grammian.determinant();
    printf("Grammian Determinant: %f\n",gramDet);
    printf("Number of vectors: %d\n",noOfVecs);

    /*
    ** Peform the Gram-Schmidt decomposition if the determinant of the Grammian
    ** matrix is non-zero
    */
    // ADD CODE HERE!!!!

    return 0;
}
