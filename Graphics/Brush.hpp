#ifndef WL_BRUSH_H
#define WL_BRUSH_H

#include <Windows.h>
#include <WinLib/Utility.hpp>
#include <WinLib/Graphics/ObjectHandleWraps.hpp>
#include <WinLib/Graphics/Color.hpp>
#include <WinLib/Graphics/Detail/BrushRoot.hpp>

namespace Graphics
{
    
    class CBrushDC : private GraphicsDetail::CBrushS
    {
    public:
        CBrushDC(CDeviceContext & DC);

        Utility::CProperty<Utility::RW, CColor,      CBrushDC> Color;
        Utility::CProperty<Utility::RW, EBrushStyle, CBrushDC> Style;
    };

	class CBrush : public GraphicsDetail::CBrushG
	{
	public:
		CBrush();

		Utility::CProperty<Utility::RO, CColor,      CBrush> Color;
		Utility::CProperty<Utility::RO, EBrushStyle, CBrush> Style;
	};

}
#endif //!WL_BRUSH_H