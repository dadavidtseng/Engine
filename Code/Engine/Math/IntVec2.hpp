//----------------------------------------------------------------------------------------------------
// IntVec2.hpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

struct Vec2;

//----------------------------------------------------------------------------------------------------
struct IntVec2
{
    // NOTE: this is one of the few cases where we break both the "m_" naming rule AND the avoid-public-members rule
    int            x = 0;
    int            y = 0;
    static IntVec2 ZERO;
    static IntVec2 ONE;
    static IntVec2 NEGATIVE_ONE;

    // Construction/Destruction
    IntVec2()                        = default;		// default constructor (do nothing)
    ~IntVec2()                       = default;		// destructor (do nothing)
    IntVec2(IntVec2 const& copyFrom) = default;		// copy constructor (from another IntVec2)
    explicit IntVec2(int initialX, int initialY);	// explicit constructor (from x, y)
    explicit IntVec2(float initialX, float initialY);
    explicit IntVec2(Vec2 const& vec2);

    // Accessors (const methods)
    float   GetLength() const;
    int     GetLengthSquared() const;
    int     GetTaxicabLength() const;
    float   GetOrientationRadians() const;
    float   GetOrientationDegrees() const;
    IntVec2 GetRotated90Degrees() const;
    IntVec2 GetRotatedMinus90Degrees() const;

    // Mutators (non-const methods)
    void Rotate90Degrees();
    void RotateMinus90Degrees();
    void SetFromText(char const* text);

    // Operators (self-mutating)
    bool operator==(IntVec2 const& compare) const;      // IntVec2 == IntVec2
    bool operator!=(IntVec2 const& compare) const;      // IntVec2 != IntVec2

    IntVec2&      operator=(const IntVec2& copyFrom); // IntVec2 = IntVec2
    IntVec2 const operator+(IntVec2 const& vecToAdd) const;      // IntVec2 + IntVec2
    IntVec2 const operator-(IntVec2 const& vecToSubtract) const;      // IntVec2 - IntVec2
};

IntVec2 Interpolate(IntVec2 const& start, IntVec2 const& end, float t);
