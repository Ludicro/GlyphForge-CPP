#include <gtest/gtest.h>
#include "bases.h"
#include <cmath>

class BaseShapeTest : public ::testing::Test {
protected:
    const float EPSILON = 0.0001f;
};

TEST_F(BaseShapeTest, PolygonGeneratesCorrectNumberOfPoints) {
    int numPoints = 6;
    auto points = BaseShape::generatePolygon(numPoints);
    EXPECT_EQ(points.size(), numPoints);
}

TEST_F(BaseShapeTest, PolygonPointsAreEquidistant) {
    int numPoints = 8;
    auto points = BaseShape::generatePolygon(numPoints);
    float firstDistance = Utils::distance(points[0], points[1]);
    
    for (int i = 1; i < numPoints; ++i) {
        float dist = Utils::distance(points[i], points[(i + 1) % numPoints]);
        EXPECT_NEAR(dist, firstDistance, EPSILON);
    }
}

TEST_F(BaseShapeTest, CirclePointsFollowArcPath) {
    int numPoints = 10;
    auto points = BaseShape::generateCircle(numPoints);
    
    // Check if points lie on circle
    float radius = Utils::distance(points[0], sf::Vector2f(400.f, 400.f));
    for (const auto& point : points) {
        float dist = Utils::distance(point, sf::Vector2f(400.f, 400.f));
        EXPECT_NEAR(dist, radius, EPSILON);
    }
}

TEST_F(BaseShapeTest, QuadraticFollowsParabolicPath) {
    int numPoints = 5;
    float a = 1.0f, b = 0.0f, c = 0.0f;
    auto points = BaseShape::generateQuadratic(numPoints, a, b, c);
    
    // Verify points follow quadratic equation y = ax² + bx + c
    for (const auto& point : points) {
        float x = (point.x - 400.f) / 50.f; // Reverse scaling and offset
        float expectedY = a * x * x + b * x + c;
        float actualY = (point.y - 400.f) / 50.f;
        EXPECT_NEAR(actualY, expectedY, EPSILON);
    }
}

TEST_F(BaseShapeTest, GoldenSpiralFollowsGrowthPattern) {
    int numPoints = 10;
    auto points = BaseShape::generateGolden(numPoints);
    
    // Verify increasing distances from center
    sf::Vector2f center(400.f, 400.f);
    float prevDist = 0.0f;
    
    for (const auto& point : points) {
        float dist = Utils::distance(point, center);
        EXPECT_GT(dist, prevDist);
        prevDist = dist;
    }
}
