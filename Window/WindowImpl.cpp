#ifndef WL_WINDOW_IMPL_CPP
#define WL_WINDOW_IMPL_CPP

#include <WinLib/Window/WindowImpl.hpp>

namespace Window
{
	WndInfo::WNDINFOEX::WNDINFOEX() : wiStyle(wsNone), wiExStyle(wesNone)
	{
	}

    WndInfo::WndInfo()
    {
        WindowStruct.wiWindowName = TEXT("Default Window Name");

        WindowStruct.wiTop      = 20;
        WindowStruct.wiLeft     = 20;
        WindowStruct.wiWidth    = 50;
        WindowStruct.wiHeight   = 50;

        WindowStruct.wiMenu     = 0;
        WindowStruct.wiInstance = System::Module->Instance;
    }

    //============================================================================================================
    inline WndInfo& WndInfo::NStyle    (const CWndStyle   & _Style) { WindowStruct.wiStyle      = _Style;      return *this; }
    inline WndInfo& WndInfo::NExStyle  (const CWndExStyle & _Style) { WindowStruct.wiExStyle    = _Style;      return *this; }
    //============================================================================================================
    inline WndInfo& WndInfo::Style     (const CWndStyle   & _Style) { WindowStruct.wiStyle     |= _Style;      return *this; }
    inline WndInfo& WndInfo::ExStyle   (const CWndExStyle & _Style) { WindowStruct.wiExStyle   |= _Style;      return *this; }
    //============================================================================================================
    inline WndInfo& WndInfo::WindowName(LPCTSTR _WindowName       ) { WindowStruct.wiWindowName = _WindowName; return *this; }
    //============================================================================================================
    inline WndInfo& WndInfo::Top       (int _Top                  ) { WindowStruct.wiTop        = _Top;        return *this; }
    inline WndInfo& WndInfo::Left      (int _Left                 ) { WindowStruct.wiLeft       = _Left;       return *this; }
    inline WndInfo& WndInfo::Pos       (int _Left, int _Top       ) { WindowStruct.wiTop        = _Top;
                                                                      WindowStruct.wiLeft       = _Left;       return *this; }
    //============================================================================================================
    inline WndInfo& WndInfo::Width     (int _Width                ) { WindowStruct.wiWidth      = _Width;      return *this; }
    inline WndInfo& WndInfo::Height    (int _Height               ) { WindowStruct.wiHeight     = _Height;     return *this; }
    inline WndInfo& WndInfo::Size      (int _Width, int _Height   ) { WindowStruct.wiWidth      = _Width;
                                                                      WindowStruct.wiHeight     = _Height;     return *this; }
    //============================================================================================================
    inline WndInfo& WndInfo::Menu      (HMENU     _Menu           ) { WindowStruct.wiMenu       = _Menu;       return *this; }
    inline WndInfo& WndInfo::Instance  (HINSTANCE _Instance       ) { WindowStruct.wiInstance   = _Instance;   return *this; }

	bool CWindowImpl::Create(CWindowHandle Parent, LPCTSTR ClassName, WndInfo & WndInfo, LPVOID lpParam)
	{
		return 	CWindow::Create(
		WndInfo.WindowStruct.wiExStyle,
		ClassName,
		WndInfo.WindowStruct.wiWindowName,
		WndInfo.WindowStruct.wiStyle,
		WndInfo.WindowStruct.wiLeft,
		WndInfo.WindowStruct.wiTop,
		WndInfo.WindowStruct.wiWidth,
		WndInfo.WindowStruct.wiHeight,
		Parent,
		WndInfo.WindowStruct.wiMenu,
		WndInfo.WindowStruct.wiInstance,
		lpParam);
	}
}

#endif // !WL_WINDOW_IMPL_CPP