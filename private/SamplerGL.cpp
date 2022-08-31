#include "FormatGL.h"
#include "SamplerGL.h"
#include "../DeviceGL.h"
namespace RHI
{

	CSamplerGL::CSamplerGL(CDeviceGL* p, const CSamplerDesc& desc):Parent(p)
	{
#ifndef  _GLEW_USE
		QOpenGLContext* context = Parent->_context;
		QSurface* sur = context->surface();
		context->makeCurrent(sur);
		initializeOpenGLFunctions();
#endif		
		glCreateSamplers(1, &sampler);
        glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GLCast(desc.MinFilter) );
        glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GLCast(desc.MagFilter) );
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GLCast(desc.AddressModeU) );
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GLCast(desc.AddressModeV) );
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_R, GLCast(desc.AddressModeW));
        glSamplerParameterfv(sampler, GL_TEXTURE_BORDER_COLOR, desc.BorderColor.data());
        glSamplerParameterf(sampler, GL_TEXTURE_MIN_LOD, desc.MinLod );
        glSamplerParameterf(sampler, GL_TEXTURE_MAX_LOD, desc.MaxLod );
		
        glSamplerParameterf(sampler, GL_TEXTURE_LOD_BIAS, desc.MipLodBias);
		if (desc.CompareEnable)
		{
			glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
			glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_FUNC, GLCast(desc.CompareOp));
		}
		else
		{
			glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_MODE, GL_NONE);
		}
        
		if (desc.AnisotropyEnable)
		{
			glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, desc.MaxAnisotropy);
		}
	}



	CSamplerGL::~CSamplerGL()
	{
		if (glIsSampler(sampler))
		{
			glDeleteSamplers(1, &sampler);
		}

	}

}