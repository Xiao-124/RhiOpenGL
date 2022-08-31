#pragma once

#include <iostream>
#include <array>
#include <cstdint>
#include <vector>

namespace RHI 
{
    enum class RHI_EXPORT EFilter
    {
        Nearest = 0,
        Linear = 1,
    };

    enum class RHI_EXPORT ESamplerMipmapMode
    {
        Nearest = 0,
        Linear = 1,
    };

    enum class RHI_EXPORT ESamplerAddressMode
    {
        Wrap = 1,
        Mirror = 2,
        Clamp = 3,
        Border = 4,
        MirrorOnce = 5,
    };

    enum class RHI_EXPORT ECompareOp
    {
        Never = 0,
        Less = 1,
        Equal = 2,
        LessEqual = 3,
        Greater = 4,
        NotEqual = 5,
        GreaterEqual = 6,
        Always = 7,
    };

    struct RHI_EXPORT CSamplerDesc
    {
        EFilter MagFilter = EFilter::Linear;
        EFilter MinFilter = EFilter::Linear;
        ESamplerMipmapMode MipmapMode = ESamplerMipmapMode::Linear;
        ESamplerAddressMode AddressModeU = ESamplerAddressMode::Clamp;
        ESamplerAddressMode AddressModeV = ESamplerAddressMode::Clamp;
        ESamplerAddressMode AddressModeW = ESamplerAddressMode::Clamp;
        float MipLodBias = 0.0f;

        bool AnisotropyEnable = false;
        float MaxAnisotropy = 1.0f;

        bool CompareEnable = false;
        ECompareOp CompareOp = ECompareOp::Never;

        float MinLod = -1000;
        float MaxLod = 1000;
        std::array<float, 4> BorderColor = { 1.0f, 1.0f, 1.0f, 1.0f };

        bool operator=(const CSamplerDesc& r) const
        {
            return MagFilter == r.MagFilter && MinFilter == r.MinFilter && MipmapMode == r.MipmapMode
                && AddressModeU == r.AddressModeU && AddressModeV == r.AddressModeV
                && AddressModeW == r.AddressModeW && MipLodBias == r.MipLodBias
                && AnisotropyEnable == r.AnisotropyEnable && MaxAnisotropy == r.MaxAnisotropy
                && CompareEnable == r.CompareEnable && CompareOp == r.CompareOp && MinLod == r.MinLod
                && MaxLod == r.MaxLod && BorderColor == r.BorderColor;
        }
    };

    class RHI_EXPORT CSampler
    {
    public:
        typedef std::shared_ptr<CSampler> Ref;
        virtual ~CSampler() = default;
    };


}