/**
 * Vector Engine - Implementation
 */

#include "vector_engine.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <execution>

namespace vector_engine {

void VectorEngine::add(Vector vec) {
    index_.push_back(std::move(vec));
}

size_t VectorEngine::size() const {
    return index_.size();
}

bool VectorEngine::empty() const {
    return index_.empty();
}

void VectorEngine::clear() {
    index_.clear();
}

float VectorEngine::dot_product(const std::vector<float>& a, 
                                 const std::vector<float>& b) {
    if (a.size() != b.size()) return 0.0f;
    return std::transform_reduce(
        std::execution::par,
        a.begin(), a.end(),
        b.begin(),
        0.0f,
        std::plus<float>(),
        std::multiplies<float>()
    );
}

float VectorEngine::cosine_similarity(const std::vector<float>& a, 
                                       const std::vector<float>& b) {
    float dot = dot_product(a, b);
    float norm_a = std::sqrt(dot_product(a, a));
    float norm_b = std::sqrt(dot_product(b, b));
    if (norm_a == 0 || norm_b == 0) return 0.0f;
    return dot / (norm_a * norm_b);
}

float VectorEngine::euclidean_distance(const std::vector<float>& a, 
                                         const std::vector<float>& b) {
    if (a.size() != b.size()) return INFINITY;
    float sum = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        float diff = a[i] - b[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

std::vector<SearchResult> VectorEngine::search(const std::vector<float>& query,
                                                size_t k,
                                                Metric metric) {
    if (k > index_.size()) k = index_.size();
    if (k == 0) return {};

    std::vector<SearchResult> results;
    results.reserve(index_.size());

    for (const auto& vec : index_) {
        float score;
        switch (metric) {
            case Metric::COSINE:
                score = cosine_similarity(query, vec.data);
                break;
            case Metric::EUCLIDEAN:
                score = -euclidean_distance(query, vec.data);
                break;
            case Metric::DOT_PRODUCT:
                score = dot_product(query, vec.data);
                break;
        }
        results.push_back({vec.id, score, vec.metadata});
    }

    // Partial sort to get top k
    std::partial_sort(results.begin(), results.begin() + k, results.end());
    results.resize(k);

    return results;
}

}  // namespace vector_engine