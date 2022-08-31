#pragma once

#ifndef  _FORMATGL_H_
#define _FORMATGL_H_

#ifdef  _GLEW_USE
#include <GL/glew.h>
#else 
#include <qopenglfunctions.h>
#include <qopenglcontext.h>
#include <qopenglfunctions_4_5_core.h>
#include <qopenglfunctions_4_5_compatibility.h>
#include <qopenglextrafunctions.h>
#include <qopenglwindow.h>
#endif // ! _GLEW_USE
#include "../DescriptorSet.h"
#include "../Pipeline.h"

namespace RHI
{

	GLenum GLCast(EBufferUsageFlags flags);
	

	GLenum GLCast(EShaderStageFlags flags);
	
	/*
	enum class GLSLType :uint32_t
	{
		VEC4 = 35666,
		VEC3 = 35665,
		VEC2 = 35664,

		IVEC4 = 35669,
		IVEC3 = 35668,
		IVEC2 = 35667

	};


	struct DepthSetGL
	{
		bool DepthEnable = false;
		GLenum DepthCompareOp = GL_LESS;
		bool DepthWriteEnable = true;
	};


	struct StencilSetGL
	{
		GLenum Face;
		GLenum CompareOp;
		GLenum CompareMask;
		GLenum WriteMask;
		GLenum FailOp;
		GLenum DepthFailOp;
		GLenum PassOp;
	};

	struct BlendSetGL
	{
		GLuint buf;
		GLenum SrcBlend;
		GLenum DestBlend;
		GLenum SrcBlendAlpha;
		GLenum DestBlendAlpha;
		GLenum BlendOp;
		GLenum BlendOpAlpha;
		bool RMask;
		bool GMask;
		bool BMask;
		bool AMask;
	};

	struct MultisampleSetGL
	{

	};
	*/



	
	GLenum EFormatToGLBase(EFormat type);
	GLenum GLCast(EFormat type);
	GLenum EFormatToGLBaseInternal(EFormat type);

	GLenum GLCast(EDescriptorType type);
	GLenum GLCast(EFilter fliter);
	GLenum GLCast(ESamplerMipmapMode mode);
	GLenum GLCast(ESamplerAddressMode mode);
	GLenum GLCast(EImageUsageFlags usage);
	GLenum GLCast(ECompareOp op);
	GLenum GLCast(EStencilOp op);
	GLenum GLCast(EBlendMode mode);
	GLenum GLCast(EBlendOp op);
	GLenum GLCast(ECullModeFlags flag);
	GLenum GLCast(EPolygonMode mode);
	GLenum GLCast(EPrimitiveTopology pology);
	GLenum GLCast(EImageViewType type);
}

#endif // ! _FORMATGL_H_