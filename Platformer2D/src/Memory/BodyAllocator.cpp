#include <Physics/Memory/BodyAllocator.h>

namespace p2d
{
    BodyAllocator::BodyAllocator(std::size_t _totalSize,
                                 std::size_t _blockSize)
                                 :
                                 m_totalSize(_totalSize),
                                 m_blockSize(_blockSize)
    {
        m_start = aligned_alloc(BODY_ALIGN, _totalSize);

        std::size_t chunks = m_totalSize / m_blockSize;
        for (std::size_t i = 0; i < chunks; i++)
        {
            std::size_t address = reinterpret_cast<std::size_t>(m_start) + (i * m_blockSize);
            m_freeBlocks.push(reinterpret_cast<void*>(address));
        }
    }

    void* BodyAllocator::Allocate(std::size_t _size)
    {

        void* address = m_freeBlocks.top();
        m_freeBlocks.pop();
        m_used += m_blockSize;
        return address;
    }

    void BodyAllocator::Free(void* p)
    {
        m_freeBlocks.push(p);
        m_used -= m_blockSize;
    }
}
