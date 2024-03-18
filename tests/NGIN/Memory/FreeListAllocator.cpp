import std;
import NGIN.Memory;
import boost.ut;
using namespace boost::ut;
using namespace NGIN::Memory;

suite<"FreeListAllocatorTests"> _ = [] {
    "BasicAllocation"_test = [] {
        FreeListAllocator allocator(1024);
        auto* ptr = allocator.Allocate(512);
        expect(ptr != nullptr);
    };

    "MultipleAllocations"_test = [] {
        FreeListAllocator allocator(1024);
        auto* block1 = allocator.Allocate(128);
        auto* block2 = allocator.Allocate(128);
        expect(block1 != nullptr);
        expect(block2 != nullptr);
        expect(reinterpret_cast<std::uintptr_t>(block1) != reinterpret_cast<std::uintptr_t>(block2)) << "Blocks should not overlap";
    };

    "OverAllocation"_test = [] {
        FreeListAllocator allocator(512);
        auto* block1 = allocator.Allocate(256);
        auto* block2 = allocator.Allocate(256);
        auto* block3 = allocator.Allocate(256);// This allocation should fail due to insufficient memory
        expect(block1 != nullptr);
        expect(block2 != nullptr);
        expect(block3 == nullptr);
    };

    "Alignment"_test = [] {
        FreeListAllocator allocator(1024);
        auto* block = allocator.Allocate(1, 256);// Requesting 256-byte alignment
        expect(reinterpret_cast<std::uintptr_t>(block) % 256 == 0_i) << "Block is not properly aligned";
    };

    "DeallocateAndReallocate"_test = [] {
        FreeListAllocator allocator(1024);
        auto* block1 = allocator.Allocate(512);
        allocator.Deallocate(block1);
        auto* block2 = allocator.Allocate(512);// Should be able to reallocate the same size block
        expect(block2 != nullptr);
    };

    "ResetFunctionality"_test = [] {
        FreeListAllocator allocator(768);
        auto* block1 = allocator.Allocate(512);
        allocator.Reset();                     // Reset should free all allocations
        auto* block2 = allocator.Allocate(512);// Should be able to allocate again after reset
        expect(block2 != nullptr);
    };

    "OwnsFunctionality"_test = [] {
        FreeListAllocator allocator(1024);
        auto* block = allocator.Allocate(512);
        expect(allocator.Owns(block)) << "Allocator should own the block";
        NGIN::Byte outsideBuffer[512];
        expect(!allocator.Owns(outsideBuffer)) << "Allocator should not own an external buffer";
    };
};