#pragma once
#include "CommandBufferGL.h"
#include "../CommandQueue.h"
#include "../Resources.h"
#include "PipelineGL.h"
#include "DescriptorSetGL.h"
namespace RHI
{

    class CCommandQueueGL;
    class CRenderPassContextGL: public std::enable_shared_from_this<CRenderPassContextGL>,
        public IParallelRenderContext
    {
    public:
        typedef std::shared_ptr <CRenderPassContextGL> Ref;
        std::vector<CClearValue> ClearValues;
        uint32_t DealSubPass = 0;
        CRenderPassContextGL(std::shared_ptr<CCommandQueueGL> cmdList, CRenderPass::Ref renderPass,
            std::vector<CClearValue> clearValues);
        ~CRenderPassContextGL() override;

        std::shared_ptr<CCommandQueueGL> GetCmdQueue() const { return CmdQueue; }
        CRenderPass::Ref GetRenderPass() const { return RenderPass; }
        GLCommandBuffer& GetCommandBuffer(uint32_t subpass)
        {
            return SubpassInfos[subpass];
        }      
        IRenderContext::Ref CreateRenderContext(uint32_t subpass) override;

        void EnqueueCommandBuffer(GLCommandBuffer& buffer, int subpass) { SubpassInfos[subpass] = buffer; }
        void FinishRecording() override;
        GLuint GetFrame(uint32_t subpass) { return Frame[subpass]; }
        
    private:
        std::shared_ptr<CCommandQueueGL> CmdQueue;
        CRenderPass::Ref RenderPass;     
        std::vector<GLCommandBuffer> SubpassInfos;
        std::vector<GLuint> Frame;
    };


    class CCommandContextGL : public ICopyContext, public IComputeContext, public IRenderContext
    {
    public:
        typedef std::shared_ptr<CCommandContextGL> Ref;
        explicit CCommandContextGL(const std::shared_ptr<CCommandQueueGL>& cmdList);
        explicit CCommandContextGL(const CRenderPassContextGL::Ref& renderPassContext,
            uint32_t subpass);
        ~CCommandContextGL() override;
        GLCommandBuffer& GetCmdBuffer() { return CmdBuffer; }

        // Copy commands
        void ClearImage(CImage::Ref image, const CClearValue& clearValue,
            const CImageSubresourceRange& range) override;
        void CopyBuffer(CBuffer::Ref src, CBuffer::Ref dst, const std::vector<CBufferCopy>& regions) override;
        void CopyImage(CImage::Ref src, CImage::Ref dst, const std::vector<CImageCopy>& regions) override;
        void CopyBufferToImage(CBuffer::Ref src, CImage::Ref dst,
            const std::vector<CBufferImageCopy>& regions) override;
        void CopyImageToBuffer(CImage::Ref src, CBuffer::Ref dst,
            const std::vector<CBufferImageCopy>& regions) override;
        void BlitImage(CImage::Ref src, CImage::Ref dst, const std::vector<CImageBlit>& regions,
            EFilter filter) override;
        void ResolveImage(CImage::Ref src, CImage::Ref dst, const std::vector<CImageResolve>& regions) override;

        // Compute commands
        void BindComputePipeline(CPipeline::Ref pipeline) override;
        void BindComputeDescriptorSet(uint32_t set, CDescriptorSet::Ref descriptorSet) override;
        void Dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) override;
        void DispatchIndirect(CBuffer::Ref buffer, size_t offset) override;

        // Render commands
        void BindRenderPipeline(CPipeline::Ref pipeline) override;
        void SetViewport(const CViewportDesc& viewportDesc) override;
        void SetScissor(const CRect2D& scissor) override;
        void SetBlendConstants(const std::array<float, 4>& blendConstants) override;
        void SetStencilReference(uint32_t reference) override;
        void BindRenderDescriptorSet(uint32_t set, CDescriptorSet::Ref descriptorSet) override;
        void BindIndexBuffer(CBuffer::Ref buffer, size_t offset, EFormat format) override;
        void BindVertexBuffer(uint32_t binding, CBuffer::Ref buffer, size_t offset) override;
        void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex,
            uint32_t firstInstance) override;
        void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex,
            int32_t vertexOffset, uint32_t firstInstance) override;
        void DrawIndirect(CBuffer::Ref buffer, size_t offset, uint32_t drawCount, uint32_t stride) override;
        void DrawIndexedIndirect(CBuffer::Ref buffer, size_t offset, uint32_t drawCount,
            uint32_t stride) override;

        // Finish this context and save the commands into the command list
        void FinishRecording() override;

    protected:        
        GLCommandBuffer CmdBuffer;
    private:
        std::shared_ptr<CCommandQueueGL> CmdQueue;      
        CRenderPassContextGL::Ref RenderPassContext;
        uint32_t SubpassIndex; 
        CPipelineGL::Ref CurrPipeline;
    };

}
