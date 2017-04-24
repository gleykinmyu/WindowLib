#ifndef WL_WINDOW_DECL_IMPL_H
#define WL_WINDOW_DECL_IMPL_H
#include <WinLib/Window/WindowDecl.hpp>

namespace Window
{

	ClsInfo::ClsInfo()
	{
		ClsStruct.ciStyle      = csHRedraw | csVRedraw;
		ClsStruct.ciIcon       = 0;
		ClsStruct.ciCursor     = LoadCursor(0, IDC_ARROW);
		ClsStruct.ciBackground = HBRUSH(COLOR_WINDOW + 1);
		ClsStruct.ciMenuName   = 0;
		ClsStruct.ciClassName  = NULL;
		ClsStruct.ciIconSm     = 0;
		ClsStruct.ciInstance   = System::Module->Instance;
		ClsStruct.ciWndProc    = NULL;
	}

	//====================================================================================================

	inline ClsInfo& ClsInfo::NStyle    (const CClsStyle & _Style) { ClsStruct.ciStyle      = _Style;     return *this; }
	inline ClsInfo& ClsInfo::Style     (const CClsStyle & _Style) { ClsStruct.ciStyle     |= _Style;     return *this; }

	inline ClsInfo& ClsInfo::ClassName (LPCTSTR     _ClassName  ) { ClsStruct.ciClassName  = _ClassName; return *this; }
	inline ClsInfo& ClsInfo::Icon      (HICON       _Icon       ) { ClsStruct.ciIcon       = _Icon;      return *this; }
	inline ClsInfo& ClsInfo::IconSm    (HICON       _IconSm     ) { ClsStruct.ciIconSm     = _IconSm;    return *this; }
	inline ClsInfo& ClsInfo::Cursor    (HCURSOR     _Cursor     ) { ClsStruct.ciCursor     = _Cursor;    return *this; }
	inline ClsInfo& ClsInfo::Background(HBRUSH      _Brush      ) { ClsStruct.ciBackground = _Brush;     return *this; }
	inline ClsInfo& ClsInfo::MenuName  (LPCTSTR     _MenuName   ) { ClsStruct.ciMenuName   = _MenuName;  return *this; }
	inline ClsInfo& ClsInfo::Instance  (HINSTANCE   _Instance   ) { ClsStruct.ciInstance   = _Instance;  return *this; }
	inline ClsInfo& ClsInfo::WndProc   (WNDPROC     _WndProc    ) { ClsStruct.ciWndProc    = _WndProc;   return *this; }


    LPCTSTR CWindowDecl::wl_RegisterWindowClass(const ClsInfo & ClassInfo)
    {
		WNDCLASSEX WndStruct;

        if (wl_ClassExist(ClassInfo.ClsStruct.ciInstance, ClassInfo.ClsStruct.ciClassName)) return NULL;

        WndStruct.cbSize        = sizeof(WNDCLASSEX);

        WndStruct.hbrBackground = ClassInfo.ClsStruct.ciBackground;
        WndStruct.hCursor       = ClassInfo.ClsStruct.ciCursor;
        WndStruct.hIcon         = ClassInfo.ClsStruct.ciIcon;
        WndStruct.hIconSm       = ClassInfo.ClsStruct.ciIconSm;
        WndStruct.hInstance     = ClassInfo.ClsStruct.ciInstance;

		WndStruct.lpfnWndProc   = ClassInfo.ClsStruct.ciWndProc ? 
			ClassInfo.ClsStruct.ciWndProc : CWindowEvent::StartWindowProcedure;

		WndStruct.lpszClassName = ClassInfo.ClsStruct.ciClassName ?
			ClassInfo.ClsStruct.ciClassName : wl_FormatClassName();

        WndStruct.lpszMenuName  = ClassInfo.ClsStruct.ciMenuName;
        WndStruct.style         = ClassInfo.ClsStruct.ciStyle;

        WndStruct.cbClsExtra    = 0;
        WndStruct.cbWndExtra    = sizeof(this);

        ATOM Atom = RegisterClassEx(&WndStruct);

        if (Atom == 0)
        {
            WL_TRACE("WL couldn't register class: %s", WndStruct.lpszClassName);
            WL_ASSERT(0);
        }
        return WndStruct.lpszClassName;
    }

	LPCTSTR CWindowDecl::wl_RegisterWindowSuperClass(LPCTSTR ClassName, LPCTSTR OriginClassName)
	{
		WNDCLASSEX WndStruct;
		if (GetClassInfoEx(0, OriginClassName, &WndStruct) == 0) return NULL;

		WndStruct.cbSize = sizeof(WNDCLASSEX);
		setSuperProcedure(WndStruct.lpfnWndProc);
		WndStruct.lpfnWndProc = CWindowEvent::StartWindowProcedure;
		WndStruct.hInstance = System::Module->Instance;
		WndStruct.lpszClassName = ClassName ?
			ClassName : wl_FormatClassName();

		if (RegisterClassEx(&WndStruct) == 0) return NULL;

		return ClassName;
	}

    bool CWindowDecl::wl_ClassExist(HINSTANCE Instance, LPCTSTR ClassName)
    {
        WNDCLASSEX WndStruct;
        return (GetClassInfoEx(Instance, ClassName, &WndStruct) != 0);
    }

    LPCTSTR CWindowDecl::wl_FormatClassName()
    {
        snprintf(m_AutoName, 20, "WL::%p", this);
        return m_AutoName;
    }
}

#endif //!WL_WINDOW_DECL_IMPL_H