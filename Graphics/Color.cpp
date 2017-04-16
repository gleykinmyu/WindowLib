#ifndef WL_COLOR_IMPL_H
#define WL_COLOR_IMPL_H

#include <WinLib/Graphics/Color.hpp>

namespace Graphics
{
    CColor::CColor()
        : m_Color(clBlack)
    {
    }

    CColor::CColor(const CColor & Color)
        : m_Color(Color.m_Color)
    {
    }

    CColor::CColor(ColorUnit Red, ColorUnit Green, ColorUnit Blue)
        : m_Color(RGB(Red, Green, Blue))
    {
    }

    CColor::CColor(ESystemColors Color)
        : m_Color(Color)
    {
    }

    CColor::CColor(COLORREF Color)
        : m_Color(Color)
    {
    }

    CColor::~CColor()
    {
    }

    inline CColor & CColor::operator=(const COLORREF Color)
    {
        m_Color = Color;
        return *this;
    }

    inline CColor & CColor::operator=(const CColor & Color)
    {
        m_Color = Color.m_Color;
        return *this;
    }

    inline CColor::operator COLORREF() const
    {
        return m_Color;
    }
}

#endif //!WL_COLOR_IMPL_H