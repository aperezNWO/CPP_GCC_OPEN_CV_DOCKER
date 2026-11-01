#ifndef OPENCVDLL_H // include guard
#define OPENCVDLL_H
#endif

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <random>  // For random number generation

#pragma hdrstop
#pragma argsused
#pragma once

using namespace cv;
using namespace std;

#define DLL_EXPORT extern "C" __declspec(dllexport) __stdcall 

using namespace std;

class OpenCvApp
{
    public :
        //
        OpenCvApp();
        ~OpenCvApp();
        //
        const char*              GetOpenCvAPIVersion();
        const char*              GetOpenCvAppVersion();
        const char*              OpenCvReadImage();
        const char*              OpenCvReadImagePath(char* path);
        vector<string>           detectShapes(const cv::Mat& inputImage) ; 
        Mat                      generateMandelbrot(int width, int height, int maxIterations);
        int                      generateMandelbrot(); 
		Mat                      generateJulia(int width, int height, int maxIterations, complex<double> c);                     
        int                      generateJulia();
        int 					 generateJuliaParams(int maxIterations, double realPart, double imagPart); 
        int                      ReadConfigFile();
        const char*              GetCPPSTDVersion(long int cppVersion);
     public :
        //
        map<string, string>      configMap;

};