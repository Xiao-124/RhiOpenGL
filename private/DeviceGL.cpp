

#include "../DeviceGL.h"
#include "BufferGL.h"
#include "PipelineGL.h"
#include "ShaderModuleGL.h"
#include "CommandQueueGL.h"
#include "RenderPassGL.h"
#include "DescriptorSetLayoutGL.h"
namespace RHI
{
	CDeviceGL::CDeviceGL()
    {
#ifndef  _GLEW_USE
		setSurfaceType(OpenGLSurface);
		create();
		_context = new QOpenGLContext();
        QSurfaceFormat surFormat;
        surFormat.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
        surFormat.setVersion(4, 5);
        _context->setFormat(surFormat);
		_context->create();
		_context->makeCurrent(this);
		initializeOpenGLFunctions();
#endif		
    }

   
    CBuffer::Ref CDeviceGL::CreateBuffer(size_t size, EBufferUsageFlags usage,
        const void* initialData)
    {
      		
        CBufferGL::Ref buffer= std::make_shared<CBufferGL>(this, size, usage, initialData);
        return std::static_pointer_cast<CBuffer>(buffer);     
    }

    CPipeline::Ref CDeviceGL::CreatePipeline(const CPipelineDesc& desc)
    {
        CPipelineGL::Ref pipe = std::make_shared<CPipelineGL>(this, desc);
        return std::static_pointer_cast<CPipeline>(pipe);
    }

    CShaderModule::Ref CDeviceGL::CreateShaderModule(EShaderStageFlags flags, std::string sources)
    {
        CShaderModuleGL::Ref shader = std::make_shared<CShaderModuleGL>(this, sources, flags);
        return shader;
    }

    CRenderPass::Ref CDeviceGL::CreateRenderPass(const CRenderPassDesc& desc)
    {
		QOpenGLContext *context = new QOpenGLContext();
        return std::make_shared<CRenderPassGL>(this, desc);
    }


    CCommandQueue::Ref CDeviceGL::CreateCommandQueue()
    {
        CCommandQueueGL::Ref queue = std::make_shared<CCommandQueueGL>(this, EQueueType::Render);
        return queue;
    }

    CDescriptorSetLayout::Ref CDeviceGL::CreateDescriptorSetLayout()
    {
        CDescriptorSetLayoutGL::Ref layout = std::make_shared<CDescriptorSetLayoutGL>(this);
        return layout;
    }

    CPipelineLayout::Ref CDeviceGL::CreatePipelineLayout(const std::vector<CDescriptorSetLayout::Ref>& setLayouts)
    {
        CPipelineLayoutGL::Ref layout = std::make_shared<CPipelineLayoutGL>(this, setLayouts);
        return layout;
    }

	CImage::Ref CDeviceGL::CreateImage1D(EFormat format, EImageUsageFlags usage, uint32_t width, uint32_t mipLevels, uint32_t arrayLayers, uint32_t sampleCount, const void * initialData)
	{
		CImageGL::Ref image = std::make_shared<CImageGL>(this, format, usage, width,
			mipLevels, arrayLayers, sampleCount, initialData);
		return image;
	}

    CImage::Ref CDeviceGL::CreateImage2D(EFormat format, EImageUsageFlags usage, uint32_t width,
        uint32_t height, uint32_t mipLevels, uint32_t arrayLayers,
        uint32_t sampleCount, const void* initialData)
    {
        CImageGL::Ref image = std::make_shared<CImageGL>(this, format, usage, width, height,
            mipLevels, arrayLayers, sampleCount, initialData);
        return image;
    }

	CImage::Ref CDeviceGL::CreateImage3D(EFormat format, EImageUsageFlags usage, uint32_t width, uint32_t height, uint32_t depth, uint32_t mipLevels, uint32_t arrayLayers, uint32_t sampleCount, const void * initialData)
	{
		CImageGL::Ref image = std::make_shared<CImageGL>(this, format, usage, width, height,depth,
			mipLevels, arrayLayers, sampleCount, initialData);
		return image;
	}

    CImageView::Ref CDeviceGL::CreateImageView(const CImageViewDesc& desc, CImage::Ref image)
    {
        CImageGL::Ref cimage = std::static_pointer_cast<CImageGL>(image);
        CImageViewGL::Ref imageView = std::make_shared<CImageViewGL>(this, desc, cimage);
        return imageView;
    }

	CSampler::Ref CDeviceGL::CreateSampler(const CSamplerDesc & desc)
	{
		CSamplerGL::Ref sampler = std::make_shared<CSamplerGL>(this, desc);
		return sampler;
	}

}