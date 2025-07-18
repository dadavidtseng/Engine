//----------------------------------------------------------------------------------------------------
// Vec3.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Engine/Math/Vec3.hpp"

#include <cmath>

#include "Engine/Core/EngineCommon.hpp"
#include "Engine/Math/MathUtils.hpp"

//----------------------------------------------------------------------------------------------------
STATIC Vec3 Vec3::ZERO    = Vec3(0, 0, 0);
STATIC Vec3 Vec3::ONE     = Vec3(1, 1, 1);
STATIC Vec3 Vec3::X_BASIS = Vec3(1, 0, 0);
STATIC Vec3 Vec3::Y_BASIS = Vec3(0, 1, 0);
STATIC Vec3 Vec3::Z_BASIS = Vec3(0, 0, 1);

//----------------------------------------------------------------------------------------------------
Vec3::Vec3(float const initialX,
           float const initialY,
           float const initialZ)
    : x(initialX),
      y(initialY),
      z(initialZ)
{
}

//----------------------------------------------------------------------------------------------------
Vec3::Vec3(int const initialX,
           int const initialY,
           int const initialZ)
    : x(static_cast<float>(initialX)),
      y(static_cast<float>(initialY)),
      z(static_cast<float>(initialZ))
{
}

//----------------------------------------------------------------------------------------------------
float Vec3::GetLength() const
{
    return
        sqrtf(x * x + y * y + z * z);
}

//----------------------------------------------------------------------------------------------------
float Vec3::GetLengthXY() const
{
    return
        sqrtf(x * x + y * y);
}

//----------------------------------------------------------------------------------------------------
float Vec3::GetLengthSquared() const
{
    return
        x * x + y * y + z * z;
}

//----------------------------------------------------------------------------------------------------
float Vec3::GetLengthXYSquared() const
{
    return
        x * x + y * y;
}

//----------------------------------------------------------------------------------------------------
float Vec3::GetAngleAboutZRadians() const
{
    return
        ConvertDegreesToRadians(Atan2Degrees(y, x));
}

//----------------------------------------------------------------------------------------------------
float Vec3::GetAngleAboutZDegrees() const
{
    return
        Atan2Degrees(y, x);
}

//----------------------------------------------------------------------------------------------------
Vec3 const Vec3::GetRotatedAboutZRadians(float const deltaRadians) const
{
    float const length    = GetLengthXY();
    float const degree    = GetAngleAboutZDegrees();
    float const newDegree = degree + ConvertRadiansToDegrees(deltaRadians);

    float const deltaX = length * CosDegrees(newDegree);
    float const deltaY = length * SinDegrees(newDegree);

    return Vec3(deltaX, deltaY, z);
}

//----------------------------------------------------------------------------------------------------
Vec3 const Vec3::GetRotatedAboutZDegrees(float const deltaDegrees) const
{
    float const length    = GetLengthXY();
    float const newDegree = GetAngleAboutZDegrees() + deltaDegrees;

    float const deltaX = length * CosDegrees(newDegree);
    float const deltaY = length * SinDegrees(newDegree);

    return Vec3(deltaX, deltaY, z);
}

//----------------------------------------------------------------------------------------------------
Vec3 const Vec3::GetClamped(float const maxLength) const
{
    float const length = GetLength();

    if (length > maxLength)
    {
        float const scale = maxLength / length;

        return Vec3(x * scale, y * scale, z * scale);
    }

    return Vec3(x, y, z);
}

//----------------------------------------------------------------------------------------------------
Vec3 const Vec3::GetNormalized() const
{
    float const length = GetLength();

    if (length == 0.f)
    {
        return ZERO;
    }

    float const scale = 1.f / length;

    return Vec3(x * scale, y * scale, z * scale);
}

//----------------------------------------------------------------------------------------------------
void Vec3::GetOrthonormalBasis(Vec3 const& iBasis,
                               Vec3*       jBasis,
                               Vec3*       kBasis) const
{
    // If the iBasis is not collinear with the zBasis.
    if (abs(DotProduct3D(iBasis, Z_BASIS)) < 0.99999f)
    {
        *jBasis = CrossProduct3D(Z_BASIS, iBasis);
        *jBasis = jBasis->GetNormalized();

        *kBasis = CrossProduct3D(iBasis, *jBasis);
        *kBasis = kBasis->GetNormalized();
    }
    else
    {
        *kBasis = CrossProduct3D(iBasis, Y_BASIS);
        *kBasis = kBasis->GetNormalized();

        *jBasis = CrossProduct3D(*kBasis, iBasis);
        *jBasis = jBasis->GetNormalized();
    }
}

