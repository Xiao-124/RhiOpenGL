#include "RenderPassGL.h"
namespace RHI
{

	CRenderPassGL::CRenderPassGL(CDeviceGL* p, const CRenderPassDesc& desc):Parent(p)
	{
#ifndef  _GLEW_USE			
		QOpenGLContext* context = Parent->_context;
		QSurface* sur = context->surface();
		context->makeCurrent(sur);
		initializeOpenGLFunctions();
#endif
		for (int i = 0; i < desc.Attachments.size(); i++)
		{
			if (desc.Attachments[i].ImageView)
			{
				CImageViewGL::Ref image = std::static_pointer_cast<CImageViewGL>(desc.Attachments[i].ImageView);
				CAttachMentGL ment;
				ment.ImageView = image;
				Attachments.push_back(ment);
			}
			else if (desc.Attachments[i].Image)
			{
				CImageGL::Ref image = std::static_pointer_cast<CImageGL>(desc.Attachments[i].Image);
				CAttachMentGL ment;
				ment.Image = image;
				Attachments.push_back(ment);
			}

		}		
		SubpassDesc = desc.Subpasses;
		Layers = desc.Layers;
		Area.Offset.Set(0, 0);
		Area.Extent.Set(desc.Width, desc.Height);
	}

	CRenderPassGL::~CRenderPassGL(){}

	void CRenderPassGL::SetSize(uint32_t width, uint32_t height)
	{
		Area.Extent.Set(width, height);
	}


	GLuint CRenderPassGL::MakeFramebuffer(uint32_t subpass)
	{
		CSubpassDesc sub = SubpassDesc[subpass];
		GLuint frame;
		glCreateFramebuffers(1, &frame);
		sub.ColorAttachments;
		sub.DepthStencilAttachment;
		std::vector<GLenum> attachMents;
		
		for (int i = 0; i < sub.ColorAttachments.size(); i++)
		{
			if (sub.ColorAttachments[i] >= 0 && sub.ColorAttachments[i] < Attachments.size())
			{
				if (Attachments[sub.ColorAttachments[i]].ImageView)
				{
					CImageViewGL::Ref image = Attachments[sub.ColorAttachments[i]].ImageView;
					glNamedFramebufferTexture(frame, GL_COLOR_ATTACHMENT0 + i, image->GetImage()->getHandle(), 0);
				}
				else if (Attachments[sub.ColorAttachments[i]].Image)
				{
					CImageGL::Ref image = Attachments[sub.ColorAttachments[i]].Image;
					glNamedFramebufferTexture(frame, GL_COLOR_ATTACHMENT0 + i, image->getHandle(), 0);
				}
				attachMents.push_back(GL_COLOR_ATTACHMENT0 + i);
				
			}
		}
		
		
		if (sub.DepthStencilAttachment >= 0 && sub.DepthStencilAttachment < Attachments.size())
		{
			if (Attachments[sub.DepthStencilAttachment].ImageView) {
				CImageViewGL::Ref depth = Attachments[sub.DepthStencilAttachment].ImageView;
				glNamedFramebufferTexture(frame, GL_DEPTH_STENCIL_ATTACHMENT, depth->GetImage()->getHandle(), 0);
			}
			else if (Attachments[sub.DepthStencilAttachment].Image)
			{
				CImageGL::Ref depth = Attachments[sub.DepthStencilAttachment].Image;
				glNamedFramebufferTexture(frame, GL_DEPTH_STENCIL_ATTACHMENT, depth->getHandle(), 0);
				
			}
			
		}	
		if (glCheckNamedFramebufferStatus(frame,GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		if (attachMents.size() > 0)
		{
			glNamedFramebufferDrawBuffers(frame, attachMents.size(), attachMents.data());
		}
		return frame;
	}

}