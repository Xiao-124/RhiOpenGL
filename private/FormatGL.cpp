#include "FormatGL.h"

namespace RHI
{
	GLenum GLCast(EBufferUsageFlags flags)
	{
		switch (flags)
		{
		case EBufferUsageFlags::Index:
			return GL_ELEMENT_ARRAY_BUFFER;
			break;
		case EBufferUsageFlags::Vertex:
			return GL_ARRAY_BUFFER;
			break;
		case EBufferUsageFlags::IndirectDraw:
			return GL_DRAW_INDIRECT_BUFFER;
			break;
		case EBufferUsageFlags::Uniform:
			return GL_UNIFORM_BUFFER;
			break;
		case EBufferUsageFlags::Storage:
			return GL_SHADER_STORAGE_BUFFER;
			break;
		case EBufferUsageFlags::UniformTexel:

			break;
		case EBufferUsageFlags::StorageTexel:
			return GL_TEXTURE_BUFFER;
			break;
		default:
			return 0;
			break;
		}

	}

	GLenum GLCast(EShaderStageFlags flags)
	{
		switch (flags)
		{
		case EShaderStageFlags::Vertex:
			return GL_VERTEX_SHADER;
			break;
		case EShaderStageFlags::TessellationControl:
			break;
		case EShaderStageFlags::TessellationEvaluation:
			break;
		case EShaderStageFlags::Geometry:
			break;
		case EShaderStageFlags::Pixel:
			break;
		case EShaderStageFlags::Compute:
			break;
		case EShaderStageFlags::Fragment:
			return GL_FRAGMENT_SHADER;
			break;
		case EShaderStageFlags::AllGraphics:
			break;
		case EShaderStageFlags::All:
			break;
		default:
			break;
		}
	}

	

	GLenum EFormatToGLBase(EFormat type)
	{
		switch (type)
		{
		case EFormat::UNDEFINED:
			return 0;
			break;
		case EFormat::R8G8B8_UINT:
		case EFormat::R8G8B8_SRGB:
		case EFormat::R8G8B8A8_UINT:
		case EFormat::R8G8B8A8_SRGB:
			return GL_UNSIGNED_BYTE;
			break;
		case EFormat::R32_UINT:
			return GL_UNSIGNED_INT;
			break;
		case EFormat::R32_SINT:
			return GL_INT;
			break;
		case EFormat::R32_SFLOAT:
			return GL_FLOAT;
			break;
		case EFormat::R32G32_UINT:
			return GL_UNSIGNED_INT;
			break;
		case EFormat::R32G32_SINT:
			return GL_INT;
			break;
		case EFormat::R32G32_SFLOAT:
			return GL_FLOAT;
			break;
		case EFormat::R32G32B32_UINT:
			return GL_UNSIGNED_INT;
			break;
		case EFormat::R32G32B32_SINT:
			return GL_INT;
			break;
		case EFormat::R32G32B32_SFLOAT:
			return GL_FLOAT;
			break;
		case EFormat::R32G32B32A32_UINT:
			return GL_UNSIGNED_INT;
			break;
		case EFormat::R32G32B32A32_SINT:
			return GL_INT;
			break;
		case EFormat::R32G32B32A32_SFLOAT:
			return GL_FLOAT;
			break;
		case EFormat::R64_UINT:		
		case EFormat::R64_SINT:
		case EFormat::R64_SFLOAT:
		case EFormat::R64G64_UINT:
		case EFormat::R64G64_SINT:
		case EFormat::R64G64_SFLOAT:
		case EFormat::R64G64B64_UINT:
		case EFormat::R64G64B64_SINT:
		case EFormat::R64G64B64_SFLOAT:
		case EFormat::R64G64B64A64_UINT:
		case EFormat::R64G64B64A64_SINT:
		case EFormat::R64G64B64A64_SFLOAT:
			return GL_DOUBLE;
			break;
		default:
			break;
		}
	}

