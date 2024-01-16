#include <NGIN/Math/Vector3.hpp>
#include <glm/glm.hpp>
namespace NGIN::Math
{


    /*
    constexpr Vector3::Vector3() noexcept
        : x(0.0f), y(0.0f), z(0.0f)
    {}
    constexpr Vector3::Vector3(F32 value) noexcept
        : x(value), y(value), z(value)
    {}
    constexpr Vector3::Vector3(F32 x, F32 y, F32 z) noexcept
        : x(x), y(y), z(z)
    {}*/

    F32 Vector3::Length() const
    {
        return glm::length(ToGLM(*this));
    }

    Void Vector3::Normalize()
    {
        *this = FromGLM(glm::normalize(ToGLM(*this)));
    }

    F32 Vector3::Dot(const Vector3& other) const
    {
        return glm::dot(ToGLM(*this), ToGLM(other));
    }
    /*
    constexpr Vector3 Vector3::Cross(const Vector3& other) const
    {
        return FromGLM(glm::cross(ToGLM(*this), ToGLM(other)));
    }
    */
    Vector3 Vector3::operator+(const Vector3& other) const
    {
        return FromGLM(ToGLM(*this) + ToGLM(other));
    }

    Vector3 Vector3::operator-(const Vector3& other) const
    {
        return FromGLM(ToGLM(*this) - ToGLM(other));
    }

    Vector3 Vector3::operator*(const Vector3& other) const
    {
        return FromGLM(ToGLM(*this) * ToGLM(other));
    }

    Vector3 Vector3::operator/(const Vector3& other) const
    {
        return FromGLM(ToGLM(*this) / ToGLM(other));
    }

    Vector3 Vector3::operator+(const F32 value) const
    {
        return FromGLM(ToGLM(*this) + value);
    }

    Vector3 Vector3::operator-(const F32 value) const
    {
        return FromGLM(ToGLM(*this) - value);
    }

    Vector3 Vector3::operator*(const F32 value) const
    {
        return FromGLM(ToGLM(*this) * value);
    }

    Vector3 Vector3::operator/(const F32 value) const
    {
        return FromGLM(ToGLM(*this) / value);
    }

    Vector3& Vector3::operator+=(const Vector3& other)
    {
        *this = FromGLM(ToGLM(*this) + ToGLM(other));
        return *this;
    }

    Vector3& Vector3::operator-=(const Vector3& other)
    {
        *this = FromGLM(ToGLM(*this) - ToGLM(other));
        return *this;
    }

    Vector3& Vector3::operator*=(const Vector3& other)
    {
        *this = FromGLM(ToGLM(*this) * ToGLM(other));
        return *this;
    }

    Vector3& Vector3::operator/=(const Vector3& other)
    {
        *this = FromGLM(ToGLM(*this) / ToGLM(other));
        return *this;
    }

    Vector3& Vector3::operator+=(const F32 value)
    {
        *this = FromGLM(ToGLM(*this) + value);
        return *this;
    }

    Vector3& Vector3::operator-=(const F32 value)
    {
        *this = FromGLM(ToGLM(*this) - value);
        return *this;
    }

    Vector3& Vector3::operator*=(const F32 value)
    {
        *this = FromGLM(ToGLM(*this) * value);
        return *this;
    }

    Vector3& Vector3::operator/=(const F32 value)
    {
        *this = FromGLM(ToGLM(*this) / value);
        return *this;
    }
}// namespace NGIN::Math
