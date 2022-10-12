#pragma once

#include <stack>
#include <cstdint>
#include <cstdlib>

#include <Physics/PhysicsBody.h>


namespace p2d
{
    constexpr std::size_t BODY_SIZE     { sizeof(PhysicsBody)  };
    constexpr uint8_t     BODY_ALIGN    { alignof(PhysicsBody) };

    class BodyAllocator
    {
    public:
        BodyAllocator(std::size_t _totalSize,
                      std::size_t _blockSize);

        void* Allocate(std::size_t _size);

        void Free(void* p);
    private:
        void* m_start;
        std::size_t m_totalSize;
        std::size_t m_used;
        std::size_t m_numAllocations;

    std::stack<void*> m_freeBlocks;
    std::size_t m_blockSize;
    };
}