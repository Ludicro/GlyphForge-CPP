#ifndef BINARY_UTILS_H
#define BINARY_UTILS_H

#include <vector>
#include <string>

class BinaryUtils {
public:
    static std::vector<int> cycleList(const std::vector<int>& list, int loops);
    static std::vector<std::string> generateBinaryStrings(int bitCount);
    static bool isUniqueCombination(const std::vector<int>& pattern, 
                                  const std::vector<std::vector<int>>& existing);
    static std::vector<int> stringToBinary(const std::string& binaryString);
    
private:
    static void generateBinaryRecursive(int n, std::string current, 
                                      std::vector<std::string>& result);
};

#endif // BINARY_UTILS_H
