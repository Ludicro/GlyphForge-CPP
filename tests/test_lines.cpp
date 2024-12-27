#include <gtest/gtest.h>
#include "line_shapes.h"

class LineShapeTest : public ::testing::Test {
protected:
    const float EPSILON = 0.0001f;
    sf::Vector2f P{100.f, 100.f};
    sf::Vector2f Q{200.f, 200.f};
};

TEST_F(LineShapeTest, StraightLineHasTwoPoints) {
    auto points = LineShape::drawStraight(P, Q);
    EXPECT_EQ(points.size(), 2);
    EXPECT_EQ(points.front(), P);
    EXPECT_EQ(points.back(), Q);
}

TEST_F(LineShapeTest, CentreCircleGeneratesCorrectNumberOfPoints) {
    auto points = LineShape::drawCentreCircle(P, Q);
    EXPECT_EQ(points.size(), 151); // 150 segments + endpoint
}

TEST_F(LineShapeTest, CentreCirclePointsLieOnCircle) {
    auto points = LineShape::drawCentreCircle(P, Q);
    sf::Vector2f center = (P + Q) / 2.f;
    float radius = Utils::distance(P, center);
    
    for (const auto& point : points) {
        float dist = Utils::distance(point, center);
        EXPECT_NEAR(dist, radius, EPSILON);
    }
}

TEST_F(LineShapeTest, FullCircleCompletesCycle) {
    auto points = LineShape::drawCentreCircle(P, Q, true);
    EXPECT_NEAR(Utils::distance(points.front(), points.back()), 0.f, EPSILON);
}

TEST_F(LineShapeTest, CentreCircleStartsAndEndsAtPoints) {
    auto points = LineShape::drawCentreCircle(P, Q);
    EXPECT_NEAR(Utils::distance(points.front(), P), 0.f, EPSILON);
    EXPECT_NEAR(Utils::distance(points.back(), Q), 0.f, EPSILON);
}
