#include "binary_utils.h"

std::vector<int> BinaryUtils::cycleList(const std::vector<int>& list, int loops) {
    std::vector<int> result = list;
    int n = list.size();
    
    for (int t = 0; t < loops; ++t) {
        std::vector<int> temp = result;
        for (int i = 0; i < n; ++i) {
            result[i] = temp[(i + 1) % n];
        }
    }
    return result;
}

std::vector<std::string> BinaryUtils::generateBinaryStrings(int bitCount) {
    std::vector<std::string> result;
    generateBinaryRecursive(bitCount, "", result);
    return result;
}

void BinaryUtils::generateBinaryRecursive(int n, std::string current, 
                                        std::vector<std::string>& result) {
    if (current.length() == n) {
        result.push_back(current);
        return;
    }
    generateBinaryRecursive(n, current + "0", result);
    generateBinaryRecursive(n, current + "1", result);
}

bool BinaryUtils::isUniqueCombination(const std::vector<int>& pattern, 
                                    const std::vector<std::vector<int>>& existing) {
    for (const auto& existing_pattern : existing) {
        for (int n = 1; n <= pattern.size(); ++n) {
            if (cycleList(existing_pattern, n) == pattern) {
                return false;
            }
        }
    }
    return true;
}

std::vector<int> BinaryUtils::stringToBinary(const std::string& binaryString) {
    std::vector<int> result;
    result.reserve(binaryString.length());
    for (char c : binaryString) {
        result.push_back(c - '0');
    }
    return result;
}
