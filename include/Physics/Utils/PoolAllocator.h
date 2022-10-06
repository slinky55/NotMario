#pragma once

#include "Allocator.h"
#include <cstdlib>
#include <stack>

namespace p2d
{
    /*class PoolAllocator : public Allocator {
    private:
        std::stack<void*> m_freeList;

        void * m_start_ptr = nullptr;
        std::size_t m_chunkSize;
    public:
        PoolAllocator(std::size_t totalSize,
                      std::size_t chunkSize);
        ~PoolAllocator() override;

        PoolAllocator(PoolAllocator &poolAllocator) = delete;

        void* Allocate(std::size_t size,
                       std::size_t alignment) override;

        void Free(void* ptr) override;

        void Init() override;

        virtual void Reset();
    };*/

    struct Chunk
    {
        Chunk *next;
    };

    class PoolAllocator {
    public:
        explicit PoolAllocator(size_t chunksPerBlock)
                : m_ChunksPerBlock(chunksPerBlock) {}

        void* allocate(size_t size);
        void deallocate(void* ptr, size_t size);

    private:
        size_t m_ChunksPerBlock;
        void* m_start {nullptr};
        Chunk* m_Alloc {nullptr};
        Chunk* allocateBlock(size_t size);
    };
}