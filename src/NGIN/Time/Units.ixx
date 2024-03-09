export module NGIN.Time:Units;

export import NGIN.Types;
export import std;

import :Ratio;

export namespace NGIN::Time
{
    //TODO: Declare this in a separate file and create a seperate ITimeUnit interface, in order to be able to support IsTimeUnit concept
    struct IUnit
    {
        virtual ~IUnit() = default;
        using RatioT = Ratio<1, 1>;
        static constexpr StringView symbol  = ""; 
    };

    //A concept to check if a type is a unit, i.e. it inherits from IUnit and has a value member
    template <typename T>
    concept IsUnit = std::is_base_of_v<IUnit, T> && requires(T t) { t.value; };



    struct Nanoseconds : IUnit
    {
        using RatioT = Ratio<1, 1000000000>;
        static constexpr StringView symbol = "ns";

        constexpr Nanoseconds(const F64 seconds)
            : value(seconds) {}

        // Constexpr conversion to std::chrono::nanoseconds
        constexpr explicit operator std::chrono::nanoseconds() const
        {
            return std::chrono::nanoseconds(static_cast<Int64>(value));
        }

        // Constexpr conversion to other time units
        template<typename T>
        constexpr explicit operator T() const
        {
            return T(value * RatioT::value / T::RatioT::value);
        }

        // Constexpr arithmetic operations
        template<typename T>
        constexpr Nanoseconds operator+(const T& other) const
        {
            return Nanoseconds(value + static_cast<Nanoseconds>(other).value);
        }

        template<typename T>
        constexpr Nanoseconds operator-(const T& other) const
        {
            return Nanoseconds(value - static_cast<Nanoseconds>(other).value);
        }

        template<typename T>
        constexpr Nanoseconds operator*(const T& other) const
        {
            return Nanoseconds(value * static_cast<Nanoseconds>(other).value);
        }

        template<typename T>
        constexpr Nanoseconds operator/(const T& other) const
        {
            return Nanoseconds(value / static_cast<Nanoseconds>(other).value);
        }

        F64 value = 0;
    };

    struct Microseconds
    {
        using RatioT = Ratio<1, 1000000>;// 1 second = 1 second
        static constexpr StringView symbol = "us";

        constexpr Microseconds(const F64 seconds)
            : value(seconds) {}

        // Constexpr conversion to std::chrono::microseconds
        constexpr explicit operator std::chrono::microseconds() const
        {
            return std::chrono::microseconds(static_cast<Int64>(value));
        }

        // Constexpr conversion to other time units
        template<typename T>
        constexpr explicit operator T() const
        {
            return T(value * RatioT::value / T::RatioT::value);
        }

        // Constexpr arithmetic operations
        template<typename T>
        constexpr Microseconds operator+(const T& other) const
        {
            return Microseconds(value + static_cast<Microseconds>(other).value);
        }

        template<typename T>
        constexpr Microseconds operator-(const T& other) const
        {
            return Microseconds(value - static_cast<Microseconds>(other).value);
        }

        template<typename T>
        constexpr Microseconds operator*(const T& other) const
        {
            return Microseconds(value * static_cast<Microseconds>(other).value);
        }

        template<typename T>
        constexpr Microseconds operator/(const T& other) const
        {
            return Microseconds(value / static_cast<Microseconds>(other).value);
        }

        F64 value = 0;
    };

    struct Milliseconds
    {
        using RatioT = Ratio<1, 1000>;// 1 second = 1 second
        static constexpr StringView symbol = "ms";
        constexpr Milliseconds(const F64 seconds)
            : value(seconds) {}

        // Constexpr conversion to std::chrono::milliseconds
        constexpr explicit operator std::chrono::milliseconds() const
        {
            return std::chrono::milliseconds(static_cast<Int64>(value));
        }

        // Constexpr conversion to other time units
        template<typename T>
        constexpr explicit operator T() const
        {
            return T(value * RatioT::value / T::RatioT::value);
        }

        // Constexpr arithmetic operations
        template<typename T>
        constexpr Milliseconds operator+(const T& other) const
        {
            return Milliseconds(value + static_cast<Milliseconds>(other).value);
        }

        template<typename T>
        constexpr Milliseconds operator-(const T& other) const
        {
            return Milliseconds(value - static_cast<Milliseconds>(other).value);
        }

        template<typename T>
        constexpr Milliseconds operator*(const T& other) const
        {
            return Milliseconds(value * static_cast<Milliseconds>(other).value);
        }

        template<typename T>
        constexpr Milliseconds operator/(const T& other) const
        {
            return Milliseconds(value / static_cast<Milliseconds>(other).value);
        }