	GLenum GLCast(EFormat type)
	{
		switch (type)
		{
		case EFormat::UNDEFINED:
			return 0;
			break;
		case EFormat::R8G8B8_UINT:
			return GL_RGB8UI;
			break;
		case EFormat::R8G8B8_SRGB:
			return GL_RGB8;
			break;
		case EFormat::R8G8B8A8_UINT:
			return GL_RGBA8UI;
			break;
		case EFormat::R8G8B8A8_SRGB:
			return GL_RGBA8;
			break;
		case EFormat::R32_UINT:
			return GL_R32UI;
			break;
		case EFormat::R32_SINT:
			return GL_R32I;
			break;
		case EFormat::R32_SFLOAT:
			return GL_R32F;
			break;
		case EFormat::R32G32_UINT:
			return GL_RG32UI;
			break;
		case EFormat::R32G32_SINT:
			return GL_RG32I;
			break;
		case EFormat::R32G32_SFLOAT:
			return GL_RG32F;
			break;
		case EFormat::R32G32B32_UINT:
			return GL_RGB32UI;
			break;
		case EFormat::R32G32B32_SINT:
			return GL_RGB32I;
			break;
		case EFormat::R32G32B32_SFLOAT:
			return GL_RGB32F;
			break;
		case EFormat::R32G32B32A32_UINT:
			return GL_RGBA32UI;
			break;
		case EFormat::R32G32B32A32_SINT:
			return GL_RGBA32I;
			break;
		case EFormat::R32G32B32A32_SFLOAT:
			return GL_RGBA32F;
			break;
		case EFormat::D24_UNORM_S8_UINT:
			return GL_DEPTH24_STENCIL8;
		case EFormat::D32_SFLOAT_S8_UINT:
			return GL_DEPTH32F_STENCIL8;
		default:
			break;
		}



	}

	GLenum EFormatToGLBaseInternal(EFormat type)
	{
		switch (type)
		{
		case RHI::EFormat::UNDEFINED:
			return 0;
		case RHI::EFormat::R8G8B8_UINT:		
		case RHI::EFormat::R8G8B8_SRGB:
			return GL_RGB;
		case RHI::EFormat::R8G8B8A8_UINT:
		case RHI::EFormat::R8G8B8A8_SRGB:
			return GL_RGBA;
		case RHI::EFormat::R32_UINT:
		case RHI::EFormat::R32_SINT:
		case RHI::EFormat::R32_SFLOAT:
			return GL_R;
		case RHI::EFormat::R32G32_UINT:
		case RHI::EFormat::R32G32_SINT:
		case RHI::EFormat::R32G32_SFLOAT:
			return GL_RG;
		case RHI::EFormat::R32G32B32_UINT:
		case RHI::EFormat::R32G32B32_SINT:
		case RHI::EFormat::R32G32B32_SFLOAT:
			return GL_RGB;
		case RHI::EFormat::R32G32B32A32_UINT:
		case RHI::EFormat::R32G32B32A32_SINT:
		case RHI::EFormat::R32G32B32A32_SFLOAT:
			return GL_RGBA;
		case RHI::EFormat::R64_UINT:
			break;
		case RHI::EFormat::R64_SINT:
			break;
		case RHI::EFormat::R64_SFLOAT:
			break;
		case RHI::EFormat::R64G64_UINT:
			break;
		case RHI::EFormat::R64G64_SINT:
			break;
		case RHI::EFormat::R64G64_SFLOAT:
			break;
		case RHI::EFormat::R64G64B64_UINT:
			break;
		case RHI::EFormat::R64G64B64_SINT:
			break;
		case RHI::EFormat::R64G64B64_SFLOAT:
			break;
		case RHI::EFormat::R64G64B64A64_UINT:
			break;
		case RHI::EFormat::R64G64B64A64_SINT:
			break;
		case RHI::EFormat::R64G64B64A64_SFLOAT:
			break;
		case RHI::EFormat::D16_UNORM:
			break;
		case RHI::EFormat::X8_D24_UNORM_PACK32:
			break;
		case RHI::EFormat::D32_SFLOAT:
			break;
		case RHI::EFormat::S8_UINT:
			break;
		case RHI::EFormat::D16_UNORM_S8_UINT:
			break;
		case RHI::EFormat::D24_UNORM_S8_UINT:
			break;
		case RHI::EFormat::D32_SFLOAT_S8_UINT:
			break;
		default:
			break;
		}
	}


