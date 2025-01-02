#include "GlyphEngine\writer.h"

int main() {
    GlyphWriter writer;
    
    writer.draw_spell(
        "0",                  // Level
        "None",       // School
        "1 hour",    // Duration
        "None",         // Range
        "None",      // Area Type
        "None",            // Damage Type
        "None",            // Condition
        false,             // Not concentration
        false,             // Not ritual
        "polygon",         // Base type
        "straight"         // Line shape
    );
    
    return 0;
}
