export module NGIN.Time:Seconds;

export import NGIN.Types;
export import std;

import :Ratio;

export namespace NGIN::Time
{
	struct Seconds
	{
		using RatioT = Ratio<1,1>;

        Seconds(F64 seconds)
            : value(seconds) {}

		// Implicit conversion to std::chrono::seconds
        explicit operator std::chrono::seconds() const
        {
            return std::chrono::seconds(static_cast<Int64>(value));
        }

		template <typename T>
		explicit operator T() const
        {
            return T(value * T::RatioT::template value);
        }

		template <typename T>
	    Seconds operator+(const T& other) const
        {
            return Seconds(value + other.value * T::RatioT::template inverse);
        }

		F64 value = 0;
	};

	struct Minute
    {
        using RatioT = Ratio<60, 1>;

        Minute(F64 seconds)
            : value(seconds) {}

        // Implicit conversion to std::chrono::seconds
        explicit operator std::chrono::minutes() const
        {
            return std::chrono::minutes(static_cast<Int64>(value));
        }

        template<typename T>
        explicit operator T() const
        {
            return T(value * T::RatioT::template value);
        }

        template<typename T>
        Minute operator+(const T& other) const
        {
            return Minute(value + other.value * T::RatioT::template inverse * RatioT::inverse);
        }

        F64 value = 0;
    };
}
