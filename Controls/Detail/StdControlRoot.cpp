#ifndef WL_STD_CONTROL_ROOT_CPP
#define WL_STD_CONTROL_ROOT_CPP

#include <WinLib/Controls/Detail/StdControlRoot.hpp>

namespace ControlsDetail
{
    CStdControlRoot::CStdControlRoot(LPCTSTR WinControlName)
    {
		WL_ASSERT(WinControlName != NULL);
		m_ClassName = WinControlName;
        WNDCLASSEX WndStruct;
        ::GetClassInfoEx(System::Module->Instance, WinControlName, &WndStruct);
        m_OwnControlProcedure = WndStruct.lpfnWndProc;
    }

	LRESULT CALLBACK CStdControlRoot::ControlProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		LRESULT Result = ::CallWindowProc(((CStdControlRoot*)getWndThis(Handle))->m_OwnControlProcedure, Handle, Message, WParam, LParam);
		if (Message == WM_NCDESTROY)
			getWndThis(Handle)->Detach();
		return Result;
	}

    bool CStdControlRoot::Create(Window::CWindowHandle * Parent, Window::WndInfo & Info)
    {
        bool Result = Window::CWindowImpl::Create(Parent, m_ClassName, Info.Style(Window::wsChild));
		//if (Result == true) setProc(ControlProcedure);
		return Result;
    }

	bool CStdControlRoot::Create(Window::CWindowHandle & Parent, Window::WndInfo & Info)
	{
		bool Result = Window::CWindowImpl::Create(Parent, m_ClassName, Info.Style(Window::wsChild));
		//if (Result == true) setProc(ControlProcedure);
		return Result;
	}
}

#endif //!WL_STD_CONTROL_ROOT_CPP