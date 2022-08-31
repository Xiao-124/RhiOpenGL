#include "CommandContextGL.h"
#include "CommandQueueGL.h"
#include "RenderPassGL.h"
namespace RHI
{

    CRenderPassContextGL::CRenderPassContextGL(std::shared_ptr<CCommandQueueGL> cmdList, CRenderPass::Ref renderPass,
        std::vector<CClearValue> clearValues)
        : CmdQueue(std::move(cmdList))
        , RenderPass(std::move(renderPass))
        , ClearValues(std::move(clearValues))
    {
        auto render = std::static_pointer_cast<CRenderPassGL>(RenderPass);
        for (int i = 0; i < ClearValues.size(); i++)
        {
            GLuint frame = render->MakeFramebuffer(i);
            Frame.push_back(frame);
        }
		SubpassInfos.resize(ClearValues.size());
    }
    

    CRenderPassContextGL::~CRenderPassContextGL()
	{
		
	}


    IRenderContext::Ref CRenderPassContextGL::CreateRenderContext(uint32_t subpass)
    {
        return std::make_shared<CCommandContextGL>(shared_from_this(), subpass);
    }

    

    void CRenderPassContextGL::FinishRecording()
    {
        GLCommandBuffer buffer;
        CmdBeginRenderPass(buffer, shared_from_this());     
        std::vector<GLCommandBuffer> command;

        command.push_back(buffer);
        command.push_back(SubpassInfos[0]);
        for (int i = 1; i < ClearValues.size(); i++)
        {
            GLCommandBuffer sbuffer;
            CmdNextSubpass(sbuffer, shared_from_this());
            command.push_back(sbuffer);
            command.push_back(SubpassInfos[i]);
        }
        GLCommandBuffer ebuffer;
        CmdEndRenderPass(ebuffer, shared_from_this());
        command.push_back(ebuffer);

        CmdQueue->EnqueueCommandList(command);
        SubpassInfos.clear();
        SubpassInfos.resize(ClearValues.size());
    }



    CCommandContextGL::CCommandContextGL(const std::shared_ptr<CCommandQueueGL>& cmdList):CmdQueue(cmdList)
    {
        
    }

    CCommandContextGL::CCommandContextGL(const CRenderPassContextGL::Ref& renderPassContext,
        uint32_t subpass)
    {
        RenderPassContext = renderPassContext;
        SubpassIndex = subpass;
        
    }
    CCommandContextGL::~CCommandContextGL(){}

    void CCommandContextGL::ClearImage(CImage::Ref image, const CClearValue& clearValue,
        const CImageSubresourceRange& range)
    {
        
    }


    void CCommandContextGL::CopyBuffer(CBuffer::Ref src, CBuffer::Ref dst, const std::vector<CBufferCopy>& regions)
    {
      
    }

    void CCommandContextGL::CopyImage(CImage::Ref src, CImage::Ref dst, const std::vector<CImageCopy>& regions)
    {
       
           
    }


    void CCommandContextGL::CopyBufferToImage(CBuffer::Ref src, CImage::Ref dst,
        const std::vector<CBufferImageCopy>& regions)
    {
        
    }

    void CCommandContextGL::CopyImageToBuffer(CImage::Ref src, CBuffer::Ref dst,
        const std::vector<CBufferImageCopy>& regions)
    {

    }


    void CCommandContextGL::BlitImage(CImage::Ref src, CImage::Ref dst, const std::vector<CImageBlit>& regions,
        EFilter filter)
    {
        
    }

    void CCommandContextGL::ResolveImage(CImage::Ref src, CImage::Ref dst,
        const std::vector<CImageResolve>& regions)
    {

    }


    void CCommandContextGL::BindComputePipeline(CPipeline::Ref pipeline)
    {
       
    }


    void CCommandContextGL::BindComputeDescriptorSet(uint32_t set, CDescriptorSet::Ref descriptorSet)
    {
        
    }


    void CCommandContextGL::Dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ)
    {

    }

    void CCommandContextGL::DispatchIndirect(CBuffer::Ref buffer, size_t offset)
    {

    }


    void CCommandContextGL::BindRenderPipeline(CPipeline::Ref pipeline)
    {
        CurrPipeline = std::static_pointer_cast<CPipelineGL>(pipeline);
        CmdBindRenderPipeline(CmdBuffer, CurrPipeline);
    }


    void CCommandContextGL::SetViewport(const CViewportDesc& viewportDesc)
    {
		CmdSetViewPort(CmdBuffer, viewportDesc);
    }

    void CCommandContextGL::SetScissor(const CRect2D& scissor)
    {
		CmdSetScissor(CmdBuffer, scissor);
    }

    void CCommandContextGL::SetBlendConstants(const std::array<float, 4>& blendConstants)
    {

    }

    void CCommandContextGL::SetStencilReference(uint32_t reference)
    {

    }

    void CCommandContextGL::BindRenderDescriptorSet(uint32_t set, CDescriptorSet::Ref descriptorSet)
    {
        auto impl = std::static_pointer_cast<CDescriptorSetGL>(descriptorSet);
        CmdBindRenderDescriptorSet(CmdBuffer, impl);
    }

    void CCommandContextGL::BindIndexBuffer(CBuffer::Ref buffer, size_t offset, EFormat format)
    {
        CBufferGL::Ref cbuffer = std::static_pointer_cast<CBufferGL>(buffer);
        CmdBindIndexBuffer(CmdBuffer, CurrPipeline->VAO, cbuffer->GetHandle());
    }

    void CCommandContextGL::BindVertexBuffer(uint32_t binding, CBuffer::Ref buffer, size_t offset)
    {
        CBufferGL::Ref cbuffer = std::static_pointer_cast<CBufferGL>(buffer);
        CmdBindVertexBuffers(CmdBuffer, CurrPipeline->VAO, binding, cbuffer->GetHandle(), offset,
            CurrPipeline->BindingStride[binding]);
    }


    void CCommandContextGL::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex,
        uint32_t firstInstance)
    {      
        CmdDraw(CmdBuffer, CurrPipeline->Primit, firstVertex, vertexCount);
    }


    void CCommandContextGL::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex,
        int32_t vertexOffset, uint32_t firstInstance)
    {
       
    }


    void CCommandContextGL::DrawIndirect(CBuffer::Ref buffer, size_t offset, uint32_t drawCount, uint32_t stride)
    {

    }

    void CCommandContextGL::DrawIndexedIndirect(CBuffer::Ref buffer, size_t offset, uint32_t drawCount,
        uint32_t stride)
    {

    }


    void CCommandContextGL::FinishRecording()
    {
        if (CmdQueue)
        {
			CmdQueue->EnqueueCommandBufffer(CmdBuffer);
        }
        else
        {
            RenderPassContext->EnqueueCommandBuffer(CmdBuffer, SubpassIndex);
        }
        CmdBuffer.clear();
    }










}