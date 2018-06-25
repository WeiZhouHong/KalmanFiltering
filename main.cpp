/*
 * @ File name:		main.cpp
 * @ Created on:	2015/5/26
 * @ Author:		Jhon
 * @ Version:		1
 * @ Parameter:		2, argc, **argv
 * @ Description:	Use Kalman filtering for computing.
 */

#include <stdio.h>
#include <iostream>
#include "struct.h"
using namespace std;

void KalmanFiltering(int iteration, double *inputData, iterations *ptrKF);
void LoadInputData(int numberOfData, char** argv, double *input);
void SaveOutputData(int numberOfData, iterations *ptrKF);

int main(int argc, char** argv)
{
    /* Variables. */
    int numberOfData = 0;
    /* Pointers to allocate dynamic memory. */
	double *input = NULL;
	iterations *ptrKF = NULL;
    /* Description and Input*/
    printf("Enter iteration (numberOfData): ");
    scanf("%d", &numberOfData);
    printf("\nStart!\n");

	/* Dynamic Memory Allocation. */
	ptrKF = new iterations[numberOfData+1];
	input = new double[numberOfData];

	/* Load input data. */
	LoadInputData(numberOfData, argv, input);

    /*********** How to use Kalman filtering for computing. ***********/
    for(int i = 1; i < numberOfData+1; i++)
    {
        KalmanFiltering(i, input, ptrKF);
        ptrKF[i].predict = ptrKF -> predict;
        ptrKF[i].predictP = ptrKF -> predictP;
        ptrKF[i].gain = ptrKF -> gain;
        ptrKF[i].correct = ptrKF -> correct;//************ importance output!!!
        ptrKF[i].correctP = ptrKF -> correctP;
    }
    /* file Output for test*/
    SaveOutputData(numberOfData, ptrKF);
	/* Free Memory */
	delete [] ptrKF;
    delete [] input;

	return 0;
}   // End Main().


void LoadInputData(int numberOfData, char** argv, double *input)
{
    FILE *txtPtr;
    /* Open file. */
    txtPtr = fopen(argv[1], "r");

    if (!txtPtr)
    {
    cout << "[ERROR] : No file open." << endl;
    //exit(1);
    }	// End if.
    for(int i = 0; i < numberOfData; i++)
    {
        fscanf(txtPtr, "%lf\n", &input[i]);
    }
    fclose(txtPtr);
}

void SaveOutputData(int numberOfData, iterations *ptrKF)
{
    FILE *txtPtr;
    /* Open file. */
    txtPtr = fopen("output.csv", "w");

    if (!txtPtr)
    {
    cout << "[ERROR] : No file open." << endl;
    //exit(1);
    }	// End if.
    for(int i = 1; i < numberOfData+1; i++)
    {
        fprintf(txtPtr, "%lf,%lf,%lf,%lf,%lf\n", ptrKF[i].predict, ptrKF[i].predictP, ptrKF[i].gain, ptrKF[i].correct, ptrKF[i].correctP);
    }
    fclose(txtPtr);
}
