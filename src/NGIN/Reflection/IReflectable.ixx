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

module :private;

static void NGIN_AUTO_REGISTRATION_FUNCTION();

namespace
{
    struct NGIN_AUTO_REGISTRATION_STRUCT
    {
        NGIN_AUTO_REGISTRATION_STRUCT()
        {
            NGIN_AUTO_REGISTRATION_FUNCTION();
        }
    };
    static NGIN_AUTO_REGISTRATION_STRUCT
            NGIN_AUTO_REGISTRATION_STRUCT_INSTANCE = {};
}
    static void NGIN_AUTO_REGISTRATION_FUNCTION()
    {
        std::cout << "NGIN_AUTO_REGISTRATION_FUNCTION" << std::endl;
    }




///TODO:
///IDEA 