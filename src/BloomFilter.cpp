#include "BloomFilter.h"

namespace bloom_filter {
    BloomFilter::BloomFilter(std::vector<std::string> &keys, uint32_t size) {
        numberOfHashes_ = calculateNumberOfHashes(keys.size());
        fpr_ = calculateFPR(keys.size(), size);

        bitArray_ = std::vector<bool>(size);

        for (const auto& key : keys) {
            for (size_t i = 0 ; i < numberOfHashes_ ; i++) {
                uint32_t result;
                MurmurHash3_x86_32(key.c_str(), key.size(), i, (void*) &result);
                bitArray_[result % bitArray_.size()] = true;
            }
        }
    }

    uint8_t BloomFilter::calculateNumberOfHashes(uint32_t n) {
        const uint8_t m = bitArray_.size();
        auto k_ = (int8_t) std::floor(std::log(2) * m / (n + 0.0));
        if (k_ == 0) return 1;
        return k_;
    }

    bool BloomFilter::lookupKey(std::string key) {
        int32_t counter = 0;
        for (size_t i = 0 ; i < numberOfHashes_ ; i++) {
            uint32_t result;
            MurmurHash3_x86_32(key.c_str(), key.size(), i, (void*) &result);
            if (!bitArray_[result % bitArray_.size()]) {
                return false;
            }
        }
        return true;
    }

    double BloomFilter::calculateFPR(uint32_t n, uint32_t size) const {
        auto a = - (double) numberOfHashes_ * (double) n / (size + 0.0);
        auto e = std::exp(a);
        return std::pow(1. - e,numberOfHashes_);
    }

    uint64_t BloomFilter::getMemoryUsage() {
        return sizeof(BloomFilter) + sizeof(bitArray_);
    }
}