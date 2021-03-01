#include "IndexBuffer.h"
#include "OpenGL.h"

static const int32 ResourceLockMode = GL_MAP_WRITE_BIT | GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT;

FIndexBuffer::FIndexBuffer(int64 InSize, const void *InitialData)
	: Size(InSize)
	, ResourceId(0)
{
	glCreateBuffers(1, &ResourceId);
	glNamedBufferStorage(ResourceId, Size, InitialData, ResourceLockMode);
}

FIndexBuffer::~FIndexBuffer()
{
	glDeleteBuffers(1, &ResourceId);
}

void *
FIndexBuffer::Lock(int64 InOffset, int64 InSize)
{
	return glMapNamedBufferRange(ResourceId, InOffset, InSize, ResourceLockMode);
}


void
FIndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ResourceId);
}