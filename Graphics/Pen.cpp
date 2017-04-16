#ifndef WL_PEN_CPP
#define WL_PEN_CPP

#include "Pen.hpp"

namespace Graphics
{
    CPen::CPen()
    {
        Style.Init(this, &CPen::getStyle, &CPen::setStyle);
        Color.Init(this, &CPen::getColor, &CPen::setColor);
        Width.Init(this, &CPen::getWidth, &CPen::setWidth);
    }

    CColor Graphics::CPen::getColor() const
    {
        LOGPEN logPen = {};
        getInfo(&logPen);
        return CColor(logPen.lopnColor);
    }

    EPenStyle Graphics::CPen::getStyle() const
    {
        LOGPEN logPen = {};
        getInfo(&logPen);
        return ConvertToStyle(logPen.lopnStyle);
    }

    int Graphics::CPen::getWidth() const
    {
        LOGPEN logPen = {};
        getInfo(&logPen);
        return logPen.lopnWidth.x;
    }

    void Graphics::CPen::setColor(CColor Color)
    {
        LOGPEN logPen = {};
        getInfo(&logPen);
        logPen.lopnColor = Color;
        m_Replace(&logPen);
    }

    void Graphics::CPen::setStyle(EPenStyle Style)
    {
        LOGPEN logPen = {};
        getInfo(&logPen);
        logPen.lopnStyle = Style;
        m_Replace(&logPen);
    }

    void Graphics::CPen::setWidth(int Width)
    {
        WL_ASSERT(Width >= 0);
        LOGPEN logPen = {};
        getInfo(&logPen);
        logPen.lopnWidth.x = Width;
        logPen.lopnWidth.y = 0;
        m_Replace(&logPen);
    }

    EPenStyle Graphics::CPen::ConvertToStyle(UINT Style) const
    {
        switch (Style)
        {
        case PS_SOLID:      return psSolid;
        case PS_DASH:       return psDash;
        case PS_DOT:        return psDot;
        case PS_DASHDOT:    return psDashDot;
        case PS_DASHDOTDOT: return psDasDotDot;
        case PS_NULL:       return psNull;
        default: WL_TRACE("There is no suitable conversion from PENSTYLE to EPenStyle!!!");
        }
        return psNull;
    }

    void Graphics::CPen::m_Replace(LOGPEN * LogPen)
    {
        GraphicsDetail::CPenRoot NewPen;
        if (NewPen.CreateIndirect(LogPen) == true)
        {
            Delete();
            Attach(NewPen.Detach());
        }
    }
}
#endif //!WL_PEN_CPP