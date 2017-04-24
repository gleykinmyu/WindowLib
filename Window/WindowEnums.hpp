#ifndef WL_WINDOW_ENUMS_HPP
#define WL_WINDOW_ENUMS_HPP

#include <Windows.h>
#include <WinLib/Utility.hpp>

namespace Window
{
	enum EWndStyles
	{
		wsNone  = 0,
		wsPopup = WS_POPUP,

		wsClipChildren = WS_CLIPCHILDREN,
		wsChild        = WS_CHILD,

		wsMinimize = WS_MINIMIZE,
		wsMaximize = WS_MAXIMIZE,

		wsVsible   = WS_VISIBLE,
		wsDisabled = WS_DISABLED,

		wsCaption = WS_CAPTION,
		wsBorder  = WS_BORDER,

		wsVScroll = WS_VSCROLL,
		wsHScroll = WS_HSCROLL,

		wsOverlappedWindow = WS_OVERLAPPEDWINDOW
	};

	enum EWndExStyles
	{
		wesNone = 0,
		wesTransparent = WS_EX_TRANSPARENT,
		wesLayered = WS_EX_LAYERED
	};

	typedef DWORD WNDSTYLE;
	typedef DWORD WNDEXSTYLE;

	DECLARE_BIT_MASK_SAFE_CLASS(CWndStyle,   WNDSTYLE,   EWndStyles)
	DECLARE_BIT_MASK_SAFE_CLASS(CWndExStyle, WNDEXSTYLE, EWndExStyles)
}

#endif //!WL_WINDOW_ENUMS_HPP