/**
 *  File Name: fibonacci.cpp
 *  Assignment: ENSF 694 Lab 2 Exercise D
 *  Created by: Mahmood Moussavi
 *  Completed by: Yael Gonzalez
 *  Submission Date: July 10, 2024
 */

#include "fibonacci.h"

int main(void) 
{
    double recursive_result[50] = {0.0};
    double iterative_result[50] = {0.0};;
    int N_value[50] = {0};

    // Uncomment for analyzing each method separately
    // printTimeTable("Recursive Matrix Exponentiation Method", fibonacciRecursive, recursive_result, 0, 46, 1, N_value);
    // printTimeTable("\nIterative Method", fibonacciIterative, iterative_result, 0, 46, 1, N_value);
    // plotMethod("Recursive Matrix Exponentiation Method", N_value, recursive_result, 47);
    // plotMethod("Iterative Method", N_value, iterative_result, 47);

    // Uncomment for analyzing both methods together
    printTimeTable("\nRecursive Matrix Exponentiation Method", fibonacciRecursive, recursive_result, 0, 10000, 500, N_value);
    printTimeTable("\nIterative Method", fibonacciIterative, iterative_result, 0, 10000, 500, N_value);    
    plotMethodComparison(N_value, iterative_result,  recursive_result, 21);

    return 0;
}

void multiplyMatrix(int a[N][N], int b[N][N], int result[N][N]) 
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {   
            result[i][j] = 0; // Set all values of result matrix to 0
            for (int k = 0; k < N; k++)
            {
                result[i][j] += a[i][k] * b[k][j]; // Perform matrix multiplication algorithm
            }
        }
    }
}

void powerMatrix(int base[N][N], int exp, int result[N][N]) 
{
    if (exp == 1) // Base case
    {
        std::copy(&base[0][0], &base[0][0] + N * N, &result[0][0]); // result = base
        return;
    }

    int half[N][N] = {0}; // Initialize half matrix with Zeroes
    powerMatrix(base, exp / 2, half); // half = A^(n/2), where 'A' is 'base', and 'n' is 'exp'
    multiplyMatrix(half, half, result); // result = A^(n/2) * A^(n/2)

    if (exp % 2 != 0) // If it's odd multiply result by A
    {
        int temp[N][N] = {0}; // Initialize half matrix with Zeroes
        multiplyMatrix(result, base, temp); // temp = A^(n/2) * A^(n/2) * A
        std::copy(&temp[0][0], &temp[0][0] + N * N, &result[0][0]); // result = temp
    }    
}

int fibonacciRecursive(int n) 
{
    if (n == 0)
    {
        // std::cout << setw(12) << 0; // Uncomment to print Fibonacci num value
        return 0;
    }        
    
    if (n == 1) 
    {
        // std::cout << setw(12) << 1; // Uncomment to print Fibonacci num value
        return 1; 
    }

    int base[N][N] = {{1, 1}, {1, 0}};
    int result[N][N] = {0};
    powerMatrix(base, n - 1, result);
    // std::cout << setw(12) << result[0][0]; // Uncomment to print Fibonacci num value
    return result[0][0];
}

int fibonacciIterative(int n) 
{
    int a = 0, b = 1, c = 0;
    
    if (n == 0)
    {
        // std::cout << setw(12) << a;  // Uncomment to print Fibonacci num value
        return a; 
    }             

    for (int i = 2; i <= n; i++) 
    {
        c = a + b;
        a = b;
        b = c;
    }

    // std::cout << setw(12) << b; // Uncomment to print Fibonacci num value
    return b;
}

double measureTime(int (*fibonacciFunc)(int), int n) 
{  
    const auto start_time = std::chrono::high_resolution_clock::now();   
    fibonacciFunc(n);
    const auto end_time = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> time_diff = end_time - start_time;
    return time_diff.count() * 1000.0; // measure in miliseconds 
}

int* printTimeTable(const string Title, int (*fibonacciFunc)(int), double result[], int n, int maxN, int n_stepsize, int N_value[])
{
    std::cout << Title << "\n";
    // Uncomment to print Fibonacci num value
    // std::cout << setw(12) << "Fibonacci Num" << setw(12) << "N" << setw(12) << "Time (ms)" << "\n";
    std::cout << setw(12) << "N" << setw(12) << "Time (ms)" << "\n";
    for (int i = 0; n <= maxN; n += n_stepsize, i++) {
        double time = measureTime(fibonacciFunc, n);
        result[i] = time;
        std::cout << setw(12) << n << setw(12) << result[i] << endl;
        N_value[i] = n;
    }

    return N_value;
}

void plotMethodComparison(int* x, double *y1, double *y2, int size)
{
    FILE * gnuplotPipe = popen ("C:\\msys64\\ucrt64\\bin\\gnuplot.exe -persistent", "w");
    
    const char* name = "Fibonacci Time Analysis";

    fprintf(gnuplotPipe, "set title '%s'\n", name);
    fprintf(gnuplotPipe, "set xlabel 'n-th Fibonacci number'\n");
    fprintf(gnuplotPipe, "set ylabel 'running time (ms)'\n");
    fprintf(gnuplotPipe, "set key top center horizontal\n");
    fprintf(gnuplotPipe, "plot '-' with linespoints pt 5 ps 1 lc 'blue' title 'Iterative', \
        '-' with linespoints pt 7 ps 1 lc 'red' title 'Recursive (Power of Matrix)'\n");

    // Iterative
    for (int i = 0; i < size; i++)
    {
        fprintf(gnuplotPipe, "%d %f\n", x[i], y1[i]);
    }
    
    fprintf(gnuplotPipe, "e\n");

    // Recursive
    for (int i = 0; i < size; i++)
    {
        fprintf(gnuplotPipe, "%d %f\n", x[i], y2[i]);
    }
}

void plotMethod(const char* Title, int* x, double *y, int size)
{
    FILE * gnuplotPipe = popen ("C:\\msys64\\ucrt64\\bin\\gnuplot.exe -persistent", "w");

    fprintf(gnuplotPipe, "set title '%s'\n", Title);
    fprintf(gnuplotPipe, "set xlabel 'n-th Fibonacci number'\n");
    fprintf(gnuplotPipe, "set ylabel 'running time (ms)'\n");
    fprintf(gnuplotPipe, "set key top center horizontal\n");
    fprintf(gnuplotPipe, "plot '-' with linespoints pt 5 ps 1 lc 'blue' title '%s'\n", Title);

    for (int i = 0; i < size; i++)
    {
        fprintf(gnuplotPipe, "%d %f\n", x[i], y[i]);
    }
}
