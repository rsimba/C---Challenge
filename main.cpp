//
//  main.cpp
//  Practice
//
//  Created by Robin Singh on 12-02-04.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include <boost/thread.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctime>

using namespace std;

void initial(int &height, int &width);
double timer(bool on_or_off);
void kernel_filter_dx(int matrix[], int transform_matrix[], bool dx_matrix);
void kernel_filter_dy(int matrix[], int transform_matrix[], bool dx_matrix);
void print_matrix(int matrix[]);
void compute_min_and_max(int matrix[]);

int height,width;

int main (int argc, char ** argv)
{
    int a;
    bool start=true, stop=false;
    int * matrix;
    int * dx_matrix;
    int * dy_matrix;
    
    height = 0;
    width = 0;
    initial(height, width);
    
    matrix = new int [height*width];
    dx_matrix = new int [height*width];
    dy_matrix = new int [height*width];
    
    delete[] matrix;
    delete[] dx_matrix;
    delete[] dy_matrix;

    cout << "fill with random data \n";
    //srand((unsigned)time(0)); 
    for(a=0;a<height*width;a++)
            matrix[a] = rand() % 10;
    
    
    timer(start);
        cout << "kernel filter\n";
        boost::thread workerone(kernel_filter_dx, matrix, dx_matrix, true);
        boost::thread workertwo(kernel_filter_dy, matrix, dx_matrix, true);
        workerone.join();
        workertwo.join();
    cout << "This is the time taken=" << timer(stop) << " seconds" << endl;

    
    timer(start);
        cout << "compute min and max\n";
        //boost::thread workerone();
        //boost::thread workertwo();
        compute_min_and_max(dx_matrix);
        compute_min_and_max(dy_matrix);
        //workerone.join();
        //workertwo.join();
    cout << "This is the time taken=" << timer(stop) << " seconds" << endl;

    return 0;
}

//********************************************
//********************************************
//********************************************
//********************************************
//********************************************
//********************************************

void initial(int &height, int &width){
    cout << "Please enter the height : ";
    //cin >> height;
    cout << "Thanks\n";
    cout << "Please enter the width : ";
    //cin >> width;
    cout << "Thanks\n";
    //return height and width
    height = 900;
    width = 900;
}

void print_matrix(int matrix[]){
    int h, x=1;
    for(h=0;h<height*width;h++){
        cout << matrix[h] << " ";
        if (h == (width*x-1)){
            cout << "\n";
            x++;
        }
    }
}

double timer(bool on){
    clock_t startClock, tempClock;
    double timeCount;
    
    if (on){
        startClock = clock();
    } else {
        tempClock = clock();
        timeCount = (tempClock-startClock)*100000/CLOCKS_PER_SEC;
        timeCount = timeCount/100000;
    }
    return timeCount;
}

void kernel_filter_dx(int matrix[], int transform_matrix[], bool dx_matrix){
    int a, b, c, x1, x2, x3;
    char kernel[3] = {-1, 0, 1};
    int value_array[height*width];
    
        c=0;
        b=0;
        for (a=0;a<height*width; a++){
                x1 = kernel[0] * matrix[a-1];
                x2 = kernel[1] * matrix[a];
                x3 = kernel[2] * matrix[a+1];

                value_array[b] = a;
                b++;
                if (a == (width*c)){
                    x1 = 0;
                    c++;
                }
                else if (a == width*c-1){
                    x3 = 0;
                }
            
            transform_matrix[a] = x1 + x2 + x3;
        }
    } 
    
void kernel_filter_dy(int matrix[], int transform_matrix[], bool dx_matrix){
    int d, e, f, y1, y2, y3;
    char kernel[3] = {-1, 0, 1};
    int value_array[height*width];
        e = 0;
        f = 0;
        for (d=0;d<height*width; d++){
                y1 = kernel[0] * matrix[d-width];
                y2 = kernel[1] * matrix[d];
                y3 = kernel[2] * matrix[d+width];
            
                if (d < width)
                    y1 = 0;
                else if (d >= (height-1)*width)
                    y3 = 0;
            
                e++;
                value_array[e] = matrix[d];
                transform_matrix[d] = y1 + y2 + y3;
        }
    }


void compute_min_and_max(int matrix[]){
    int max_val1;
    int min_val1;
    int a;
    min_val1 = matrix[0];
    max_val1 = matrix[0];
    for (a=0;a<width*height; a++){
            if (matrix[a] < min_val1)
                min_val1 = matrix[a];
            if (matrix[a] > max_val1)
                max_val1 = matrix[a];
    }
    cout << "The min value is equal to " << min_val1 << endl;
    cout << "The max value is equal to " << max_val1 << endl;
}
