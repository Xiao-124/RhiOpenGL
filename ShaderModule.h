#pragma once

#include <iostream>
#include <memory>
#include <cassert>
#include <map>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "Format.h"
#include "Sampler.h"
#include "Resources.h"
namespace RHI 
{
    //shader type
    enum class RHI_EXPORT EShaderStageFlags
    {
        Vertex = 0x00000001,
        TessellationControl = 0x00000002,
        TessellationEvaluation = 0x00000004,
        Geometry = 0x00000008,
        Pixel = 0x00000010,
        Compute = 0x00000020,
        Fragment = 0x00000040,
        //These can be ignored
        AllGraphics = 0x0000001f,
        All = 0x7fffffff
    };


    
    struct RHI_EXPORT CVertexShaderInputDesc
    {
        EFormat Format;
        std::string Name; 
    };


    struct RHI_EXPORT CVertexShaderInputSignature
    {
     
        std::map<uint32_t, CVertexShaderInputDesc> InputDescs;
    };



   
    struct RHI_EXPORT CVertexInputs
    {
        struct CBoundAccessor
        {
            uint32_t Binding;
            CBuffer::Ref Buffer;
            uint32_t Offset;

            bool operator==(const CBoundAccessor& rhs) const
            {
                return Binding == rhs.Binding && Buffer == rhs.Buffer && Offset == rhs.Offset;
            }
        };

        std::vector<CBoundAccessor> BoundAccessors;

        void AddAccessor(uint32_t binding, CBuffer::Ref buffer, uint32_t offset)
        {
            BoundAccessors.push_back(CBoundAccessor{ binding, buffer, offset });
        }
    };

     
    //input attribute desc, example: layout(location = 1) in vec3 position;
    // the Location = 1, Format = vec3, Offset = size(vec3).
    //The binding: from which binding the per-vertex data comes
    struct RHI_EXPORT CVertexInputAttributeDesc
    {
        uint32_t Location = 0;
        EFormat Format = EFormat::UNDEFINED;
        uint32_t Offset = 0;
        uint32_t Binding = 0;
    };

    //binding parameter specifies the index of the binding in the array of bindings
    //stride is a byte step between contiguous elements in a buffer.
    //bIsPerInstance: Move to the next data entry after each instance, 
    struct RHI_EXPORT CVertexInputBindingDesc
    {
        uint32_t Binding = 0;
        uint32_t Stride = 0;
        bool bIsPerInstance = false;    
    };

    struct RHI_EXPORT CPixelShaderOutputDesc
    {
        EFormat Format;
        uint32_t Location;
        std::string Name;
    };

    // Arguments supplied for the shaders within a pipeline
    struct RHI_EXPORT CPipelineArguments
    {
        
        struct CArgType {
            CBuffer::Ref buffer;
            CImageView::Ref imageview;
            CSampler::Ref sampler;
        };
        std::map<uint32_t, CArgType> Arguments;

        template <typename T> void Add(uint32_t id, const T& arg)
        {
            // TODO warn if override
            assert(arg);
            Arguments.insert_or_assign(id, CArgType(arg));
        }
    };


    enum class RHI_EXPORT EPipelineResourceType : uint8_t
    {
        StageInput,
        StageOutput,
        SeparateSampler,
        CombinedImageSampler,
        SeparateImage,
        StorageImage,
        UniformTexelBuffer,
        StorageTexelBuffer,
        UniformBuffer,
        StorageBuffer,
        SubpassInput,
        PushConstantBuffer,
    };

    enum class RHI_EXPORT EBaseType
    {
        Bool,
        Char,
        Int,
        UInt,
        Half,
        Float,
        Double,
        Struct
    };

    const int MaxDescriptionSize = 256;

    struct RHI_EXPORT CPipelineResource
    {
        EShaderStageFlags Stages;
        EPipelineResourceType ResourceType;
        EBaseType BaseType;
        uint32_t Access;
        uint32_t Set;
        uint32_t Binding;
        uint32_t Location;
        uint32_t InputAttachmentIndex;
        uint32_t VecSize;
        uint32_t Columns;
        uint32_t ArraySize;
        uint32_t Offset;
        uint32_t Size;
        char Name[MaxDescriptionSize];
    };

    // the shaderModule is used to compile shader and use.
    class RHI_EXPORT CShaderModule:public std::enable_shared_from_this<CShaderModule>
    {
    public:
        typedef std::shared_ptr<CShaderModule> Ref;
        virtual ~CShaderModule() = default;
        virtual const std::vector<CPipelineResource>& GetShaderResources() = 0;       
    protected:
        CShaderModule() = default;
    };



}