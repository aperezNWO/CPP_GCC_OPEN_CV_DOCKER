#ifndef OPENCVAPP_H
#define OPENCVAPP_H

#pragma once

// ---------------------------------------------------------------
// Windows-only includes (skipped when building on Linux / Docker)
// ---------------------------------------------------------------
#ifdef _WIN32
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0A00
  #endif
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif
  // winsock2.h must come before windows.h (httplib.h needs this order)
  #include <winsock2.h>
  #include <windows.h>

  #ifndef DLL_EXPORT
    #define DLL_EXPORT extern "C" __declspec(dllexport) __stdcall
  #endif
#endif

#include <opencv2/opencv.hpp>

#include <complex>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// NOTE: no "using namespace std;" in a header. Everything is qualified.

class OpenCvApp
{
public:
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

public:
    std::map<std::string, std::string> configMap;
};

#endif // OPENCVAPP_H