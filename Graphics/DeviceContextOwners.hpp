#ifndef WL_DEVICE_CONTEXT_OWNERS_HPP
#define WL_DEVICE_CONTEXT_OWNERS_HPP

#include <WinLib/Graphics/DeviceContextSafeHelpers.hpp>
#include <WinLib/Graphics/Pen.hpp>
#include <WinLib/Graphics/Brush.hpp>

namespace Graphics
{
	class COPainterDC : public CPaintDCsafe
	{
	public:
		CPenDC   Pen;
		CBrushDC Brush;
		COPainterDC(Window::CWindowHandle Owner);
		~COPainterDC();
	private:
		
	};
}

#endif // !WL_DEVICE_CONTEXT_OWNERS_HPP
