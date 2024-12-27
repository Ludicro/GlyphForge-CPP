#include <fstream>
#include <vector>
#include <cstdint>
#include "writer.h"

// Utility to generate and save combinations to binary file
class CombinationGenerator {
public:
    static void generateAndSave(const std::string& filename, int N) {
        std::vector<std::vector<int>> combinations = Writer::generateUniqueCombinations(N);
        
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Could not create combinations file");
        }
        
        // Write header
        uint32_t numCombinations = combinations.size();
        uint32_t combinationSize = combinations[0].size();
        file.write(reinterpret_cast<char*>(&numCombinations), sizeof(uint32_t));
        file.write(reinterpret_cast<char*>(&combinationSize), sizeof(uint32_t));
        
        // Write patterns
        for (const auto& combo : combinations) {
            file.write(reinterpret_cast<const char*>(combo.data()), 
                      combo.size() * sizeof(int));
        }
    }
};

int main() {
    // Generate combinations for N=15 (based on attribute count)
    CombinationGenerator::generateAndSave("resources/combinations.bin", 15);
    return 0;
}
