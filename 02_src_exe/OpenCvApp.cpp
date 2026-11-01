
///////////////////////////////////////////////////////////////////
// Application CPP_GCC_OPEN_CV v[1.0.1]
///////////////////////////////////////////////////////////////////
/*
    1) Toolchain :  MSYS MINGW64 

    2) pacman -S mingw-w64-x86_64-opencv
    C:\msys64\usr\bin\pacman.exe -S mingw-w64-x86_64-make

    3) Path to Generated Files:
        a) C:\msys64\mingw64\bin
        b) C:\msys64\mingw64\include\opencv2

    4) Dynamic compilation Command  [STATIC IS NOT POSSIBLE] :

    cd /c/Users/pablo.perez/dev/cpp/CPP_GCC_OPEN_CV/src/mingwin

    g++ -shared -m64 -o OpenCvDll.dll OpenCvDll.cpp OpenCvDll.def \
        -I/mingw64/include/opencv2 \
            -Wl,--start-group $(pkg-config --cflags  --libs opencv4)  -Wl,--end-group \
            -lopencv_gapi -lz -llibjpeg -llibpng -lopengl32 -lglu32 -lgdi32 -luser32 -lole32 -lopencv_ccalib -lopencv_cvv   -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_stitching  -lopencv_alphamat  -lopencv_aruco -lopencv_bgsegm  -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform -lopencv_line_descriptor -lopencv_mcc -lopencv_ovis -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_signal -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_highgui -lopencv_datasets -lopencv_text -lopencv_plot -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_wechat_qrcode -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_dnn -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core -lpthread

    5) CMAKE

        md build && cd build

        // dos / powershell

		set PATH=C:\msys64\mingw64\bin;C:\Windows\System32;C:\Windows
		
		C:\msys64\mingw64\bin\cmake.exe -G "MinGW Makefiles" ^
		  -DCMAKE_C_COMPILER=C:/msys64/mingw64/bin/gcc.exe ^
		  -DCMAKE_CXX_COMPILER=C:/msys64/mingw64/bin/g++.exe ^
		  -DCMAKE_MAKE_PROGRAM=C:/msys64/mingw64/bin/mingw32-make.exe ^
		  -DPKG_CONFIG_EXECUTABLE=C:/msys64/mingw64/bin/pkg-config.exe ^
		  ..
		  
        // msys

        cmake -G "MinGW Makefiles" \
            -DCMAKE_C_COMPILER="C:/msys64/mingw64/bin/gcc.exe" \
            -DCMAKE_CXX_COMPILER="C:/msys64/mingw64/bin/g++.exe" \
            ..

		// windows
		
        cmake --build .

     5.1) COPY NEEDED FILES
     
		cd /d D:\usuarios\pabloperez\dev\cpp\CPP_GCC_OPEN_CV_DOCKER\02_src_exe\__test

		C:\msys64\msys2_shell.cmd -mingw64 -defterm -no-start -here -c "ldd OpenCvAppV2.exe | grep -i '/mingw64/bin' | awk '{print $3}' | xargs -I{} cp -f {} ."

    6) CMAKE -> INTEGRACION CONTINUA

        A) (MODIFICAR ARCHIVOS *.CPP)
        B) (dentro de la carpate "build")  cmake --build .
        C) output en carpeta \bin
        C) Publicar via DOCKER

*/

#include "include/OpenCvApp.h"
#include "include/httplib.h"
#include "include/Algorithm.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <filesystem>
#include <fstream>

// Añade esto aquí para que el código reconozca las funciones y tipos de OpenCV sin prefijo
using namespace cv;

using AppAlgorithm = ::Algorithm;

