#ifndef WL_WINDOW_EVENT_IMPL_H
#define WL_WINDOW_EVENT_IMPL_H
#include <WinLib/Window/WindowEvent.hpp>

namespace Window
{
    LRESULT CALLBACK CWindowEvent::StartWindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
    {
        if (Message == WM_NCCREATE)
        {
            CWindowEvent* Window = getWndThis(LParam);
			setWndThis(Handle, Window);
            Window->Attach(Handle);
            Window->setProc(WindowProcedure);
            return WindowProcedure(Handle, Message, WParam, LParam);
        }
        return ::DefWindowProc(Handle, Message, WParam, LParam);
    }

    LRESULT CALLBACK CWindowEvent::WindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
    {
        CWindowEvent * Window = getWndThis(Handle);
        System::CMessage wl_Message(Message, WParam, LParam);
		
		bool Handled = false;

        if (Window != NULL)
        {
			switch (Message)
			{
			case WM_NCCREATE:
			case WM_SIZE:
			case WM_MOVE:
			case WM_THEMECHANGED:
			case WM_STYLECHANGED:
			case WM_DPICHANGED:
			case WM_WINDOWPOSCHANGED:
				Window->WindowParamsChangingProcessor(&wl_Message);
				Handled = true;
				break;
			default: break;
			}

                       Window->MessagePreProcessor (&wl_Message);
			Handled |= Window->MessageProcessor    (&wl_Message);        
			           Window->MessagePostProcessor(&wl_Message);
			
			if (Message == WM_NCDESTROY)
			{
				Window->Detach();
				clearWndThis(Handle);
			}

			if (Handled == false) Window->DefaultMessageProcessor(&wl_Message);
			return wl_Message.Result;
        }
		return ::DefWindowProc(Handle, Message, WParam, LParam);
    }
}

#endif //!WL_WINDOW_EVENT_IMPL_H