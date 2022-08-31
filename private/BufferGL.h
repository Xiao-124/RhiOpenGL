#pragma once
#include "../Resources.h"
#include "../DeviceGL.h"
#include "FormatGL.h"
namespace RHI
{
	
#ifdef  _GLEW_USE
	class CBufferGL :public CBuffer 
#else
	class CBufferGL :public CBuffer,protected QOpenGLFunctions_4_5_Core
#endif
	{
	private:
		CDeviceGL* Parent;
		GLuint buffer;
		GLenum mapUsage = 0;
	public:
		typedef std::shared_ptr<CBufferGL> Ref;		
		CBufferGL(CDeviceGL* p,size_t size, EBufferUsageFlags usage, const void* initialData);
		~CBufferGL();
		const GLuint& GetHandle() const { return buffer; }
		void* Map(size_t offset, size_t size);
		void Unmap();
		
	};



}