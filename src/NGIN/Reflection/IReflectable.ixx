module;
#include <iostream>

export module NGIN.Reflection:IReflectable;

export namespace NGIN::Reflection
{
    class IReflectable
    {
    public:
        virtual ~IReflectable() = default;
        ///TODO:
        ///static void Reflect(ClassRegistrar& registrar)
        ///{
        ///}
    };
}



