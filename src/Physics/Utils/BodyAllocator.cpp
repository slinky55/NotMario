#include <Physics/Utils/BodyAllocator.h>

namespace p2d
{
    BodyAllocator::BodyAllocator(uint32_t _maxObjects)
    {
        m_size = _maxObjects * (sizeof(PhysicsBody));

        m_start = malloc(m_size);
        m_current = m_start;
    }

    BodyAllocator::~BodyAllocator()
    {
        free(m_start);
    }

    void* BodyAllocator::Allocate()
    {
        void* address = reinterpret_cast<uint8_t*>(m_current);
        m_current = reinterpret_cast<uint8_t*>(m_current) + sizeof(PhysicsBody);
        m_numBodies++;
        return address;
    }

    void* BodyAllocator::Start() const
    {
        return m_start;
    }

    uint32_t BodyAllocator::NumBodies() const
    {
        return m_numBodies;
    }
}