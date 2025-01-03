#pragma once
#include "bases.h"
#include "line_shapes.h"
#include "attributes.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>

class GlyphWriter {
private:
    std::vector<std::vector<int>> unique_combinations;
    Attributes attributes;
    std::ofstream debug_file;

    void load_combinations(const std::string& filename);
    std::vector<int> get_attribute_indices(
        const std::string& level,
        const std::string& school,
        const std::string& duration,
        const std::string& range,
        const std::string& area,
        const std::string& damage_type,
        const std::string& condition
    );

public:
    GlyphWriter(const std::string& combinations_file = "unique_combinations.bin");
    ~GlyphWriter() { if(debug_file.is_open()) debug_file.close(); }

    void draw_spell(
        const std::string& level,
        const std::string& school,
        const std::string& duration,
        const std::string& range,
        const std::string& area,
        const std::string& damage_type,
        const std::string& condition,
        bool concentration,
        bool ritual,
        const std::string& base_type,
        const std::string& shape_type,
        const std::string& output_file = "output.png"
    );
};
