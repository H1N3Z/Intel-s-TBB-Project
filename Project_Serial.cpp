//
//
//  Compile with g++ --std=c++14 Project_Serial.cpp -o Project_Serial
//
//  Created by Matthew Hines
//
#include <sys/time.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;
  
//Bench
void get_walltime(double* wcTime) {

     struct timeval tp;

     gettimeofday(&tp, NULL);

     *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);

}

int main(int argc, char **argv) {
    
    double d_S,d_E;


    get_walltime(&d_S);

    auto values = std::vector<double>(100000000);
    
    for (int i=0; i<values.size(); ++i) {
        
        values[i] = std::sin(i * 0.001);
        
    }
    
    
    // Compute mean
    int sum = 0;
    for (int i = 0; i < values.size(); i++)
        sum += values[i];
    
    double mean = (double)sum / (double)values.size();
    
    // Compute sum squared
    double sqDiff = 0;
    for (int i = 0; i < values.size(); i++) {
        
        sqDiff += (values[i] - mean) * (values[i] - mean);
        
    }
    
    
    get_walltime(&d_E);
    
    
    cout << "Variance: "
         << sqDiff / values.size() << "\n";
    cout << "Standard Deviation: "
         << sqrt(sqDiff / values.size()) << "\n";
    cout << "Elapsed time: " << d_E - d_S << "\n";
    
}
