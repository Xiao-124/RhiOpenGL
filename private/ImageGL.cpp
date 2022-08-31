#include "ImageGL.h"
#include "FormatGL.h"
namespace RHI
{
	CImageGL::CImageGL(CDeviceGL * p, EFormat format, EImageUsageFlags usage, uint32_t width, uint32_t mipLevels, uint32_t arrayLayers, uint32_t sampleCount, const void * initialData):Parent(p)
	{
#ifndef  _GLEW_USE			
		QOpenGLContext* context = Parent->_context;
		QSurface* sur = context->surface();
		context->makeCurrent(sur);
		initializeOpenGLFunctions();
#endif
		this->Format = format;
		this->flags = usage;
		this->width = width;
		this->height = 0;
		this->mipLevel = mipLevels;
		this->arrayLevel = arrayLayers;
		this->sampleCount = sampleCount;
		this->depth = 0;
		glCreateTextures(GL_TEXTURE_1D, 1, &texture);
		glTextureStorage1D(texture, arrayLayers, GLCast(format), width);
		if (initialData)
		{
			glTextureSubImage1D(texture, 0, 0, width, GLCast(format),
				EFormatToGLBase(format), initialData);
		}
			
		if (((int)EImageUsageFlags::GenMIPMaps & (int)usage) != 0)
			glGenerateTextureMipmap(texture);

	}


	CImageGL::CImageGL(CDeviceGL * p, EFormat format, EImageUsageFlags usage, uint32_t width, uint32_t height, uint32_t mipLevels, uint32_t arrayLayers, uint32_t sampleCount, const void * initialData) :Parent(p)
	{
#ifndef  _GLEW_USE			
		QOpenGLContext* context = Parent->_context;
		QSurface* sur = context->surface();
		context->makeCurrent(sur);
		initializeOpenGLFunctions();
#endif
		this->Format = format;
		this->flags = usage;
		this->width = width;
		this->height = height;
		this->mipLevel = mipLevels;
		this->arrayLevel = arrayLayers;
		this->sampleCount = sampleCount;
		this->depth = 0;
		GLenum target;
		if (((int)EImageUsageFlags::CubeMap & (int)usage) != 0)
		{
			target = GL_TEXTURE_CUBE_MAP;
			glCreateTextures(target, 1, &texture);		
			glTextureStorage3D(texture, 1, GLCast(format), width, height, 6);
			if (initialData)
			{
				for (int i = 0; i < 6; i++)
				{
					glTextureSubImage3D(texture, 0, 0, 0, i, width, height, 1, EFormatToGLBaseInternal(format),
						EFormatToGLBase(format), (char*)initialData+width*height*3*i);
				}
			}
		}
		else
		{
			target = GL_TEXTURE_2D;	
			glCreateTextures(target, 1, &texture);
			glTextureStorage2D(texture, arrayLayers, GLCast(format), width, height);
			if (initialData)
			{
				glTextureSubImage2D(texture, 0, 0, 0, width, height, EFormatToGLBaseInternal(format),
					EFormatToGLBase(format), initialData);
			}
		}
		
		if (((int)EImageUsageFlags::GenMIPMaps & (int)usage) != 0)
			glGenerateTextureMipmap(texture);
		
	}

	CImageGL::CImageGL(CDeviceGL* p, EFormat format, EImageUsageFlags usage,
		uint32_t width, uint32_t height, uint32_t depth, uint32_t mipLevels, uint32_t arrayLayers,
		uint32_t sampleCount, const void* initialData):Parent(p)
	{
#ifndef  _GLEW_USE			
		QOpenGLContext* context = Parent->_context;
		QSurface* sur = context->surface();
		context->makeCurrent(sur);
		initializeOpenGLFunctions();
#endif

		this->Format = format;
		this->flags = usage;
		this->width = width;
		this->height = height;
		this->mipLevel = mipLevels;
		this->arrayLevel = arrayLayers;
		this->sampleCount = sampleCount;
		this->depth = depth;

		glCreateTextures(GL_TEXTURE_3D, 1, &texture);
		glTextureStorage3D(texture, arrayLayers, GLCast(format), width, height, depth);
		if (initialData)
		{
			glTextureSubImage3D(texture, 0, 0, 0, 0, width, height, depth, GLCast(format),
				EFormatToGLBase(format), initialData);
		}	
		if (((int)EImageUsageFlags::GenMIPMaps & (int)usage) != 0)
			glGenerateTextureMipmap(texture);

	}


	CImageGL::~CImageGL()
	{
		if (glIsTexture(texture))
		{
			glDeleteTextures(1, &texture);
		}
	}
}