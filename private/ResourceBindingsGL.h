#pragma once
#include <map>
#include <unordered_map>
#include "BufferGL.h"
#include "SamplerGL.h"
#include "ImageViewGL.h"
namespace RHI
{
    struct BindingInfo
    {
        uint32_t Offset;
        uint32_t Range;
        std::shared_ptr<CBufferGL> BufferHandle;  
        std::shared_ptr<CImageViewGL> ImageView;
        std::shared_ptr<CSamplerGL> SamplerHandle;
        std::shared_ptr<CImageGL> Image;
        BindingInfo(){}

        BindingInfo(std::shared_ptr<CBufferGL> buffer, uint32_t offset, uint32_t range)
            : BufferHandle(buffer)
            , Offset(offset)
            , Range(range)
        {
        }

        
        BindingInfo(std::shared_ptr<CImageViewGL> view):ImageView(view)
        {
            
        }


        BindingInfo(std::shared_ptr<CSamplerGL> sampler)
            : SamplerHandle(sampler)
        {
        }

        BindingInfo(std::shared_ptr<CImageGL> view) :Image(view)
        {

        }


    };

    typedef std::map<uint32_t, std::vector<BindingInfo>> ArrayBindings;  

    struct SetBindings
    {
        std::unordered_map<uint32_t, ArrayBindings> Bindings;
        bool bDirty;
    };

    class CResourceBindings
    {
    public:
        bool IsDirty() const { return bDirty; }
        void ClearDirtyBit() { bDirty = false; }
        ArrayBindings& GetSetBindings() { return Bindings; }


        void Reset()
        {
            Bindings.clear();
            bDirty = false;
        }

        void BindSampler(CSamplerGL::Ref sampler,uint32_t binding);
        void BindImageView(std::shared_ptr<CImageViewGL> iamge, uint32_t binding);
        void BindBuffer(CBufferGL::Ref buffer, uint32_t offset, uint32_t range, uint32_t binding);
        void BindImage(std::shared_ptr<CImageGL> image, uint32_t binding);
    private:
        ArrayBindings Bindings;
        bool bDirty = false;
    };
    

} /* namespace RHI */
