#pragma once

namespace NGIN::Util
{
    template<typename T>
    class ISingleton
    {
    public:
        /// @brief  Gets the singleton instance of the class.
        /// @return  The singleton instance of the class.
        static T& GetInstance()
        {
            static T instance;
            return instance;
        }

        /// @brief Deleted copy constructor.
        ISingleton(const ISingleton&) = delete;
        /// @brief Deleted copy assignment operator.
        ISingleton& operator=(const ISingleton&) = delete;

    protected:
        /// @brief Protected constructor.
        ISingleton() = default;
        /// @brief Virtual destructor for proper cleanup if derived class has its own resources
        virtual ~ISingleton() = default;
    };
}// namespace NGIN::Util