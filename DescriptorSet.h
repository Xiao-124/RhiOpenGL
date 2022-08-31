#pragma once
#include "ShaderModule.h"
#include <memory>

namespace RHI
{

    enum class RHI_EXPORT EDescriptorType
    {
        Sampler,
        Image,
        StorageImage,
        UniformTexelBuffer,
        StorageTexelBuffer,
        UniformBuffer,
        StorageBuffer,
        UniformBufferDynamic,
        StorageBufferDynamic,
        InputAttachment
    };


    struct RHI_EXPORT CDescriptorSetLayoutBinding
    {
        uint32_t Binding;
        EDescriptorType Type;
        uint32_t Count;
        EShaderStageFlags StageFlags;
    };


    class RHI_EXPORT CDescriptorSet
    {
    public:
        typedef std::shared_ptr<CDescriptorSet> Ref;

        virtual ~CDescriptorSet() = default;

        virtual void BindBuffer(CBuffer::Ref buffer, size_t offset, size_t range, uint32_t binding = 0) = 0;
        virtual void BindConstants(const void* data, size_t size, uint32_t binding, uint32_t index = 0) = 0;
        virtual void BindImageView(CImageView::Ref imageView, uint32_t binding, uint32_t index = 0) = 0;
        virtual void BindSampler(CSampler::Ref sampler, uint32_t binding, uint32_t index = 0) = 0;
        virtual void BindBufferView(CBufferView::Ref bufferView, uint32_t binding, uint32_t index = 0) = 0;
        virtual void SetDynamicOffset(size_t offset, uint32_t binding, uint32_t index = 0) = 0;
        virtual void BindImage(CImage::Ref image, uint32_t binding, uint32_t index = 0) = 0;
    };

    class RHI_EXPORT CDescriptorSetLayout: public std::enable_shared_from_this<CDescriptorSetLayout>
    {
    public:
        typedef std::shared_ptr<CDescriptorSetLayout> Ref;
        virtual ~CDescriptorSetLayout() = default;
        virtual CDescriptorSet::Ref CreateDescriptorSet() = 0;
    };

   

}
