#include "CommandBufferGL.h"
#include "CommandGL.h"
namespace RHI
{

	void GLCommandBuffer::push(CMD c, std::shared_ptr<void> dec)
	{
		CMDArgument arg{ c, dec };
		cmdArguments.push_back(arg);
	}

	

}