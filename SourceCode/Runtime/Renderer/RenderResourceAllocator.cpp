#include "RenderResourceAllocator.h"

static const uint64 RenderResourceHeapSize  = 64LL * 1024LL * 1024LL;
static const uint64 RenderResourceMaxHeaps  = 16;
static const uint32 RenderResourceMaxFrames = 4;

static FRenderResourceAllocator AllocatorGlobal;

FRenderResourceAllocator *
FRenderResourceAllocator::Get()
{
    return &AllocatorGlobal;
}

bool
FRenderResourceAllocator::CreateVertexBuffer(FVertexBufferAllocation **OutAllocation, uint64 Capacity)
{
    for (FVertexBufferHeap &VertexBufferHeap : VertexBufferHeaps)
    {
        FHeapAllocator *Allocator = VertexBufferHeap.Allocator;
        
        void *Memory = Allocator->Allocate(Capacity, 16);
        if (Memory)
        {
            void *RootMemory = Allocator->GetMemory();
            uint64 Offset = (uint8 *)Memory - (uint8 *)RootMemory;

            FVertexBufferAllocation *Allocation = new FVertexBufferAllocation();
            Allocation->Resource     = VertexBufferHeap.Resource;
            Allocation->Memory       = Memory;
            Allocation->Offset       = Offset;
            Allocation->Capacity     = Capacity;
            Allocation->FrameCounter = 0;
            VertexBufferAllocations.Add(Allocation);

            *OutAllocation = Allocation;
            return true;
        }
    }

    if (Capacity < RenderResourceHeapSize)
    { 
        FVertexBuffer *VertexBuffer = new FVertexBuffer(RenderResourceHeapSize);
        void *MappedMemory = VertexBuffer->Lock(0, RenderResourceHeapSize);
        FMemory::Zero(MappedMemory, RenderResourceHeapSize);
    
        FHeapAllocator *Allocator = new FHeapAllocator(MappedMemory, RenderResourceHeapSize);

        FVertexBufferHeap VertexBufferHeap;
        VertexBufferHeap.Resource  = VertexBuffer;
        VertexBufferHeap.Allocator = Allocator;
        VertexBufferHeaps.Add(VertexBufferHeap);

        void *Memory = Allocator->Allocate(Capacity, 16);
        if (Memory)
        {
            void *RootMemory = Allocator->GetMemory();
            uint64 Offset = (uint8 *)Memory - (uint8 *)RootMemory;

            FVertexBufferAllocation *Allocation = new FVertexBufferAllocation();
            Allocation->Resource     = VertexBufferHeap.Resource;
            Allocation->Memory       = Memory;
            Allocation->Offset       = Offset;
            Allocation->Capacity     = Capacity;
            Allocation->FrameCounter = 0;
            VertexBufferAllocations.Add(Allocation);

            *OutAllocation = Allocation;
            return true;
        }
    }

    return false;
}

bool
FRenderResourceAllocator::FreeVertexBuffer(FVertexBufferAllocation *InAllocation)
{
    for (FVertexBufferHeap &VertexBufferHeap : VertexBufferHeaps)
    {
        if (VertexBufferHeap.Resource == InAllocation->Resource)
        {
            FHeapAllocator *Allocator = VertexBufferHeap.Allocator;
            Allocator->DeAllocate(InAllocation->Memory);
            if (!Allocator->GetUsedMemory())
            {
                delete VertexBufferHeap.Resource;
                delete VertexBufferHeap.Allocator;
                VertexBufferHeaps.Remove(VertexBufferHeap);
            }

            return true;
        }
    }

    return false;
}

