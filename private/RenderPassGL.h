#pragma once
#include "../RenderPass.h"
#include "ImageGL.h"
#include "ImageViewGL.h"
namespace RHI
{
    struct CAttachMentGL
    {
        CImageViewGL::Ref ImageView;
        CImageGL::Ref Image;
    };

#ifdef  _GLEW_USE
    class CRenderPassGL : public CRenderPass
#else
	class CRenderPassGL : public CRenderPass,protected QOpenGLFunctions_4_5_Core
#endif
    {
    public:
        CRect2D Area;
        CRenderPassGL(CDeviceGL* p, const CRenderPassDesc& desc);
        ~CRenderPassGL() override;

        void SetSize(uint32_t width, uint32_t height) override;
        const std::vector<CAttachMentGL>& GetAttachments() const { return Attachments; }
        const std::vector<CSubpassDesc>& GetSubpassDesc() const { return SubpassDesc; }
        uint32_t GetSubpassCount() const { return SubpassDesc.size(); }
        
        GLuint MakeFramebuffer(uint32_t subpass);
        
    private:
		CDeviceGL* Parent;
        std::vector<CAttachMentGL> Attachments; // Sole purpose is to hold images alive
        std::vector<CSubpassDesc> SubpassDesc;
        
        uint32_t Layers = 0;
    };

} /* namespace RHI */
