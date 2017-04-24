#ifndef WL_PEN_CPP
#define WL_PEN_CPP

#include "Pen.hpp"

namespace Graphics
{
	CPenDC::CPenDC(CDeviceContext & DC) : CPenS(DC)
	{
		Color.Init(this, &CPenDC::getColor, &CPenDC::setColor);
		Width.Init(this, &CPenDC::getWidth, &CPenDC::setWidth);
		Style.Init(this, &CPenDC::getStyle, &CPenDC::setStyle);
	}

	CPen::CPen()
	{
		Color.Init(this, &CPen::getColor);
		Width.Init(this, &CPen::getWidth);
		Style.Init(this, &CPen::getStyle);
	}
}
#endif //!WL_PEN_CPP