#pragma once

#include <cstddef> // size_t
#include <cstdint>

#include <Physics/PhysicsBody.h>

namespace p2d
{
    constexpr std::size_t BODY_SIZE     { sizeof(PhysicsBody)  };
    constexpr uint8_t     BODY_ALIGN    { alignof(PhysicsBody) };

    class Allocator {
    public:
        explicit Allocator(const std::size_t totalSize) : m_totalSize { totalSize }, m_used { 0 }, m_peak { 0 } { }

        virtual ~Allocator() { m_totalSize = 0; }

        virtual void* Allocate(std::size_t size,
                               std::size_t alignment) = 0;

        virtual void Free(void* ptr) = 0;

        virtual void Init() = 0;

        friend class Benchmark;
    protected:
        std::size_t m_totalSize;
        std::size_t m_used;
        std::size_t m_peak;
    };
}


