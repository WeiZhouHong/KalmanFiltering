/*
 * @ File name:		KalmanFiltering.c
 * @ Created on:	2015/5/24
 * @ Author:		Jhon
 * @ Version:		1
 * @ Parameter:		2, inputData, ptrKF
 * @ Description:	Independent function for Kalman Filtering
 */

#include <stdio.h>
#include <iostream>
#include "struct.h"
using namespace std;

void KalmanFiltering(int iteration, double *inputData, iterations *ptrKF)
{
    /* Variables. */
    double predict = 0;
    double predictP = 0;
    double gain = 0;
    double correct = 0;
    double correctP = 0;
    double input = 0;
    double Q = 0;
    double R = 0;
    double A = 0;
    double H = 0;
    double B = 0;
    double initialPredict = 0;
    double initialPredictP = 0;

    /* load Parameters. */
    FILE *configPtr;
    configPtr = fopen("parameters.conf", "r");
    fscanf(configPtr, "Q=%lf\n", &Q);
    fscanf(configPtr, "R=%lf\n", &R);
    fscanf(configPtr, "A=%lf\n", &A);
    fscanf(configPtr, "H=%lf\n", &H);
    fscanf(configPtr, "B=%lf\n", &B);
    fscanf(configPtr, "initialPredict=%lf\n", &initialPredict);
    fscanf(configPtr, "initialPredictP=%lf", &initialPredictP);
    fclose(configPtr);
    /* load previous data. */
    input = inputData[iteration-1];
    //printf("sensor[%lf]:", input);
    correct = ptrKF -> correct;
    correctP = ptrKF -> correctP;

    /*****    Prediction     *****/
    if(iteration < 2)
    {
        /* Step-1: compute the priori state estimate at time 'k' given observations up to and including at time 'k' */
        predict = initialPredict;
        ptrKF -> predict = predict;
        /* Step-2: compute the priori error covariance */
        predictP = initialPredictP;
        ptrKF -> predictP = predictP;
    }else
    {
        /* Step-1: compute the priori state estimate at time 'k' given observations up to and including at time 'k' */
        predict = A * correct + B;
        ptrKF -> predict = predict;
        /* Step-2: compute the priori error covariance */
        predictP = A * correctP * A + Q;
        ptrKF -> predictP = predictP;
    }

    /*****    Correction     *****/
    /* Step-3: compute the Kalman gain */
    gain = predictP * H / (H * predictP * H + R);
    ptrKF -> gain = gain;
    /* Step-4: compute the posteriori state estimate at time k given observations up to and including at time k*/
    correct = predict + gain * (input - H * predict);
    ptrKF -> correct = correct;
    /* Step-5: compute the posteriori error covariance */
    correctP = (1 - gain * H) * predictP;
    ptrKF -> correctP = correctP;
}


