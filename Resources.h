#pragma once

#include <iostream>
#include <memory>
#include "Format.h"
#define	DEFINE_ENUM_CLASS_BITWISE_OPERATORS(T)  \
inline T operator | (T lhs, T rhs){ return static_cast<T>( (uint32_t)lhs|(uint32_t)rhs);  }\
inline T operator & (T lhs, T rhs){ return static_cast<T>( (uint32_t)lhs&(uint32_t)rhs ); }

namespace RHI {

	


    enum class RHI_EXPORT EBufferUsageFlags : uint32_t
    {
        // Binding flags
		UNDEFINED = 0,
        Index = 1 << 0,
        Vertex = 1 << 1,
        IndirectDraw = 1 << 2,
        Uniform = 1 << 3,
        Storage = 1 << 4,
        UniformTexel = 1 << 5,
        StorageTexel = 1 << 6,

        // Accessibility flags
        Dynamic = 1 << 16,  //cpu to gpu
        Upload = 1 << 17,   //cpu only
        Readback = 1 << 18  //gpu to cpu
    };
	DEFINE_ENUM_CLASS_BITWISE_OPERATORS(EBufferUsageFlags)


	class RHI_EXPORT CBuffer: public std::enable_shared_from_this<CBuffer> {
	public:		
        typedef std::shared_ptr<CBuffer> Ref;		
        virtual void* Map(size_t offset, size_t size) = 0;
        virtual void Unmap() = 0;

	};

    
    class RHI_EXPORT CBufferView
    {
    public:
        typedef std::shared_ptr<CBufferView> Ref;
        virtual ~CBufferView() = default;
    };

    enum class RHI_EXPORT EImageType
    {
        Image1D,
        Image2D,
        Image3D,
    };

    enum class RHI_EXPORT EImageUsageFlags : uint32_t
    {
        None = 0,
        Sampled = 1 << 0,
        DepthStencil = 1 << 1,
        RenderTarget = 1 << 2,
        CubeMap = 1 << 3,
        GenMIPMaps = 1 << 4,
        Staging = 1 << 5,
        Storage = 1 << 6,
    };
	DEFINE_ENUM_CLASS_BITWISE_OPERATORS(EImageUsageFlags)
  
    class RHI_EXPORT CImage : public std::enable_shared_from_this<CImage>
    {
    public:
        typedef std::shared_ptr<CImage> Ref;

        virtual ~CImage() = default;
        
        virtual EFormat GetFormat() const = 0;
        virtual EImageUsageFlags GetUsageFlags() const = 0;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetDepth() const = 0;
        virtual uint32_t GetMipLevels() const = 0;
        virtual uint32_t GetArrayLayers() const = 0;
        virtual uint32_t GetSampleCount() const = 0;

    protected:
        CImage() = default;
    };



    enum class RHI_EXPORT EImageViewType
    {
        View1D = 0,
        View2D = 1,
        View3D = 2,
        Cube = 3,
        View1DArray = 4,
        View2DArray = 5,
        CubeArray = 6,
    };

   
    struct RHI_EXPORT CImageSubresourceRange
    {
        uint32_t BaseMipLevel = 0;      //The first MiPMap level accessible to the view.
        uint32_t LevelCount = 1;        //The number of MiPMap levels (from the start) that the view can access
        uint32_t BaseArrayLayer = 0;    //The first array layer accessible to the view
        uint32_t LayerCount = 1;        //Number of array layers accessible to the view (from the start)

        void Set(uint32_t mip, uint32_t mipCount, uint32_t layer, uint32_t layerCount)
        {
            BaseMipLevel = mip;
            LevelCount = mipCount;
            BaseArrayLayer = layer;
            LayerCount = layerCount;
        }

        bool Overlaps(const CImageSubresourceRange& rhs) const
        {
            if (BaseMipLevel + LevelCount <= rhs.BaseMipLevel
                || rhs.BaseMipLevel + rhs.LevelCount <= BaseMipLevel)
                return false;
            if (BaseArrayLayer + LayerCount <= rhs.BaseArrayLayer
                || rhs.BaseArrayLayer + rhs.LayerCount <= BaseArrayLayer)
                return false;
            return true;
        }

        bool operator<(const CImageSubresourceRange& rhs) const
        {
            if (BaseMipLevel < rhs.BaseMipLevel)
                return true;
            if (BaseMipLevel > rhs.BaseMipLevel)
                return false;
            if (LevelCount < rhs.LevelCount)
                return true;
            if (LevelCount > rhs.LevelCount)
                return false;
            if (BaseArrayLayer < rhs.BaseArrayLayer)
                return true;
            if (BaseArrayLayer > rhs.BaseArrayLayer)
                return false;
            if (LayerCount < rhs.LayerCount)
                return true;
            if (LayerCount > rhs.LayerCount)
                return false;
            return false;
        }

        bool operator==(const CImageSubresourceRange& rhs) const
        {
            return BaseMipLevel == rhs.BaseMipLevel && LevelCount == rhs.LevelCount
                && BaseArrayLayer == rhs.BaseArrayLayer && LayerCount == rhs.LayerCount;
        }
    };



    enum class RHI_EXPORT EDepthStencilAspectFlags : uint32_t
    {
        Depth = 1,
        Stencil = 2,
        Both = 3,
    };

    struct RHI_EXPORT CImageViewDesc
    {
        EImageViewType Type;
        EFormat Format;
        EDepthStencilAspectFlags DepthStencilAspect = EDepthStencilAspectFlags::Both;
        CImageSubresourceRange Range;
    };

    class RHI_EXPORT CImageView : public std::enable_shared_from_this<CImageView>
    {
    public:
        typedef std::shared_ptr<CImageView> Ref;
        virtual ~CImageView() = default;
    };

}