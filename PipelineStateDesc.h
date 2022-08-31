#pragma once

#include "ShaderModule.h"

namespace RHI {

    //viewport desc,
    struct RHI_EXPORT CViewportDesc
    {
        float X;
        float Y;
        float Width;
        float Height;
        float MinDepth = 0;
        float MaxDepth = 1;

        CViewportDesc& SetX(float value)
        {
            X = value;
            return *this;
        }
        CViewportDesc& SetY(float value)
        {
            Y = value;
            return *this;
        }
        CViewportDesc& SetWidth(float value)
        {
            Width = value;
            return *this;
        }
        CViewportDesc& SetHeight(float value)
        {
            Height = value;
            return *this;
        }
        CViewportDesc& SetMinDepth(float value)
        {
            MinDepth = value;
            return *this;
        }
        CViewportDesc& SetMaxDepth(float value)
        {
            MaxDepth = value;
            return *this;
        }
    };

    //polygon mode
    enum class RHI_EXPORT EPolygonMode
    {
        Fill,
        Wireframe
    };

    //cull mode
    enum class RHI_EXPORT ECullModeFlags
    {
        None = 0,
        Front = 1,
        Back = 1 << 1
    };


    struct RHI_EXPORT CRasterizerDesc
    {
        EPolygonMode PolygonMode = EPolygonMode::Fill;
        ECullModeFlags CullMode = ECullModeFlags::None;
        bool  FrontFaceCCW = true;
        bool  DepthBiasEnable = false;
        float DepthBiasConstantFactor = 0.0f;
        float DepthBiasClamp = 0.0f;
        float DepthBiasSlopeFactor = 0.0f;
        bool  DepthClampEnable = false;


        CRasterizerDesc& SetPolygonMode(EPolygonMode value)
        {
            PolygonMode = value;
            return *this;
        }
        CRasterizerDesc& SetCullMode(ECullModeFlags value)
        {
            CullMode = value;
            return *this;
        }
        CRasterizerDesc& SetFrontFaceCCW(bool value)
        {
            FrontFaceCCW = value;
            return *this;
        }
        CRasterizerDesc& SetDepthBiasEnable(bool value)
        {
            DepthBiasEnable = value;
            return *this;
        }
        CRasterizerDesc& SetDepthBiasConstantFactor(float value)
        {
            DepthBiasConstantFactor = value;
            return *this;
        }
        CRasterizerDesc& SetDepthBiasClamp(float value)
        {
            DepthBiasClamp = value;
            return *this;
        }
        CRasterizerDesc& SetDepthBiasSlopeFactor(float value)
        {
            DepthBiasSlopeFactor = value;
            return *this;
        }
        CRasterizerDesc& SetDepthClampEnable(bool value)
        {
            DepthClampEnable = value;
            return *this;
        }

        bool operator==(const CRasterizerDesc& rhs) const
        {
            return PolygonMode == rhs.PolygonMode && CullMode == rhs.CullMode
                && FrontFaceCCW == rhs.FrontFaceCCW && DepthBiasEnable == rhs.DepthBiasEnable
                && DepthBiasConstantFactor == rhs.DepthBiasConstantFactor
                && DepthBiasClamp == rhs.DepthBiasClamp
                && DepthBiasSlopeFactor == rhs.DepthBiasSlopeFactor
                && DepthClampEnable == rhs.DepthClampEnable;
        }

       
    };

    struct RHI_EXPORT CMultisampleStateDesc
    {
        bool MultisampleEnable = false; // Replace with sample count?
        uint64_t SampleMask = ~0U;
        bool AlphaToCoverageEnable = false;

        CMultisampleStateDesc& SetMultisampleEnable(bool value)
        {
            MultisampleEnable = value;
            return *this;
        }
        CMultisampleStateDesc& SetSampleMask(uint64_t value)
        {
            SampleMask = value;
            return *this;
        }
        CMultisampleStateDesc& SetAlphaToCoverageEnable(bool value)
        {
            AlphaToCoverageEnable = value;
            return *this;
        }

