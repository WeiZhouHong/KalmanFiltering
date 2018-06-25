/*
 * @ File name:		structure.h
 * @ Created on:	2015/5/26
 * @ Author:		Jhon
 * @ Version:		1
 * @ Description:	the structure for computing.
 */

/* Define vector structure. */
typedef struct KF_Data
{
    double predict;
    double predictP;
    double gain;
    double correct;
    double correctP;
} iterations;
