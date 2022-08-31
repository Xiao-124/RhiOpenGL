#include "DescriptorSetLayoutGL.h"
namespace RHI
{

    CDescriptorSetLayoutGL::CDescriptorSetLayoutGL(CDeviceGL* p):Parent(p)
    {
        
    }

    CDescriptorSetLayoutGL::~CDescriptorSetLayoutGL(){}

    CDescriptorSet::Ref CDescriptorSetLayoutGL::CreateDescriptorSet()
    {
        CDescriptorSetLayoutGL::Ref layout = std::static_pointer_cast<CDescriptorSetLayoutGL> (shared_from_this());
        return std::static_pointer_cast<CDescriptorSet>(std::make_shared<CDescriptorSetGL>(layout));
    }

    CPipelineLayoutGL::CPipelineLayoutGL(CDeviceGL* p,
        const std::vector<CDescriptorSetLayout::Ref>& setLayouts){}
    CPipelineLayoutGL::~CPipelineLayoutGL(){}

}