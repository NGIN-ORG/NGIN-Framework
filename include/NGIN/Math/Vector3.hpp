#pragma once


#include <NGIN/Common/Defines.hpp>
#include <NGIN/Common/Types/Primitive.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

namespace NGIN::Math
{


    /// @class Vector3
    /// @brief A 3D vector.
    /// @details This class is a wrapper around glm::vec3.
    struct NGIN_API Vector3
    {
        union
        {

            struct
            {
                /// @brief The x component of the vector.
                F32 x;
                /// @brief The y component of the vector.
                F32 y;
                /// @brief The z component of the vector.
                F32 z;
            };
            struct
            {
                /// @brief The red component of the color.
                F32 r;
                /// @brief The green component of the color.
                F32 g;
                /// @brief The blue component of the color.
                F32 b;
            };
            /// @brief The components of the vector as an array.
            F32 components[3];
        };


        /// @brief Constructs a Vector3 with all components set to 0.
        constexpr Vector3() noexcept
            : x(0.0f), y(0.0f), z(0.0f)
        {}
        /// @brief Constructs a Vector3 with all components set to the same value.
        /// @param value The value to set all components to.
        constexpr explicit Vector3(const F32 value) noexcept
            : x(value), y(value), z(value)
        {}
        /// @brief Constructs a Vector3 with the specified components.
        /// @param x The x component of the vector.
        /// @param y The y component of the vector.
        /// @param z The z component of the vector.
        constexpr Vector3(const F32 x, const F32 y, const F32 z) noexcept
            : x(x), y(y), z(z)
        {}

        explicit constexpr Vector3(const glm::vec3& v) noexcept
            : x(v.x), y(v.y), z(v.z)
        {}

        explicit constexpr operator glm::vec3() const
        {
            return {x, y, z};
        }


        /// @brief Returns the length of the vector.
        [[nodiscard]] F32 Length() const
        {
            return glm::length(static_cast<glm::vec3>(*this));
        }

        [[nodiscard]] F32 LengthSquared() const
        {
            return glm::length2(static_cast<glm::vec3>(*this));
        }

        /// @brief Normalizes the vector.
        Void Normalize()
        {
            *this = static_cast<Vector3>(glm::normalize(static_cast<glm::vec3>(*this)));
        }

        /// @brief Returns a normalized copy of the vector.
        [[nodiscard]] Vector3 Normalized() const
        {
            return static_cast<Vector3>(glm::normalize(static_cast<glm::vec3>(*this)));
        }

        /// @brief Returns the dot product of this vector and another.
        /// @param other The other vector.
        [[nodiscard]] F32 Dot(const Vector3& other) const
        {
            return glm::dot(static_cast<glm::vec3>(*this), static_cast<glm::vec3>(other));
        }

        /// @brief Returns the cross product of this vector and another.
        /// @param other The other vector.
        [[nodiscard]] Vector3 Cross(const Vector3& other) const
        {
            return static_cast<Vector3>(glm::cross(static_cast<glm::vec3>(*this), static_cast<glm::vec3>(other)));
        }

        /// @brief Addition operator overload for Vector3.
        /// @param other The other vector.
        Vector3 operator+(const Vector3& other) const
        {
            return {x + other.x, y + other.y, z + other.z};
        }

        /// @brief Subtraction operator overload for Vector3.
        /// @param other The other vector.
        Vector3 operator-(const Vector3& other) const
        {
            return {x - other.x, y - other.y, z - other.z};
        }

        /// @brief Multiplication operator overload for Vector3.
        /// @param other The other vector.
        Vector3 operator*(const Vector3& other) const
        {
            return {x * other.x, y * other.y, z * other.z};
        }

        /// @brief Division operator overload for Vector3.
        /// @param other The other vector.
        Vector3 operator/(const Vector3& other) const
        {
            return {x / other.x, y / other.y, z / other.z};
        }

        /// @brief Addition operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3 operator+(const F32 value) const
        {
            return {x + value, y + value, z + value};
        }

        /// @brief Subtraction operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3 operator-(const F32 value) const
        {
            return {x - value, y - value, z - value};
        }

        /// @brief Multiplication operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3 operator*(const F32 value) const
        {
            return {x * value, y * value, z * value};
        }

        /// @brief Division operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3 operator/(const F32 value) const
        {
            return {x / value, y / value, z / value};
        }

        /// @brief Addition assignment operator overload for Vector3.
        /// @param other The other vector.
        Vector3& operator+=(const Vector3& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        /// @brief Subtraction assignment operator overload for Vector3.
        /// @param other The other vector.
        Vector3& operator-=(const Vector3& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        /// @brief Multiplication assignment operator overload for Vector3.
        /// @param other The other vector.
        Vector3& operator*=(const Vector3& other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        /// @brief Division assignment operator overload for Vector3.
        /// @param other The other vector.
        Vector3& operator/=(const Vector3& other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        /// @brief Addition assignment operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3& operator+=(const F32 value)
        {
            x += value;
            y += value;
            z += value;
            return *this;
        }

        /// @brief Subtraction assignment operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3& operator-=(const F32 value)
        {
            x -= value;
            y -= value;
            z -= value;
            return *this;
        }

        /// @brief Multiplication assignment operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3& operator*=(const F32 value)
        {
            x *= value;
            y *= value;
            z *= value;
            return *this;
        }

        /// @brief Division assignment operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3& operator/=(const F32 value)
        {
            x /= value;
            y /= value;
            z /= value;
            return *this;
        }
    };
}// namespace NGIN::Math