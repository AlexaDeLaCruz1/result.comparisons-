#include "SearchLab.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>


SearchLab::~SearchLab() {
    clearData();
}

void SearchLab::clearData() {
    for (Product* p : products_) {
        delete p; 
    }
    products_.clear();
    totalInsertComparisons_ = 0;
}


void SearchLab::insertProduct(Product *product) {
    auto it = products_.begin();
    
    while (it != products_.end()) {
        totalInsertComparisons_++; 
        if ((*it)->getProductId() >= product->getProductId()) {
            break;
        }
        ++it;
    }
    
    products_.insert(it, product);
}


long long SearchLab::batchSort() {
    long long comparisons = 0;
    
 
    std::sort(products_.begin(), products_.end(),
        [&comparisons](const Product* a, const Product* b) {
            comparisons++; 
            return a->getProductId() < b->getProductId();
        });
    return comparisons;
}


SearchResult SearchLab::linearSearch(const std::string& targetId) const {
    SearchResult result;
    result.comparisons = 0;

    for (const Product* p : products_) {
        result.comparisons++;
        if (p->getProductId() == targetId) {
            result.product = p;
            return result; 
        }
    }
    return result;
}


SearchResult SearchLab::binarySearch(const std::string& targetId) const {
    SearchResult result;
    result.comparisons = 0;

    int low = 0;
    int high = products_.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        const std::string& midId = products_[mid]->getProductId();

        result.comparisons++;
        if (midId == targetId) {
            result.product = products_[mid];
            return result; 
        }

        result.comparisons++;
        if (midId < targetId) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}


BatchResult SearchLab::runBatchTest(int numRuns, long long batchSortCost) const {
    if (products_.empty() || numRuns <= 0) {
        return {0, 0.0, 0.0, 0, 0.0, 0};
    }

    long long totalLinearComparisons = 0;
    long long totalBinaryComparisons = 0;
    
    for (int i = 0; i < numRuns; ++i) {
        int randomIndex = std::rand() % products_.size();
        std::string targetId = products_[randomIndex]->getProductId();

        SearchResult linear = linearSearch(targetId);
        totalLinearComparisons += linear.comparisons;

        SearchResult binary = binarySearch(targetId);
        totalBinaryComparisons += binary.comparisons;
    }

    BatchResult result;
    result.totalRuns = numRuns;
    result.avgLinearComparisons = static_cast<double>(totalLinearComparisons) / numRuns;
    result.avgBinaryComparisons = static_cast<double>(totalBinaryComparisons) / numRuns;
    result.totalInsertComparisons = totalInsertComparisons_;
    result.avgInsertComparisons = totalInsertComparisons_ / static_cast<double>(products_.size());
    result.batchSortComparisons = batchSortCost;

    return result;
}
