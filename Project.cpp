//
//
//  Compile with g++ --std=c++14 Project.cpp -ltbb -o Project
//
//  Created by Matthew Hines
//
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_reduce.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;
using namespace tbb;
  

//Bench
void get_walltime(double* wcTime) {

     struct timeval tp;

     gettimeofday(&tp, NULL);

     *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);

}

// Main
int main(int argc, char **argv) {
    
    double d_S,d_E;


    get_walltime(&d_S);
    
    
    auto values = std::vector<double>(100000);
    
    tbb::parallel_for(tbb::blocked_range<int>(0,values.size()), [&](tbb::blocked_range<int> r) {
        for(int i=r.begin(); i<r.end(); ++i) {
            values[i] = std::sin(i * 0.001);
        }
    });
    
    auto sum = tbb::parallel_reduce(tbb::blocked_range<int>(0,values.size()),0.0, [&](tbb::blocked_range<int> r, double sumTemp) {
        
        for (int i=r.begin(); i<r.end(); ++i) {
            
            sumTemp += values[i];
        }
        return sumTemp;
        
    }, std::plus<double>());
    
    
    // Compute Mean
    double mean = (double)sum /
                  (double)values.size();
  
    // Compute sum squared
    // differences with mean.
    auto sqDiff = tbb::parallel_reduce(tbb::blocked_range<int>(0,values.size()),0.0, [&](tbb::blocked_range<int> r, double sqDiffTemp) {
        
        for (int i=r.begin(); i<r.end(); ++i) {
            
            sqDiffTemp += (values[i] - mean) * (values[i] - mean);
        }
        return sqDiffTemp;
        
    }, std::plus<double>());
    
    get_walltime(&d_E);
    
    //Print Results
    cout << "Variance: "
         << sqDiff / values.size() << "\n";
    cout << "Standard Deviation: "
        << sqrt(sqDiff / values.size()) << "\n";
    cout << "Elapsed time: " << d_E - d_S << "\n";
}
  

