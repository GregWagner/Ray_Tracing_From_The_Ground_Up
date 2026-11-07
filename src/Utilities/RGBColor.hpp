#ifndef RGBCOLOR_HPP
#define RGBCOLOR_HPP

class RGBColor {
    public:
    float r, g, b;

    RGBColor();
    explicit RGBColor(float c);
    RGBColor(float _r, float _g, float _b);
    RGBColor(const RGBColor& c);

    RGBColor(RGBColor&& c) = default;

    ~RGBColor() = default;

    RGBColor& operator=(const RGBColor& rhs);

    RGBColor& operator=(RGBColor&& rhs) = default;

    RGBColor // addition
    operator+(const RGBColor& c) const;

    RGBColor& // compound addition
    operator+=(const RGBColor& c);

    RGBColor // multiplication by a float on the right
    operator*(const float a) const;

    RGBColor& // compound multiplication by a float on the right
    operator*=(const float a);

    RGBColor // division by a float
    operator/(const float a) const;

    RGBColor& // compound division by a float
    operator/=(const float a);

    RGBColor // component-wise multiplication
    operator*(const RGBColor& c) const;

    bool // are two RGBColours the same?
    operator==(const RGBColor& c) const;

    [[nodiscard]] RGBColor // raise components to a power
    powc(float p) const;

    [[nodiscard]] float // the average of the components
    average() const;
};

// inlined member functions

// addition of two colors
[[nodiscard]] inline RGBColor RGBColor::operator+(const RGBColor& c) const {
    return (RGBColor(r + c.r, g + c.g, b + c.b));
}

// compound addition of two colors
inline RGBColor& RGBColor::operator+=(const RGBColor& c) {
    r += c.r;
    g += c.g;
    b += c.b;
    return (*this);
}

// multiplication by a float on the right
[[nodiscard]] inline RGBColor RGBColor::operator*(const float a) const {
    return (RGBColor(r * a, g * a, b * a));
}

// compound multiplication by a float on the right
inline RGBColor& RGBColor::operator*=(const float a) {
    r *= a;
    g *= a;
    b *= a;
    return (*this);
}

// division by float
[[nodiscard]] inline RGBColor RGBColor::operator/(const float a) const {
    return (RGBColor(r / a, g / a, b / a));
}

// compound division by float
inline RGBColor& RGBColor::operator/=(const float a) {
    r /= a;
    g /= a;
    b /= a;
    return (*this);
}

// component-wise multiplication of two colors
[[nodiscard]] inline RGBColor RGBColor::operator*(const RGBColor& c) const {
    return (RGBColor(r * c.r, g * c.g, b * c.b));
}

// are two RGBColors the same?
inline bool RGBColor::operator==(const RGBColor& c) const {
    return (r == c.r && g == c.g && b == c.b);
}

// the average of the three components
inline float RGBColor::average() const {
    return (0.333333333333 * (r + g + b));
}

// inlined non-member function

// multiplication by a float on the left
RGBColor operator*(const float a, const RGBColor& c);

[[nodiscard]] inline RGBColor operator*(const float a, const RGBColor& c) {
    return (RGBColor(a * c.r, a * c.g, a * c.b));
}

#endif
