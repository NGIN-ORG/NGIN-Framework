import NGIN.Logging;
import NGIN.Reflection;
import NGIN.Meta;
import NGIN.Util;
import NGIN.Units;
import NGIN.Memory;
import std;

using namespace std::chrono;
using namespace NGIN::Memory;

constexpr int NUM_ALLOCATIONS = 1000000;
constexpr NGIN::Size BLOCK_SIZE = 4;
constexpr NGIN::Size ALIGNMENT = 4;

void BenchmarkFreeListAllocator()
{
    FreeListAllocator allocator(1024 * 1024);// 1MB for simplicity

    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ALLOCATIONS; ++i)
    {
        void* ptr = allocator.Allocate(BLOCK_SIZE, ALIGNMENT);
        allocator.Deallocate(ptr);
    }
    auto end = high_resolution_clock::now();

    duration<double, std::milli> duration = end - start;
    std::cout << "FreeListAllocator: " << duration.count() << "ms\n";
}

void BenchmarkLinearAllocator()
{
    LinearAllocator allocator(1024 * 1024);// 1MB for simplicity

    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ALLOCATIONS; ++i)
    {
        void* ptr = allocator.Allocate(BLOCK_SIZE, ALIGNMENT);
        allocator.Reset();// Simulate deallocation
    }
    auto end = high_resolution_clock::now();

    duration<double, std::milli> duration = end - start;
    std::cout << "LinearAllocator: " << duration.count() << "ms\n";
}

void BenchmarkOperatorNew()
{
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ALLOCATIONS; ++i)
    {
        void* ptr = ::operator new(BLOCK_SIZE);
        ::operator delete(ptr);
    }
    auto end = high_resolution_clock::now();

    duration<double, std::milli> duration = end - start;
    std::cout << "Operator new: " << duration.count() << "ms\n";
}

int main()
{
    BenchmarkFreeListAllocator();
    BenchmarkLinearAllocator();
    BenchmarkOperatorNew();

    return 0;
}
