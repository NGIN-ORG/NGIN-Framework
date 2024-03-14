export module NGIN.Memory:IAllocator;

export import NGIN.Types;

namespace NGIN::Memory
{
    /// @brief Interface for memory allocators
    export class IAllocator
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
            return new (memory) T(std::forward<Args>(args)...);
        }

        template <typename T>
        void Delete (T* ptr)
        {
            ptr->~T();
            Deallocate(ptr);
        }
    };
}// namespace NGIN::Memory