//
OpenCvApp::OpenCvApp() {
	//
	ReadConfigFile();
}
//
OpenCvApp::~OpenCvApp() {
	//
}
//
const char* OpenCvApp::GetOpenCvAPIVersion() {
    std::string version = cv::getVersionString();
    char* copy = new char[version.size() + 1];
    strcpy(copy, version.c_str());
    return copy; // Llama delete[] después de usarla!
}
//
const char*  OpenCvApp::GetOpenCvAppVersion() {
	//
	return this->configMap["DLL_VERSION"].c_str();
}
//
const char* OpenCvApp::OpenCvReadImage() {
	const char * result = "OK";

	cv::Mat image = cv::imread("image.png");

	if (image.empty()) {
		std::cerr << "Could not read the image!" << std::endl;
		return "Could not read the image 'image.png'";
	}

	// Detect shapes in the image
	std::vector<std::string> shapes = detectShapes(image);


	// Use stringstream to build the comma-separated list cleanly
    std::stringstream ss;
    for (size_t i = 0; i < shapes.size(); ++i) {
        ss << shapes[i];
        if (i < shapes.size() - 1) {
            ss << ", "; // Add comma for all but the last element
        }
    }
    //
    std::string s_result = ss.str();
    result               = s_result.c_str();
    
	//
	return result;
}
//
const char* OpenCvApp::OpenCvReadImagePath(char* path) {
    // static ensures the string memory stays alive after the function returns
    static std::string result_accumulator; 
    result_accumulator.clear(); // Clear old results from previous runs

    cv::Mat image = cv::imread(path);

    if (image.empty()) {
        std::cerr << "Could not read the image!" << std::endl;
        return "Could not read the image";
    }

    std::vector<std::string> shapes = detectShapes(image);

    if (shapes.empty()) {
        return "No shapes found.";
    }

    // Build comma-separated list
    std::stringstream ss;
    for (size_t i = 0; i < shapes.size(); ++i) {
        ss << shapes[i];
        if (i < shapes.size() - 1) {
            ss << ", ";
        }
    }

    result_accumulator = ss.str();
    return result_accumulator.c_str(); // Safe now because result_accumulator is static
}

