cmake_minimum_required(VERSION 3.18)

project(OpenCvApp VERSION 1.0 LANGUAGES CXX)

# Configuración del estándar de C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directorio donde se generará el archivo ejecutable final
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Directorios de cabeceras de MSYS2 MinGW64 y OpenCV
include_directories("C:/msys64/mingw64/include")
include_directories("C:/msys64/mingw64/include/opencv4")

# Archivos fuente del proyecto
set(SOURCES OpenCvApp.cpp)

# Crear el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Asignar el nombre exacto OpenCvApp.exe al binario resultante
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "OpenCvAppV2"
)

# Enlazar los módulos de OpenCV, soporte multihilo y librerías de red de Windows
target_link_libraries(${PROJECT_NAME} PRIVATE
    opencv_core
    opencv_imgcodecs
    opencv_imgproc
    pthread
    ws2_32
    crypt32
)

# Forzar compatibilidad con Windows 10/11 para evitar errores en cpp-httplib
target_compile_definitions(${PROJECT_NAME} PRIVATE _WIN32_WINNT=0x0A00)

# Enlace estático de GCC/libstdc++ para evitar errores de puntos de entrada en Windows
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")