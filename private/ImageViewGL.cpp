#include "ImageViewGL.h"
#include "FormatGL.h"
namespace RHI
{
	CImageViewGL::CImageViewGL(CDeviceGL* p, const CImageViewDesc& desc, CImageGL::Ref image)
		:Parent(p),Image(image)
	{
		
		CImageSubresourceRange range = desc.Range;
		EDepthStencilAspectFlags flag = desc.DepthStencilAspect;
		glCreateTextures(GLCast(desc.Type), 1, &ImageView);
		
		glTextureView(ImageView, GLCast(desc.Type), image->getHandle(), GLCast(desc.Format),
			range.BaseMipLevel, range.LevelCount, range.BaseArrayLayer, range.LayerCount);
		
	}
	CImageViewGL::~CImageViewGL(){}
}