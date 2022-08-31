#pragma once
#include "../RHICommon.h"
#include "../Resources.h"
#include <queue>
#include "SamplerGL.h"
#include "../DeviceGL.h"
namespace RHI
{

#ifdef  _GLEW_USE
	class CImageGL :public CImage
#else
	class CImageGL :public CImage, protected QOpenGLFunctions_4_5_Core
#endif
	{
    public:     
        typedef std::shared_ptr<CImageGL> Ref;


		CImageGL(CDeviceGL* p, EFormat format, EImageUsageFlags usage,
			uint32_t width, uint32_t mipLevels, uint32_t arrayLayers,
			uint32_t sampleCount, const void* initialData);
		CImageGL(CDeviceGL* p, EFormat format, EImageUsageFlags usage,
			uint32_t width, uint32_t height, uint32_t mipLevels, uint32_t arrayLayers,
			uint32_t sampleCount, const void* initialData);
        CImageGL(CDeviceGL* p, EFormat format, EImageUsageFlags usage, 
			uint32_t width, uint32_t height, uint32_t depth, uint32_t mipLevels, uint32_t arrayLayers,
			uint32_t sampleCount, const void* initialData);




        ~CImageGL();    
        EImageUsageFlags GetUsageFlags() const override { return flags; }
		EFormat  GetFormat()	  const override		{ return Format; }
        uint32_t GetWidth()       const override		{ return width; }
        uint32_t GetHeight()      const override		{ return height; }
        uint32_t GetDepth()       const override		{ return depth; }
        uint32_t GetMipLevels()   const override		{ return mipLevel; }
        uint32_t GetArrayLayers() const override		{ return arrayLevel; }
        uint32_t GetSampleCount() const override		{ return sampleCount; }
		GLuint   getHandle()	  const					{ return texture; }
	private:       
		CDeviceGL* Parent;
		GLuint texture;
        EFormat Format;
        EImageUsageFlags flags;
        uint32_t width;
        uint32_t height;
        uint32_t depth;
        uint32_t mipLevel;
        uint32_t arrayLevel;
        uint32_t sampleCount;

    };






   
} /* namespace RHI */
