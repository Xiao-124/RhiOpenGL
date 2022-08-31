#include "DescriptorSetGL.h"
#include "DescriptorSetLayoutGL.h"
#include "CommandBufferGL.h"
#include "SamplerGL.h"
namespace RHI
{
	CDescriptorSetGL::CDescriptorSetGL(std::shared_ptr<CDescriptorSetLayoutGL> layout)
		:Layout(layout)
	{

	}

	CDescriptorSetGL::~CDescriptorSetGL()
	{

	}

	void CDescriptorSetGL::BindBuffer(CBuffer::Ref buffer, size_t offset, size_t range, uint32_t binding)
	{
		CBufferGL::Ref cbuffer = std::static_pointer_cast<CBufferGL>(buffer);
		ResourceBindings.BindBuffer(cbuffer, offset, range, binding);
	}


	void CDescriptorSetGL::BindImageView(CImageView::Ref imageView, uint32_t binding, uint32_t index)
	{
		CImageViewGL::Ref image = std::static_pointer_cast<CImageViewGL>(imageView);
		ResourceBindings.BindImageView(image, binding);
	}

	void CDescriptorSetGL::BindSampler(CSampler::Ref sampler, uint32_t binding, uint32_t index)
	{
		CSamplerGL::Ref sam = std::static_pointer_cast<CSamplerGL>(sampler);
		ResourceBindings.BindSampler(sam, binding);
	}

	void CDescriptorSetGL::BindImage(CImage::Ref image, uint32_t binding, uint32_t index)
	{
		CImageGL::Ref cimage = std::static_pointer_cast<CImageGL>(image);
		ResourceBindings.BindImage(cimage, binding);
	}

	void CDescriptorSetGL::BindBufferView(CBufferView::Ref bufferView, uint32_t binding, uint32_t index) {}

	
}