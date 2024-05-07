#pragma once

#include <NGIN/Common/Defines.hpp>
#include <NGIN/Types/Primitives.hpp>
#include <cstddef>
#include <utility>

namespace NGIN::Memory
{
    /// @brief Interface for memory allocators
    class IAllocator
    {
    public:
        virtual ~IAllocator() = default;
        virtual void* Allocate(Size size, Size alignment) = 0;
        virtual void Deallocate(void* ptr) = 0;
        virtual void Reset() = 0;
        virtual bool Owns(const void* ptr) = 0;

        template <typename T, typename... Args>
        T* New(Args&&... args)
        {
            void* memory = Allocate(sizeof(T), alignof(T));
            return new(memory) T(std::forward<Args>(args)...);
        }

        template <typename T>
        void Delete(T* ptr)
        {
            ptr->~T();
            Deallocate(ptr);
        }
    };
} // namespace NGIN::Memory
