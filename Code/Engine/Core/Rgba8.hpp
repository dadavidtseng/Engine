//----------------------------------------------------------------------------------------------------
// Rgba8.hpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once
#include "Engine/Math/Vec3.hpp"
#include "Engine/Math/Vec4.hpp"

//----------------------------------------------------------------------------------------------------
struct Rgba8
{
    unsigned char r = 255;
    unsigned char g = 255;
    unsigned char b = 255;
    unsigned char a = 255;

    // TODO: ADD colors 
    static Rgba8 WHITE;
    static Rgba8 TRANSLUCENT_WHITE;
    static Rgba8 BLACK;
    static Rgba8 TRANSLUCENT_BLACK;
    static Rgba8 DARK_GREY;
    static Rgba8 GREY;
    static Rgba8 RED;
    static Rgba8 DARK_RED;
    static Rgba8 GREEN;
    static Rgba8 MAGENTA;
    static Rgba8 CYAN;
    static Rgba8 YELLOW;
    static Rgba8 BLUE;
    static Rgba8 LIGHT_BLUE;
    static Rgba8 ORANGE;

    Rgba8() = default;
    explicit Rgba8(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);

    void SetFromText(char const* text);
    void GetAsFloats(float* colorAsFloats) const;
    Vec3 GetAsVec3() const;
    Vec4 GetAsVec4() const;
    bool operator==(Rgba8 const& compare) const;
};

//----------------------------------------------------------------------------------------------------
Rgba8 Interpolate(Rgba8 start, Rgba8 end, float fractionOfEnd);
