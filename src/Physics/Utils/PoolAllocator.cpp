
#include <Physics/Utils/PoolAllocator.h>

namespace p2d
{
/*    PoolAllocator::PoolAllocator(std::size_t totalSize,
                                 std::size_t chunkSize)
            :
            Allocator(totalSize)
    {
        assert(chunkSize >= 8 && "Chunk size must be greater or equal to 8");
        assert(totalSize % chunkSize == 0 && "Total Size must be a multiple of Chunk Size");
        m_chunkSize = chunkSize;
    }

    void PoolAllocator::Init() {
        m_start_ptr = malloc(m_totalSize);
        Reset();
    }

    PoolAllocator::~PoolAllocator() {
        free(m_start_ptr);
    }

    void *PoolAllocator::Allocate(std::size_t allocationSize,
                                  std::size_t alignment)
    {
        assert(allocationSize == this->m_chunkSize && "Allocation size must be equal to chunk size");

        void* freePosition = m_freeList.top();
        m_freeList.pop();

        assert(freePosition != nullptr && "The pool allocator is full");

        m_used += m_chunkSize;

        return freePosition;
    }

    void PoolAllocator::Free(void* ptr)
    {
        m_used -= m_chunkSize;

        m_freeList.push(ptr);
    }

    void PoolAllocator::Reset() {
        m_used = 0;
        m_peak = 0;

        const std::size_t nChunks = m_totalSize / m_chunkSize;
        for (int i = 0; i < nChunks; ++i)
        {
            std::size_t address = reinterpret_cast<std::size_t>(m_start_ptr) + i * m_chunkSize;
            m_freeList.push(reinterpret_cast<void*>(address));
        }
    }*/

    void *PoolAllocator::allocate(size_t size) {

        // No chunks left in the current block, or no any block
        // exists yet. Allocate a new one, passing the chunk size:

        if (m_Alloc == nullptr) {
            m_Alloc = allocateBlock(size);
        }

        // The return value is the current position of
        // the allocation pointer:

        Chunk *freeChunk = m_Alloc;

        // Advance (bump) the allocation pointer to the next chunk.
        //
        // When no chunks left, the `mAlloc` will be set to `nullptr`, and
        // this will cause allocation of a new block on the next request:

        m_Alloc = m_Alloc->next;

        return freeChunk;
    }

    Chunk *PoolAllocator::allocateBlock(size_t chunkSize) {
        // The first chunk of the new block.
        auto* blockBegin = reinterpret_cast<Chunk *>(malloc(m_ChunksPerBlock * chunkSize));

        // Once the block is allocated, we need to chain all
        // the chunks in this block:

        Chunk *chunk = blockBegin;

        for (int i = 0; i < m_ChunksPerBlock - 1; ++i) {
            chunk->next =
                    reinterpret_cast<Chunk *>(reinterpret_cast<char *>(chunk) + chunkSize);
            chunk = chunk->next;
        }

        chunk->next = nullptr;

        return blockBegin;
    }

    void PoolAllocator::deallocate(void *chunk, size_t size) {

        // The freed chunk's next pointer points to the
        // current allocation pointer:

        reinterpret_cast<Chunk *>(chunk)->next = m_Alloc;

        // And the allocation pointer is now set
        // to the returned (free) chunk:

        m_Alloc = reinterpret_cast<Chunk *>(chunk);
    }
}
