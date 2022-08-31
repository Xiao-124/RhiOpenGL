#pragma once
#ifdef  _GLEW_USE
#include <GL/glew.h>
#else 
#include <qopenglfunctions.h>
#endif // ! _GLEW_USE
#include <iostream>
#include <array>
#include <cstdint>
#include <vector>
#include "../Sampler.h"
#include "../DeviceGL.h"

namespace RHI
{
#ifdef  _GLEW_USE
    class CSamplerGL : public CSampler
#else
	class CSamplerGL : public CSampler,public QOpenGLFunctions_4_5_Core
#endif
    {
    public:
        typedef std::shared_ptr<CSamplerGL> Ref;
        CSamplerGL(CDeviceGL* p, const CSamplerDesc& desc);
        ~CSamplerGL();   
		GLuint getHandle() const { return sampler; }
    private:
		CDeviceGL* Parent;
		GLuint sampler;
    };

} /* namespace RHI */
