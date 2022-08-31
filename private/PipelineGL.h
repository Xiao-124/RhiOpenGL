#pragma once
#include "../Pipeline.h"
#include "ShaderModuleGL.h"
#include <unordered_map>
namespace RHI
{

    const size_t kMaxBoundDescriptorSets = 32;

#ifdef  _GLEW_USE
    class CPipelineGL : public CPipeline
#else
	class CPipelineGL : public CPipeline,protected QOpenGLFunctions_4_5_Core
#endif
    {
    public:
        typedef std::shared_ptr<CPipelineGL> Ref;
        CPipelineGL(CDeviceGL* p, const CPipelineDesc& desc);
        CPipelineGL(CDeviceGL* p, const CComputePipelineDesc& desc);
        ~CPipelineGL() override;
        GLuint GetHandle() const { return PipelineHandle; }

        
        GLuint VAO;
        std::unordered_map<uint32_t, uint32_t> BindingStride;

        CBlendDesc BlendState;
        CDepthStencilDesc DepthStencilState;
        CMultisampleStateDesc MultisampleState;
        uint32_t PatchControlPoints;
        GLenum Primit = GL_TRIANGLES;
        CRasterizerDesc RasterizerState;
        EPrimitiveTopology PrimitiveTopology;
        uint32_t Subpass;
        CRenderPass::WeakRef RenderPass;
        CPipelineLayout::Ref Layout;

    private:
        void AddShaderModule(const CShaderModule::Ref shaderModule, GLenum stage);
		CDeviceGL* Parent;
        GLuint PipelineHandle = 0;
        
       


    };

} /* namespace RHI */
