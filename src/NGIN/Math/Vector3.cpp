#include <NGIN/Math/Vector3.hpp>
#include <glm/glm.hpp>
namespace NGIN::Math
{
    constexpr Vector3 FromGLM(const glm::vec3& vec)
    {
        return {vec.x, vec.y, vec.z};
    }
    inline Vector3 FromGLM(const glm::vec4& vec)
    {
        return {vec.x, vec.y, vec.z};
    }
    inline glm::vec3 ToGLM(const Vector3& vec)
    {
        return {vec.x, vec.y, vec.z};
    }

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

    Vector3 Vector3::Cross(const Vector3& other) const
    {
        return Vector3(
                y * other.z - z * other.y,// x component
                z * other.x - x * other.z,// y component
                x * other.y - y * other.x // z component
        );
    }

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

    Vector3 Cross(const Vector3& that, const Vector3& other)
    {
        return Vector3(
                that.y * other.z - that.z * other.y,// x component
                that.z * other.x - that.x * other.z,// y component
                that.x * other.y - that.y * other.x // z component
        );
    }
}// namespace NGIN::Math
