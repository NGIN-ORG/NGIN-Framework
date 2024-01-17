#pragma once


#include <NGIN/Common/Defines.hpp>
#include <NGIN/Common/Types/Primitive.hpp>

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
        constexpr explicit Vector3(F32 value) noexcept
            : x(value), y(value), z(value)
        {}
        /// @brief Constructs a Vector3 with the specified components.
        /// @param x The x component of the vector.
        /// @param y The y component of the vector.
        /// @param z The z component of the vector.
        constexpr Vector3(F32 x, F32 y, F32 z) noexcept
            : x(x), y(y), z(z)
        {}


        /// @brief Returns the length of the vector.
        F32 Length() const;

        /// @brief Normalizes the vector.
        Void Normalize();

        /// @brief Returns the dot product of this vector and another.
        /// @param other The other vector.
        F32 Dot(const Vector3& other) const;

        /// @brief Returns the cross product of this vector and another.
        /// @param other The other vector.
        Vector3 Cross(const Vector3& other) const;

        /// @brief Addition operator overload for Vector3.
        /// @param other The other vector.
        Vector3 operator+(const Vector3& other) const;

        /// @brief Subtraction operator overload for Vector3.
        /// @param other The other vector.
        Vector3 operator-(const Vector3& other) const;

        /// @brief Multiplication operator overload for Vector3.
        /// @param other The other vector.
        Vector3 operator*(const Vector3& other) const;

        /// @brief Division operator overload for Vector3.
        /// @param other The other vector.
        Vector3 operator/(const Vector3& other) const;

        /// @brief Addition operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3 operator+(const F32 value) const;

        /// @brief Subtraction operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3 operator-(const F32 value) const;

        /// @brief Multiplication operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3 operator*(const F32 value) const;

        /// @brief Division operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3 operator/(const F32 value) const;

        /// @brief Addition assignment operator overload for Vector3.
        /// @param other The other vector.
        Vector3& operator+=(const Vector3& other);

        /// @brief Subtraction assignment operator overload for Vector3.
        /// @param other The other vector.
        Vector3& operator-=(const Vector3& other);

        /// @brief Multiplication assignment operator overload for Vector3.
        /// @param other The other vector.
        Vector3& operator*=(const Vector3& other);

        /// @brief Division assignment operator overload for Vector3.
        /// @param other The other vector.
        Vector3& operator/=(const Vector3& other);

        /// @brief Addition assignment operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3& operator+=(const F32 value);

        /// @brief Subtraction assignment operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3& operator-=(const F32 value);

        /// @brief Multiplication assignment operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3& operator*=(const F32 value);

        /// @brief Division assignment operator overload for Vector3 and scalar.
        /// @param value The scalar value.
        Vector3& operator/=(const F32 value);
    };

    Vector3 Cross(const Vector3& that, const Vector3& other);

}// namespace NGIN::Math