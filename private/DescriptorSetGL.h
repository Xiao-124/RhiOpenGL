#pragma once
#include "../DescriptorSet.h"
#include <vector>

#include "BufferGL.h"
#include "SamplerGL.h"
#include "ResourceBindingsGL.h"
#include "CommandBufferGL.h"
namespace RHI
{
    class CDescriptorSetLayoutGL;

    class CDescriptorSetGL: public CDescriptorSet
    {
    public:
        typedef std::shared_ptr<CDescriptorSetGL> Ref;

        explicit CDescriptorSetGL(std::shared_ptr<CDescriptorSetLayoutGL> layout);
        ~CDescriptorSetGL() override;

        void BindBuffer(CBuffer::Ref buffer, size_t offset, size_t range, uint32_t binding = 0) override;
		void BindConstants(const void* data, size_t size, uint32_t binding, uint32_t index = 0) {}
        void BindImageView(CImageView::Ref imageView, uint32_t binding, uint32_t index = 0) override;
        void BindSampler(CSampler::Ref sampler, uint32_t binding, uint32_t index = 0) override;
        void BindBufferView(CBufferView::Ref bufferView, uint32_t binding, uint32_t index = 0) override;
		void SetDynamicOffset(size_t offset, uint32_t binding, uint32_t index = 0) {}
        void BindImage(CImage::Ref image, uint32_t binding, uint32_t index = 0) override;

        // Internal API 
        bool IsContentDirty() const { return ResourceBindings.IsDirty(); }
        void SetUsed() { bIsUsed = true; }
        CResourceBindings& GetResourceBinding() { return ResourceBindings; }

    private:   
        std::shared_ptr<CDescriptorSetLayoutGL> Layout; 
        CResourceBindings ResourceBindings;   
        bool bIsUsed = false;
    };

}
