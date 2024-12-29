#include "GlyphEngine\writer.h"

int main() {
    GlyphWriter writer;
    
    // Test case 1: Fireball-like spell
    writer.draw_spell(
        3,                  // 3rd level
        "150 feet",         // Range
        "sphere (20)",      // Area
        "Fire",            // Damage type
        "Evocation",       // School
        "Instantaneous",    // Duration
        "None",            // Condition
        false,             // Not concentration
        false,             // Not ritual
        "polygon",         // Base type
        "straight"         // Line shape
    );
    
    
    return 0;
}
