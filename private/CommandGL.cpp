#include "CommandGL.h"
#include "CommandBufferGL.h"
#include "RenderPassGL.h"
#include "CommandContextGL.h"
namespace RHI
{
	
	void CmdBindRenderPipeline(GLCommandBuffer& com, std::shared_ptr<CPipelineGL> pipeline)
	{
		com.push(CMD::CmdBindRenderPipeline, pipeline);
	}

	void CmdBindVertexBuffers(GLCommandBuffer& com, GLuint vaobj,
		GLuint bindingindex,GLuint buffer,GLintptr offset,GLsizei stride)
	{
		BindVertexInfo info{ vaobj, bindingindex, buffer, offset,stride };
		std::shared_ptr<BindVertexInfo> arg = std::make_shared<BindVertexInfo>(info);
		com.push(CMD::CmdBindVertexBuffers, arg);
	}

	void CmdBindIndexBuffer(GLCommandBuffer& com,GLuint vaobj, GLuint buffer)
	{
		BindElementInfo info{ vaobj, buffer };
		std::shared_ptr<BindElementInfo> arg = std::make_shared<BindElementInfo>(info);
		com.push(CMD::CmdBindIndexBuffer, arg);
	}


	void CmdDraw(GLCommandBuffer& com, GLenum mode, GLint first, GLsizei count)
	{
		DrawInfo info{ mode, first,count };
		std::shared_ptr<DrawInfo> arg = std::make_shared<DrawInfo>(info);
		com.push(CMD::CmdDraw, arg);
	}


	void CmdBindRenderDescriptorSet(GLCommandBuffer &com, std::shared_ptr<CDescriptorSetGL> descriptorSet)
	{
		com.push(CMD::CmdBindRenderDescriptorSet, descriptorSet);
	}
	
	void CmdClearImage(GLCommandBuffer & com, GLuint image, const CClearValue & clearValue, const CImageSubresourceRange & range)
	{
		ClearImageInfo info{ image, clearValue, range };
		auto desc = std::make_shared<ClearImageInfo>(info);
		com.push(CMD::CmdClearImage, desc);
	}

	void CmdCopyBuffer(GLCommandBuffer& com, GLuint src, GLuint dst,
		const std::vector<CBufferCopy>& regions)
	{
		CopyBufferInfo info{ src, dst, regions };
		auto desc = std::make_shared<CopyBufferInfo>(info);
		com.push(CMD::CmdCopyBuffer, desc);
	}

	void CmdSetViewPort(GLCommandBuffer& com, const CViewportDesc& viewportDesc)
	{
		std::shared_ptr<CViewportDesc> desc = std::make_shared< CViewportDesc>(viewportDesc);
		com.push(CMD::CmdSetViewPort, desc);
	}

	void CmdSetScissor(GLCommandBuffer& com, const CRect2D& scissor)
	{
		std::shared_ptr<CRect2D> desc = std::make_shared<CRect2D>(scissor);
		com.push(CMD::CmdSetScissor, desc);
	}

	void CmdCopyImage(GLCommandBuffer& com, GLuint src, GLuint dst,
		const std::vector<CImageCopy>& regions)
	{
		CopyImageInfo info{ src, dst, regions };
		auto desc = std::make_shared<CopyImageInfo>(info);
		com.push(CMD::CmdCopyImage, desc);
	}



	void CmdBeginRenderPass(GLCommandBuffer& com, std::shared_ptr<CRenderPassContextGL> render)
	{
		
		com.push(CMD::CmdBeginRenderPass, render);
	}


	void CmdNextSubpass(GLCommandBuffer& com, std::shared_ptr<CRenderPassContextGL> render)
	{
		com.push(CMD::CmdNextSubpass, render);
	}


	void CmdEndRenderPass(GLCommandBuffer& com, std::shared_ptr<CRenderPassContextGL> render)
	{
		com.push(CMD::CmdEndRenderPass, render);
	}



}