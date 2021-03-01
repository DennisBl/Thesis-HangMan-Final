#include "SpriteRenderer.h"
#include "RenderResourceAllocator.h"

FSpriteRenderer::FSpriteRenderer()
	: VertexShader(0)
	, PixelShader(0)
	, PipelineState(0)
{
    FString VertexShaderSourceCode =
        "#version 450\n"
        "layout(location = 0) in vec2 InPosition;\n"
        "layout(location = 1) in vec2 InTexCoord;\n"
        "layout(location = 2) in vec4 InColor;\n"
        "layout(location = 0) out vec2 OutTexCoord;\n"
        "layout(location = 1) out vec4 OutColor;\n"
        "uniform mat4 OrthographicMatrix;\n"
        "void main()\n"
        "{\n"
        "OutTexCoord = InTexCoord;\n"
        "OutColor    = InColor;\n"
        "gl_Position = OrthographicMatrix * vec4(InPosition.x, InPosition.y, 0.0, 1.0);\n"
        "}";
    VertexShader = new FVertexShader(VertexShaderSourceCode);

    FString PixelShaderSourceCode =
        "#version 450\n"
        "layout(location = 0) in vec2 InTexCoord;\n"
        "layout(location = 1) in vec4 InColor;\n"
        "layout(location = 0) out vec4 OutColor;\n"
        "uniform sampler2D SpriteTexture;\n"
        "void main()\n"
        "{\n"
        "vec4 SpriteColor = texture(SpriteTexture, InTexCoord);\n"
        "OutColor = SpriteColor * InColor;\n"
        "}";
    PixelShader = new FPixelShader(PixelShaderSourceCode);

    FPipelineStateInitializer Initializer;
    Initializer.VertexShader = VertexShader;
    Initializer.PixelShader = PixelShader;
    PipelineState = new FPipelineState(Initializer);
}

FSpriteRenderer::~FSpriteRenderer()
{
    delete PipelineState;
    delete VertexShader;
    delete PixelShader;
}

void 
FSpriteRenderer::AddItem(const FCanvasSpriteItem &Item)
{
	SpriteItems.Add(Item);
}

void 
FSpriteRenderer::RemoveItem(const FCanvasSpriteItem &Item)
{
	SpriteItems.Remove(Item);
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
FSpriteRenderer::Render()
{
    TArray<FCanvasSpriteRenderData> Vertices;
    for (const FCanvasSpriteItem &SpriteItem : SpriteItems)
    {
        FCanvasSpriteRenderData Vertex00;
        Vertex00.Position = FVector2D(SpriteItem.X, SpriteItem.Y);
        Vertex00.TexCoord = FVector2D(0.0f, 1.0f);
        Vertex00.Color    = SpriteItem.Color;
        Vertices.Add(Vertex00);
 
        FCanvasSpriteRenderData Vertex01;
        Vertex01.Position = FVector2D(SpriteItem.X, SpriteItem.Y + SpriteItem.SizeY);
        Vertex01.TexCoord = FVector2D(0.0f, 0.0f);
        Vertex01.Color    = SpriteItem.Color;
        Vertices.Add(Vertex01);

        FCanvasSpriteRenderData Vertex10;
        Vertex10.Position = FVector2D(SpriteItem.X + SpriteItem.SizeX, SpriteItem.Y);
        Vertex10.TexCoord = FVector2D(1.0f, 1.0f);
        Vertex10.Color    = SpriteItem.Color;
        Vertices.Add(Vertex10);

        FCanvasSpriteRenderData Vertex11;
        Vertex11.Position = FVector2D(SpriteItem.X + SpriteItem.SizeX, SpriteItem.Y + SpriteItem.SizeY);
        Vertex11.TexCoord = FVector2D(1.0f, 0.0f);
        Vertex11.Color    = SpriteItem.Color;
        Vertices.Add(Vertex11);
    }

    const void *VertexData = Vertices.GetData();
    int64 VertexSize = Vertices.GetCapacity();
    
    FVertexBufferAllocation *VertexBuffer;
    FRenderResourceAllocator::Get()->CreateVertexBuffer(&VertexBuffer, VertexSize);
    FMemory::Copy(VertexBuffer->Memory, VertexData, VertexSize);

    const uint32 IndexData[6] =
    {
        0, 1, 3,
        0, 2, 3
    };
    
    FIndexBufferAllocation *IndexBuffer;
    FRenderResourceAllocator::Get()->CreateIndexBuffer(&IndexBuffer, sizeof(IndexData));
    FMemory::Copy(IndexBuffer->Memory, IndexData, sizeof(IndexData));

    PipelineState->Bind();

    FIndexBuffer *IndexBufferRef = IndexBuffer->Resource;
    IndexBufferRef->Bind();

    FVertexBuffer *VertexBufferRef = VertexBuffer->Resource;
    VertexBufferRef->Bind();

    const TArray<FVertexAttribute> VertexAttributes =
    {
         FVertexAttribute(0, 2,  0, sizeof(FCanvasSpriteRenderData), true, false),
         FVertexAttribute(1, 2,  8, sizeof(FCanvasSpriteRenderData), true, false),
         FVertexAttribute(2, 4, 16, sizeof(FCanvasSpriteRenderData), false, true),
    };

    FVertexDeclaration VertexDeclaration;
    VertexDeclaration.AddAttributes(VertexAttributes);
    VertexDeclaration.BindAttributes();

    int32 ResolutionSizeX, ResolutionSizeY;
    FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);

    FMatrix OrthographicMatrix = GetOrthographic(0.0f, 0.0f, ResolutionSizeX, ResolutionSizeY);
    PipelineState->SetUniformMatrix("OrthographicMatrix", OrthographicMatrix);

    for (uint32 Index = 0; Index < SpriteItems.GetCount(); ++Index)
    {
        const FCanvasSpriteItem &SpriteItem = SpriteItems[Index];
        const FTexture2D *Sprite = SpriteItem.Sprite;
        Sprite->BindTexture();

        const uint32 IndexCount = 6;
        const uint32 FirstIndex = IndexBuffer->Offset;
        const uint32 BaseVertex = VertexBuffer->Offset / sizeof(FCanvasSpriteRenderData);
        FOpenGL::DrawIndexed(IndexCount, FirstIndex, BaseVertex + Index * 4);
    }
}