bool 
FRenderResourceAllocator::CreateIndexBuffer(FIndexBufferAllocation **OutAllocation, uint64 Capacity)
{
    for (FIndexBufferHeap &IndexBufferHeap : IndexBufferHeaps)
    {
        FHeapAllocator *Allocator = IndexBufferHeap.Allocator;

        void *Memory = Allocator->Allocate(Capacity, 4);
        if (Memory)
        {
            void *RootMemory = Allocator->GetMemory();
            uint64 Offset = (uint8 *)Memory - (uint8 *)RootMemory;

            FIndexBufferAllocation *Allocation = new FIndexBufferAllocation();
            Allocation->Resource     = IndexBufferHeap.Resource;
            Allocation->Memory       = Memory;
            Allocation->Offset       = Offset;
            Allocation->Capacity     = Capacity;
            Allocation->FrameCounter = 0;
            IndexBufferAllocations.Add(Allocation);

            *OutAllocation = Allocation;
            return true;
        }
    }

    if (Capacity < RenderResourceHeapSize)
    {
        FIndexBuffer *IndexBuffer = new FIndexBuffer(RenderResourceHeapSize);
        void *MappedMemory = IndexBuffer->Lock(0, RenderResourceHeapSize);
        FMemory::Zero(MappedMemory, RenderResourceHeapSize);

        FHeapAllocator *Allocator = new FHeapAllocator(MappedMemory, RenderResourceHeapSize);

        FIndexBufferHeap IndexBufferHeap;
        IndexBufferHeap.Resource  = IndexBuffer;
        IndexBufferHeap.Allocator = Allocator;
        IndexBufferHeaps.Add(IndexBufferHeap);

        void *Memory = Allocator->Allocate(Capacity, 4);
        if (Memory)
        {
            void *RootMemory = Allocator->GetMemory();
            uint64 Offset = (uint8 *)Memory - (uint8 *)RootMemory;

            FIndexBufferAllocation *Allocation = new FIndexBufferAllocation();
            Allocation->Resource     = IndexBufferHeap.Resource;
            Allocation->Memory       = Memory;
            Allocation->Offset       = Offset;
            Allocation->Capacity     = Capacity;
            Allocation->FrameCounter = 0;
            IndexBufferAllocations.Add(Allocation);

            *OutAllocation = Allocation;
            return true;
        }
    }

    return false;
}

bool
FRenderResourceAllocator::FreeIndexBuffer(FIndexBufferAllocation *InAllocation)
{
    for (FIndexBufferHeap &IndexBufferHeap : IndexBufferHeaps)
    {
        if (IndexBufferHeap.Resource == InAllocation->Resource)
        {
            FHeapAllocator *Allocator = IndexBufferHeap.Allocator;
            Allocator->DeAllocate(InAllocation->Memory);
            if (!Allocator->GetUsedMemory())
            {
                delete IndexBufferHeap.Resource;
                delete IndexBufferHeap.Allocator;
                IndexBufferHeaps.Remove(IndexBufferHeap);
            }

            return true;
        }
    }

    return false;
}

void 
FRenderResourceAllocator::TickPendingResources()
{
    {
        TArray<FVertexBufferAllocation *> PendingAllocations;
        for (FVertexBufferAllocation *Allocation : VertexBufferAllocations)
        {
            if (++Allocation->FrameCounter == RenderResourceMaxFrames)
            {
                FreeVertexBuffer(Allocation);
                PendingAllocations.Add(Allocation);
            }
        }
        for (FVertexBufferAllocation *Allocation : PendingAllocations)
        {
            VertexBufferAllocations.Remove(Allocation);
            delete Allocation;
        }
    }
    {
        TArray<FIndexBufferAllocation *> PendingAllocations;
        for (FIndexBufferAllocation *Allocation : IndexBufferAllocations)
        {
            if (++Allocation->FrameCounter == RenderResourceMaxFrames)
            {
                FreeIndexBuffer(Allocation);
                PendingAllocations.Add(Allocation);
            }
        }
        for (FIndexBufferAllocation *Allocation : PendingAllocations)
        {
            IndexBufferAllocations.Remove(Allocation);
            delete Allocation;
        }
    }
}

void
FRenderResourceAllocator::FreePendingResources()
{
    for (FVertexBufferHeap &Heap : VertexBufferHeaps)
    {
        delete Heap.Resource;
    }
    for (FIndexBufferHeap &Heap : IndexBufferHeaps)
    {
        delete Heap.Resource;
    }
    for (FVertexBufferAllocation *Allocation : VertexBufferAllocations)
    {
        delete Allocation;
    }
    for (FIndexBufferAllocation *Allocation : IndexBufferAllocations)
    {
        delete Allocation;
    }
}