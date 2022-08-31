#pragma once
#include "CopyContext.h"
#include "ComputeContext.h"
#include "RenderContext.h"
#include <memory>

namespace RHI
{

    enum class RHI_EXPORT EQueueType : uint32_t
    {
        Copy,
        Compute,
        Render,
        Count
    };

    class RHI_EXPORT CCommandQueue : public std::enable_shared_from_this<CCommandQueue>
    {
    public:
        typedef std::shared_ptr<CCommandQueue> Ref;
        virtual ~CCommandQueue() = default;
       
        virtual ICopyContext::Ref CreateCopyContext() = 0;
        virtual IComputeContext::Ref CreateComputeContext() = 0;
        virtual IParallelRenderContext::Ref CreateParallelRenderContext(CRenderPass::Ref renderPass,
            const std::vector<CClearValue>& clearValues) = 0;

        virtual void Flush() = 0;
        virtual void Finish() = 0;
    };

} /* namespace RHI */