        bool operator==(const CMultisampleStateDesc& rhs) const
        {
            return MultisampleEnable == rhs.MultisampleEnable && SampleMask == rhs.SampleMask
                && AlphaToCoverageEnable == rhs.AlphaToCoverageEnable;
        }

    };


    enum class RHI_EXPORT EStencilOp
    {
        Keep = 0,
        Zero = 1,
        Replace = 2,
        IncrementAndClamp = 3,
        DecrementAndClamp = 4,
        Invert = 5,
        IncrementAndWrap = 6,
        DecrementAndWrap = 7,
    };

    struct RHI_EXPORT CStencilOpState
    {
        EStencilOp FailOp = EStencilOp::Keep;
        EStencilOp PassOp = EStencilOp::Keep;
        EStencilOp DepthFailOp = EStencilOp::Keep;
        ECompareOp CompareOp = ECompareOp::Always;
        uint32_t CompareMask = 255;
        uint32_t WriteMask = 255;

        CStencilOpState& SetFailOp(EStencilOp value)
        {
            FailOp = value;
            return *this;
        }
        CStencilOpState& SetPassOp(EStencilOp value)
        {
            PassOp = value;
            return *this;
        }
        CStencilOpState& SetDepthFailOp(EStencilOp value)
        {
            DepthFailOp = value;
            return *this;
        }
        CStencilOpState& SetCompareOp(ECompareOp value)
        {
            CompareOp = value;
            return *this;
        }
        CStencilOpState& SetCompareMask(uint32_t value)
        {
            CompareMask = value;
            return *this;
        }
        CStencilOpState& SetWriteMask(uint32_t value)
        {
            WriteMask = value;
            return *this;
        }

        bool operator==(const CStencilOpState& rhs) const
        {
            return FailOp == rhs.FailOp && PassOp == rhs.PassOp && DepthFailOp == rhs.DepthFailOp
                && CompareOp == rhs.CompareOp && CompareMask == rhs.CompareMask
                && WriteMask == rhs.WriteMask;
        }

       
    };

    struct RHI_EXPORT CDepthStencilDesc
    {
        bool DepthEnable = false;
        bool DepthWriteEnable = true;
        ECompareOp DepthCompareOp = ECompareOp::Less;
        bool StencilEnable = false;
        CStencilOpState Front;
        CStencilOpState Back;

        CDepthStencilDesc& SetDepthEnable(bool value)
        {
            DepthEnable = value;
            return *this;
        }
        CDepthStencilDesc& SetDepthWriteEnable(bool value)
        {
            DepthWriteEnable = value;
            return *this;
        }
        CDepthStencilDesc& SetDepthCompareOp(ECompareOp value)
        {
            DepthCompareOp = value;
            return *this;
        }
        CDepthStencilDesc& SetStencilEnable(bool value)
        {
            StencilEnable = value;
            return *this;
        }
        CDepthStencilDesc& SetFront(CStencilOpState value)
        {
            Front = value;
            return *this;
        }
        CDepthStencilDesc& SetBack(CStencilOpState value)
        {
            Back = value;
            return *this;
        }

        bool operator==(const CDepthStencilDesc& rhs) const
        {
            return DepthEnable == rhs.DepthEnable && DepthWriteEnable == rhs.DepthWriteEnable
                && DepthCompareOp == rhs.DepthCompareOp && StencilEnable == rhs.StencilEnable
                && Front == rhs.Front && Back == rhs.Back;
        }

       
    };

    enum class RHI_EXPORT EBlendMode
    {
        Zero,
        One,
        SrcColor,
        OneMinusSrcColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstAlpha,
        OneMinusDstAlpha,
        DstColor,
        OneMinusDstColor,
        SrcAlphaSaturate,
        // TODO: Custom blend factor support
    };

    enum class RHI_EXPORT EBlendOp
    {
        Add,
        Subtract,
        ReverseSubtract,
        Min,
        Max
    };

    enum class RHI_EXPORT EColorComponentFlags : uint8_t
    {
        None = 0,
        Red = 1,
        Green = 1 << 1,
        Blue = 1 << 2,
        Alpha = 1 << 3,
        All = Red | Green | Blue | Alpha
    };

  

