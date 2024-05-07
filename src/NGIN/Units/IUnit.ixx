export module NGIN.Units:IUnit;

export import std;

export namespace NGIN
{
    struct IUnit
    {
        virtual ~IUnit() = default;
    };

    template <typename T>
    concept IsUnit = std::is_base_of_v<IUnit, T>;
}