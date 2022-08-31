#pragma once
#include "ImageGL.h"

namespace RHI
{
#ifdef  _GLEW_USE
    class CImageViewGL: public CImageView
#else
	class CImageViewGL : public CImageView,public QOpenGLFunctions_4_5_Core
#endif
    {
    public:
        typedef std::shared_ptr<CImageViewGL> Ref;
        CImageViewGL(CDeviceGL* p, const CImageViewDesc& desc, CImageGL::Ref image);
        ~CImageViewGL() override;
        GLuint GetGLImageView()  const  { return ImageView; }
        CImageGL::Ref GetImage() const  { return Image; }
    private:
		CDeviceGL* Parent;
        CImageGL::Ref Image;      
        GLuint ImageView;
    };

} /* namespace RHI */
