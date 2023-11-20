#pragma once
#include <NGIN/Common/Containers/Array.hpp>
#include <NGIN/Common/Types/Primitive.hpp>
#include <NGIN/System/Exceptions/Error.hpp>
#include <iterator>// For std::forward_iterator_tag

namespace NGIN::Containers
{
    template<typename T, Size N>
    class StaticRingBuffer
    {
    public:
        void Push(const T& value);

        void Push(T&& value);

        T Pop();

        [[nodiscard]] Bool IsEmpty() const { return !full && (head == tail); };

        [[nodiscard]] Bool IsFull() const { return full; };


    private:
        T buffer[N] = {};
        Size head = 0;
        Size tail = 0;
        Bool full = false;

    public:
        class Iterator
        {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            Iterator(StaticRingBuffer& buffer, Size pos, bool end = false)
                : buffer(buffer), pos(pos), isEnd(end) {}

            reference operator*() const { return buffer.buffer[pos]; }
            pointer operator->() { return &buffer.buffer[pos]; }

            // Prefix increment
            Iterator& operator++()
            {
                pos = (pos + 1) % N;
                // If we reached tail and buffer is full, we are at the end
                if (pos == buffer.tail && buffer.full)
                    isEnd = true;
                return *this;
            }

            // Equality check
            bool operator==(const Iterator& other) const
            {
                if (buffer.full && pos == other.pos)
                    return isEnd == other.isEnd;
                return pos == other.pos;
            }

            // Inequality check
            bool operator!=(const Iterator& other) const
            {
                // Can be simplified to return (*this != other), BUT DON'T DO IT! != is not defined yet...;
                return !(*this == other);
            }

        private:
            /// @brief Reference to the buffer
            StaticRingBuffer& buffer;
            Size pos;
            bool isEnd;// Needed to distinguish between end iterator in a full buffer
        };

        Iterator begin() { return Iterator(*this, tail); }
        Iterator end() { return Iterator(*this, head, true); }
    };

    // Implementation -------------------------------------------

    template<typename T, Size N>
    void StaticRingBuffer<T, N>::Push(const T& value)
    {
        buffer[head] = value;

        // if buffer is full, tail will be incremented because old data will be overwritten
        if (full)
        {
            tail = (tail + 1) % N;
            head = tail;
        } else// if buffer is not full, only head will be incremented
        {
            head = (head + 1) % N;
            full = (head == tail);
        }
    }

    template<typename T, Size N>
    void StaticRingBuffer<T, N>::Push(T&& value)
    {
        buffer[head] = std::move(value);

        // if buffer is full, tail will be incremented because old data will be overwritten
        if (full)
        {
            tail = (tail + 1) % N;
            head = tail;
        } else// if buffer is not full, only head will be incremented
        {
            head = (head + 1) % N;
            full = (head == tail);
        }
    }
    template<typename T, Size N>
    T StaticRingBuffer<T, N>::Pop()
    {
        if (IsEmpty()) [[unlikely]]
        {
#ifdef NGIN_ENABLE_EXCEPTIONS
            throw NGIN::System::Exceptions::Error("Pop called on empty StaticRingBuffer.");
#else
            /// TODO: Log error
            return T();
#endif
        }
        auto val = buffer[tail];

        full = false;
        tail = (tail + 1) % N;
        return val;
    }


}// namespace NGIN::Containers