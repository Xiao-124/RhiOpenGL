#pragma once
#include "PipelineStateDesc.h"
#include "Resources.h"
#include "Sampler.h"
#include "RHICommon.h"
#include <memory>

namespace RHI
{

    struct RHI_EXPORT CBufferCopy
    {
        size_t SrcOffset;
        size_t DstOffset;
        size_t Size;
    };

    struct RHI_EXPORT CImageSubresourceLayers
    {
        uint32_t MipLevel;
        uint32_t BaseArrayLayer;
        uint32_t LayerCount;
    };

    struct RHI_EXPORT CImageCopy
    {
        CImageSubresourceLayers SrcSubresource;
        COffset3D SrcOffset;
        CImageSubresourceLayers DstSubresource;
        COffset3D DstOffset;
        CExtent3D Extent;
    };

    struct RHI_EXPORT CBufferImageCopy
    {
        size_t BufferOffset;
        uint32_t BufferRowLength;
        uint32_t BufferImageHeight;
        CImageSubresourceLayers ImageSubresource;
        COffset3D ImageOffset;
        CExtent3D ImageExtent;
    };

    struct RHI_EXPORT CImageBlit
    {
        CImageSubresourceLayers SrcSubresource;
        COffset3D SrcOffsets[2];
        CImageSubresourceLayers DstSubresource;
        COffset3D DstOffsets[2];
    };

    struct RHI_EXPORT CImageResolve
    {
        CImageSubresourceLayers SrcSubresource;
        COffset3D SrcOffset;
        CImageSubresourceLayers DstSubresource;
        COffset3D DstOffset;
        CExtent3D Extent;
    };

    struct RHI_EXPORT CClearDepthStencilValue
    {
        float Depth = -1;
        int32_t Stencil = -1;
    };

    struct RHI_EXPORT CClearValue
    {   
        float ColorFloat32[4] = {-1,-1,-1,-1};
        CClearDepthStencilValue DepthStencilValue;
        CClearValue(float r, float g, float b, float a)
        {
            ColorFloat32[0] = r;
            ColorFloat32[1] = g;
            ColorFloat32[2] = b;
            ColorFloat32[3] = a;
        }

        CClearValue(float d, int32_t s)
            : DepthStencilValue{ d, s }
        {
        }


        void SetDepthStencil(float d, int32_t s = -1)
        {
            DepthStencilValue= {d, s };
        }

    };

    class RHI_EXPORT ICopyContext
    {
    public:
        typedef std::shared_ptr<ICopyContext> Ref;

        virtual ~ICopyContext() = default;

        virtual void ClearImage(CImage::Ref image, const CClearValue& clearValue,
            const CImageSubresourceRange& range) = 0;
        virtual void CopyBuffer(CBuffer::Ref src, CBuffer::Ref dst,
            const std::vector<CBufferCopy>& regions) = 0;
        virtual void CopyImage(CImage::Ref src, CImage::Ref dst, const std::vector<CImageCopy>& regions) = 0;
        virtual void CopyBufferToImage(CBuffer::Ref src, CImage::Ref dst,
            const std::vector<CBufferImageCopy>& regions) = 0;
        virtual void CopyImageToBuffer(CImage::Ref src, CBuffer::Ref dst,
            const std::vector<CBufferImageCopy>& regions) = 0;
        virtual void BlitImage(CImage::Ref src, CImage::Ref dst, const std::vector<CImageBlit>& regions,
            EFilter filter) = 0;
        virtual void ResolveImage(CImage::Ref src, CImage::Ref dst,
            const std::vector<CImageResolve>& regions) = 0;

        virtual void FinishRecording() = 0;
    };

} /* namespace RHI */