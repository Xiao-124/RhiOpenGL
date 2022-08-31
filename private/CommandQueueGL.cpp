#include "CommandQueueGL.h"
#include "CommandContextGL.h"
#include "DescriptorSetGL.h"
#include "RenderPassGL.h"
namespace RHI
{

	CCommandQueueGL::CCommandQueueGL(CDeviceGL* p, EQueueType queueType):Parent(p),Type(queueType)
	{
#ifndef  _GLEW_USE			
		QOpenGLContext* context = Parent->_context;
		QSurface* sur = context->surface();
		context->makeCurrent(sur);
		initializeOpenGLFunctions();
#endif
		funsMap[CMD::CmdBindRenderPipeline] = std::bind(&CCommandQueueGL::glCmdBindPipeline, 
			this, std::placeholders::_1);
		funsMap[CMD::CmdBindVertexBuffers] = std::bind(&CCommandQueueGL::glCmdBindVertexBuffers, 
			this, std::placeholders::_1);
		funsMap[CMD::CmdBindIndexBuffer] = std::bind(&CCommandQueueGL::glCmdBindElementBuffer, 
			this, std::placeholders::_1);
		funsMap[CMD::CmdDraw] = std::bind(&CCommandQueueGL::glCmdDraw, this, std::placeholders::_1);
		funsMap[CMD::CmdBindRenderDescriptorSet] = std::bind(&CCommandQueueGL::glCmdBindDescriptorSet, 
			this, std::placeholders::_1);

		funsMap[CMD::CmdBeginRenderPass] = std::bind(&CCommandQueueGL::glCmdBeginRenderPass,
			this, std::placeholders::_1);
		funsMap[CMD::CmdNextSubpass] = std::bind(&CCommandQueueGL::glCmdNextSubpass,
			this, std::placeholders::_1);
		funsMap[CMD::CmdEndRenderPass] = std::bind(&CCommandQueueGL::glCmdEndRenderPass,
			this, std::placeholders::_1);
		funsMap[CMD::CmdSetViewPort] = std::bind(&CCommandQueueGL::glCmdSetViewPort,
			this, std::placeholders::_1);
	}



	CCommandQueueGL::~CCommandQueueGL(){}

	ICopyContext::Ref CCommandQueueGL::CreateCopyContext()
	{
		return std::make_shared<CCommandContextGL>(
			std::static_pointer_cast<CCommandQueueGL>(shared_from_this()));
	}

	IComputeContext::Ref CCommandQueueGL::CreateComputeContext()
	{
		return std::make_shared<CCommandContextGL>(
			std::static_pointer_cast<CCommandQueueGL>(shared_from_this()));
	}

	IParallelRenderContext::Ref
		CCommandQueueGL::CreateParallelRenderContext(CRenderPass::Ref renderPass,
			const std::vector<CClearValue>& clearValues)
	{
		return std::make_shared<CRenderPassContextGL>(
			std::static_pointer_cast<CCommandQueueGL>(shared_from_this()), renderPass, clearValues);

	}
  

    void CCommandQueueGL::Finish()
    {
#ifndef  _GLEW_USE			
		QOpenGLContext* context = Parent->_context;
		QSurface* sur = context->surface();
		context->makeCurrent(sur);
#endif
		for (auto& it : Sections)
		{
			for (auto& arg : it.cmdArguments)
			{
				if (funsMap.find(arg.cmd) != funsMap.end())
				{
					funsMap[arg.cmd](arg.dec);
				}
			}
		}
		if(Sections.size() > 0)
			Sections.clear();
    }

    void CCommandQueueGL::Flush()
    {

    }

	void CCommandQueueGL::EnqueueCommandList(std::vector<GLCommandBuffer>& buffer)
	{
		Sections.insert(Sections.end(), buffer.begin(), buffer.end());
	}

	void CCommandQueueGL::EnqueueCommandBufffer(GLCommandBuffer& buffer)
	{
		Sections.push_back(buffer);
	}

