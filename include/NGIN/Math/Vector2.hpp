#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Common/Types/Primitive.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

namespace NGIN::Math
{
    struct NGIN_API Vector2
    {
        union
        {
            struct
            {
                /// @brief The x component of the vector.
                F32 x;
                /// @brief The y component of the vector.
                F32 y;
            };
            /// @brief The components of the vector as an array.
            F32 components[2];
        };


        constexpr Vector2() noexcept
            : x(0.0f), y(0.0f)
        {}

        explicit constexpr Vector2(const F32 value) noexcept
            : x(value), y(value)
        {}

        constexpr Vector2(const F32 x, const F32 y) noexcept
            : x(x), y(y)
        {}

        explicit constexpr Vector2(const glm::vec2& v) noexcept
            : x(v.x), y(v.y)
        {}

        explicit constexpr operator glm::vec2() const
        {
            return {x, y};
        }

        /// @brief Returns the length of the vector.
        [[nodiscard]] F32 Length() const
        {
            return glm::length(static_cast<glm::vec2>(*this));
        }

        [[nodiscard]] F32 LengthSquared() const
        {
            return glm::length2(static_cast<glm::vec2>(*this));
        }

        /// @brief Normalizes the vector.
        Void Normalize()
        {
            *this = static_cast<Vector2>(glm::normalize(static_cast<glm::vec2>(*this)));
        }

        /// @brief Returns a normalized copy of the vector.
        [[nodiscard]] Vector2 Normalized() const
        {
            return static_cast<Vector2>(glm::normalize(static_cast<glm::vec2>(*this)));
        }

        /// @brief Returns the dot product of this vector and another.
        /// @param other The other vector.
        [[nodiscard]] F32 Dot(const Vector2& other) const
        {
            return glm::dot(static_cast<glm::vec2>(*this), static_cast<glm::vec2>(other));
        }

        /// @brief Addition operator overload for Vector2.
        /// @param other The other vector.
        Vector2 operator+(const Vector2& other) const
        {
            return {x + other.x, y + other.y};
        }

        /// @brief Subtraction operator overload for Vector2.
        /// @param other The other vector.
        Vector2 operator-(const Vector2& other) const
        {
            return {x - other.x, y - other.y};
        }

        /// @brief Multiplication operator overload for Vector2.
        /// @param other The other vector.
        Vector2 operator*(const Vector2& other) const
        {
            return {x * other.x, y * other.y};
        }

        /// @brief Division operator overload for Vector2.
        /// @param other The other vector.
        Vector2 operator/(const Vector2& other) const
        {
            return {x / other.x, y / other.y};
        }

        /// @brief Addition operator overload for Vector2 and scalar.
        /// @param value The scalar value.
        Vector2 operator+(const F32 value) const
        {
            return {x + value, y + value};
        }

        /// @brief Subtraction operator overload for Vector2 and scalar.
        /// @param value The scalar value.
        Vector2 operator-(const F32 value) const
        {
            return {x - value, y - value};
        }

        /// @brief Multiplication operator overload for Vector2 and scalar.
        /// @param value The scalar value.
        Vector2 operator*(const F32 value) const
        {
            return {x * value, y * value};
        }

        /// @brief Division operator overload for Vector2 and scalar.
        /// @param value The scalar value.
        Vector2 operator/(const F32 value) const
        {
            return {x / value, y / value};
        }

        /// @brief Addition assignment operator overload for Vector2.
        /// @param other The other vector.
        Vector2& operator+=(const Vector2& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        /// @brief Subtraction assignment operator overload for Vector2.
        /// @param other The other vector.
        Vector2& operator-=(const Vector2& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        /// @brief Multiplication assignment operator overload for Vector2.
        /// @param other The other vector.
        Vector2& operator*=(const Vector2& other)
        {
            x *= other.x;
            y *= other.y;
            return *this;
        }

        /// @brief Division assignment operator overload for Vector2.
        /// @param other The other vector.
        Vector2& operator/=(const Vector2& other)
        {
            x /= other.x;
            y /= other.y;
            return *this;
        }

        /// @brief Addition assignment operator overload for Vector2 and scalar.
        /// @param value The scalar value.
        Vector2& operator+=(const F32 value)
        {
            x += value;
            y += value;
            return *this;
        }

        /// @brief Subtraction assignment operator overload for Vector2 and scalar.
        /// @param value The scalar value.
        Vector2& operator-=(const F32 value)
        {
            x -= value;
            y -= value;
            return *this;
        }

        /// @brief Multiplication assignment operator overload for Vector2 and scalar.
        /// @param value The scalar value.
        Vector2& operator*=(const F32 value)
        {
            x *= value;
            y *= value;
            return *this;
        }

        /// @brief Division assignment operator overload for Vector2 and scalar.
        /// @param value The scalar value.
        Vector2& operator/=(const F32 value)
        {
            x /= value;
            y /= value;
            return *this;
        }
    };
}// namespace NGIN::Math