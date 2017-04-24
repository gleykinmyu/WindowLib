#ifndef WL_PEN_H
#define WL_PEN_H

#include <Windows.h>
#include <WinLib/Graphics/ObjectHandleWraps.hpp>
#include <WinLib/Graphics/Color.hpp>
#include <WinLib/Graphics/Detail/PenRoot.hpp>

namespace Graphics
{
    class CPenDC : private GraphicsDetail::CPenS
    {
    public:
		CPenDC(CDeviceContext & DC);
		Utility::CProperty<Utility::RW, CColor,    CPenDC> Color;
        Utility::CProperty<Utility::RW, EPenStyle, CPenDC> Style;
        Utility::CProperty<Utility::RW, int,       CPenDC> Width;
	};

	class CPen : public GraphicsDetail::CPenG
	{
	public:
		CPen();

		Utility::CProperty<Utility::RO, CColor,    CPenG> Color;
		Utility::CProperty<Utility::RO, EPenStyle, CPenG> Style;
		Utility::CProperty<Utility::RO, int,       CPenG> Width;
	};
}


 
#endif //!WL_PEN_H