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

std::vector<std::vector<int>> generate_unique_combinations(int L) {
    auto combinations = generate_binary_strings(L);
    std::vector<std::vector<int>> non_repeating;
    
    std::cout << "Generating combinations..." << std::endl;
    std::cout << "[" << std::string(50, ' ') << "] 0%" << std::flush;
    
    for(size_t i = 0; i < combinations.size(); i++) {
        non_repeating.push_back(string_to_list(combinations[i]));
        
        // Progress bar
        int percentage = (i * 100) / combinations.size();
        int pos = (i * 50) / combinations.size();
        std::cout << "\r[" << std::string(pos, '=') << std::string(50-pos, ' ') << "] " 
                  << percentage << "%" << std::flush;
    }
    std::cout << std::endl;
    
    return non_repeating;
}

int main() {
    int L = 15;
    auto combinations = generate_unique_combinations(L);
    
    std::ofstream outfile("unique_combinations.bin", std::ios::binary);
    size_t size = combinations.size();
    outfile.write(reinterpret_cast<char*>(&size), sizeof(size));
    
    for(const auto& comb : combinations) {
        outfile.write(reinterpret_cast<const char*>(comb.data()), comb.size() * sizeof(int));
    }
    
    std::cout << "Generated " << combinations.size() << " combinations\n";
    return 0;
}
