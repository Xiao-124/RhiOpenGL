#include "BufferGL.h"
namespace RHI
{

	CBufferGL::CBufferGL(CDeviceGL* p, size_t size, EBufferUsageFlags usage, const void* initialData):Parent(p)
	{
#ifndef  _GLEW_USE			
		QOpenGLContext* context = Parent->_context;
		QSurface* sur = context ->surface();
		context->makeCurrent(sur);
		initializeOpenGLFunctions();
#endif	
		
		GLenum _usage = 0;		
		if ( (usage &  EBufferUsageFlags::Dynamic) != EBufferUsageFlags::UNDEFINED)
		{
			_usage   |= (GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
			mapUsage |= (GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
		}
		if ((usage & EBufferUsageFlags::Upload) != EBufferUsageFlags::UNDEFINED)
		{
			_usage |= GL_DYNAMIC_STORAGE_BIT;	
		}
		if ((usage & EBufferUsageFlags::Readback) != EBufferUsageFlags::UNDEFINED)
		{
			_usage   |= (GL_MAP_WRITE_BIT | GL_MAP_READ_BIT);
			mapUsage |= (GL_MAP_WRITE_BIT | GL_MAP_READ_BIT);
		}
		glCreateBuffers(1, &buffer);
		glNamedBufferStorage(buffer, size, initialData, _usage);	
	}

	CBufferGL::~CBufferGL()
	{
		if (glIsBuffer(buffer))
		{
			glDeleteBuffers(1, &buffer);
		}
	}

	void* CBufferGL::Map(size_t offset, size_t size)
	{
		void* data = glMapNamedBufferRange(buffer, offset, size, mapUsage);
		return data;
	}

	void CBufferGL::Unmap()
	{
		glUnmapNamedBuffer(buffer);
	}

}