	GLenum GLCast(EDescriptorType type)
	{
		switch (type)
		{
		case EDescriptorType::Sampler:
			break;
		case EDescriptorType::Image:
			break;
		case EDescriptorType::StorageImage:
			break;
		case EDescriptorType::UniformTexelBuffer:
			break;
		case EDescriptorType::StorageTexelBuffer:
			break;
		case EDescriptorType::UniformBuffer:
			return GL_UNIFORM_BUFFER;
			break;
		case EDescriptorType::StorageBuffer:
			return GL_SHADER_STORAGE_BUFFER;
			break;
		case EDescriptorType::UniformBufferDynamic:
			break;
		case EDescriptorType::StorageBufferDynamic:
			break;
		case EDescriptorType::InputAttachment:
			break;
		default:
			break;
		}
	}





	GLenum GLCast(EFilter fliter)
	{
		switch (fliter)
		{
		case EFilter::Linear:
			return GL_LINEAR;
		case EFilter::Nearest:
			return GL_NEAREST;
		}

	}



	GLenum GLCast(ESamplerMipmapMode mode)
	{
		switch (mode)
		{
		case ESamplerMipmapMode::Linear:
			return GL_LINEAR_MIPMAP_LINEAR;
		case ESamplerMipmapMode::Nearest:
			return GL_NEAREST_MIPMAP_NEAREST;
		}

	}


	GLenum GLCast(ESamplerAddressMode mode)
	{
		switch (mode)
		{
		case ESamplerAddressMode::Wrap:
			return GL_REPEAT;
			break;
		case ESamplerAddressMode::Mirror:
			GL_MIRROR_CLAMP_TO_EDGE;
			break;
		case ESamplerAddressMode::Clamp:
			GL_CLAMP_TO_EDGE;
			break;
		case ESamplerAddressMode::Border:
			GL_CLAMP_TO_BORDER;
			break;
		case ESamplerAddressMode::MirrorOnce:
			GL_MIRRORED_REPEAT;
			break;
		default:
			break;
		}

	}




	GLenum GLCast(EImageUsageFlags usage)
	{
		switch (usage)
		{
		case EImageUsageFlags::None:
			return GL_NONE;
			break;
		case EImageUsageFlags::Sampled:
			return GL_SAMPLER;
			break;
		case EImageUsageFlags::DepthStencil:
			return GL_DEPTH_STENCIL;
			break;
		case EImageUsageFlags::RenderTarget:
			return GL_RENDER;
			break;
		case EImageUsageFlags::CubeMap:
			return GL_TEXTURE_CUBE_MAP;
			break;
		case EImageUsageFlags::GenMIPMaps:
			return GL_MIPMAP;
			break;
		case EImageUsageFlags::Staging:
			break;
		case EImageUsageFlags::Storage:
			break;

		default:
			break;
		}
	}



	GLenum GLCast(ECompareOp op)
	{
		switch (op)
		{
		case ECompareOp::Never:
			return GL_NEVER;
			break;
		case ECompareOp::Less:
			return GL_LESS;
			break;
		case ECompareOp::Equal:
			return GL_EQUAL;
			break;
		case ECompareOp::LessEqual:
			return GL_LEQUAL;
			break;
		case ECompareOp::Greater:
			return GL_GREATER;
			break;
		case ECompareOp::NotEqual:
			return GL_NOTEQUAL;
			break;
		case ECompareOp::GreaterEqual:
			return GL_GEQUAL;
			break;
		case ECompareOp::Always:
			return GL_ALWAYS;
			break;
		default:
			break;
		}


	}



	GLenum GLCast(EStencilOp op)
	{
		switch (op)
		{
		case EStencilOp::Keep:
			return GL_KEEP;
			break;
		case EStencilOp::Zero:
			return GL_ZERO;
			break;
		case EStencilOp::Replace:
			return GL_REPLACE;
			break;
		case EStencilOp::IncrementAndClamp:
			return GL_INCR;
			break;
		case EStencilOp::DecrementAndClamp:
			return GL_DECR;
			break;
		case EStencilOp::Invert:
			return GL_INVERT;
			break;
		case EStencilOp::IncrementAndWrap:
			return GL_INCR_WRAP;
			break;
		case EStencilOp::DecrementAndWrap:
			return GL_DECR_WRAP;
			break;
		default:
			break;
		}

	}


