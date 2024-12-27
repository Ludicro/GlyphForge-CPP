#include <gtest/gtest.h>
#include "writer.h"
#include "spell_data.h"

class WriterTest : public ::testing::Test {
protected:
    Writer writer;
    SpellAttributes testAttrs{
        "1",            // level
        "Evocation",    // school
        "Instantaneous", // duration
        "60 feet",      // range
        "Sphere",       // area
        "Fire",         // dtype
        "None",         // condition
        false,          // concentration
        false          // ritual
    };
};

TEST_F(WriterTest, CreateGlyphGeneratesValidImage) {
    sf::Image image = writer.createGlyph(testAttrs);
    EXPECT_GT(image.getSize().x, 0);
    EXPECT_GT(image.getSize().y, 0);
}

TEST_F(WriterTest, PatternGenerationIsConsistent) {
    auto pattern1 = writer.generatePattern(testAttrs);
    auto pattern2 = writer.generatePattern(testAttrs);
    EXPECT_EQ(pattern1, pattern2);
}

TEST_F(WriterTest, FindMatchingSpellReturnsCorrectSpell) {
    // Test with Burning Hands spell attributes
    testAttrs.name = "";
    testAttrs.level = "1";
    testAttrs.school = "Evocation";
    testAttrs.duration = "Instantaneous";
    testAttrs.range = "Self";
    testAttrs.area_type = "Cone";
    testAttrs.dtype = "Fire";
    
    std::string matchingSpell = writer.findMatchingSpell(testAttrs);
    EXPECT_EQ(matchingSpell, "Burning Hands");
}

TEST_F(WriterTest, NonExistentSpellReturnsEmptyString) {
    testAttrs.level = "9";
    testAttrs.school = "Illusion";
    testAttrs.duration = "24 hours";
    testAttrs.range = "1 mile";
    testAttrs.area_type = "Wall";
    testAttrs.dtype = "Thunder";
    
    std::string matchingSpell = writer.findMatchingSpell(testAttrs);
    EXPECT_TRUE(matchingSpell.empty());
}

TEST_F(WriterTest, ConcentrationAffectsGlyphGeneration) {
    testAttrs.concentration = true;
    sf::Image imageWithConc = writer.createGlyph(testAttrs);
    
    testAttrs.concentration = false;
    sf::Image imageWithoutConc = writer.createGlyph(testAttrs);
    
    EXPECT_NE(imageWithConc.getSize(), imageWithoutConc.getSize());
}
