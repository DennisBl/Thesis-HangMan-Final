#include "TextRenderer.h"
#include "RenderResourceAllocator.h"
#include "GameCharCodeMap.h"

FTextRenderer::FTextRenderer()
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
        "uniform sampler2D FontTexture;\n"
        "void main()\n"
        "{\n"
        "float FontAlpha = texture(FontTexture, InTexCoord).r;\n"
        "vec4 FontColor = vec4(1.0, 1.0, 1.0, FontAlpha);\n"
        "OutColor = FontColor * InColor;\n"
        "}";
    PixelShader = new FPixelShader(PixelShaderSourceCode);

    FPipelineStateInitializer Initializer;
    Initializer.VertexShader = VertexShader;
    Initializer.PixelShader = PixelShader;
    PipelineState = new FPipelineState(Initializer);
}

FTextRenderer::~FTextRenderer()
{
    delete PipelineState;
    delete VertexShader;
    delete PixelShader;
}

void 
FTextRenderer::AddItem(const FCanvasTextItem &Item)
{
    TextItems.Add(Item);
}

void 
FTextRenderer::RemoveItem(const FCanvasTextItem &Item)
{
    TextItems.Remove(Item);
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
FTextRenderer::Render()
{
    FGameCharCodeMap::Get()->SetGameLanguage(GL_Greek);
    uint8 TempLetter;
    for (const FCanvasTextItem &TextItem : TextItems)
    {
        const FFontCache *FontCache = TextItem.FontCache;
        const FString& TextString = TextItem.Text;

        TArray<FCanvasTextRenderData> Vertices;
        for (uint32 Index = 0, Offset = 0; Index < TextString.GetLength(); ++Index)
        {
           
            const uint8& gLetter = TextString[Index];
            
            const TCHAR CharCode = FGameCharCodeMap::Get()->GetMappedCharCodes(gLetter);
            if (CharCode)
            {
                TempLetter = CharCode;
            }     
            else
            {
                TempLetter = TextString[Index];
            }
            const uint8& Letter = TempLetter;
            const FTextCharacter &Character = FontCache->GetCharacter(Letter);

            float PositionX = TextItem.X + (float)Character.Bearing.X * TextItem.FontScale + Offset;
            float PositionY = TextItem.Y - (float)(Character.FontSize.Y - Character.Bearing.Y) * TextItem.FontScale;

            float TileSizeX = (float)Character.FontSize.X * TextItem.FontScale;
            float TileSizeY = (float)Character.FontSize.Y * TextItem.FontScale;

            float TexCoordZ = (float)Letter / (float)FontTextureCount;
            float TexCoordX = (float)Letter / (float)FontTextureCount + Character.TexCoord.X;
            float TexCoordY = 1.0f - Character.TexCoord.Y;

            FCanvasTextRenderData Vertex00;
            Vertex00.Position = FVector2D(PositionX, PositionY);
            Vertex00.TexCoord = FVector2D(TexCoordZ, 1.0f);
            Vertex00.Color    = TextItem.Color;
            Vertices.Add(Vertex00);
 
            FCanvasTextRenderData Vertex01;
            Vertex01.Position = FVector2D(PositionX, PositionY + TileSizeY);
            Vertex01.TexCoord = FVector2D(TexCoordZ, TexCoordY);
            Vertex01.Color    = TextItem.Color;
            Vertices.Add(Vertex01);

            FCanvasTextRenderData Vertex10;
            Vertex10.Position = FVector2D(PositionX + TileSizeX, PositionY);
            Vertex10.TexCoord = FVector2D(TexCoordX, 1.0f);
            Vertex10.Color    = TextItem.Color;
            Vertices.Add(Vertex10);

            FCanvasTextRenderData Vertex11;
            Vertex11.Position = FVector2D(PositionX + TileSizeX, PositionY + TileSizeY);
            Vertex11.TexCoord = FVector2D(TexCoordX, TexCoordY);
            Vertex11.Color    = TextItem.Color;
            Vertices.Add(Vertex11);

            Offset += (Character.Advance >> 6) * TextItem.FontScale;
        }

        const void *VertexData = Vertices.GetData();
        int64 VertexSize = Vertices.GetCapacity();

        FVertexBufferAllocation *VertexBuffer;
        FRenderResourceAllocator::Get()->CreateVertexBuffer(&VertexBuffer, VertexSize);
        FMemory::Copy(VertexBuffer->Memory, VertexData, VertexSize);

        TArray<uint32> Indices;
        for (uint32 Index = 0; Index < TextString.GetLength(); ++Index)
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
             FVertexAttribute(0, 2,  0, sizeof(FCanvasTextRenderData), true, false),
             FVertexAttribute(1, 2,  8, sizeof(FCanvasTextRenderData), true, false),
             FVertexAttribute(2, 4, 16, sizeof(FCanvasTextRenderData), false, true),
        };

        FVertexDeclaration VertexDeclaration;
        VertexDeclaration.AddAttributes(VertexAttributes);
        VertexDeclaration.BindAttributes();

        const FTexture2D *FontTexture = FontCache->GetFontTexture();
        FontTexture->BindTexture();

        int32 ResolutionSizeX, ResolutionSizeY;
        FApplication::Get()->GetApplicationResolution(&ResolutionSizeX, &ResolutionSizeY);

        FMatrix OrthographicMatrix = GetOrthographic(0.0f, 0.0f, ResolutionSizeX, ResolutionSizeY);
        PipelineState->SetUniformMatrix("OrthographicMatrix", OrthographicMatrix);

        Assert(!(VertexBuffer->Offset % sizeof(FCanvasTextRenderData)));

        const uint32 IndexCount = Indices.GetCount();
        const uint32 FirstIndex = IndexBuffer->Offset;
        const uint32 BaseVertex = VertexBuffer->Offset / sizeof(FCanvasTextRenderData);
        FOpenGL::DrawIndexed(IndexCount, FirstIndex, BaseVertex);
    }
}