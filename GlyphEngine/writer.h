#pragma once
#include "bases.h"
#include "line_shapes.h"
#include "attributes.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>  // Add this for debug file

class GlyphWriter {
private:
    std::vector<std::vector<int>> unique_combinations;
    Attributes attributes;
    std::ofstream debug_file;  // Add debug file stream

    void load_combinations(const std::string& filename);
    std::vector<int> get_attribute_indices(
        int level,
        const std::string& range,
        const std::string& area,
        const std::string& damage_type,
        const std::string& school,
        const std::string& duration,
        const std::string& condition
    );

public:
    GlyphWriter(const std::string& combinations_file = "unique_combinations.bin");
    ~GlyphWriter() { if(debug_file.is_open()) debug_file.close(); }  // Add destructor

    void draw_spell(
        int level,
        const std::string& range,
        const std::string& area,
        const std::string& damage_type,
        const std::string& school,
        const std::string& duration,
        const std::string& condition,
        bool concentration,
        bool ritual,
        const std::string& base_type,
        const std::string& shape_type,
        const std::string& output_file = "output.png"
    );
};
