
#include "ShaderModuleGL.h"
#include "FormatGL.h"
namespace RHI
{

    CShaderModuleGL::CShaderModuleGL(CDeviceGL* p, std::string source, EShaderStageFlags flag):Parent(p)
    {    
#ifndef  _GLEW_USE			
		QOpenGLContext* context = Parent->_context;
		QSurface* sur = context->surface();
		context->makeCurrent(sur);
		initializeOpenGLFunctions();
#endif	

        GLuint shader = glCreateShader(GLCast(flag));
        const GLchar* code = source.c_str();
        glShaderSource(shader, 1, &code, NULL);  
        glCompileShader(shader);

        GLint success;
        char infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR\n" << infoLog
                << std::endl;
        }
        ShaderModule = glCreateProgram();
        glAttachShader(ShaderModule, shader);
        
        glProgramParameteri(ShaderModule, GL_PROGRAM_SEPARABLE, GL_TRUE);
        glLinkProgram(ShaderModule);
        glGetProgramiv(ShaderModule, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ShaderModule, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog
                <<  std::endl;
        }
     
    }

    

    CShaderModuleGL::~CShaderModuleGL(){}




}