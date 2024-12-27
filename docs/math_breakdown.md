
# Mathematical Components of GlyphForge

## Base Shape Generation

### Polygon Base
- Uses parametric equations for circle points
- x = r * sin(θ)
- y = r * cos(θ)
- Points distributed evenly around circle: θ = startAngle + i * (2π/n)
- n determines number of vertices
- startAngle = π/n for proper orientation

### Circle Base
- Parametric equations for arc generation
- x = r * cos(θ)
- y = r * sin(θ)
- θ ranges from θ0 to θ1
- Default quarter circle: θ0 = 0, θ1 = -π/2

### Quadratic Base
- Standard form: y = ax² + bx + c
- Points alternate between positive/negative x values
- Creates symmetric pattern around y-axis

### Golden Spiral
- Uses golden ratio φ = (1 + √5)/2
- Growth factor: f = φ^(tφ/2π)
- Parametric equations:
  - x = cos(t) * f
  - y = sin(t) * f

## Line Generation

### Centre Circle
- Midpoint calculation: (x₁+x₂)/2, (y₁+y₂)/2
- Radius: r = √((x₁-a)² + (y₁-b)²)
- Arc equations:
  - x = r * cos(θ) + a
  - y = r * sin(θ) + b

### Straight Lines
- Linear interpolation between points
- Direct point-to-point connection

## Pattern Generation
- Binary pattern creation for unique glyphs
- Cyclic permutation checking for uniqueness
- Pattern combination for multiple attributes
