#include "TileRenderer.h"
#include "RenderResourceAllocator.h"

FTileRenderer::FTileRenderer()
	: VertexShader(0)
	, PixelShader(0)
	, PipelineState(0)
{
    FString VertexShaderSourceCode =
        "#version 450\n"
        "layout(location = 0) in vec2 InPosition;\n"
        "layout(location = 1) in vec4 InColor;\n"
        "layout(location = 0) out vec4 OutColor;\n"
        "uniform mat4 OrthographicMatrix;\n"
        "void main()\n"
        "{\n"
        "OutColor = InColor;\n"
        "gl_Position = OrthographicMatrix * vec4(InPosition.x, InPosition.y, 0.0, 1.0);\n"
        "}";
    VertexShader = new FVertexShader(VertexShaderSourceCode);

    FString PixelShaderSourceCode =
        "#version 450\n"
        "layout(location = 0) in vec4 InColor;\n"
        "layout(location = 0) out vec4 OutColor;\n"
        "void main()\n"
        "{\n"
        "OutColor = InColor;\n"
        "}";
    PixelShader = new FPixelShader(PixelShaderSourceCode);

	FPipelineStateInitializer Initializer;
	Initializer.VertexShader = VertexShader;
	Initializer.PixelShader  = PixelShader;
	PipelineState = new FPipelineState(Initializer);
}

FTileRenderer::~FTileRenderer()
{
    delete PipelineState;
    delete VertexShader;
    delete PixelShader;
}

void 
FTileRenderer::AddItem(const FCanvasTileItem &Item)
{
	TileItems.Add(Item);
}

void
FTileRenderer::RemoveItem(const FCanvasTileItem &Item)
{
	TileItems.Remove(Item);
}

FORCEINLINE const FMatrix
GetOrthographic(float X, float Y, float Width, float Height)
{
    FMatrix Result(1.0f);
    Result[0][0] = 2.0f / Width;
    Result[1][1] = 2.0f / Height;
    Result[2][2] = -1.0f;
    Result[3][0] = -1.0f;
    Result[3][1] = -1.0f;

    return Result;
}

void
FTileRenderer::Render()
{
    TArray<FCanvasTileRenderData> Vertices;
    for (const FCanvasTileItem &TileItem : TileItems)
    {
        FCanvasTileRenderData Vertex00;
        Vertex00.Position = FVector2D(TileItem.X, TileItem.Y);
        Vertex00.Color    = TileItem.Color;
        Vertices.Add(Vertex00);
 
        FCanvasTileRenderData Vertex01;
        Vertex01.Position = FVector2D(TileItem.X, TileItem.Y + TileItem.SizeY);
        Vertex01.Color    = TileItem.Color;
        Vertices.Add(Vertex01);

        FCanvasTileRenderData Vertex10;
        Vertex10.Position = FVector2D(TileItem.X + TileItem.SizeX, TileItem.Y);
        Vertex10.Color    = TileItem.Color;
        Vertices.Add(Vertex10);

        FCanvasTileRenderData Vertex11;
        Vertex11.Position = FVector2D(TileItem.X + TileItem.SizeX, TileItem.Y + TileItem.SizeY);
        Vertex11.Color    = TileItem.Color;
        Vertices.Add(Vertex11);
    }

    const void *VertexData = Vertices.GetData();
    int64 VertexSize = Vertices.GetCapacity();
    
    FVertexBufferAllocation *VertexBuffer;
    FRenderResourceAllocator::Get()->CreateVertexBuffer(&VertexBuffer, VertexSize);
    FMemory::Copy(VertexBuffer->Memory, VertexData, VertexSize);

    TArray<uint32> Indices;
    for (uint32 Index = 0; Index < TileItems.GetCount(); ++Index)
    {
        uint32 IndexData[6] =
        {
            0 + Index * 4,
            1 + Index * 4,
            3 + Index * 4,
            0 + Index * 4,
            2 + Index * 4,
            3 + Index * 4,
        };
        Indices.Add(IndexData, sizeof(IndexData));
    }

    const void *IndexData = Indices.GetData();
    int64 IndexSize = Indices.GetCapacity();
   
    FIndexBufferAllocation *IndexBuffer;
    FRenderResourceAllocator::Get()->CreateIndexBuffer(&IndexBuffer, IndexSize);
    FMemory::Copy(IndexBuffer->Memory, IndexData, IndexSize);

    PipelineState->Bind();

    FIndexBuffer *IndexBufferRef = IndexBuffer->Resource;
    IndexBufferRef->Bind();

    FVertexBuffer *VertexBufferRef = VertexBuffer->Resource;
    VertexBufferRef->Bind();

    const TArray<FVertexAttribute> VertexAttributes =
    {
            FVertexAttribute(0, 2, 0, sizeof(FCanvasTileRenderData), true, false),
            FVertexAttribute(1, 4, 8, sizeof(FCanvasTileRenderData), false, true),
    };

    FVertexDeclaration VertexDeclaration;
    VertexDeclaration.AddAttributes(VertexAttributes);
    VertexDeclaration.BindAttributes();

    int32 ResolutionSizeX, ResolutionSizeY;
    FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);

    FMatrix OrthographicMatrix = GetOrthographic(0.0f, 0.0f, ResolutionSizeX, ResolutionSizeY);
    PipelineState->SetUniformMatrix("OrthographicMatrix", OrthographicMatrix);

    const uint32 IndexCount = Indices.GetCount();
    const uint32 FirstIndex = IndexBuffer->Offset;
    const uint32 BaseVertex = VertexBuffer->Offset / sizeof(FCanvasTileRenderData);
    FOpenGL::DrawIndexed(IndexCount, FirstIndex, BaseVertex);
}