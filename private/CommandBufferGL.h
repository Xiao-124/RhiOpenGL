#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "../Pipeline.h"

#include "CommandGL.h"
namespace RHI
{
	class GLCommandBuffer
	{
	public:		
		void push(CMD c, std::shared_ptr<void> dec);
		void clear()
		{
			cmdArguments.clear();
		}
		std::vector<CMDArgument> cmdArguments;
	
		
	};
}