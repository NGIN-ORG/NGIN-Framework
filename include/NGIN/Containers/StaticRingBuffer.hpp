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

        Bool IsEmpty() const { return !full && (head == tail); };

        Bool IsFull() const { return full; };


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
                : buffer_(buffer), pos_(pos), isEnd_(end) {}

            reference operator*() const { return buffer_.buffer[pos_]; }
            pointer operator->() { return &buffer_.buffer[pos_]; }

            // Prefix increment
            Iterator& operator++()
            {
                pos_ = (pos_ + 1) % N;
                if (pos_ == buffer_.tail && buffer_.full)
                {
                    isEnd_ = true;
                }
                return *this;
            }

            // Equality check
            bool operator==(const Iterator& other) const
            {
                if (buffer_.full && pos_ == other.pos_)
                {
                    return isEnd_ == other.isEnd_;
                }
                return pos_ == other.pos_;
            }

            // Inequality check
            bool operator!=(const Iterator& other) const
            {
                return !(*this == other);
            }

        private:
            StaticRingBuffer& buffer_;
            Size pos_;
            bool isEnd_;// Needed to distinguish end iterator in full buffer
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
#ifdef NGIN_ENABLE_EXCEPTIONS¨
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