#pragma once
#include "ComputeContext.h"

namespace RHI
{

    class RHI_EXPORT IRenderContext
    {
    public:
        typedef std::shared_ptr<IRenderContext> Ref;
        virtual void BindRenderPipeline(CPipeline::Ref pipeline) = 0;
        virtual void SetViewport(const CViewportDesc& viewportDesc) = 0;
        virtual void SetScissor(const CRect2D& scissor) = 0;
        virtual void SetBlendConstants(const std::array<float, 4>& blendConstants) = 0;
        virtual void SetStencilReference(uint32_t reference) = 0;
        virtual void BindRenderDescriptorSet(uint32_t set, CDescriptorSet::Ref descriptorSet) = 0;
        virtual void BindIndexBuffer(CBuffer::Ref buffer, size_t offset, EFormat format) = 0;
        virtual void BindVertexBuffer(uint32_t binding, CBuffer::Ref buffer, size_t offset) = 0;
        virtual void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex,
            uint32_t firstInstance) = 0;
        virtual void DrawIndexed(uint32_t indexCount, uint32_t instanceCount,
            uint32_t firstIndex, int32_t vertexOffset,
            uint32_t firstInstance) = 0;
        virtual void DrawIndirect(CBuffer::Ref buffer, size_t offset, uint32_t drawCount, uint32_t stride) = 0;
        virtual void DrawIndexedIndirect(CBuffer::Ref buffer, size_t offset, uint32_t drawCount, uint32_t stride) = 0;

        virtual void FinishRecording() = 0;
       
    };

    class RHI_EXPORT IParallelRenderContext
    {
    public:
        typedef std::shared_ptr<IParallelRenderContext> Ref;
        virtual ~IParallelRenderContext() = default;
        virtual IRenderContext::Ref CreateRenderContext(uint32_t subpass) = 0;
        virtual void FinishRecording() = 0;
    };

} /* namespace RHI */
