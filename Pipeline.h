#pragma once
#include "PipelineStateDesc.h"
#include "RenderPass.h"
namespace RHI 
{
    class RHI_EXPORT CPipelineLayout
    {
    public:
        typedef std::shared_ptr<CPipelineLayout> Ref;

        virtual ~CPipelineLayout() = default;
    };


    struct RHI_EXPORT CPipelineDesc
    {
        CShaderModule::Ref VS;
        CShaderModule::Ref FS;
        CShaderModule::Ref GS;
        CShaderModule::Ref HS;
        CShaderModule::Ref DS;
        std::vector<CVertexInputAttributeDesc> VertexAttributes;
        std::vector<CVertexInputBindingDesc> VertexBindings;
        EPrimitiveTopology PrimitiveTopology = EPrimitiveTopology::TriangleList;
        uint32_t PatchControlPoints = 0;

        
        CRasterizerDesc RasterizerState;    
        CMultisampleStateDesc MultisampleState;
        CDepthStencilDesc DepthStencilState;
        CBlendDesc BlendState;
        CPipelineLayout::Ref Layout;
        CRenderPass::WeakRef RenderPass;
        uint32_t Subpass = 0;

        void VertexAttribFormat(uint32_t location, EFormat format, uint32_t offset, uint32_t binding)
        {
            CVertexInputAttributeDesc desc{ location, format, offset, binding };
            VertexAttributes.push_back(desc);
        }

        void VertexBinding(uint32_t binding, uint32_t stride, bool bIsPerInstance = false)
        {
            CVertexInputBindingDesc desc{ binding, stride, bIsPerInstance };
            VertexBindings.push_back(desc);
        }
    };

    struct RHI_EXPORT CComputePipelineDesc
    {
        CShaderModule::Ref CS;
        CPipelineLayout::Ref Layout;
    };

    class RHI_EXPORT CPipeline
    {
    public:
        typedef std::shared_ptr<CPipeline> Ref;

        virtual ~CPipeline() = default;
    };










}