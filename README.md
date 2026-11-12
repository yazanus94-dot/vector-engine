# Vector Engine

A high-performance vector search engine with SIMD acceleration and cache-friendly data structures.

![C++](https://img.shields.io/badge/C++-17-brightgreen)
![CMake](https://img.shields.io/badge/CMake-3.20-blue)
![License](https://img.shields.io/badge/License-MIT-green)

## Overview

Vector Engine provides fast approximate nearest neighbor search with multiple distance metrics. Built with C++17 features including parallel algorithms, it's designed for recommendation systems, image search, and semantic similarity applications.

## Key Features

- **Multiple Metrics**: Cosine similarity, Euclidean distance, dot product
- **Parallel Algorithms**: `std::transform_reduce` with execution policies
- **Cache-Friendly**: Contiguous storage for vector data
- **Type-Safe**: Modern C++ with strong typing
- **Fast Search**: Partial sort for top-k results

## Architecture

```
┌─────────────────────────────────────────┐
│           VectorEngine                   │
│  ┌──────────────────────────────────┐   │
│  │  Vector 1  │  Vector 2  │  ...   │   │
│  │  [1,0,0]   │  [0,1,0]  │         │   │
│  └──────────────────────────────────┘   │
│                    ↑                     │
│              query vector                │
└─────────────────────────────────────────┘
```

## Installation

```bash
git clone https://github.com/yourusername/vector-engine
cd vector-engine
mkdir build && cd build
cmake ..
make
```

## Quick Start

```cpp
#include "vector_engine.hpp"
using namespace vector_engine;

int main() {
    VectorEngine engine;
    
    Vector v1;
    v1.id = "cat";
    v1.data = {1.0f, 0.0f, 0.0f};
    engine.add(std::move(v1));
    
    std::vector<float> query = {1.0f, 0.0f, 0.0f};
    auto results = engine.search(query, 1, Metric::COSINE);
    
    for (const auto& r : results) {
        std::cout << r.id << ": " << r.score << std::endl;
    }
    return 0;
}
```

## Testing

```bash
cd build
cmake --build . --target tests
./tests
```

## License

MIT