	void CCommandQueueGL::glCmdBindPipeline(std::shared_ptr<void>& desc)
	{	
		auto pipeline = std::static_pointer_cast<CPipelineGL>(desc);	
		glBindProgramPipeline(pipeline->GetHandle());
		glBindVertexArray(pipeline->VAO);
		CBlendDesc bDesc = pipeline->BlendState;
		CDepthStencilDesc sDesc = pipeline->DepthStencilState;
		CMultisampleStateDesc mdesc = pipeline->MultisampleState;
		uint32_t patch = pipeline->PatchControlPoints;
		EPrimitiveTopology primit = pipeline->PrimitiveTopology;
		CRasterizerDesc rdesc = pipeline->RasterizerState;
		uint32_t sub = pipeline->Subpass;

		
		if (sDesc.DepthEnable)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GLCast(sDesc.DepthCompareOp));
			glDepthMask(sDesc.DepthWriteEnable);
		}
		

		
		if (sDesc.StencilEnable)
		{
			CStencilOpState stenci = sDesc.Front;
			CStencilOpState bstenci = sDesc.Back;
			glEnable(GL_STENCIL_TEST);
			glStencilFuncSeparate(GL_FRONT, GLCast(stenci.CompareOp), stenci.CompareMask, stenci.WriteMask);
			glStencilOpSeparate(GL_FRONT, GLCast(stenci.FailOp), GLCast(stenci.DepthFailOp), GLCast(stenci.PassOp));

			glStencilFuncSeparate(GL_BACK, GLCast(bstenci.CompareOp), bstenci.CompareMask, bstenci.WriteMask);
			glStencilOpSeparate(GL_BACK, GLCast(bstenci.FailOp), GLCast(bstenci.DepthFailOp), GLCast(bstenci.PassOp));
		}

		if (bDesc.IndependentBlendEnable)
		{
			if (bDesc.RenderTargets[0].BlendEnable)
			{
				CRenderTargetBlendDesc r = bDesc.RenderTargets[0];
				glEnable(GL_BLEND);
				glBlendFuncSeparatei(0, GLCast(r.SrcBlend), GLCast(r.DestBlend),
					GLCast(r.SrcBlendAlpha), GLCast(r.DestBlendAlpha));
				r.BlendOp;
				r.RenderTargetWriteMask;
				r.BlendOpAlpha;
				glBlendEquationSeparatei(0, GLCast(r.BlendOp), GLCast(r.BlendOpAlpha));
				glColorMaski(0, GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

			}

		}

		if (mdesc.AlphaToCoverageEnable)
		{
			glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		}

		if (mdesc.MultisampleEnable)
		{
			glEnable(GL_MULTISAMPLE);
			glSampleMaski(0, mdesc.SampleMask);
		}
		glCullFace(GLCast(rdesc.CullMode));
		if (rdesc.FrontFaceCCW)
		{
			glFrontFace(GL_CCW);
		}
		else
		{
			glFrontFace(GL_CW);
		}

		if (rdesc.DepthClampEnable)
		{
			glEnable(GL_DEPTH_CLAMP);

		}
		glPolygonMode(GL_FRONT_AND_BACK, GLCast(rdesc.PolygonMode));

		if (rdesc.DepthBiasEnable)
		{
			glEnable(GL_DEPTH_BIAS);
			rdesc.DepthBiasClamp;
			rdesc.DepthBiasConstantFactor;
			rdesc.DepthBiasSlopeFactor;
			
		}	
		
	}

	void CCommandQueueGL::glCmdBindVertexBuffers(std::shared_ptr<void>& desc)
	{
		auto cdesc = std::static_pointer_cast<BindVertexInfo>(desc);
		glVertexArrayVertexBuffer(cdesc->vaobj, cdesc->bindingindex, cdesc->buffer, cdesc->offset,
				cdesc->stride);
	}

	void CCommandQueueGL::glCmdBindElementBuffer(std::shared_ptr<void>& desc)
	{
		auto cdesc = std::static_pointer_cast<BindElementInfo>(desc);
		glVertexArrayElementBuffer(cdesc->vaobj, cdesc->buffer);
	}

	void CCommandQueueGL::glCmdDraw(std::shared_ptr<void>& desc)
	{
		auto cdesc = std::static_pointer_cast<DrawInfo>(desc);
		glDrawArrays(cdesc->mode, cdesc->first, cdesc->count);
		
	}


	void CCommandQueueGL::glCmdBindDescriptorSet(std::shared_ptr<void>& desc)
	{
		auto cdesc = std::static_pointer_cast<CDescriptorSetGL>(desc);
		ArrayBindings binding = cdesc->GetResourceBinding().GetSetBindings();
		for (auto& impl : binding)
		{
			std::vector<BindingInfo> v_binding = impl.second;
			for (int i = 0; i < v_binding.size(); i++)
			{
				if (v_binding[i].BufferHandle)
				{
					GLuint handle = v_binding[i].BufferHandle->GetHandle();
					glBindBufferRange(GL_UNIFORM_BUFFER, impl.first, handle, v_binding[i].Offset, v_binding[i].Range);
				}
				else if (v_binding[i].SamplerHandle)
				{
					glBindSampler(impl.first, v_binding[i].SamplerHandle->getHandle());
				}
				else if (v_binding[i].ImageView)
				{
					glBindTextureUnit(impl.first, v_binding[i].ImageView->GetGLImageView());
				}
				else if (v_binding[i].Image)
				{
					glBindTextureUnit(impl.first, v_binding[i].Image->getHandle());
				}
			}

		}
	}



	void CCommandQueueGL::glCmdBeginRenderPass(std::shared_ptr<void>& desc)
	{
		auto render = std::static_pointer_cast<CRenderPassContextGL>(desc);
		GLuint frame = render->GetFrame(render->DealSubPass);
		glBindFramebuffer(GL_FRAMEBUFFER, frame);
		GLenum ClearBit = 0;
		
		CClearValue& value = render->ClearValues[render->DealSubPass];
		if (value.ColorFloat32[0] >= 0 && value.ColorFloat32[1] >= 0 &&
			value.ColorFloat32[2] >= 0 && value.ColorFloat32[3] >= 0)
		{
			ClearBit |= GL_COLOR_BUFFER_BIT;
			glClearColor(value.ColorFloat32[0], value.ColorFloat32[1], value.ColorFloat32[2], value.ColorFloat32[3]);
		}
		if (value.DepthStencilValue.Depth >= 0)
		{
			ClearBit |= GL_DEPTH_BUFFER_BIT;
			glClearDepth(value.DepthStencilValue.Depth);
		}
		if (value.DepthStencilValue.Stencil >= 0)
		{
			ClearBit |= GL_STENCIL_BUFFER_BIT;
			glClearStencil(value.DepthStencilValue.Stencil);
		}
		glClear(ClearBit);
		render->DealSubPass ++;
		
	}

	void CCommandQueueGL::glCmdNextSubpass(std::shared_ptr<void>& desc)
	{
		auto render = std::static_pointer_cast<CRenderPassContextGL>(desc);
		GLuint frame = render->GetFrame(render->DealSubPass);
		glBindFramebuffer(GL_FRAMEBUFFER, frame);
		GLenum ClearBit = 0;
		CClearValue& value = render->ClearValues[render->DealSubPass];
		if (value.ColorFloat32[0] >= 0 && value.ColorFloat32[1] >= 0 &&
			value.ColorFloat32[2] >= 0 && value.ColorFloat32[3] >= 0)
		{
			ClearBit |= GL_COLOR_BUFFER_BIT;
			glClearColor(value.ColorFloat32[0], value.ColorFloat32[1], value.ColorFloat32[2], value.ColorFloat32[3]);
		}
		if (value.DepthStencilValue.Depth >= 0)
		{
			ClearBit |= GL_DEPTH_BUFFER_BIT;
			glClearDepth(value.DepthStencilValue.Depth);
		}
		if (value.DepthStencilValue.Stencil >= 0)
		{
			ClearBit |= GL_STENCIL_BUFFER_BIT;
			glClearStencil(value.DepthStencilValue.Stencil);
		}
		glClear(ClearBit);
		render->DealSubPass++;
	}

	void CCommandQueueGL::glCmdEndRenderPass(std::shared_ptr<void>& desc)
	{
		auto render = std::static_pointer_cast<CRenderPassContextGL>(desc);
		GLuint frame = render->GetFrame(render->DealSubPass-1);
		render->DealSubPass = 0;
		auto pass = std::static_pointer_cast<CRenderPassGL>(render->GetRenderPass());
		
		glBlitNamedFramebuffer(frame, 0, 0, 0, 800, 600, pass->Area.Offset.X, pass->Area.Offset.Y, 
			pass->Area.Extent.Width, pass->Area.Extent.Height,
			GL_COLOR_BUFFER_BIT, GL_NEAREST);


		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void CCommandQueueGL::glCmdSetViewPort(std::shared_ptr<void>& desc)
	{
		auto port = std::static_pointer_cast<CViewportDesc>(desc);
		glViewport(port->X, port->Y, port->Width, port->Height);
	}

	void CCommandQueueGL::glCmdSetScissor(std::shared_ptr<void>& desc)
	{
	}

	void CCommandQueueGL::glCmdCopyBuffer(std::shared_ptr<void>& desc)
	{
		auto copy = std::static_pointer_cast<CopyBufferInfo>(desc);
		for (int i = 0; i < copy->regions.size(); i++)
		{
			glCopyNamedBufferSubData(copy->src, copy->dst, copy->regions[i].SrcOffset, 
				copy->regions[i].DstOffset, copy->regions[i].Size);
		}
	}

	void CCommandQueueGL::glCmdCopyImage(std::shared_ptr<void>& desc)
	{
		auto copy = std::static_pointer_cast<CopyImageInfo>(desc);
		glCopyImageSubData(copy->src, GL_TEXTURE_2D, copy->regions[0].SrcSubresource.BaseArrayLayer,
			copy->regions[0].SrcOffset.X, copy->regions[0].SrcOffset.Y, copy->regions[0].SrcOffset.Z,
			copy->dst, GL_TEXTURE_2D, copy->regions[0].DstSubresource.BaseArrayLayer, copy->regions[0].DstOffset.X,
			copy->regions[0].DstOffset.Y, copy->regions[0].DstOffset.Z, copy->regions[0].Extent.Width, copy->regions[0].Extent.Height,
			copy->regions[0].Extent.Depth
		);
	}






}