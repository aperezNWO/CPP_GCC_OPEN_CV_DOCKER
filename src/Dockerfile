# Stage 1: Build the C++ binary
FROM debian:bookworm-slim AS builder

RUN apt-get update && apt-get install -y \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

##    libtesseract-dev \
##    tesseract-ocr-eng \

WORKDIR /app
COPY . .

# Added -Iinclude so the compiler can locate the include directory properly
RUN g++ -std=c++17 -O3 CppWebServer.cpp Algorithm.cpp -I.  -o cpp_web_server -lpthread 

# Stage 2: Runtime image
FROM debian:bookworm-slim
WORKDIR /app

RUN apt-get update && apt-get install -y \
     && rm -rf /var/lib/apt/lists/*
##    libtesseract5 \
##    tesseract-ocr-eng \

# Copy runtime binaries and config files
COPY --from=builder /app/opencv.ini     /app/opencv.ini
COPY --from=builder /app/cpp_web_server /app/cpp_web_server
COPY --from=builder /app/image.png      /app/image.png


# Explicitly tell Tesseract where to find trained data files
ENV TESSDATA_PREFIX=/app/tessdata

EXPOSE 8080
CMD ["./cpp_web_server"]