#pragma once

class Point2D {
    public:
    float x, y;

    Point2D();
    explicit Point2D(const float arg);
    Point2D(const float x1, const float y1);
    Point2D(const Point2D& p);
    ~Point2D() {}

    Point2D& operator=(const Point2D& rhs);

    Point2D // multiplication on right by scalar
    operator*(const float a) const;
};

// scales the point by the float a
inline Point2D Point2D::operator*(const float a) const {
    return (Point2D(a * x, a * y));
}