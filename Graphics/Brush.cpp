 #ifndef WL_BRUSH_IMPL_H
#define WL_BRUSH_IMPL_H
#include <Windows.h>
#include <WinLib/Graphics/Brush.hpp>

namespace Graphics
{
    CBrushDC::CBrushDC(CDeviceContext & DC) : CBrushS(DC)
    {
        Style.Init(this, &CBrushDC::getStyle, &CBrushDC::setStyle);
        Color.Init(this, &CBrushDC::getColor, &CBrushDC::setColor);
    }

	CBrush::CBrush()
	{
		Style.Init(this, &CBrush::getStyle);
		Color.Init(this, &CBrush::getColor);
	}

}

#endif // !WL_BRUSH_IMPL_H
