export module NGIN.Units:TimeUnits;

import :IUnit;
import :Ratio;
export import NGIN.Types;
export import std;

export namespace NGIN
{


    /// <summary>
    /// Represents the base class for all time units using the Curiously Recurring Template Pattern (CRTP).
    /// This class provides common functionality for time unit arithmetic and conversions while enforcing
    /// compile-time checks for required features in derived classes, such as the presence of a RatioType.
    /// </summary>
    /// <typeparam name="T">The derived class which inherits from TimeUnitCRTP.</typeparam>
    template<typename T>
    class TimeUnitCRTP : IUnit
    {
    public:
        constexpr TimeUnitCRTP() = default;

        /// <summary>
        /// Initializes a new instance of the time unit with the specified value.
        /// </summary>
        /// <param name="value">The value of the time unit in terms of its base unit.</param>
        constexpr TimeUnitCRTP(const F64 value)
            : value(value) {}

        /// <summary>
        /// Converts this time unit to another time unit of type T, based on the ratio defined in both units.
        /// </summary>
        /// <typeparam name="U">The type of the time unit to convert to. Must be derived from TimeUnitCRTP.</typeparam>
        /// <returns>A new instance of type T, representing the converted value of this time unit.</returns>
        template<typename U>
            requires std::is_base_of_v<TimeUnitCRTP<U>, U>
        constexpr explicit operator U() const
        {
            return U(value * T::RatioType::value * U::RatioType::inverse);
        }

        /// <summary>
        /// Adds the value of another time unit to this unit, resulting in a new time unit of type T.
        /// </summary>
        /// <typeparam name="U">The type of the other time unit. Must be derived from TimeUnitCRTP.</typeparam>
        /// <param name="other">The other time unit to add to this unit.</param>
        /// <returns>A new time unit of type T, representing the sum of this unit and the other unit.</returns>
        template<typename U>
            requires std::is_base_of_v<TimeUnitCRTP<U>, U>
        constexpr T operator+(const U& other) const
        {
            return T(value + static_cast<T>(other).value);
        }

        /// <summary>
        /// Subtracts the value of another time unit from this unit, resulting in a new time unit of type T.
        /// </summary>
        /// <typeparam name="U">The type of the other time unit. Must be derived from TimeUnitCRTP.</typeparam>
        /// <param name="other">The other time unit to subtract from this unit.</param>
        /// <returns>A new time unit of type T, representing the difference between this unit and the other unit.</returns>
        template<typename U>
            requires std::is_base_of_v<TimeUnitCRTP<U>, U>
        constexpr T operator-(const U& other) const
        {
            return T(value - static_cast<T>(other).value);
        }

        /// <summary>
        /// Multiplies this time unit by another unit's value, resulting in a new time unit of type T.
        /// </summary>
        /// <typeparam name="U">The type of the other time unit. Must be derived from TimeUnitCRTP.</typeparam>
        /// <param name="other">The other time unit to multiply with this unit.</param>
        /// <returns>A new time unit of type T, representing the product of this unit and the other unit's value.</returns>
        template<typename U>
            requires std::is_base_of_v<TimeUnitCRTP<U>, U>
        constexpr T operator*(const U& other) const
        {
            return T(value * static_cast<T>(other).value);
        }

        /// <summary>
        /// Divides this time unit by another unit's value, resulting in a new time unit of type T.
        /// </summary>
        /// <typeparam name="U">The type of the other time unit. Must be derived from TimeUnitCRTP.</typeparam>
        /// <param name="other">The other time unit by which to divide this unit.</param>
        /// <returns>A new time unit of type T, representing the quotient of this unit divided by the other unit's value.</returns>
        template<typename U>
            requires std::is_base_of_v<TimeUnitCRTP<U>, U>
        constexpr T operator/(const U& other) const
        {
            return T(value / static_cast<T>(other).value);
        }

        friend std::ostream& operator<<(std::ostream& os, const T& unit)
        {
            return os << unit.value << T::symbol;
        }

        F64 GetValue() const
        {
            return value;
        }

    protected:
        F64 value = 0;
    };

    /// <summary>
    /// Concept that checks if a given type is derived from TimeUnitCRTP, ensuring
    /// type safety and consistency across time-related operations and conversions.
    /// </summary>
    /// <typeparam name="T">The type to be checked.</typeparam>
    template<typename T>
    concept IsTimeUnit = std::is_base_of_v<TimeUnitCRTP<T>, T>;


    /// <summary>
    /// Represents time in nanoseconds, derived from the BaseTimeUnit, providing
    /// functionality for time unit conversions and arithmetic operations.
    /// </summary>
    struct Nanoseconds : TimeUnitCRTP<Nanoseconds>
    {
        using RatioType = Ratio<1, 1000000000>;
        static constexpr StringView symbol = "ns";

        constexpr Nanoseconds(const F64 value)
            : TimeUnitCRTP(value) {}
    };

    /// <summary>
    /// Represents time in Microseconds, derived from the BaseTimeUnit, providing
    /// functionality for time unit conversions and arithmetic operations.
    /// </summary>
    struct Microseconds : TimeUnitCRTP<Microseconds>
    {
        using RatioType = Ratio<1, 1000000>;
        static constexpr StringView symbol = "us";

        constexpr Microseconds(const F64 value)
            : TimeUnitCRTP(value) {}
    };

    /// <summary>
    /// Represents time in Milliseconds, derived from the BaseTimeUnit, providing
    /// functionality for time unit conversions and arithmetic operations.
    /// </summary>
    struct Milliseconds : TimeUnitCRTP<Milliseconds>
    {
        using RatioType = Ratio<1, 1000>;
        static constexpr StringView symbol = "ms";

        constexpr Milliseconds(const F64 value)
            : TimeUnitCRTP(value) {}
    };

    /// <summary>
    /// Represents time in Seconds, derived from the BaseTimeUnit, providing
    /// functionality for time unit conversions and arithmetic operations.
    /// </summary>
    struct Seconds : TimeUnitCRTP<Seconds>
    {
        using RatioType = Ratio<1, 1>;
        static constexpr StringView symbol = "s";

        constexpr Seconds(const F64 value)
            : TimeUnitCRTP(value) {}
    };

    /// <summary>
    /// Represents time in Minutes, derived from the BaseTimeUnit, providing
    /// functionality for time unit conversions and arithmetic operations.
    /// </summary>
    struct Minutes : TimeUnitCRTP<Minutes>
    {
        using RatioType = Ratio<60, 1>;
        static constexpr StringView symbol = "m";

        constexpr Minutes(const F64 value)
            : TimeUnitCRTP(value) {}
    };

    /// <summary>
    /// Represents time in Hours, derived from the BaseTimeUnit, providing
    /// functionality for time unit conversions and arithmetic operations.
    /// </summary>
    struct Hours : TimeUnitCRTP<Hours>
    {
        using RatioType = Ratio<3600, 1>;
        static constexpr StringView symbol = "h";

        constexpr Hours(const F64 value)
            : TimeUnitCRTP(value) {}
    };


}// namespace NGIN

namespace std
{
    export template<NGIN::IsTimeUnit T>
    struct formatter<T> : std::formatter<NGIN::F64>
    {
        constexpr auto parse(format_parse_context& ctx)
        {
            // You can extend this to parse specific format specifiers if needed
            return ctx.begin();
        }

        template<typename FormatContext>
        auto format(const T& unit, FormatContext& ctx) const
        {
            // Use T::symbol for unit symbol. Ensure all time units have this member.
            return format_to(ctx.out(), "{:.2}{}", unit.GetValue(), T::symbol);
        }
    };
}// namespace std
