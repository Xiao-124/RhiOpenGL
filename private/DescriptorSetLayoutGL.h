#include "DescriptorSetGL.h"
#include "../DeviceGL.h"
namespace RHI
{

    class CDescriptorSetLayoutGL : public CDescriptorSetLayout
    {
    public:
        typedef std::shared_ptr<CDescriptorSetLayoutGL> Ref;
        CDescriptorSetLayoutGL(CDeviceGL* p);
        ~CDescriptorSetLayoutGL() override;
        CDescriptorSet::Ref CreateDescriptorSet() override;
        CDeviceGL* GetDevice() const { return Parent; }
    private:
        CDeviceGL* Parent;
    };

    class CPipelineLayoutGL : public CPipelineLayout
    {
    public:
        typedef std::shared_ptr<CPipelineLayoutGL> Ref;
        CPipelineLayoutGL(CDeviceGL* p, const std::vector<CDescriptorSetLayout::Ref>& setLayouts);
        ~CPipelineLayoutGL() override;
        CDeviceGL* GetDevice() const { return Parent; }
        const std::vector<CDescriptorSetLayoutGL::Ref>& GetSetLayouts() const { return SetLayouts; }

    private:
        CDeviceGL* Parent;
        std::vector<CDescriptorSetLayoutGL::Ref> SetLayouts;

    };

}