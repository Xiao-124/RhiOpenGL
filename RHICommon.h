#pragma once
#include <cstdint>
#include <memory>
#include "RHIExport.h"
namespace RHI
{

    struct RHI_EXPORT COffset2D
    {
        int32_t X;
        int32_t Y;

        void Set(int32_t x, int32_t y)
        {
            X = x;
            Y = y;
        }
    };

    struct RHI_EXPORT COffset3D
    {
        int32_t X;
        int32_t Y;
        int32_t Z;

        void Set(int32_t x, int32_t y, int32_t z)
        {
            X = x;
            Y = y;
            Z = z;
        }
    };

    struct RHI_EXPORT CExtent2D
    {
        uint32_t Width;
        uint32_t Height;

        void Set(uint32_t w, uint32_t h)
        {
            Width = w;
            Height = h;
        }
    };

    struct RHI_EXPORT CExtent3D
    {
        uint32_t Width;
        uint32_t Height;
        uint32_t Depth;

        void Set(uint32_t w, uint32_t h, uint32_t d)
        {
            Width = w;
            Height = h;
            Depth = d;
        }
    };

    struct RHI_EXPORT CRect2D
    {
        COffset2D Offset;
        CExtent2D Extent;

        CRect2D& SetX(int32_t value)
        {
            Offset.X = value;
            return *this;
        }
        CRect2D& SetY(int32_t value)
        {
            Offset.Y = value;
            return *this;
        }
        CRect2D& SetWidth(uint32_t value)
        {
            Extent.Width = value;
            return *this;
        }
        CRect2D& SetHeight(uint32_t value)
        {
            Extent.Height = value;
            return *this;
        }
    };

    

} /* namespace RHI */