	GLenum GLCast(EBlendMode mode)
	{
		switch (mode)
		{
		case EBlendMode::Zero:
			return GL_ZERO;
			break;
		case EBlendMode::One:
			return GL_ONE;
			break;
		case EBlendMode::SrcColor:
			return GL_SRC_COLOR;
			break;
		case EBlendMode::OneMinusSrcColor:
			return GL_ONE_MINUS_SRC_COLOR;
			break;
		case EBlendMode::SrcAlpha:
			return GL_SRC_ALPHA;
			break;
		case EBlendMode::OneMinusSrcAlpha:
			return GL_ONE_MINUS_SRC_ALPHA;
			break;
		case EBlendMode::DstAlpha:
			return GL_DST_ALPHA;
			break;
		case EBlendMode::OneMinusDstAlpha:
			return GL_ONE_MINUS_DST_ALPHA;
			break;
		case EBlendMode::DstColor:
			return GL_DST_COLOR;
			break;
		case EBlendMode::OneMinusDstColor:
			return GL_ONE_MINUS_DST_COLOR;
			break;
		case EBlendMode::SrcAlphaSaturate:
			return GL_SRC_ALPHA_SATURATE;
			break;
		default:
			break;
		}

	}



	GLenum GLCast(EBlendOp op)
	{
		switch (op)
		{
		case EBlendOp::Add:
			return GL_FUNC_ADD;
			break;
		case EBlendOp::Subtract:
			return GL_FUNC_SUBTRACT;
			break;
		case EBlendOp::ReverseSubtract:
			return GL_FUNC_REVERSE_SUBTRACT;
			break;
		case EBlendOp::Min:
			return GL_MIN;
			break;
		case EBlendOp::Max:
			return GL_MAX;
			break;
		default:
			break;
		}

	}




	GLenum GLCast(ECullModeFlags flag)
	{
		switch (flag)
		{
		case ECullModeFlags::None:
			return GL_NONE;
			break;
		case ECullModeFlags::Front:
			return GL_FRONT;
			break;
		case ECullModeFlags::Back:
			return GL_BACK;
			break;
		default:
			break;
		}
	}


	GLenum GLCast(EPolygonMode mode)
	{
		switch (mode)
		{
		case EPolygonMode::Fill:
			return GL_FILL;
			break;
		case EPolygonMode::Wireframe:
			return GL_LINE;
			break;
		default:
			break;
		}
	}



	GLenum GLCast(EPrimitiveTopology pology)
	{
		switch (pology)
		{
		case EPrimitiveTopology::PointList:
			return GL_POINTS;
			break;
		case EPrimitiveTopology::LineList:
			return GL_LINES;
			break;
		case EPrimitiveTopology::LineStrip:
			return GL_LINE_STRIP;
			break;
		case EPrimitiveTopology::TriangleList:
			return GL_TRIANGLES;
			break;
		case EPrimitiveTopology::TriangleStrip:
			return GL_TRIANGLE_STRIP;
			break;
		case EPrimitiveTopology::TriangleFan:
			return GL_TRIANGLE_FAN;
			break;
		default:
			break;
		}

	}


	GLenum GLCast(EImageViewType type)
	{
		switch (type)
		{
		case EImageViewType::View1D:
			return GL_TEXTURE_1D;
			break;
		case EImageViewType::View2D:
			return GL_TEXTURE_2D;
			break;
		case EImageViewType::View3D:
			return GL_TEXTURE_3D;
			break;
		case EImageViewType::Cube:
			return GL_TEXTURE_CUBE_MAP;
			break;
		case EImageViewType::View1DArray:
			return GL_TEXTURE_1D_ARRAY;
			break;
		case EImageViewType::View2DArray:
			return GL_TEXTURE_2D_ARRAY;
			break;
		case EImageViewType::CubeArray:
			return GL_TEXTURE_CUBE_MAP_ARRAY;
			break;
		default:
			break;
		}
	}
}