// Required header files
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

// Progress bar function to display the current progress of operations
void print_progress(float progress) {
    int bar_width = 70;
    std::cout << "[";
    int pos = bar_width * progress;
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << (progress * 100.0) << "%\r";
    std::cout.flush();
}

// Generate all possible binary strings of given length
std::vector<std::vector<int>> generate_binary_strings(int bit_count) {
    std::vector<std::vector<int>> result;
    int total = 1 << bit_count;  // Calculate total number of possible combinations (2^bit_count)
    
    // Generate each binary string
    for(int i = 0; i < total; i++) {
        std::vector<int> combination;
        // Convert number to binary representation
        for(int j = 0; j < bit_count; j++) {
            combination.push_back((i >> j) & 1);
        }
        result.push_back(combination);
        print_progress(float(i) / float(total - 1));
    }
    std::cout << std::endl;
    return result;
}

// Rotate a list by a specified number of positions
std::vector<int> cycle_list(const std::vector<int>& list, int loops) {
    std::vector<int> result = list;
    int n = list.size();
    
    // Perform rotation 'loops' number of times
    for(int t = 0; t < loops; t++) {
        std::vector<int> temp(n);
        for(int i = 0; i < n; i++) {
            temp[i] = result[(i + 1) % n];
        }
        result = temp;
    }
    return result;
}

// Generate unique combinations by filtering out rotational duplicates
std::vector<std::vector<int>> generate_unique_combinations(int L) {
    std::cout << "Generating binary strings..." << std::endl;
    auto combinations = generate_binary_strings(L);
    std::vector<std::vector<int>> non_repeating;
    non_repeating.push_back(combinations[0]);  // Add first combination as baseline
    
    std::cout << "Filtering unique combinations..." << std::endl;
    size_t total = combinations.size();
    // Check each combination against existing unique combinations
    for(size_t idx = 0; idx < combinations.size(); idx++) {
        const auto& comb = combinations[idx];
        bool is_unique = true;
        // Compare with all existing unique combinations
        for(const auto& existing : non_repeating) {
            // Check all possible rotations
            for(int n = 0; n < L; n++) {
                if(cycle_list(existing, n + 1) == comb) {
                    is_unique = false;
                    break;
                }
            }
            if(!is_unique) break;
        }
        if(is_unique) {
            non_repeating.push_back(comb);
        }
        print_progress(float(idx) / float(total - 1));
    }
    std::cout << std::endl;
    return non_repeating;
}

// Main function - entry point of the program
int main() {
    std::cout << "Starting combination generation for 15 points..." << std::endl;
    auto combinations = generate_unique_combinations(15);
    
    std::cout << "Saving to file..." << std::endl;
    // Open binary file for writing
    std::ofstream outfile("unique_combinations.bin", std::ios::binary);
    size_t size = combinations.size();
    // Write the number of combinations first
    outfile.write(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Write each combination to the binary file
    for(const auto& comb : combinations) {
        outfile.write(reinterpret_cast<const char*>(comb.data()), comb.size() * sizeof(int));
    }
    
    std::cout << "Generated " << combinations.size() << " unique combinations" << std::endl;
    std::cout << "Process complete!" << std::endl;
    return 0;
}
