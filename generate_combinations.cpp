#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

std::vector<std::string> generate_binary_strings(int bit_count) {
    std::vector<std::string> binary_strings;
    
    std::function<void(int, std::string)> genbin;
    genbin = [&](int n, std::string bs) {
        if (bs.length() == size_t(n)) {
            binary_strings.push_back(bs);
        } else {
            genbin(n, bs + "0");
            genbin(n, bs + "1");
        }
    };
    
    genbin(bit_count, "");
    return binary_strings;
}

std::vector<int> cycle_list(const std::vector<int>& l, int loops = 1) {
    std::vector<int> result = l;
    int n = l.size();
    
    for(int t = 0; t < loops; t++) {
        std::vector<int> temp(n);
        for(int i = 0; i < n; i++) {
            temp[i] = result[(i + 1) % n];
        }
        result = temp;
    }
    return result;
}

std::vector<int> string_to_list(const std::string& s) {
    std::vector<int> result;
    for(char c : s) {
        result.push_back(c - '0');
    }
    return result;
}

bool is_rotational_duplicate(const std::vector<int>& ref, const std::vector<std::vector<int>>& non_repeating) {
    int N = ref.size();
    
    for(const auto& existing : non_repeating) {
        for(int n = 0; n < N; n++) {
            if(cycle_list(existing, n + 1) == ref) {
                return true;
            }
        }
    }
    return false;
}

std::vector<std::vector<int>> generate_unique_combinations(int L) {
    auto combinations = generate_binary_strings(L);
    std::vector<std::vector<int>> non_repeating;
    
    std::cout << "Generating unique combinations..." << std::endl;
    std::cout << "[" << std::string(50, ' ') << "] 0%" << std::flush;
    
    // Add first combination as baseline
    non_repeating.push_back(string_to_list(combinations[0]));
    
    // Check each combination against existing ones
    for(size_t i = 1; i < combinations.size(); i++) {
        auto current = string_to_list(combinations[i]);
        
        if(!is_rotational_duplicate(current, non_repeating)) {
            non_repeating.push_back(current);
        }
        
        // Progress bar
        int percentage = (i * 100) / combinations.size();
        int pos = (i * 50) / combinations.size();
        std::cout << "\r[" << std::string(pos, '=') << std::string(50-pos, ' ') << "] " 
                  << percentage << "%" << std::flush;
    }
    std::cout << std::endl;
    
    return non_repeating;
}

void test_read_combinations(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    std::ofstream debug("generate_debug.log");
    
    debug << "\nTesting binary file read:" << std::endl;
    
    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    debug << "Reading " << size << " combinations" << std::endl;
    
    std::vector<std::vector<int>> test_combinations;
    test_combinations.resize(size);
    
    for(size_t i = 0; i < size; i++) {
        test_combinations[i].resize(15);
        file.read(reinterpret_cast<char*>(test_combinations[i].data()), 15 * sizeof(int));
    }
    
    debug << "\nInput Array Contents:" << std::endl;
    const std::vector<std::string> attributeLabels = {
        "Level", "School", "Duration", "Range", "Area Type", "Damage Type", "Condition"
    };
    
    for(size_t i = 0; i < 7; i++) {
        debug << attributeLabels[i] << " Array: ";
        for(int val : test_combinations[i]) {
            debug << val << " ";
        }
        debug << std::endl;
    }
}

int main() {
    int L = 15;  // Changed to 15 to match the expected size in writer.cpp
    auto combinations = generate_unique_combinations(L);

    std::string filename = "unique_combinations.bin";
    
    // Write results to binary file
    std::ofstream outfile(filename, std::ios::binary);
    
    // Write total number of combinations
    size_t size = combinations.size();
    outfile.write(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Write each combination's data directly
    for(const auto& comb : combinations) {
        std::vector<int> zeros(15, 0);  // Create vector of 15 zeros
        // Fill in the 1s based on the combination pattern
        for(size_t i = 0; i < comb.size(); i++) {
            if(comb[i] == 1) {
                zeros[i] = 1;
            }
        }
        outfile.write(reinterpret_cast<const char*>(zeros.data()), 15 * sizeof(int));
    }
    outfile.close();
    
    std::cout << "Generated " << combinations.size() << " unique combinations\n";

    // Test reading the file
    test_read_combinations(filename);

    return 0;
}



