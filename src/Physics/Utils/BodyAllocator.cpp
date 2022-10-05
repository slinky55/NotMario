#include <Physics/Utils/BodyAllocator.h>

namespace p2d
{
    BodyAllocator::BodyAllocator(uint32_t _maxObjects)
    {
        m_size = _maxObjects * (sizeof(PhysicsBody));

        m_start = aligned_alloc(alignof(PhysicsBody), m_size);
        m_current = m_start;
    }

    BodyAllocator::~BodyAllocator()
    {
        free(m_start);
    }

    void* BodyAllocator::Allocate()
    {
        void* address = m_current;
        m_current = reinterpret_cast<uint8_t*>(m_current) + sizeof(PhysicsBody);
        return address;
    }
}