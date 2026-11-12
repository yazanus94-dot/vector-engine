/**
 * Vector Engine - High-Performance Vector Search Engine
 * 
 * A cache-friendly vector search engine with SIMD acceleration,
 * supporting cosine similarity, Euclidean distance, and dot product.
 */

#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>
#include <string>
#include <string_view>

namespace vector_engine {

/**
 * Represents a vector in the search index.
 */
struct Vector {
    std::vector<float> data;
    std::string id;
    std::string metadata;
};

/**
 * Search result containing the vector ID and similarity score.
 */
struct SearchResult {
    std::string id;
    float score;
    std::string metadata;

    bool operator<(const SearchResult& other) const {
        return score > other.score;  // Higher score first
    }
};

/**
 * Distance metric options.
 */
enum class Metric {
    COSINE,      // Cosine similarity
    EUCLIDEAN,   // Euclidean distance
    DOT_PRODUCT  // Dot product
};

/**
 * High-performance vector search engine.
 */
class VectorEngine {
public:
    VectorEngine() = default;
    ~VectorEngine() = default;

    // Non-copyable, movable
    VectorEngine(const VectorEngine&) = delete;
    VectorEngine& operator=(const VectorEngine&) = delete;
    VectorEngine(VectorEngine&&) noexcept = default;
    VectorEngine& operator=(VectorEngine&&) noexcept = default;

    /**
     * Adds a vector to the index.
     */
    void add(Vector vec);

    /**
     * Searches for the k nearest neighbors.
     * 
     * @param query The query vector
     * @param k The number of results to return
     * @param metric The distance metric to use
     * @return Vector of search results sorted by similarity
     */
    std::vector<SearchResult> search(const std::vector<float>& query, 
                                      size_t k, 
                                      Metric metric = Metric::COSINE);

    /**
     * Returns the number of vectors in the index.
     */
    size_t size() const;

    /**
     * Clears all vectors from the index.
     */
    void clear();

    /**
     * Returns true if the index is empty.
     */
    bool empty() const;

    /**
     * Computes cosine similarity between two vectors.
     */
    static float cosine_similarity(const std::vector<float>& a, 
                                    const std::vector<float>& b);

    /**
     * Computes Euclidean distance between two vectors.
     */
    static float euclidean_distance(const std::vector<float>& a, 
                                      const std::vector<float>& b);

    /**
     * Computes dot product between two vectors.
     */
    static float dot_product(const std::vector<float>& a, 
                              const std::vector<float>& b);

private:
    std::vector<Vector> index_;
};

}  // namespace vector_engine