//
vector<string> OpenCvApp::detectShapes(const cv::Mat& inputImage) {
	//
	std::vector<std::string> shapes;

	// Ensure the input image is valid
	if (inputImage.empty()) {
		std::cerr << "Error: Input image is empty!" << std::endl;
		return shapes;
	}

	// Create matrices for grayscale and edges
	cv::Mat gray, edges;

	// Convert the input image to grayscale
	cv::cvtColor(inputImage, gray, cv::COLOR_BGR2GRAY);

	// Apply Canny edge detector
	cv::Canny(gray, edges, 50, 150, 3, false);

	// Find contours
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(edges, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	// Iterate over contours and classify shapes
	for (size_t i = 0; i < contours.size(); ++i) {
		std::vector<cv::Point> contour = contours[i];
		std::vector<cv::Point> approx;

		// Approximate the contour to a polygon
		double epsilon = 0.04 * cv::arcLength(contour, true);
		cv::approxPolyDP(contour, approx, epsilon, true);

		std::string shape;
		if (approx.size() == 3) {
			shape = "[Triangle]";
		} else if (approx.size() == 4) {
			// Calculate bounding rectangle and aspect ratio
			cv::Rect rect = cv::boundingRect(approx);
			double aspectRatio = static_cast<double>(rect.width) / rect.height;
			shape = (aspectRatio >= 0.95 && aspectRatio <= 1.05) ? "[Square]" : "[Rectangle]";
		} else if (approx.size() > 4) {
			shape = "[Circle]";
		}

		if (!shape.empty()) {
			shapes.push_back(shape);
		}
	}

	// Return the detected shapes
	return shapes;
}
//
int          OpenCvApp::ReadConfigFile() {
	// Open the configuration file
	std::ifstream configFile("opencv.ini");

	// Check if the file is opened successfully
	if (!configFile.is_open()) {
		std::cerr << "Error opening the configuration file." << std::endl;
		return 1;
	}

	// Read the file line by line
	std::string line = "";
	while (std::getline(configFile, line)) {
		// Skip empty lines or lines starting with '#' (comments)
		if (line.empty() || line[0] == '#') {
			continue;
		}

		// Split the line into key and value
		std::istringstream iss(line);
		std::string key, value;
		if (std::getline(iss, key, '=') && std::getline(iss, value)) {
			// Trim leading and trailing whitespaces from key and value
			key.erase(0, key.find_first_not_of(" \t"));
			key.erase(key.find_last_not_of(" \t") + 1);
			value.erase(0, value.find_first_not_of(" \t"));
			value.erase(value.find_last_not_of(" \t") + 1);

			// Insert key-value pair into the map
			this->configMap[key] = value;
		}
	}

	// Close the configuration file
	configFile.close();

	//
	return 0;
}
//
Vec3b GetColor(int iteration, int maxIterations) {
    if (iteration == maxIterations) {
        return Vec3b(0, 0, 0); // Black for points inside the set
    }

    // Map iteration count to RGB
    float t = static_cast<float>(iteration) / maxIterations;
    uchar r = static_cast<uchar>(9 * (1 - t) * t * t * t * 255);
    uchar g = static_cast<uchar>(15 * (1 - t) * (1 - t) * t * t * 255);
    uchar b = static_cast<uchar>(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

    return Vec3b(b, g, r);
};
// Function to compute the Mandelbrot set
Mat OpenCvApp::generateMandelbrot(int width, int height, int maxIterations) 
{
  Mat img(height, width, CV_8UC3, Scalar(0, 0, 0));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
        	
            double cx = -2.0 + (x / static_cast<double>(width)) * 3.5;
            double cy = -1.5 + (y / static_cast<double>(height)) * 3.0;
            
            complex<double> z(0, 0);
            
			complex<double> c(cx, cy);

            int iteration = 0;
            while (abs(z) < 2 && iteration < maxIterations) {
                z = z * z + c;
                ++iteration;
            }

            img.at<Vec3b>(y, x) = GetColor(iteration, maxIterations);
        }
    }
    return img;
}
//
int OpenCvApp::generateMandelbrot()
{
 	int width = 800, height = 800;

    // Random number generator
    random_device rd;                                             // Seed for the random number engine
    mt19937 gen(rd());                                            // Mersenne Twister engine
    uniform_int_distribution<int>     distMaxIterations(1,255);   // Range [1, 255]
    
    // Generate random values
    int    maxIterations = distMaxIterations(gen);
	
    // Generate the Mandelbrot fractal
    Mat fractalImage = generateMandelbrot(width, height, maxIterations);

    // Save the fractal image
    imwrite("mandelbrot.png", fractalImage);

    return 0;
} 
//
Mat OpenCvApp::generateJulia(int width, int height, int maxIterations, complex<double> c) 
{

    Mat img(height, width, CV_8UC3, Scalar(0, 0, 0));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Map pixel position to a point in the complex plane
            double zx = -1.5 + (x / static_cast<double>(width)) * 3.0;
            double zy = -1.5 + (y / static_cast<double>(height)) * 3.0;
            complex<double> z(zx, zy);

            int iteration = 0;
            while (abs(z) < 2 && iteration < maxIterations) {
                z = z * z + c;
                ++iteration;
            }

            // Color the pixel based on the number of iterations
            img.at<Vec3b>(y, x) = GetColor(iteration, maxIterations);
        }
    }
    return img;
}
//
int OpenCvApp::generateJulia() 
{
 	int width = 800, height = 800;
	
    // Random number generator
    random_device rd;  // Seed for the random number engine
    mt19937 gen(rd()); // Mersenne Twister engine

    // Define distributions for realPart and imagPart
    uniform_real_distribution<double> distReal(-1.0, 1.0);        // Range [-1.0, 1.0]
    uniform_real_distribution<double> distImag(-1.0, 1.0);        // Range [-1.0, 1.0]
    uniform_int_distribution<int>     distMaxIterations(1,255);   // Range [1, 255]
    
    // Generate random values
    int    maxIterations = distMaxIterations(gen);
    double realPart      = distReal(gen); // -4.0
    double imagPart      = distImag(gen); // 6.0
    
    //cout << endl << "iterations : " << maxIterations << endl;
    //cout << endl << "real part  : " << realPart      << endl;
    //cout << endl << "imgn part  : " << imagPart      << endl;

    // Create the complex number c
    // valid values :
    // c=0.355+0.355i 
    // c=−0.4+0.6i 
    complex<double> c(realPart, imagPart);
    
	//
	Mat juliaImage = generateJulia(width, height, maxIterations, c);

	//    
	imwrite("julia.png", juliaImage);

    return 0;
}
//
int OpenCvApp::generateJuliaParams(int maxIterations, double realPart, double imagPart) 
{
	//
	int width = 800, height = 800;
	
 	//
    complex<double> c(realPart, imagPart);
    
	//
	Mat juliaImage = generateJulia(width, height, maxIterations, c);

	//    
	imwrite("julia.png", juliaImage);

	//
    return 0;
}
//
const char* OpenCvApp::GetCPPSTDVersion(long int cppVersion)	
{
	switch (cppVersion) {
	        case 199711L: return "C++98/C++03";
	        case 201103L: return "C++11";
	        case 201402L: return "C++14";
	        case 201703L: return "C++17";
	        case 202002L: return "C++20";
	        case 202302L: return "C++23";
	        default: return "Unknown C++ Standard";
	}
}
	

//////////////////////////////////////////////////////////////////////
// CLASS DECLARATION
//////////////////////////////////////////////////////////////////////

