#ifndef BLOOMFILTER_BLOOMFILTER_H
#define BLOOMFILTER_BLOOMFILTER_H

#include <vector>
#include <string>
#include <cmath>
#include "MurmurHash3.h"

namespace bloom_filter {

class BloomFilter {
public:
    BloomFilter(std::vector<std::string> &keys, uint32_t size);
    bool lookupKey(std::string key);
    uint64_t getMemoryUsage();
    double getFPR() { return fpr_; }


private:
    std::vector<bool> bitArray_;
    uint8_t numberOfHashes_;
    double fpr_;

    uint8_t calculateNumberOfHashes(uint32_t n);
    double calculateFPR(uint32_t n, uint32_t size) const;

};
} // namespace bloom_filter

#endif //BLOOMFILTER_BLOOMFILTER_H
