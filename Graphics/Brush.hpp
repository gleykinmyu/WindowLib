#ifndef WL_BRUSH_H
#define WL_BRUSH_H

#include <Windows.h>
#include <WinLib/Utility.hpp>
#include <WinLib/Graphics/DeviceContext.hpp>
#include <WinLib/Graphics/Color.hpp>
#include <WinLib/Graphics/Detail/BrushRoot.hpp>

namespace Graphics
{
    enum EBrushStyle
    {
        bsHollow,
        bsSolid,
        bsHorizontal,
        bsVertical,
        bsFDiagonal,
        bsBDiagonal,
        bsCross,
        bsDiagCross
    };

    class CBrush : public GraphicsDetail::CBrushRoot
    {
    public:
        CBrush();

        Utility::CProperty<Utility::RW, CColor, CBrush> Color;
        Utility::CProperty<Utility::RW, EBrushStyle, CBrush> Style;

    private:
        void            m_ConvertToLogBrush(LOGBRUSH* LogBrush, EBrushStyle Style);
        EBrushStyle     m_ConvertFromLogBrush(const LOGBRUSH* LogBrush) const;
        void            m_Replace(const LOGBRUSH* LogBrush);

        CColor      getColor() const;
        EBrushStyle getStyle() const;

        void setColor(CColor Color);
        void setStyle(EBrushStyle Style);
    };
}
#endif //!WL_BRUSH_H