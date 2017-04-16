#include "Heap.hpp"

namespace Alloc
{
    bool CHeap::Create(size_t InitSize, size_t MaxSize, DWORD Options)
    {
        m_Heap = ::HeapCreate(Options, InitSize, MaxSize);
        return m_Heap != NULL;
    }

    bool CHeap::Delete()
    {
        return true && ::HeapDestroy(m_Heap);
    }

    void * CHeap::Allocate(size_t Size, DWORD Options)
    {
        return ::HeapAlloc(m_Heap, Options, Size);
    }

    void * CHeap::ReAllocate(void * BlockPtr, size_t Size, DWORD Options)
    {
        return ::HeapReAlloc(m_Heap, Options, BlockPtr, Size);
    }

    bool CHeap::Free(void * BlockPtr)
    {
        return true && ::HeapFree(m_Heap, 0, BlockPtr);
    }

    bool CHeap::MemBlockOK(void * BlockPtr)
    {
        return true && ::HeapValidate(m_Heap, 0, BlockPtr);
    }

    size_t CHeap::MemBlockSize(void * BlockPtr)
    {
        return ::HeapSize(m_Heap, 0, BlockPtr);
    }

}