    struct RHI_EXPORT CRenderTargetBlendDesc
    {
        bool BlendEnable = false;
        EBlendMode SrcBlend = EBlendMode::One;
        EBlendMode DestBlend = EBlendMode::Zero;
        EBlendOp BlendOp = EBlendOp::Add;
        EBlendMode SrcBlendAlpha = EBlendMode::One;
        EBlendMode DestBlendAlpha = EBlendMode::Zero;
        EBlendOp BlendOpAlpha = EBlendOp::Add;
        EColorComponentFlags RenderTargetWriteMask = EColorComponentFlags::All;

        CRenderTargetBlendDesc& SetBlendEnable(bool value)
        {
            BlendEnable = value;
            return *this;
        }
        CRenderTargetBlendDesc& SetSrcBlend(EBlendMode value)
        {
            SrcBlend = value;
            return *this;
        }
        CRenderTargetBlendDesc& SetDestBlend(EBlendMode value)
        {
            DestBlend = value;
            return *this;
        }
        CRenderTargetBlendDesc& SetBlendOp(EBlendOp value)
        {
            BlendOp = value;
            return *this;
        }
        CRenderTargetBlendDesc& SetSrcBlendAlpha(EBlendMode value)
        {
            SrcBlendAlpha = value;
            return *this;
        }
        CRenderTargetBlendDesc& SetDestBlendAlpha(EBlendMode value)
        {
            DestBlendAlpha = value;
            return *this;
        }
        CRenderTargetBlendDesc& SetBlendOpAlpha(EBlendOp value)
        {
            BlendOpAlpha = value;
            return *this;
        }
        CRenderTargetBlendDesc& SetRenderTargetWriteMask(EColorComponentFlags value)
        {
            RenderTargetWriteMask = value;
            return *this;
        }

        bool operator==(const CRenderTargetBlendDesc& rhs) const
        {
            return (BlendEnable == false && rhs.BlendEnable == false)
                || (BlendEnable == rhs.BlendEnable && SrcBlend == rhs.SrcBlend
                    && DestBlend == rhs.DestBlend && BlendOp == rhs.BlendOp
                    && SrcBlendAlpha == rhs.SrcBlendAlpha && DestBlendAlpha == rhs.DestBlendAlpha
                    && BlendOpAlpha == rhs.BlendOpAlpha
                    && RenderTargetWriteMask == rhs.RenderTargetWriteMask);
        }

        
    };

    struct RHI_EXPORT CBlendDesc
    {
        bool IndependentBlendEnable = false;
        std::array<CRenderTargetBlendDesc, 8> RenderTargets;

        CBlendDesc& SetRenderTargets(size_t num, CRenderTargetBlendDesc desc)
        {
            RenderTargets[num] = desc;
            return *this;
        }

        CBlendDesc& SetRenderTargets(const std::vector<CRenderTargetBlendDesc>& value)
        {
            size_t bound = value.size() < 8 ? value.size() : 8;
            for (size_t i = 0; i < bound; i++)
            {
                RenderTargets[i] = value[i];
            }
            return *this;
        }

        bool operator==(const CBlendDesc& rhs) const
        {
            return RenderTargets[0] == rhs.RenderTargets[0] && RenderTargets[1] == rhs.RenderTargets[1]
                && RenderTargets[2] == rhs.RenderTargets[2] && RenderTargets[3] == rhs.RenderTargets[3]
                && RenderTargets[4] == rhs.RenderTargets[4] && RenderTargets[5] == rhs.RenderTargets[5]
                && RenderTargets[6] == rhs.RenderTargets[6] && RenderTargets[7] == rhs.RenderTargets[7];
        }

        
    };


    enum class RHI_EXPORT EPrimitiveTopology   //draw type.
    {
        PointList = 0,
        LineList = 1,
        LineStrip = 2,
        TriangleList = 3,
        TriangleStrip = 4,
        TriangleFan = 5,
    };








}
