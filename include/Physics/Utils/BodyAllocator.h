#pragma once

#include <cstdint>
#include <cstdlib>

#include "../PhysicsBody.h"

namespace p2d
{
    class BodyAllocator
    {
    public:
        explicit BodyAllocator(uint32_t _maxObjects);
        ~BodyAllocator();

        BodyAllocator(const BodyAllocator&) = delete;
        BodyAllocator& operator=(const BodyAllocator&) = delete;

        void* Allocate();
        //void Free();
        //void Clear();

        void* Start() const;
        uint32_t NumBodies() const;

    private:
        void* m_start;
        void* m_current;
        uint32_t m_size {0};
        uint32_t m_numBodies {0};
        uint32_t m_bytesUsed {0};
    };
}