        F64 value = 0;
    };

    struct Seconds
    {
        using RatioT = Ratio<1, 1>;// 1 second = 1 second
        static constexpr StringView symbol = "s";
        constexpr Seconds(const F64 seconds)
            : value(seconds) {}

        // Constexpr conversion to std::chrono::seconds
        constexpr explicit operator std::chrono::seconds() const
        {
            return std::chrono::seconds(static_cast<Int64>(value));
        }

        // Constexpr conversion to other time units
        template<typename T>
        constexpr explicit operator T() const
        {
            return T(value * RatioT::value / T::RatioT::value);
        }

        // Constexpr arithmetic operations
        template<typename T>
        constexpr Seconds operator+(const T& other) const
        {
            return Seconds(value + static_cast<Seconds>(other).value);
        }

        template<typename T>
        constexpr Seconds operator-(const T& other) const
        {
            return Seconds(value - static_cast<Seconds>(other).value);
        }

        template<typename T>
        constexpr Seconds operator*(const T& other) const
        {
            return Seconds(value * static_cast<Seconds>(other).value);
        }

        template<typename T>
        constexpr Seconds operator/(const T& other) const
        {
            return Seconds(value / static_cast<Seconds>(other).value);
        }

        friend std::ostream& operator<<(std::ostream& stream, const Seconds& value)
        {
            stream << value.value << "s";
            return stream;
        }

        F64 value = 0;
    };


    struct Minutes
    {
        using RatioT = Ratio<60, 1>;// 1 minute = 60 seconds
        static constexpr StringView symbol = "m";
        constexpr Minutes(const F64 minutes)
            : value(minutes) {}

        // Constexpr conversion to std::chrono::minutes
        constexpr explicit operator std::chrono::minutes() const
        {
            return std::chrono::minutes(static_cast<Int64>(value));
        }

        // Constexpr conversion to other time units
        template<typename T>
        constexpr explicit operator T() const
        {
            return T(value * RatioT::value / T::RatioT::value);
        }

        // Constexpr arithmetic operations
        template<typename T>
        constexpr Minutes operator+(const T& other) const
        {
            return Minutes(value + static_cast<Minutes>(other).value);
        }

        template<typename T>
        constexpr Minutes operator-(const T& other) const
        {
            return Minutes(value - static_cast<Minutes>(other).value);
        }

        template<typename T>
        constexpr Minutes operator*(const T& other) const
        {
            return Minutes(value * static_cast<Minutes>(other).value);
        }

        template<typename T>
        constexpr Minutes operator/(const T& other) const
        {
            return Minutes(value / static_cast<Minutes>(other).value);
        }

        F64 value = 0;
    };

    struct Hours
    {
        using RatioT = Ratio<3600, 1>;// 1 hour = 3600 seconds
        static constexpr StringView symbol = "h";
        constexpr Hours(const F64 hours)
            : value(hours) {}

        // Constexpr conversion to std::chrono::hours
        constexpr explicit operator std::chrono::hours() const
        {
            return std::chrono::hours(static_cast<Int64>(value));
        }

        // Constexpr conversion to other time units
        template<typename T>
        constexpr explicit operator T() const
        {
            return T(value * RatioT::value / T::RatioT::value);
        }

        // Constexpr arithmetic operations
        template<typename T>
        constexpr Hours operator+(const T& other) const
        {
            return Hours(value + static_cast<Hours>(other).value);
        }

        template<typename T>
        constexpr Hours operator-(const T& other) const
        {
            return Hours(value - static_cast<Hours>(other).value);
        }

        template<typename T>
        constexpr Hours operator*(const T& other) const
        {
            return Hours(value * static_cast<Hours>(other).value);
        }

        template<typename T>
        constexpr Hours operator/(const T& other) const
        {
            return Hours(value / static_cast<Hours>(other).value);
        }

        F64 value = 0;
    };
}// namespace NGIN::Time

export template<NGIN::Time::IsUnit T>
struct std::formatter<T>
{
    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    auto format(T& id, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{}{}", id.value, T::symbol);
    }
};

export template<>
struct std::formatter<NGIN::Time::Minutes>
{

    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    auto format(const NGIN::Time::Minutes& id, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{}m", id.value);
    }
};

export template<>
struct std::formatter<NGIN::Time::Hours>
{

    constexpr auto parse(std::format_parse_context& ctx)
    {
        return ctx.begin();
    }

    auto format(const NGIN::Time::Hours& id, std::format_context& ctx) const
    {
        return std::format_to(ctx.out(), "{:.2}h", id.value);
    }
};