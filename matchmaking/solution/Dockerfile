FROM ubuntu:22.04

# Install build tools and libraries
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    git \
    libssl-dev

WORKDIR /solution

COPY . .

# Build
RUN mkdir -p build && cd build && \
    cmake .. && \
    cmake --build .

EXPOSE 8080

CMD ["./build/Solution"]
