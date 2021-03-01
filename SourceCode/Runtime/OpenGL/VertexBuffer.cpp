#include "VertexBuffer.h"
#include "OpenGL.h"

static const int32 ResourceLockMode = GL_MAP_WRITE_BIT | GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT;

FVertexBuffer::FVertexBuffer(int64 InSize, const void *InitialData)
	: Size(InSize)
	, ResourceId(0)
{
	glCreateBuffers(1, &ResourceId);
	glNamedBufferStorage(ResourceId, Size, InitialData, ResourceLockMode);
}

FVertexBuffer::~FVertexBuffer()
{
	glDeleteBuffers(1, &ResourceId);
}

void *
FVertexBuffer::Lock(int64 InOffset, int64 InSize)
{
	return glMapNamedBufferRange(ResourceId, InOffset, InSize, ResourceLockMode);
}

void
FVertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ResourceId);
}