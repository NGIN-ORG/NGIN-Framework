import std;
import NGIN.Memory;
import boost.ut;
using namespace boost::ut;
using namespace NGIN::Memory;

suite<"LinearAllocatorTests"> _ = [] {
    "BasicAllocation"_test = [] {
        LinearAllocator allocator(1024);
        auto* ptr = allocator.Allocate(128, alignof(std::max_align_t));
        expect(ptr != nullptr);
    };

    "UnsupportedDeallocate"_test = [] {
        LinearAllocator allocator(1024);
        auto* ptr = allocator.Allocate(128);
        expect(throws<std::runtime_error>([&allocator, ptr] { allocator.Deallocate(ptr); }));
    };

    "ResetFunctionality"_test = [] {
        LinearAllocator allocator(1024);
        auto* firstAllocation = allocator.Allocate(128);
        allocator.Reset();
        auto* secondAllocation = allocator.Allocate(128);
        expect(firstAllocation == secondAllocation);
    };

    "OwnsFunctionality"_test = [] {
        LinearAllocator allocator(1024);
        auto* block = allocator.Allocate(128);
        expect(allocator.Owns(block)) << "Allocator should own the block";
        NGIN::Byte outsideBuffer[128];
        expect(!allocator.Owns(outsideBuffer)) << "Allocator should not own an external buffer";
    };

    "AlignmentHandling"_test = [] {
        LinearAllocator allocator(1024);
        auto* ptr1 = allocator.Allocate(128, 64);
        expect(reinterpret_cast<NGIN::UIntPtr>(ptr1) % 64 == 0_i) << "Block is not properly aligned";
        auto* ptr2 = allocator.Allocate(128, 32);
        expect(reinterpret_cast<NGIN::UIntPtr>(ptr2) % 32 == 0_i) << "Block is not properly aligned";
    };

    "OutOfMemory"_test = [] {
        LinearAllocator allocator(128);
        auto* ptr1 = allocator.Allocate(64, 8);
        auto* ptr2 = allocator.Allocate(65, 8);// This should fail due to lack of memory.
        expect(ptr1 != nullptr);
        expect(ptr2 == nullptr);
    };

    "ExactFitAllocation"_test = [] {
        LinearAllocator allocator(512);
        auto* ptr = allocator.Allocate(512);
        expect(ptr != nullptr);
        // Further allocations should fail.
        expect(allocator.Allocate(1) == nullptr);
    };

    "PatternCheckAfterReset"_test = [] {
        LinearAllocator allocator(1024);
        auto* ptr = static_cast<NGIN::Byte*>(allocator.Allocate(512));

        // Fill pattern
        for (NGIN::Size i = 0; i < 512; ++i)
        {
            ptr[i] = static_cast<NGIN::Byte>(i % 256);
        }

        allocator.Reset();
        auto* ptr2 = static_cast<NGIN::Byte*>(allocator.Allocate(512));

        // Check pattern
        bool patternValid = true;
        for (NGIN::Size i = 0; i < 512; ++i)
        {
            if (ptr2[i] != static_cast<NGIN::Byte>(i % 256))
            {
                patternValid = false;
                break;
            }
        }
        expect(patternValid);
    };

    "LargeAlignmentRequests"_test = [] {
        LinearAllocator allocator(2048);
        auto* ptr = allocator.Allocate(128, 1024);// Requesting 1KB alignment.
        expect(reinterpret_cast<NGIN::UIntPtr>(ptr) % 1024 == 0_i) << "Block is not properly aligned";
    };
};
