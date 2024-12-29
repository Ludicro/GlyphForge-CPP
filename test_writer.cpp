#include "GlyphEngine\writer.h"

int main() {
    GlyphWriter writer;
    
    writer.draw_spell(
        0,                  // Level
        "Abjuration",       // School
        "1 hour",    // Duration
        "1 mile",         // Range
        "cone (15)",      // Area Type
        "Acid",            // Damage Type
        "Blinded",            // Condition
        false,             // Not concentration
        false,             // Not ritual
        "polygon",         // Base type
        "straight"         // Line shape
    );
    
    return 0;
}
