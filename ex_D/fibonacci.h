/**
 *  File Name: fibonacci.h
 *  Assignment: ENSF 694 Lab 2 Exercise D
 *  Created by: Mahmood Moussavi
 *  Completed by: Yael Gonzalez
 *  Submission Date: July 10, 2024
 */

#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std;

#define N 2


void plotMethodComparison(int* x, double *y1, double *y2, int size);
/**
 * Function to plot the algorithm time analysis.
 * 
 * REQUIRES: 
 *  x points to an array of integers representing the x-axis data.
 *  y1 points to an array of doubles representing the y-axis data for the first method.
 *  y2 points to an array of doubles representing the y-axis data for the second method.
 *  size is the number of data points.
 * PROMISES:
 *  Plots a comparison of the algorithm time analysis for two methods using the provided data.
 */

void plotMethod(const char* Title, int* x, double *y, int size);
/**
 * REQUIRES: 
 *  Title is the title of the plot.
 *  x points to an array of integers representing the x-axis data.
 *  y points to an array of doubles representing the y-axis data.
 *  size is the number of data points.
 * PROMISES:
 *  Plots the provided data with the given title.
 */

void multiplyMatrix(int a[N][N], int b[N][N], int result[N][N]);
/**
 * Function to multiply two matrices of size N x N.
 * 
 * Source:
 * https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm
 * 
 * REQUIRES: 
 *  a and b are NxN matrices to be multiplied.
 *  result is an NxN matrix to store the result of the multiplication.
 * PROMISES:
 *  Multiplies matrices a and b, storing the result in the result matrix.
 */

void powerMatrix(int base[N][N], int exp, int result[N][N]);
/**
 * Power of Matrix recursive method.
 * 
 * Source:
 * https://www.geeksforgeeks.org/program-for-nth-fibonacci-number/
 * https://robwilsondev.medium.com/bigo-and-beyond-how-to-compute-fibonacci-sequence-efficiently-with-matrix-exponentiation-d9924545fe54
 * 
 * REQUIRES: 
 *  base is an NxN matrix to be exponentiated.
 *  exp is the exponent.
 *  result is an NxN matrix to store the result of the exponentiation.
 * PROMISES:
 *  Computes the power of the base matrix raised to the exp, storing the result in the result matrix.
 */

int fibonacciRecursive(int n);
/**
 * Function to calculate the nth Fibonacci number using recursive matrix exponentiation
 * 
 * REQUIRES: 
 *  n > 0, where n is the n-th number of the Fibonacci sequence.
 * PROMISES:
 *  Returns the nth Fibonacci number using recursive matrix exponentiation.
 */

int fibonacciIterative(int n);
/**
 * Function to calculate the nth Fibonacci number iteratively
 * 
 * Source:
 * https://www.geeksforgeeks.org/program-for-nth-fibonacci-number/
 *
 * REQUIRES: 
 *  n > 0, where n is the n-th number of the Fibonacci sequence.
 * PROMISES:
 *  Returns the nth Fibonacci number using an iterative approach.
 */
    
double measureTime(int (*fibonacciFunc)(int), int n);
/**
 * Function to measure the time taken by a function to calculate the nth Fibonacci number
 *  
 * REQUIRES: 
 *  fibonacciFunc is a pointer to a function that calculates the nth Fibonacci number.
 *  n > 0, where n is the position of the desired Fibonacci number.
 * PROMISES:
 *  Measures and returns the time taken by the fibonacciFunc to calculate the nth Fibonacci number.
 */

int* printTimeTable(const string Title, int (*fibonacciFunc)(int), double result[], int n, int maxN, int n_stepsize, int N_value[]);
/**
 * REQUIRES: 
 *  Title is the title of the table.
 *  fibonacciFunc is a pointer to a function that calculates the nth Fibonacci number.
 *  result is an array to store the measured times.
 *  n is the initial position of the Fibonacci number.
 *  maxN is the maximum position of the Fibonacci number.
 *  n_stepsize is the step size for n.
 *  N_value is an array to store the positions of Fibonacci numbers.
 * PROMISES:
 *  Prints a table of times taken by fibonacciFunc to calculate Fibonacci numbers from n to maxN, with step size n_stepsize.
 */


#endif
