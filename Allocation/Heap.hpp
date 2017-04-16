#ifndef WL_HEAP_HPP
#define WL_HEAP_HPP

#include <Windows.h>
#include <assert.h>
#include <inttypes.h>

namespace Alloc
{

    enum EReallocOptions
    {
        roInPlaceOnly = HEAP_REALLOC_IN_PLACE_ONLY,
        roZeroMem     = HEAP_ZERO_MEMORY
    };

    enum EAllocateOptions
    {
        aoNoSerialize = HEAP_NO_SERIALIZE,
        aoZeroMem     = HEAP_ZERO_MEMORY
    };

    enum EHeapCreateOptions
    {
        hcoExecute     = HEAP_CREATE_ENABLE_EXECUTE,
        hcoNoSerialize = HEAP_NO_SERIALIZE
    };

    class CHeap
    {
    private:
        HANDLE m_Heap = NULL;

    public:
        bool   Create(size_t InitSize, size_t MaxSize, DWORD Options);
        bool   Delete();

        void * Allocate(size_t Size, DWORD Options);
        void * ReAllocate(void* BlockPtr, size_t Size, DWORD Options);
        bool   Free(void* BlockPtr);
        
        bool   MemBlockOK(void * BlockPtr);
        size_t MemBlockSize(void * BlockPtr);
    };

    template<typename T>
    class CMemoryBlock
    {
    private:
        void  * m_MemBlock = NULL;
        CHeap * m_Heap     = NULL;

    public:
        CMemoryBlock(void * MemPtr, CHeap * Heap);
        operator void*();
        operator T*();

        bool ReAllocate(size_t Size, DWORD Options);
        bool Free();
        bool OK();
        size_t Size();
        
    };

    template<typename T>
    CMemoryBlock<T>::CMemoryBlock(void * MemPtr, CHeap * Heap)
    {
        assert(Heap);
        assert(MemPtr);
        m_Heap = Heap;
        m_MemBlock = MemPtr;
    }

    template<typename T>
    inline CMemoryBlock<T>::operator void*()
    {
        return m_MemBlock;
    }

    template<typename T>
    inline CMemoryBlock<T>::operator T*()
    {
        return (T*)m_MemBlock;
    }

    template<typename T>
    inline bool CMemoryBlock<T>::ReAllocate(size_t Size, DWORD Options)
    {
        return m_Heap->ReAllocate(m_MemBlock, Size, Options);
    }

    template<typename T>
    inline bool CMemoryBlock<T>::Free()
    {
        return m_Heap->Free(m_MemBlock);
    }

    template<typename T>
    inline bool CMemoryBlock<T>::OK()
    {
        return m_Heap->MemBlockOK(m_MemBlock);
    }

    template<typename T>
    inline size_t CMemoryBlock<T>::Size()
    {
        return m_Heap->MemBlockSize(m_MemBlock);
    }

}

#endif //!WL_HEAP_HPP