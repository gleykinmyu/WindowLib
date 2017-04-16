#ifndef WL_PEN_H
#define WL_PEN_H

#include <Windows.h>
#include <WinLib/Graphics/DeviceContext.hpp>
#include <WinLib/Graphics/Color.hpp>
#include <WinLib/Graphics/Detail/PenRoot.hpp>

namespace Graphics
{
    enum EPenStyle
    {
        psSolid     = PS_SOLID,      /*__________*/
        psDash      = PS_DASH,       /* -------  */
        psDot       = PS_DOT,        /* .......  */
        psDashDot   = PS_DASHDOT,    /* _._._._  */
        psDasDotDot = PS_DASHDOTDOT, /* _.._.._  */
        psNull      = PS_NULL
    };

    class CPen : public GraphicsDetail::CPenRoot
    {
    public:
        CPen();

        Utility::CProperty<Utility::RW, CColor,    CPen> Color;
        Utility::CProperty<Utility::RW, EPenStyle, CPen> Style;
        Utility::CProperty<Utility::RW, int,       CPen> Width;

    private:
        //====================================Getters==============================================
        CColor    getColor() const;
        EPenStyle getStyle() const;
        int       getWidth() const;

        //=========================================Setters=========================================
        void setColor(CColor Color);
        void setStyle(EPenStyle Style);
        void setWidth(int Width);

        //========================================Service==========================================
        EPenStyle ConvertToStyle(UINT Style) const;
        void m_Replace(LOGPEN * LogPen);
    };
}


 
#endif //!WL_PEN_H