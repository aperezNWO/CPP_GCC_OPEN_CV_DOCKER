#ifndef OPENCVDLL_H
#define OPENCVDLL_H

#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <winsock2.h>
#include <windows.h>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>
#include <cstdlib>
#include <ctime>
#include <random>
#include <map>
#include <unordered_map>

using namespace std;

#define DLL_EXPORT extern "C" __declspec(dllexport) __stdcall 

class OpenCvApp
{
    public :
        OpenCvApp();
        ~OpenCvApp();
        
        const char*              GetOpenCvAPIVersion();
        const char*              GetOpenCvAppVersion();
        const char*              OpenCvReadImage();
        const char*              OpenCvReadImagePath(char* path);
        std::vector<std::string> detectShapes(const cv::Mat& inputImage); 
        cv::Mat                  generateMandelbrot(int width, int height, int maxIterations);
        int                      generateMandelbrot(); 
        cv::Mat                  generateJulia(int width, int height, int maxIterations, std::complex<double> c);                     
        int                      generateJulia();
        int                      generateJuliaParams(int maxIterations, double realPart, double imagPart); 
        int                      ReadConfigFile();
        const char*              GetCPPSTDVersion(long int cppVersion);
        
    public :
        map<string, string>      configMap;
};

#endif // OPENCVDLL_H