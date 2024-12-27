#include <gtest/gtest.h>
#include "utils.h"

class UtilsTest : public ::testing::Test {
protected:
    const float EPSILON = 0.0001f;
};

TEST_F(UtilsTest, StringManipulation) {
    EXPECT_EQ(Utils::toLower("Hello WORLD"), "hello world");
    EXPECT_EQ(Utils::toUpper("Hello world"), "HELLO WORLD");
    
    auto tokens = Utils::split("one,two,three", ',');
    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0], "one");
    EXPECT_EQ(tokens[1], "two");
    EXPECT_EQ(tokens[2], "three");
}

TEST_F(UtilsTest, AngleConversion) {
    EXPECT_NEAR(Utils::degToRad(180.0f), M_PI, EPSILON);
    EXPECT_NEAR(Utils::radToDeg(M_PI), 180.0f, EPSILON);
    EXPECT_NEAR(Utils::normalizeAngle(3 * M_PI), M_PI, EPSILON);
}

TEST_F(UtilsTest, VectorOperations) {
    sf::Vector2f v1(3.0f, 4.0f);
    sf::Vector2f v2(6.0f, 8.0f);
    
    EXPECT_NEAR(Utils::distance(v1, v2), 5.0f, EPSILON);
    
    auto normalized = Utils::normalize(v1);
    EXPECT_NEAR(Utils::distance(normalized, sf::Vector2f(0, 0)), 1.0f, EPSILON);
    
    EXPECT_NEAR(Utils::dotProduct(v1, v2), 50.0f, EPSILON);
}

TEST_F(UtilsTest, ColorOperations) {
    sf::Color c1(255, 0, 0);
    sf::Color c2(0, 255, 0);
    
    auto interpolated = Utils::interpolateColor(c1, c2, 0.5f);
    EXPECT_EQ(interpolated.r, 127);
    EXPECT_EQ(interpolated.g, 127);
    EXPECT_EQ(interpolated.b, 0);
    
    auto brightened = Utils::adjustBrightness(c1, 0.5f);
    EXPECT_EQ(brightened.r, 127);
    EXPECT_EQ(brightened.g, 0);
    EXPECT_EQ(brightened.b, 0);
}

TEST_F(UtilsTest, RandomUtilities) {
    float randFloat = Utils::randomFloat(0.0f, 1.0f);
    EXPECT_GE(randFloat, 0.0f);
    EXPECT_LE(randFloat, 1.0f);
    
    int randInt = Utils::randomInt(1, 10);
    EXPECT_GE(randInt, 1);
    EXPECT_LE(randInt, 10);
    
    bool randBool = Utils::randomBool();
    EXPECT_TRUE(randBool == true || randBool == false);
}
