#include "writer.h"
#include <fstream>
#include <algorithm>
#include <SFML/Graphics.hpp>

GlyphWriter::GlyphWriter(const std::string& combinations_file) {
    debug_file.open("glyph_debug.log");
    debug_file << "Starting GlyphWriter initialization..." << std::endl;
    
    std::string path = "GlyphEngine/unique_combinations.bin";
    debug_file << "Loading combinations from: " << path << std::endl;
    load_combinations(path);
}

void GlyphWriter::load_combinations(const std::string& filename) {
    debug_file << "Opening file: " << filename << std::endl;
    std::ifstream file(filename, std::ios::binary);
    
    if (!file.is_open()) {
        debug_file << "Failed to open file" << std::endl;
        return;
    }
    
    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    debug_file << "Reading " << size << " combinations" << std::endl;
    
    unique_combinations.resize(size);
    for(size_t i = 0; i < size; i++) {
        unique_combinations[i].resize(15);
        file.read(reinterpret_cast<char*>(unique_combinations[i].data()), 15 * sizeof(int));
        debug_file << "Loaded combination " << i << ": ";
        for(int val : unique_combinations[i]) {
            debug_file << val << " ";
        }
        debug_file << std::endl;
    }
    debug_file << "Finished loading combinations" << std::endl;
    debug_file.flush();
}

std::vector<int> GlyphWriter::get_attribute_indices(
    int level,
    const std::string& range,
    const std::string& area,
    const std::string& damage_type,
    const std::string& school,
    const std::string& duration,
    const std::string& condition
) {
    debug_file << "\n=== Getting Attribute Indices ===" << std::endl;
    debug_file << "Input parameters:" << std::endl;
    debug_file << "Level: " << level << std::endl;
    debug_file << "Range: " << range << std::endl;
    debug_file << "Area: " << area << std::endl;
    debug_file << "Damage Type: " << damage_type << std::endl;
    debug_file << "School: " << school << std::endl;
    debug_file << "Duration: " << duration << std::endl;
    debug_file << "Condition: " << condition << std::endl;

    std::vector<int> indices;
    
    auto find_index = [](const std::vector<std::string>& vec, const std::string& value) {
        return std::find(vec.begin(), vec.end(), value) - vec.begin();
    };

    indices.push_back(find_index(attributes.levels, std::to_string(level)));
    indices.push_back(find_index(attributes.schools, school));
    indices.push_back(find_index(attributes.durations, duration));
    indices.push_back(find_index(attributes.ranges, range));
    indices.push_back(find_index(attributes.area_types, area));
    indices.push_back(find_index(attributes.damage_types, damage_type));
    indices.push_back(find_index(attributes.conditions, condition));

    debug_file << "Generated indices: ";
    for(int idx : indices) {
        debug_file << idx << " ";
    }
    debug_file << std::endl;
    debug_file.flush();

    return indices;
}

void GlyphWriter::draw_spell(
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
    const std::string& output_file
) {
    debug_file << "\n=== Starting draw_spell ===" << std::endl;
    
    auto indices = get_attribute_indices(level, range, area, damage_type, school, duration, condition);
    debug_file << "Attribute Indices: ";
    for(int idx : indices) {
        debug_file << idx << " ";
    }
    debug_file << std::endl;
    
    std::vector<std::vector<int>> input_array;
    for(int idx : indices) {
        input_array.push_back(unique_combinations[idx]);
    }

    debug_file << "\nInput Array Contents:" << std::endl;
    for(size_t i = 0; i < input_array.size(); i++) {
        debug_file << "Array " << i << ": ";
        for(int val : input_array[i]) {
            debug_file << val << " ";
        }
        debug_file << std::endl;
    }

    sf::RenderTexture renderTexture;
    renderTexture.create(800, 800);
    renderTexture.clear(sf::Color::White);
    debug_file << "\nRenderTexture created and cleared" << std::endl;

    std::pair<std::vector<double>, std::vector<double>> base_points;
    if (base_type == "polygon") {
        base_points = bases::polygon(15);
    } else if (base_type == "line") {
        base_points = bases::line(15);
    } else if (base_type == "quadratic") {
        base_points = bases::quadratic(15);
    } else if (base_type == "circle") {
        base_points = bases::circle(15);
    } else if (base_type == "cubic") {
        base_points = bases::cubic(15);
    } else if (base_type == "golden") {
        base_points = bases::golden(15);
    }

    debug_file << "\nBase Points (" << base_type << "):" << std::endl;
    for(size_t i = 0; i < base_points.first.size(); i++) {
        debug_file << "Point " << i << ": (" 
                  << base_points.first[i] << "," 
                  << base_points.second[i] << ")" << std::endl;
    }

    float scale = 300.0f;
    float offsetX = 400.0f;
    float offsetY = 400.0f;

    debug_file << "\nTransformation values:" << std::endl;
    debug_file << "Scale: " << scale << std::endl;
    debug_file << "Offset X: " << offsetX << std::endl;
    debug_file << "Offset Y: " << offsetY << std::endl;

    for(size_t i = 0; i < input_array.size(); i++) {
        for(size_t j = 0; j < input_array[i].size(); j++) {
            if(input_array[i][j] == 1) {
                size_t current = j;
                size_t next = (j + i + 1) % input_array[i].size();

                std::pair<double, double> P(
                    base_points.first[current] * scale + offsetX,
                    base_points.second[current] * scale + offsetY
                );
                std::pair<double, double> Q(
                    base_points.first[next] * scale + offsetX,
                    base_points.second[next] * scale + offsetY
                );

                debug_file << "\nDrawing line from (" << P.first << "," << P.second 
                          << ") to (" << Q.first << "," << Q.second << ")" << std::endl;

                std::pair<std::vector<double>, std::vector<double>> line_points;
                if (shape_type == "straight") {
                    line_points = line_shapes::straight(P, Q);
                } else if (shape_type == "centre_circle") {
                    line_points = line_shapes::centre_circle(P, Q);
                } else if (shape_type == "non_centre_circle") {
                    line_points = line_shapes::non_centre_circle(P, Q);
                }

                debug_file << "Generated " << line_points.first.size() << " line points" << std::endl;

                sf::VertexArray line(sf::LineStrip, line_points.first.size());
                for(size_t k = 0; k < line_points.first.size(); k++) {
                    line[k].position = sf::Vector2f(
                        static_cast<float>(line_points.first[k]), 
                        static_cast<float>(line_points.second[k])
                    );
                    line[k].color = sf::Color::Black;
                }
                renderTexture.draw(line);
            }
        }
    }

    if (concentration) {
        debug_file << "\nDrawing concentration indicator" << std::endl;
        sf::CircleShape circle(20);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::Black);
        circle.setFillColor(sf::Color::Transparent);
        circle.setPosition(sf::Vector2f(20.f, 20.f));
        renderTexture.draw(circle);
    }
    if (ritual) {
        debug_file << "\nDrawing ritual indicator" << std::endl;
        sf::CircleShape dot(5);
        dot.setFillColor(sf::Color::Black);
        dot.setPosition(sf::Vector2f(35.f, 35.f));
        renderTexture.draw(dot);
    }

    renderTexture.display();
    renderTexture.getTexture().copyToImage().saveToFile(output_file);
    debug_file << "\nSaved image to: " << output_file << std::endl;
    debug_file << "=== Finished draw_spell ===" << std::endl;
    debug_file.flush();
}
