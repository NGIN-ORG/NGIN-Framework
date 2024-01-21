#pragma once

#include <NGIN/Common/Defines.hpp>
#include <NGIN/Common/Types/Primitive.hpp>
#include <concepts>
#include <source_location>
#include <type_traits>

namespace NGIN::Memory
{
    /// @brief Interface for an allocator.
    /// @details An allocator is a class that allocates and deallocates memory.
    class IAllocator
    {
    public:
        /// @brief Virtual destructor.
        virtual ~IAllocator() = default;

        /// @brief Allocates a block of memory.
        /// @param size The size of the block to allocate.
        /// @return A pointer to the allocated block of memory.
        /// @details This method must be overridden by any class that inherits from IAllocator.
        /// @note The caller is responsible for calling Deallocate on the returned pointer.
        virtual Void* Allocate(Size size, Size alignment = alignof(std::max_align_t), const std::source_location& location = std::source_location::current()) = 0;

        /// @brief Deallocates a block of memory.
        /// @param ptr A pointer to the block of memory to deallocate.
        /// @details This method must be overridden by any class that inherits from IAllocator.
        virtual Void Deallocate(Void* ptr) = 0;

        /// @brief Checks if the allocator owns a block of memory.
        /// @param ptr A pointer to the block of memory to check.
        /// @return Boolean indicating if the allocator owns the block of memory.
        /// @details This method must be overridden by any class that inherits from IAllocator.
        virtual Bool Owns(void* ptr) const = 0;

        /// \brief Allocates memory and constructs an object of type T.
        ///
        /// This method reserves memory for an object of type T and constructs the object in-place.
        /// \tparam T The object type to allocate and construct.
        /// \tparam Args Types of the constructor arguments.
        /// \param location Source location for debugging (defaults to current location).
        /// \param args Arguments forwarded to T's constructor.
        /// \return Pointer to the constructed object or nullptr if allocation fails.
        template<typename T, typename... Args>
        T* New(const std::source_location& location, Args&&... args)
        {
            void* memory = this->Allocate(sizeof(T), alignof(T), location);
            ///TODO: ERROR HANDLING
            NGIN_ASSERT(memory != nullptr, "Failed to allocate memory for object of type");
            return new (memory) T(std::forward<Args>(args)...);
        }

        /// \brief Calls the destructor for the object and deallocates its memory.
        ///
        /// Calls the destructor of the object of type T and deallocates its memory using the allocator.
        /// \tparam T The type of the object to destroy and deallocate.
        /// \param obj Pointer to the object.
        template<typename T>
        Void Delete(T* obj)
        {
            if (!obj) [[unlikely]]
                return;
            obj->~T();
            Deallocate(obj);
        }
    };

    template<typename T>
    concept IsAllocator = std::is_base_of_v<IAllocator, T>;
}// namespace NGIN::Memory