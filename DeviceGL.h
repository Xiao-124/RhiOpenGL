#pragma once
#include "CommandQueue.h"
#include <memory>
#include "RHIExport.h"
namespace RHI
{
#ifdef  _GLEW_USE
	class RHI_EXPORT CDeviceGL:public std::enable_shared_from_this<CDeviceGL>
#else
	class RHI_EXPORT CDeviceGL :public QOpenGLWindow, protected QOpenGLFunctions_4_5_Core
#endif
	{
	public:
		typedef std::shared_ptr<CDeviceGL>  Ref;
		typedef std::weak_ptr<CDeviceGL>   WeakRef;
#ifndef  _GLEW_USE
		QOpenGLContext *_context;
#endif
		CDeviceGL();  
        CBuffer::Ref CreateBuffer(size_t size, EBufferUsageFlags usage,
            const void* initialData = nullptr);
        CPipeline::Ref CreatePipeline(const CPipelineDesc& desc);
        CShaderModule::Ref CreateShaderModule(EShaderStageFlags flags, std::string sources);  

        CRenderPass::Ref CreateRenderPass(const CRenderPassDesc& desc);
        CCommandQueue::Ref CreateCommandQueue();

        CDescriptorSetLayout::Ref CreateDescriptorSetLayout();
        CPipelineLayout::Ref CreatePipelineLayout(const std::vector<CDescriptorSetLayout::Ref>& setLayouts);

		CImage::Ref CreateImage1D(EFormat format, EImageUsageFlags usage, uint32_t width,
			uint32_t mipLevels = 1, uint32_t arrayLayers = 1,
			uint32_t sampleCount = 1, const void* initialData = nullptr);

        CImage::Ref CreateImage2D(EFormat format, EImageUsageFlags usage, uint32_t width,
			uint32_t height, uint32_t mipLevels = 1, uint32_t arrayLayers = 1,
            uint32_t sampleCount = 1, const void* initialData = nullptr);

		CImage::Ref CreateImage3D(EFormat format, EImageUsageFlags usage, uint32_t width,
			uint32_t height, uint32_t depth, uint32_t mipLevels = 1,
			uint32_t arrayLayers = 1, uint32_t sampleCount = 1,
			const void* initialData = nullptr);

        CImageView::Ref CreateImageView(const CImageViewDesc& desc, CImage::Ref image);
		CSampler::Ref CreateSampler(const CSamplerDesc& desc);


    private:
        friend class CCommandQueueGL; 
        
	};

    

   

  
}