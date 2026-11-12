/**
 * Vector Engine - Test Suite
 */

#include "vector_engine.hpp"
#include <cassert>
#include <iostream>
#include <cmath>

using namespace vector_engine;

static int tests_run = 0;
static int tests_passed = 0;

#define TEST(name) do { \
    tests_run++; \
    std::cout << "  TEST: " << name << " ... "; \
} while(0)

#define PASS() do { \
    tests_passed++; \
    std::cout << "PASS\n"; \
} while(0)

#define FAIL(msg) do { \
    std::cout << "FAIL: " << msg << "\n"; \
} while(0)

void test_add_and_size() {
    TEST("add and size");
    VectorEngine engine;
    assert(engine.empty());
    assert(engine.size() == 0);
    
    Vector v1;
    v1.id = "vec1";
    v1.data = {1.0f, 2.0f, 3.0f};
    engine.add(std::move(v1));
    
    assert(!engine.empty());
    assert(engine.size() == 1);
    PASS();
}

void test_dot_product() {
    TEST("dot product");
    std::vector<float> a = {1.0f, 2.0f, 3.0f};
    std::vector<float> b = {4.0f, 5.0f, 6.0f};
    float result = VectorEngine::dot_product(a, b);
    assert(std::abs(result - 32.0f) < 0.001f);
    PASS();
}

void test_cosine_similarity() {
    TEST("cosine similarity");
    std::vector<float> a = {1.0f, 0.0f};
    std::vector<float> b = {0.0f, 1.0f};
    float result = VectorEngine::cosine_similarity(a, b);
    assert(std::abs(result - 0.0f) < 0.001f);
    
    // Same vectors should have similarity 1.0
    std::vector<float> c = {1.0f, 2.0f, 3.0f};
    float same = VectorEngine::cosine_similarity(c, c);
    assert(std::abs(same - 1.0f) < 0.001f);
    PASS();
}

void test_euclidean_distance() {
    TEST("euclidean distance");
    std::vector<float> a = {0.0f, 0.0f};
    std::vector<float> b = {3.0f, 4.0f};
    float result = VectorEngine::euclidean_distance(a, b);
    assert(std::abs(result - 5.0f) < 0.001f);
    PASS();
}

void test_search_cosine() {
    TEST("search with cosine metric");
    VectorEngine engine;
    
    Vector v1;
    v1.id = "cat";
    v1.data = {1.0f, 0.0f, 0.0f};
    engine.add(std::move(v1));
    
    Vector v2;
    v2.id = "dog";
    v2.data = {0.0f, 1.0f, 0.0f};
    engine.add(std::move(v2));
    
    Vector v3;
    v3.id = "similar";
    v3.data = {0.9f, 0.1f, 0.0f};
    engine.add(std::move(v3));
    
    std::vector<float> query = {1.0f, 0.0f, 0.0f};
    auto results = engine.search(query, 2, Metric::COSINE);
    
    assert(results.size() == 2);
    assert(results[0].id == "cat");
    assert(std::abs(results[0].score - 1.0f) < 0.001f);
    PASS();
}

void test_search_dot_product() {
    TEST("search with dot product metric");
    VectorEngine engine;
    
    Vector v1;
    v1.id = "a";
    v1.data = {1.0f, 2.0f};
    engine.add(std::move(v1));
    
    Vector v2;
    v2.id = "b";
    v2.data = {3.0f, 4.0f};
    engine.add(std::move(v2));
    
    std::vector<float> query = {1.0f, 1.0f};
    auto results = engine.search(query, 1, Metric::DOT_PRODUCT);
    
    assert(results.size() == 1);
    // dot({1,1}, {3,4}) = 7, dot({1,1}, {1,2}) = 3
    assert(results[0].id == "b");
    PASS();
}

void test_search_k_larger_than_size() {
    TEST("search k larger than index size");
    VectorEngine engine;
    
    Vector v1;
    v1.id = "only";
    v1.data = {1.0f, 0.0f};
    engine.add(std::move(v1));
    
    std::vector<float> query = {1.0f, 0.0f};
    auto results = engine.search(query, 10, Metric::COSINE);
    
    assert(results.size() == 1);
    PASS();
}

void test_clear() {
    TEST("clear empties index");
    VectorEngine engine;
    
    Vector v1;
    v1.data = {1.0f};
    engine.add(std::move(v1));
    
    assert(engine.size() == 1);
    engine.clear();
    assert(engine.empty());
    assert(engine.size() == 0);
    PASS();
}

int main() {
    std::cout << "Vector Engine Test Suite\n";
    std::cout << "========================\n\n";
    
    test_add_and_size();
    test_dot_product();
    test_cosine_similarity();
    test_euclidean_distance();
    test_search_cosine();
    test_search_dot_product();
    test_search_k_larger_than_size();
    test_clear();
    
    std::cout << "\nResults: " << tests_passed << "/" << tests_run << " tests passed\n";
    return tests_passed == tests_run ? 0 : 1;
}