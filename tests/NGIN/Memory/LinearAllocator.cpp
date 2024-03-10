import std;
import NGIN.Memory;
import boost.ut;
using namespace boost::ut;

namespace
{
    // Helper function to create a buffer with a pattern
    void FillPattern(NGIN::Byte* buffer, NGIN::Size size)
    {
        for (NGIN::Size i = 0; i < size; ++i)
        {
            buffer[i] = static_cast<NGIN::Byte>(i % 256);
        }
    }

    // Helper function to check buffer pattern
    bool CheckPattern(const NGIN::Byte* buffer, NGIN::Size size)
    {
        for (NGIN::Size i = 0; i < size; ++i)
        {
            if (buffer[i] != static_cast<NGIN::Byte>(i % 256))
            {
                return false;
            }
        }
        return true;
    }
}// namespace

suite<"LinearAllocatorTests"> _ = [] {
    "ConstructorAndBasicAllocation"_test = [] {
        NGIN::Memory::LinearAllocator allocator(1024);
        void* ptr = allocator.Allocate(128, alignof(std::max_align_t));
        expect(ptr != nullptr);
    };

    "DeallocateUnsupported"_test = [] {
        NGIN::Memory::LinearAllocator allocator(1024);
        void* ptr = allocator.Allocate(128);
        expect(throws<std::runtime_error>([&allocator, ptr] { allocator.Deallocate(ptr); }));
    };

    "ResetAllocator"_test = [] {
        NGIN::Memory::LinearAllocator allocator(1024);
        void* firstAllocation = allocator.Allocate(128);
        allocator.Reset();
        void* secondAllocation = allocator.Allocate(128);
        expect(firstAllocation == secondAllocation);
    };

    "OwnsFunctionality"_test = [] {
        NGIN::Memory::LinearAllocator allocator(1024);
        void* ptr = allocator.Allocate(128);
        expect(allocator.Owns(ptr));
        NGIN::Byte outsideBuffer[128];
        expect(!allocator.Owns(outsideBuffer));
    };

    "AlignmentHandling"_test = [] {
        NGIN::Memory::LinearAllocator allocator(1024);
        void* ptr1 = allocator.Allocate(128, 64);
        expect(reinterpret_cast<NGIN::UIntPtr>(ptr1) % 64 == 0);
        void* ptr2 = allocator.Allocate(128, 32);
        expect(reinterpret_cast<NGIN::UIntPtr>(ptr2) % 32 == 0);
        void* ptr3 = allocator.Allocate(128, 48);
        expect(reinterpret_cast<NGIN::UIntPtr>(ptr3) % 48 == 0);
    };

    "OutOfMemory"_test = [] {
        NGIN::Memory::LinearAllocator allocator(128);
        void* ptr1 = allocator.Allocate(64, 64);
        void* ptr2 = allocator.Allocate(65, 64);// This should fail due to lack of memory.
        expect(ptr1 != nullptr);
        expect(ptr2 == nullptr);
    };

    "PatternCheckAfterReset"_test = [] {
        NGIN::Memory::LinearAllocator allocator(1024);
        NGIN::Byte* ptr = static_cast<NGIN::Byte*>(allocator.Allocate(512));
        FillPattern(ptr, 512);
        allocator.Reset();
        NGIN::Byte* ptr2 = static_cast<NGIN::Byte*>(allocator.Allocate(512));
        expect(CheckPattern(ptr2, 512));
    };
};
