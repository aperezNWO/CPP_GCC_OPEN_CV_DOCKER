# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.18)

# Nombre del proyecto
project(OpenCvDll VERSION 1.0 LANGUAGES CXX)

# Configuración para generar una DLL en Windows
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(BUILD_SHARED_LIBS ON)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Directorio donde se generarán los archivos
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Incluir cabeceras de OpenCV
include_directories("C:/msys64/mingw64/include/opencv4")

# Buscar pkg-config
find_package(PkgConfig REQUIRED)

# Usar pkg-config para obtener cflags/libs de OpenCV
pkg_check_modules(OPENCV REQUIRED IMPORTED_TARGET opencv4)

# Fuentes del proyecto
set(SOURCES OpenCvDll.cpp)
set(DEF_FILE OpenCvDll.def)

# Crear la DLL
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${DEF_FILE})

set_target_properties(OpenCvDll PROPERTIES
    PREFIX ""
    IMPORT_PREFIX ""
    OUTPUT_NAME "OpenCvDll"
)

# Enlazar OpenCV y otras librerías
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${OPENCV_LIBRARIES}
    z
    jpeg
    png
    opengl32
    glu32
    gdi32
    user32
    ole32
    pthread

    # Lista completa de módulos OpenCV (si no están cubiertos por pkg-config)
    opencv_gapi
    opencv_ccalib
    opencv_cvv
    opencv_dnn_objdetect
    opencv_dnn_superres
    opencv_stitching
    opencv_alphamat
    opencv_aruco
    opencv_bgsegm
    opencv_dpm
    opencv_face
    opencv_freetype
    opencv_fuzzy
    opencv_hdf
    opencv_hfs
    opencv_img_hash
    opencv_intensity_transform
    opencv_line_descriptor
    opencv_mcc
    opencv_ovis
    opencv_quality
    opencv_rapid
    opencv_reg
    opencv_rgbd
    opencv_saliency
    opencv_sfm
    opencv_signal
    opencv_stereo
    opencv_structured_light
    opencv_phase_unwrapping
    opencv_superres
    opencv_optflow
    opencv_surface_matching
    opencv_tracking
    opencv_highgui
    opencv_datasets
    opencv_text
    opencv_plot
    opencv_videostab
    opencv_videoio
    opencv_viz
    opencv_wechat_qrcode
    opencv_xfeatures2d
    opencv_shape
    opencv_ml
    opencv_ximgproc
    opencv_video
    opencv_xobjdetect
    opencv_objdetect
    opencv_calib3d
    opencv_imgcodecs
    opencv_features2d
    opencv_dnn
    opencv_flann
    opencv_xphoto
    opencv_photo
    opencv_imgproc
    opencv_core
)