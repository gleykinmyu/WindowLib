 #ifndef WL_BRUSH_IMPL_H
#define WL_BRUSH_IMPL_H
#include <Windows.h>
#include <WinLib/Graphics/Brush.hpp>

namespace Graphics
{
    CBrush::CBrush()
    {
        Style.Init(this, &CBrush::getStyle, &CBrush::setStyle);
        Color.Init(this, &CBrush::getColor, &CBrush::setColor);
    }

    void CBrush::m_ConvertToLogBrush(LOGBRUSH* LogBrush, EBrushStyle Style)
    {
        switch (Style)
        {
        case bsHollow:     LogBrush->lbStyle = BS_HOLLOW;                                     break;
        case bsSolid:      LogBrush->lbStyle = BS_SOLID;                                      break;
        case bsHorizontal: LogBrush->lbStyle = BS_HATCHED; LogBrush->lbHatch = HS_HORIZONTAL; break;
        case bsVertical:   LogBrush->lbStyle = BS_HATCHED; LogBrush->lbHatch = HS_VERTICAL;   break;
        case bsFDiagonal:  LogBrush->lbStyle = BS_HATCHED; LogBrush->lbHatch = HS_FDIAGONAL;  break;
        case bsBDiagonal:  LogBrush->lbStyle = BS_HATCHED; LogBrush->lbHatch = HS_BDIAGONAL;  break;
        case bsCross:      LogBrush->lbStyle = BS_HATCHED; LogBrush->lbHatch = HS_CROSS;      break;
        case bsDiagCross:  LogBrush->lbStyle = BS_HATCHED; LogBrush->lbHatch = HS_DIAGCROSS;  break;
        }
    }

    EBrushStyle CBrush::m_ConvertFromLogBrush(const LOGBRUSH* LogBrush) const
    {
        switch (LogBrush->lbStyle)
        {
        case BS_SOLID: return bsSolid;

        case BS_HATCHED:
            switch (LogBrush->lbHatch)
            {
            case HS_BDIAGONAL:  return bsBDiagonal;
            case HS_CROSS:      return bsCross;
            case HS_DIAGCROSS:  return bsDiagCross;
            case HS_FDIAGONAL:  return bsFDiagonal;
            case HS_HORIZONTAL: return bsHorizontal;
            case HS_VERTICAL:   return bsVertical;
            default: WL_TRACE("There is no suitable conversion from LOGBRUSH to EBrushStyle!!!"); WL_ASSERT(0); break;
            }
            break;
        case BS_HOLLOW: return bsHollow;
        default: WL_TRACE("There is no suitable conversion from LOGBRUSH to EBrushStyle!!!"); WL_ASSERT(0); break;
        }
        return bsHollow;
    }

    void CBrush::m_Replace(const LOGBRUSH * LogBrush)
    {
        GraphicsDetail::CBrushRoot NewBrush;
        if (NewBrush.CreateIndirect(LogBrush) == true)
        {
            Delete();
            Attach(NewBrush.Detach());
        }
    }

    CColor CBrush::getColor() const
    {
        LOGBRUSH logBrush = {};
        getInfo(&logBrush);
        return CColor(logBrush.lbColor);
    }

    EBrushStyle CBrush::getStyle() const
    {
        LOGBRUSH logBrush = {};
        getInfo(&logBrush);
        return m_ConvertFromLogBrush(&logBrush);
    }

    void CBrush::setColor(CColor Color)
    {
        LOGBRUSH logBrush = {};
        getInfo(&logBrush);
        logBrush.lbColor = Color;
        m_Replace(&logBrush);
    }

    void CBrush::setStyle(EBrushStyle Style)
    {
        LOGBRUSH logBrush = {};
        getInfo(&logBrush);
        m_ConvertToLogBrush(&logBrush, Style);
        m_Replace(&logBrush);
    }
}

#endif // !WL_BRUSH_IMPL_H
