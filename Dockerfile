FROM gcc:13-alpine

WORKDIR /app
COPY CMakeLists.txt ./
COPY include/ ./include/
COPY src/ ./src/
COPY tests/ ./tests/

RUN apk add --no-cache cmake && \
    mkdir build && cd build && \
    cmake .. && cmake --build . && \
    ctest --output-on-failure

RUN rm -rf build

CMD ["cmake", "--build", "build"]