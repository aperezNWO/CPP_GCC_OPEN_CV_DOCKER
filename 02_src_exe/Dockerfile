# syntax=docker/dockerfile:1

############ build stage ############
FROM ubuntu:24.04 AS build
RUN apt-get update && apt-get install -y --no-install-recommends \
      build-essential cmake pkg-config libopencv-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY CMakeLists.txt ./
COPY OpenCvApp.cpp Algorithm.cpp ./
COPY include/ ./include/
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
 && cmake --build build -j"$(nproc)"

############ runtime stage ############
FROM ubuntu:24.04
RUN apt-get update && apt-get install -y --no-install-recommends \
      libopencv-core406t64 libopencv-imgcodecs406t64 libopencv-imgproc406t64 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=build /src/build/OpenCvAppV2 ./OpenCvAppV2
# the app reads these relative to its working directory
COPY image.png opencv.ini ./

EXPOSE 8080
CMD ["./OpenCvAppV2"]