#include "PipelineGL.h"
#include "FormatGL.h"
namespace RHI
{
	CPipelineGL::CPipelineGL(CDeviceGL* p, const CPipelineDesc& desc):Parent(p)
	{
#ifndef  _GLEW_USE			
		QOpenGLContext* context = Parent->_context;
		QSurface* sur = context->surface();
		context->makeCurrent(sur);
		initializeOpenGLFunctions();
#endif
		glCreateProgramPipelines(1, &PipelineHandle);
		AddShaderModule(desc.VS, GL_VERTEX_SHADER_BIT);
		AddShaderModule(desc.FS, GL_FRAGMENT_SHADER_BIT);
		AddShaderModule(desc.GS, GL_GEOMETRY_SHADER_BIT);
		
		
		glCreateVertexArrays(1, &VAO);
		for (int i = 0; i < desc.VertexAttributes.size(); i++)
		{
			CVertexInputAttributeDesc adesc = desc.VertexAttributes[i];
			CVertexInputBindingDesc bdesc = desc.VertexBindings[i];		
			glEnableVertexArrayAttrib(VAO, adesc.Location);
			if ((int)adesc.Format >= 110 && (int)adesc.Format <= 121)
			{
				glVertexArrayAttribLFormat(VAO, adesc.Location, bdesc.Stride, EFormatToGLBase(adesc.Format),
					adesc.Offset);
			}
			else
			{
				glVertexArrayAttribFormat(VAO, adesc.Location, bdesc.Stride,  EFormatToGLBase(adesc.Format),
					GL_FALSE, adesc.Offset);
			}
			glVertexArrayAttribBinding(VAO, adesc.Location, bdesc.Binding);
			if (BindingStride.find(bdesc.Binding) == BindingStride.end())
			{
				BindingStride[bdesc.Binding] = 0;
			}
			BindingStride[bdesc.Binding] += bdesc.Stride * 4;

			if (bdesc.bIsPerInstance)//One object instance corresponds to one piece of data
			{
				glVertexArrayBindingDivisor(VAO, adesc.Location, 1);
			}



		}

		BlendState = desc.BlendState;
		DepthStencilState = desc.DepthStencilState;
		MultisampleState = desc.MultisampleState;
		PatchControlPoints = desc.PatchControlPoints;
		PrimitiveTopology = desc.PrimitiveTopology;
		RasterizerState = desc.RasterizerState;
		Subpass = desc.Subpass;
		RenderPass = desc.RenderPass;
		Layout = desc.Layout;
	
	}



	CPipelineGL::CPipelineGL(CDeviceGL* p, const CComputePipelineDesc& desc):Parent(p)
	{
		
	}



	CPipelineGL::~CPipelineGL(){}

	void CPipelineGL::AddShaderModule(const CShaderModule::Ref shaderModule, GLenum stage)
	{
		if (shaderModule) {
			auto smImpl = std::static_pointer_cast<CShaderModuleGL>(shaderModule);
			glUseProgramStages(PipelineHandle, stage, smImpl->GetGLModule());
		}
	}

}