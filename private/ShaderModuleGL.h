#pragma once
#ifdef  _GLEW_USE
#include <GL/glew.h>
#else 
#include <qopenglfunctions.h>
#endif // ! _GLEW_USE
#include <iostream>
#include <vector>
#include "../DeviceGL.h"

namespace RHI
{
#ifdef  _GLEW_USE
    class CShaderModuleGL: public CShaderModule
#else
	class CShaderModuleGL : public CShaderModule, protected QOpenGLFunctions_4_5_Core
#endif
    {
    public:
        typedef std::shared_ptr<CShaderModuleGL> Ref;
        CShaderModuleGL(CDeviceGL* p, std::string source, EShaderStageFlags flag);
        ~CShaderModuleGL();    
        GLuint GetGLModule() const { return ShaderModule; }
        const std::vector<CPipelineResource>& GetShaderResources() override { return Resources; }

    private:
		CDeviceGL* Parent;
        GLuint ShaderModule;
        std::vector<CPipelineResource> Resources;
    };

} /* namespace RHI */
