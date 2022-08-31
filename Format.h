#pragma once

#include <iostream>
#include <memory>
#include "RHIExport.h"

namespace RHI {

    enum class RHI_EXPORT EFormat:uint32_t
    {
        UNDEFINED = 0,      
		R8G8B8_UINT,
		R8G8B8_SRGB,

		R8G8B8A8_UINT,
		R8G8B8A8_SRGB,


        R32_UINT = 98,
        R32_SINT = 99,
        R32_SFLOAT = 100,
        R32G32_UINT = 101,
        R32G32_SINT = 102,
        R32G32_SFLOAT = 103,
        R32G32B32_UINT = 104,
        R32G32B32_SINT = 105,
        R32G32B32_SFLOAT = 106,
        R32G32B32A32_UINT = 107,
        R32G32B32A32_SINT = 108,
        R32G32B32A32_SFLOAT = 109,

		R64_UINT = 110,
		R64_SINT = 111,
		R64_SFLOAT = 112,
		R64G64_UINT = 113,
		R64G64_SINT = 114,
		R64G64_SFLOAT = 115,
		R64G64B64_UINT = 116,
		R64G64B64_SINT = 117,
		R64G64B64_SFLOAT = 118,
		R64G64B64A64_UINT = 119,
		R64G64B64A64_SINT = 120,
		R64G64B64A64_SFLOAT = 121,



		// Depth only formats and stencil only formats:
		D16_UNORM = 124,
		X8_D24_UNORM_PACK32 = 125,
		D32_SFLOAT = 126,
		S8_UINT = 127,

		// Depth stencil formats:
		D16_UNORM_S8_UINT = 128, // This format is rarely supported, don't use
		D24_UNORM_S8_UINT = 129,
		D32_SFLOAT_S8_UINT = 130,
    };



}