//----------------------------------------------------------------------------------------------------
Vec2  Vec3::GetXY() const
{
    return Vec2(x, y);
}

//----------------------------------------------------------------------------------------------------
void Vec3::SetFromText(char const* text)
{
    // Use SplitStringOnDelimiter to divide the input text into parts based on the delimiter ','
    StringList const parts = SplitStringOnDelimiter(text, ',');

    // Input must contain exactly two parts; otherwise, reset to default values
    if (parts.size() != 3)
    {
        x = 0.f;
        y = 0.f;
        z = 0.f;
        return;
    }

    // Convert the two parts to floats using atof
    x = static_cast<float>(atof(parts[0].c_str()));
    y = static_cast<float>(atof(parts[1].c_str()));
    z = static_cast<float>(atof(parts[2].c_str()));
}

//----------------------------------------------------------------------------------------------------
bool Vec3::operator==(Vec3 const& compare) const
{
    return
        std::fabs(x - compare.x) < FLOAT_MIN &&
        std::fabs(y - compare.y) < FLOAT_MIN &&
        std::fabs(z - compare.z) < FLOAT_MIN;
}

//----------------------------------------------------------------------------------------------------
bool Vec3::operator!=(Vec3 const& compare) const
{
    return
        !(*this == compare);
}

bool Vec3::operator<(Vec3 const& compare) const
{
    if (x != compare.x) return x < compare.x;
    if (y != compare.y) return y < compare.y;
    return z < compare.z;
}

//----------------------------------------------------------------------------------------------------
Vec3 const Vec3::operator+(Vec3 const& vecToAdd) const
{
    return
        Vec3(x + vecToAdd.x, y + vecToAdd.y, z + vecToAdd.z);
}

//----------------------------------------------------------------------------------------------------
Vec3 const Vec3::operator-(Vec3 const& vecToSubtract) const
{
    return
        Vec3(x - vecToSubtract.x, y - vecToSubtract.y, z - vecToSubtract.z);
}

//----------------------------------------------------------------------------------------------------
Vec3 Vec3::operator-() const
{
    return
        Vec3(-x, -y, -z);
}

//----------------------------------------------------------------------------------------------------
Vec3 const Vec3::operator*(float const uniformScale) const
{
    return
        Vec3(x * uniformScale, y * uniformScale, z * uniformScale);
}

//----------------------------------------------------------------------------------------------------
Vec3 const Vec3::operator/(float const inverseScale) const
{
    float const scale = 1.f / inverseScale;

    return Vec3(x * scale, y * scale, z * scale);
}

//----------------------------------------------------------------------------------------------------
void Vec3::operator+=(Vec3 const& vecToAdd)
{
    x += vecToAdd.x;
    y += vecToAdd.y;
    z += vecToAdd.z;
}

//----------------------------------------------------------------------------------------------------
void Vec3::operator-=(Vec3 const& vecToSubtract)
{
    x -= vecToSubtract.x;
    y -= vecToSubtract.y;
    z -= vecToSubtract.z;
}

//----------------------------------------------------------------------------------------------------
void Vec3::operator*=(const float uniformScale)
{
    x *= uniformScale;
    y *= uniformScale;
    z *= uniformScale;
}

//----------------------------------------------------------------------------------------------------
void Vec3::operator/=(const float uniformDivisor)
{
    float const scale = 1.f / uniformDivisor;

    x *= scale;
    y *= scale;
    z *= scale;
}

//----------------------------------------------------------------------------------------------------
Vec3& Vec3::operator=(Vec3 const& copyFrom)
{
    // Check for self-assignment
    if (this != &copyFrom)
    {
        x = copyFrom.x;
        y = copyFrom.y;
        z = copyFrom.z;
    }

    return *this;	// Return the current object by reference (dereference)
}

//----------------------------------------------------------------------------------------------------
Vec3 const operator*(float const uniformScale, Vec3 const& vecToScale)
{
    return Vec3(uniformScale * vecToScale.x, uniformScale * vecToScale.y, uniformScale * vecToScale.z);
}

//----------------------------------------------------------------------------------------------------
Vec3 Interpolate(Vec3 const& start,
                 Vec3 const& end,
                 float const t)
{
    Vec3 result;
    result.x = Interpolate(start.x, end.x, t);
    result.y = Interpolate(start.y, end.y, t);
    result.z = Interpolate(start.z, end.z, t);

    return result;
}