#pragma once

#include "../CommandQueue.h"
#include <iostream>
#include <memory>
#include <functional>
#include <unordered_map>
#include "../DeviceGL.h"
#include "CommandGL.h"
namespace RHI
{
    class GLCommandBuffer;
#ifdef  _GLEW_USE
    class CCommandQueueGL :public CCommandQueue
#else	
	class CCommandQueueGL :public CCommandQueue,protected QOpenGLFunctions_4_5_Core
    {
#endif
    public:
        typedef std::shared_ptr<CCommandQueueGL> Ref;
       

        CCommandQueueGL(CDeviceGL* p, EQueueType queueType);
        ~CCommandQueueGL() override;

		CDeviceGL* GetDevice() const { return Parent; }
        EQueueType GetType() const { return Type; }

        ICopyContext::Ref CreateCopyContext() override;
        IComputeContext::Ref CreateComputeContext() override;
        IParallelRenderContext::Ref
            CreateParallelRenderContext(CRenderPass::Ref renderPass,
                const std::vector<CClearValue>& clearValues) override;

        void EnqueueCommandList(std::vector<GLCommandBuffer> &buffer );
        void EnqueueCommandBufffer(GLCommandBuffer& buffer);
        void Flush() override;
        void Finish() override;
        std::vector<GLCommandBuffer> Sections;

    private:
        typedef std::function< void(std::shared_ptr<void>&) > FunctionsMap;
        CDeviceGL* Parent;
        EQueueType Type;      
        std::unordered_map<CMD,FunctionsMap> funsMap;
        GLuint GLVersion = 430;

        void glCmdBindPipeline(std::shared_ptr<void>& desc);
        void glCmdBindVertexBuffers(std::shared_ptr<void>& desc);
        void glCmdBindElementBuffer(std::shared_ptr<void>& desc);
        void glCmdDraw(std::shared_ptr<void>& desc);
        void glCmdBindDescriptorSet(std::shared_ptr<void>& desc);

        void glCmdBeginRenderPass(std::shared_ptr<void>& desc);
        void glCmdNextSubpass(std::shared_ptr<void>& desc);
        void glCmdEndRenderPass(std::shared_ptr<void>& desc);

		void glCmdSetViewPort(std::shared_ptr<void>& desc);
		void glCmdSetScissor(std::shared_ptr<void>& desc);
		void glCmdCopyBuffer(std::shared_ptr<void>& desc);
		void glCmdCopyImage(std::shared_ptr<void>& desc);



    };

}