class CppWebServerApp
{
	//
	public :
		//
		struct EndpointInfo {
		    std::string endpointName;
		    std::string endpointDescription;
		};
		//
		std::unordered_map<std::string, EndpointInfo> endpointDictionary;
		//
	    httplib::Server svr;
	    //
	    const char* cppWebServerVersion;
    //
    public :
		//
		CppWebServerApp();
		//
		~CppWebServerApp();	
		//
		static const char* GetCPPHttpVersion();
    	//
    	int Run();
    
};

//////////////////////////////////////////////////////////////////////
// HELPER METHODS
//////////////////////////////////////////////////////////////////////

// Simple Base64 decoder function
std::vector<unsigned char> base64_decode(const std::string& in) {
    static const std::string chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::vector<unsigned char> out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        if (c == '=') break;
        size_t index = chars.find(c);
        if (index == std::string::npos) continue;
        val = (val << 6) + index;
        valb += 6;
        if (valb >= 0) {
            out.push_back(static_cast<unsigned char>((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

// Lightweight JSON field extractor for "base64Image"
std::string extractJsonField(const std::string& json, const std::string& key) {
    std::string searchKey = "\"" + key + "\":";
    size_t pos = json.find(searchKey);
    if (pos == std::string::npos) return "";
    pos += searchKey.length();
    
    // Skip whitespace
    while (pos < json.length() && (json[pos] == ' ' || json[pos] == '\t' || json[pos] == '\n' || json[pos] == '\r')) {
        pos++;
    }
    if (pos >= json.length() || json[pos] != '"') return "";
    pos++; // skip opening quote
    
    size_t endPos = json.find('"', pos);
    if (endPos == std::string::npos) return "";
    return json.substr(pos, endPos - pos);
}

////////////////////////////////////////////////////////////////
// HELPER METHODS
////////////////////////////////////////////////////////////////
const char* GetOpenCvAPIVersion() {
	//
	std::unique_ptr<OpenCvApp> uniquePtr = std::make_unique<OpenCvApp>();
	//
	return uniquePtr->GetOpenCvAPIVersion();
}

//
const char* GetOpenCvAppVersion() {
	//
	std::unique_ptr<OpenCvApp> uniquePtr = std::make_unique<OpenCvApp>();
	//
	return uniquePtr->GetOpenCvAppVersion();
}

//
const char* OpenCvReadImage() {
	//
	std::unique_ptr<OpenCvApp> uniquePtr = std::make_unique<OpenCvApp>();
	//
	return uniquePtr->OpenCvReadImage();
}

//
const char* OpenCvReadImagePath(char* path) {
	//
	std::unique_ptr<OpenCvApp> uniquePtr = std::make_unique<OpenCvApp>();
	//
	return uniquePtr->OpenCvReadImagePath(path);
}

// C++ VERSION
const char* OpenCv_GetCPPSTDVersion()
{
	//
	OpenCvApp *app = new OpenCvApp();
	
	//
	return app->GetCPPSTDVersion(__cplusplus);	
}

//
int generateMandelbrot() {
	//
	std::unique_ptr<OpenCvApp> uniquePtr = std::make_unique<OpenCvApp>();
	//
	return uniquePtr->generateMandelbrot();
}

//
int generateJulia() {
	//
	std::unique_ptr<OpenCvApp> uniquePtr = std::make_unique<OpenCvApp>();
	//
	return uniquePtr->generateJulia();
}

//
int generateJuliaParams(int maxIterations, double realPart, double imagPart) {
	//
	std::unique_ptr<OpenCvApp> uniquePtr = std::make_unique<OpenCvApp>();
	//
	// Create the complex number c
	// valid values :
	// c=0.355+0.355i 
	// c=−0.4+0.6i 
	//
	return uniquePtr->generateJuliaParams(maxIterations,realPart,imagPart);
}

//////////////////////////////////////////////////////////////////////
// CLASS IMPLEMENTATION
//////////////////////////////////////////////////////////////////////

//
CppWebServerApp::CppWebServerApp()
{	
	//
	this->endpointDictionary = {
	    {"HEALTH_ENDPOINT"             , {"/health"                     , "Print all endpoints"}},
	    {"PING_ENDPOINT"               , {"/zero"                       , "Render workaround"}},
	    {"APP_VERSION_ENDPOINT"        , {"/getAppVersion"              , "Get Application Version"}},
	    {"STD_VERSION_ENDPOINT"        , {"/getSTDVersion"              , "Get Standard C++ Version"}},
	    {"SERVER_VERSION_ENDPOINT"     , {"/getServerVersion"           , "Get Http Server Version"}},
	    {"OPEN_CV_VERSION_ENDPOINT"    , {"/api/OpenCv/getAPIVersion"   , "Get Tesseract API Version"}},
	    //{"TESSERACT_UPLOAD_ENDPOINT"     , {"/api/ocr/upload"          , "Upload image from html form via HTTP POST"}},    
	    //{"TESSERACT_OCR_IMAGE_ENDPOINT"  , {"/api/ocr/getImage"        , "UNIT TESTING"}},       
	};
	//
	this->cppWebServerVersion = this->GetCPPHttpVersion();
}
//
CppWebServerApp::~CppWebServerApp()
{	
	//
}
//
const char* CppWebServerApp::GetCPPHttpVersion()
{
    #ifdef CPPHTTPLIB_VERSION
        return CPPHTTPLIB_VERSION;
    #else
        return "Unknown cpp-httplib Version";
    #endif
}
//
int CppWebServerApp::Run()
{
	// HTTP Interceptor & Global CORS Middleware
    svr.set_pre_routing_handler([](const httplib::Request& req, httplib::Response& res) {
        // 1. Request Logging Interceptor
        std::cout << "[Interceptor] " << req.method << " " << req.path << std::endl;

        // 2. Global CORS Header Policy
        res.set_header("Access-Control-Allow-Origin"     , "*");
        res.set_header("Access-Control-Allow-Methods"    , "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers"    , "Origin, Content-Type, Accept, Authorization");
        res.set_header("Access-Control-Allow-Credentials", "true");

        // 3. Handle browser preflight OPTIONS requests automatically
        if (req.method == "OPTIONS") {
            res.status = 204; // No Content
            return httplib::Server::HandlerResponse::Handled;
        }

        // Proceed to route handlers
        return httplib::Server::HandlerResponse::Unhandled;
    });
    
       // Ping / Zero Endpoint
    svr.Get(endpointDictionary["PING_ENDPOINT"].endpointName.c_str(), [](const httplib::Request&, httplib::Response& res) {
        res.status = 204;
    });

    // Server Diagnostics (Health Endpoint listing all routes)
    svr.Get(endpointDictionary["HEALTH_ENDPOINT"].endpointName.c_str(), [&](const httplib::Request&, httplib::Response& res) {
    	//
		std::string webServerVersion = GetCPPHttpVersion();
        //
		std::string jsonResponse     = "{\n  \"server\": \"C++ Http Server 'cpp-httplib' - v[" + webServerVersion  + "] Working!\",\n  \"endpoints\": [\n";
        //
        size_t count = 0;
        for (const auto& pair : endpointDictionary) {
            const std::string& key = pair.first;
            const EndpointInfo& info = pair.second;
            
            std::string comma = (++count < endpointDictionary.size()) ? "," : "";

            jsonResponse += "    {\n";
            jsonResponse += "      \"key\": \"" + key + "\",\n";
            jsonResponse += "      \"path\": \"" + info.endpointName + "\",\n";
            jsonResponse += "      \"description\": \"" + info.endpointDescription + "\"\n";
            jsonResponse += "    }" + comma + "\n";
        }
        
        jsonResponse += "  ]\n}";
        
        res.set_content(jsonResponse, "application/json");
        res.status = 200;
    });
    
    // Get Standard C++ Version
    svr.Get(endpointDictionary["STD_VERSION_ENDPOINT"].endpointName.c_str(), [](const httplib::Request&, httplib::Response& res) {
		 	//
	        std::unique_ptr<AppAlgorithm> uniquePtr = std::make_unique<AppAlgorithm>(true);   
    		//
			std::string jsonResponse             = uniquePtr->GetCPPSTDVersion(__cplusplus); 
            //
			res.set_content(jsonResponse, "application/json");
            res.status = 200;
    });
    
        
    // Get Application Version
    svr.Get(endpointDictionary["APP_VERSION_ENDPOINT"].endpointName.c_str(), [](const httplib::Request&, httplib::Response& res) {
    		//
 	        std::unique_ptr<AppAlgorithm> uniquePtr = std::make_unique<AppAlgorithm>(true);   
			//
    		std::string jsonResponse  = uniquePtr->configMap["DLL_VERSION"]; 
    		//
            res.set_content(jsonResponse, "application/json");
            res.status = 200;
    });
    
	// Get Http Server Version
    svr.Get(endpointDictionary["SERVER_VERSION_ENDPOINT"].endpointName.c_str(), [](const httplib::Request&, httplib::Response& res) {
    		//
			std::string jsonResponse  = CppWebServerApp::GetCPPHttpVersion();
            res.set_content(jsonResponse, "application/json");
            res.status = 200;
    });
    
    // Get API Version
    svr.Get(endpointDictionary["OPEN_CV_VERSION_ENDPOINT"].endpointName.c_str(), [](const httplib::Request&, httplib::Response& res) {
 			//
    		std::string jsonResponse  = GetOpenCvAPIVersion(); 
    		//
            res.set_content(jsonResponse, "application/json");
            res.status = 200;
    });


    /*

    
    // UNIT TEST 
    svr.Get(endpointDictionary["TESSERACT_OCR_IMAGE_ENDPOINT"].endpointName.c_str(), [](const httplib::Request&, httplib::Response& res) {
   	    //
	    std::unique_ptr<TesseractApp> uniquePtr = std::make_unique<TesseractApp>();
		
		//
		std::string jsonResponse  = uniquePtr->GetTesseractOcrOutput();
        res.set_content(jsonResponse, "application/json");
        res.status = 200;
    });
    
	// UPLOAD IMAGE FROM HTML FORM VIA POST
	svr.Post(endpointDictionary["TESSERACT_UPLOAD_ENDPOINT"].endpointName.c_str(), [](const httplib::Request& req, httplib::Response& res) {
	    
	    if (req.body.empty()) {
	        res.status = 400;
	        res.set_content("{\"error\": \"No data received\"}", "application/json");
	        return;
	    }
	
	    try {
	    
			// Cross-platform path management (Windows vs Docker Linux container)
			#ifdef _WIN32
			    std::string savedPath = "uploaded_image.png";
			#else
			    std::string savedPath = "/app/uploaded_image.png";
			#endif

	  	    std::cout << "loading image on path [" << savedPath  << "]" << std::endl;
			  		    
		    std::ofstream outfile(savedPath, std::ios::binary);
		    outfile.write(req.body.data(), req.body.size());
		    outfile.close();
	    
	    	const char * savedPath_cstr = savedPath.c_str();
			 
	    	std::cout << "Processing upload on path [" << savedPath_cstr << "]" << std::endl;
	        
			std::unique_ptr<TesseractApp> uniquePtr = std::make_unique<TesseractApp>();
	        std::string message     = uniquePtr->GetTesseractOcrOutputPath(savedPath_cstr);
	        
	        // Sanitize the Tesseract message to remove or escape raw newlines
			std::string sanitizedMessage = message;
			
			// Remove newlines/carriage returns entirely
			sanitizedMessage.erase(std::remove(sanitizedMessage.begin(), sanitizedMessage.end(), '\n'), sanitizedMessage.end());
			sanitizedMessage.erase(std::remove(sanitizedMessage.begin(), sanitizedMessage.end(), '\r'), sanitizedMessage.end());
			
			//
			sanitizedMessage             = "Text from C++ (httplib) : " + sanitizedMessage;
			cout << "[" <<sanitizedMessage << "]" << endl;
			
			// final response			
			std::string jsonResponse = "{\n  \"message\": \"" + sanitizedMessage + "\",\n  \"status\": \"ok\",\n  \"data\": \"" + savedPath + "\"\n}";
			res.set_content(jsonResponse, "application/json");
			res.status = 200;
	        
	    } catch (const std::exception& e) {
	        std::cout << "Tesseract Exception: " << e.what() << std::endl;
	        res.status = 500;
	        res.set_content("{\"error\": \"OCR processing failed\"}", "application/json");
	    } catch (...) {
	        std::cout << "Unknown Tesseract Crash/Exception" << std::endl;
	        res.status = 500;
	        res.set_content("{\"error\": \"Unknown OCR failure\"}", "application/json");
	    }
	});
	*/
	
	//
    int port = 8080;
    if (getenv("PORT")) {
        port = std::stoi(getenv("PORT"));
    }

	//
    std::cout << "C++ REST Server listening on port " << port << "...\n";
    svr.listen("0.0.0.0", port);

	//
	return 0;
};



////////////////////////////////////////////////////////////
// MAIN PROGRAM ENTRY
////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
	//
	try
	{
		//
		CppWebServerApp* app = new CppWebServerApp();
	
		//
		app->Run();
	} 
	catch(exception &e)
	{
		cout << "Error occurred : [" << e.what() << "]" << endl;
 	}
	
	//
    return 0;
}
	
////////////////////////////////////////////////////////////////