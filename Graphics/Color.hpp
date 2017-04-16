#ifndef WL_COLOR_H
#define WL_COLOR_H

#include <Windows.h>

namespace Graphics
{
    typedef unsigned char ColorUnit;
    enum ESystemColors
    {
        clBlack     = RGB(0, 0, 0),
        clRed       = RGB(255, 0, 0),
        clDarkRed   = RGB(127, 0, 0),
        clGreen     = RGB(0, 255, 0),
        clDarkGreen = RGB(0, 127, 0),
        clBlue      = RGB(0, 0, 255),
        clDarkBlue  = RGB(0, 0, 127),
        clWhite     = RGB(255, 255, 255)
    };

    class CColor
    {
    private:
        COLORREF m_Color;

    public:
        CColor();
        CColor(const CColor& Color);
        CColor(ColorUnit Red, ColorUnit Green, ColorUnit Blue);
        CColor(ESystemColors Color);
        CColor(COLORREF Color);
        ~CColor();

        inline CColor& operator= (const COLORREF Color);
        inline CColor& operator= (const CColor&  Color);
        inline operator COLORREF() const;
    };
};

#endif //!WL_COLOR_H