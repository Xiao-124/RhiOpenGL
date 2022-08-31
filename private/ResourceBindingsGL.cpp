#include "ResourceBindingsGL.h"
namespace RHI
{

    void CResourceBindings::BindBuffer(CBufferGL::Ref buffer, uint32_t offset, uint32_t range, uint32_t binding)
    {
        Bindings[binding].push_back(BindingInfo(buffer, offset, range));
    }

   
    void CResourceBindings::BindSampler(CSamplerGL::Ref sampler, uint32_t binding)
    {
        Bindings[binding].push_back(BindingInfo(sampler));
    }

    void CResourceBindings::BindImageView(std::shared_ptr<CImageViewGL> iamge, uint32_t binding)
    {
        Bindings[binding].push_back(BindingInfo(iamge));
    }


    void CResourceBindings::BindImage(std::shared_ptr<CImageGL> image, uint32_t binding)
    {
        Bindings[binding].push_back(BindingInfo(image));
    }

}