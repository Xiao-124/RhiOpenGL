#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "../CommandQueue.h"
#include "FormatGL.h"
namespace RHI
{
	enum class CMD
	{

		CmdClearImage,
		CmdCopyBuffer,
		CmdCopyImage,
		CmdCopyBufferToImage,
		CmdCopyImageToBuffer,
		CmdBlitImage,
		CmdResolveImage,

		CmdBindComputePipeline,
		CmdBindComputeDescriptorSet,
		CmdDispatch,
		CmdDispatchIndirect,


		CmdBindRenderPipeline,
		CmdSetViewPort,
		CmdSetScissor,
		CmdSetBlendConstants,
		CmdSetStencilReference,
		CmdBindRenderDescriptorSet,
		CmdBindIndexBuffer,
		CmdBindVertexBuffers,
		CmdDraw,
		CmdDrawIndexed,
		CmdDrawIndirect,
		CmdDrawIndexedIndirect,

		CmdBeginRenderPass,
		CmdNextSubpass,
		CmdEndRenderPass,

		

		
	};

	struct CMDArgument
	{
		CMD cmd;
		std::shared_ptr<void> dec;
	};

	struct ClearImageInfo
	{
		GLuint image;
		const CClearValue clearValue;
		const CImageSubresourceRange range;
	};

	struct CopyBufferInfo
	{
		GLuint src;
		GLuint dst;
		const std::vector<CBufferCopy>& regions;
	};

	struct CopyImageInfo
	{
		GLuint src;
		GLuint dst;
		const std::vector<CImageCopy>& regions;
	};

	struct CopyBufferToImageInfo
	{

	};

	struct CopyImageToBufferInfo
	{

	};

	struct BlitImageInfo
	{

	};

	struct ResolveImageInfo
	{


	};

	struct DispatchInfo
	{

	};

	struct DispatchIndirectInfo
	{

	};




	struct BindVertexInfo
	{
		GLuint vaobj;
		GLuint bindingindex;
		GLuint buffer;
		GLintptr offset;
		GLsizei stride;
	};

	struct DrawInfo
	{
		GLenum mode;
		GLint first;
		GLsizei count;
	};

	struct BindElementInfo
	{
		GLuint vaobj;
		GLuint buffer;
	};

	

	

	

	


	class GLCommandBuffer;
	class CPipelineGL;
	class CDescriptorSetGL;
	class CRenderPassGL;
	class CRenderPassContextGL;

	void CmdClearImage(GLCommandBuffer& com, GLuint image, const CClearValue& clearValue, 
		const CImageSubresourceRange& range);
	void CmdCopyBuffer(GLCommandBuffer& com, GLuint src, GLuint dst,const std::vector<CBufferCopy>& regions);
	void CmdCopyImage(GLCommandBuffer& com, GLuint src, GLuint dst,const std::vector<CImageCopy>& regions);
	void CmdCopyBufferToImage(GLCommandBuffer& com, GLuint src, GLuint dst,
		const std::vector<CBufferImageCopy>& regions);
	void CmdCopyImageToBuffer(GLCommandBuffer& com, GLuint src, GLuint dst,
		const std::vector<CBufferImageCopy>& regions);
	void CmdBlitImage(GLCommandBuffer& com, GLuint src, GLuint dst, const std::vector<CImageBlit>& regions,
		EFilter filter);
	void CmdResolveImage(GLCommandBuffer& com, GLuint src, GLuint dst, const std::vector<CImageResolve>& regions);

	void CmdBindComputePipeline(GLCommandBuffer& com, std::shared_ptr<CPipelineGL> pipeline);
	void CmdBindComputeDescriptorSet(GLCommandBuffer& com, std::shared_ptr<CDescriptorSetGL> descriptorSet);
	void CmdDispatch(GLCommandBuffer& com, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
	void CmdDispatchIndirect(GLCommandBuffer& com, GLuint buffer, size_t offset);

	void CmdBindRenderPipeline(GLCommandBuffer& com, std::shared_ptr<CPipelineGL> pipeline);
	void CmdSetViewPort(GLCommandBuffer& com, const CViewportDesc& viewportDesc);
	void CmdSetScissor(GLCommandBuffer& com, const CRect2D& scissor);
	void CmdSetBlendConstants(GLCommandBuffer& com, const std::array<float, 4>& blendConstants);
	void CmdSetStencilReference(GLCommandBuffer& com, uint32_t reference);
	void CmdBindRenderDescriptorSet(GLCommandBuffer& com, std::shared_ptr<CDescriptorSetGL> descriptorSet);
	void CmdBindIndexBuffer(GLCommandBuffer& com, GLuint vaobj, GLuint buffer);
	void CmdBindVertexBuffers(GLCommandBuffer& com, GLuint vaobj,
		GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
	void CmdDraw(GLCommandBuffer& com, GLenum mode, GLint first, GLsizei count);
	void CmdDrawIndexed(GLCommandBuffer& com, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex,
		int32_t vertexOffset, uint32_t firstInstance);
	void CmdDrawIndirect(GLCommandBuffer& com, GLuint buffer, size_t offset, 
		uint32_t drawCount, uint32_t stride);
	void CmdDrawIndexedIndirect(GLCommandBuffer& com, GLuint buffer, size_t offset, uint32_t drawCount,
		uint32_t stride);

	void CmdBeginRenderPass(GLCommandBuffer& com, std::shared_ptr<CRenderPassContextGL> render);
	void CmdNextSubpass(GLCommandBuffer& com, std::shared_ptr<CRenderPassContextGL> render);
	void CmdEndRenderPass(GLCommandBuffer& com, std::shared_ptr<CRenderPassContextGL> render);


}