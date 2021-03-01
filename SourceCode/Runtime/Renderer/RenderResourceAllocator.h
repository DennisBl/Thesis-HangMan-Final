#ifndef RENDER_RESOURCE_ALLOCATOR_H
#define RENDER_RESOURCE_ALLOCATOR_H

#include <OpenGL.h>

template <class TResourceType>
struct TRenderResourceHeap
{
    TResourceType *Resource;
    FHeapAllocator *Allocator;

    FORCEINLINE bool operator==(const TRenderResourceHeap &Other) const
    {
        return Resource == Other.Resource &&
               Allocator == Other.Allocator;
    }
};

typedef TRenderResourceHeap<FVertexBuffer> FVertexBufferHeap;
typedef TRenderResourceHeap<FIndexBuffer> FIndexBufferHeap;

template <class TResourceType>
struct TRenderResourceAllocation
{
    TResourceType *Resource;
    void *Memory;
    uint64 Offset;
    uint64 Capacity;
    uint32 FrameCounter;
};

typedef TRenderResourceAllocation<FVertexBuffer> FVertexBufferAllocation;
typedef TRenderResourceAllocation<FIndexBuffer> FIndexBufferAllocation;

class FRenderResourceAllocator
{
public:
    static FRenderResourceAllocator *Get();

    bool CreateVertexBuffer(FVertexBufferAllocation **OutAllocation, uint64 Capacity);
    bool FreeVertexBuffer(FVertexBufferAllocation *InAllocation);

    bool CreateIndexBuffer(FIndexBufferAllocation **OutAllocation, uint64 Capacity);
    bool FreeIndexBuffer(FIndexBufferAllocation *InAllocation);

    void TickPendingResources();
    void FreePendingResources();

private:
    TArray<FVertexBufferHeap> VertexBufferHeaps;
    TArray<FIndexBufferHeap> IndexBufferHeaps;

    TArray<FVertexBufferAllocation *> VertexBufferAllocations;
    TArray<FIndexBufferAllocation *> IndexBufferAllocations;
};

#endif