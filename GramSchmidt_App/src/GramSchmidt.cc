/**
********************************************************************************
** @file    GramSchmidt.cc
**
** @brief   Starting point for the Modified Gram-Schmidt algorithm
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
    UINT32 noOfVecs = 4;
    UINT32 ndims = 4;
    UINT32 gramRank;
    UINT32 vecsToGo;
    UINT32* pOrthVecInd;

    double vecSet[noOfVecs][ndims];
    double matArray[noOfVecs*noOfVecs];

    Vector vec[noOfVecs];
    Vector zeroVec(ndims);

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

    vecSet[3][0] = -3;
    vecSet[3][1] = 6;
    vecSet[3][2] = 1;
    vecSet[3][3] = 9;

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
    gramRank = grammian.rank();
    vecsToGo = gramRank;

    pOrthVecInd = new UINT32 [gramRank];

    /*
    ** Perform the Modified Gram-Schmidt algorithm
    */
    if (gramRank > 0)
    {
        for (UINT32 i = 0; i < noOfVecs; i++)
        {
            /*
            ** Subtract the current vector component from every vector still
            ** left and calculate the next unit vector
            */
            if (i > 0)
            {
                for (UINT32 j = i; j < noOfVecs; j++)
                {
                    vec[j] = vec[j] - (vec[i-1]*vec[j])*vec[i-1];
                }
            }

            if (vec[i].mag() >= FLOAT_TOL || vecsToGo == noOfVecs-i)
            {
                vec[i] = vec[i].unit();
                pOrthVecInd[gramRank-vecsToGo] = i;
                vecsToGo--;
            }
            else
            {
                vec[i] = zeroVec;
            }

            /*
            ** If all of the orthogonal vectors have been found, end the loop
            */
            if (0 == vecsToGo)
            {
                break;
            }
        }
    }

    /*
    ** Print the orthogonal vectors
    */
    printf("Number of orthogonal vectors: %d\n",gramRank);
    for (UINT32 i = 0; i < gramRank; i++)
    {
        vec[pOrthVecInd[i]].objPrint();
    }

    return 0;
}
