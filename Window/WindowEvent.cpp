#ifndef WL_WINDOW_EVENT_IMPL_H
#define WL_WINDOW_EVENT_IMPL_H
#include <WinLib/Window/WindowEvent.hpp>

namespace Window
{
    inline CWindowEvent* CWindowEvent::getWndThis(LPARAM LParam)
    {
        return (CWindowEvent*)LPCREATESTRUCT(LParam)->lpCreateParams;
    }

    inline CWindowEvent* CWindowEvent::getWndThis(HWND Handle)
    {
        return (CWindowEvent*)CWindow::getWndThis(Handle);
    }

	void CWindowEvent::DefaultMessageProcessor(System::CEvent * Event)
    {
        Event->Result = m_DefWindowProc(*this, Event->Message, Event->WParam, Event->LParam);
    };

    LRESULT CALLBACK CWindowEvent::StartWindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
    {
        if (Message == WM_NCCREATE)
        {
            CWindowEvent* Window = getWndThis(LParam);
            CWindow::setWndThis(Handle, Window);
            Window->Attach(Handle);
            Window->setProc(WindowProcedure);
            return WindowProcedure(Handle, Message, WParam, LParam);
        }
        return ::DefWindowProc(Handle, Message, WParam, LParam);
    }

    LRESULT CALLBACK CWindowEvent::WindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
    {
        CWindowEvent* Window = getWndThis(Handle);
        System::CEvent Event(Message, WParam, LParam);

        if (Window != NULL)
        {
            Window->MessagePreProcessor (&Event);
            Window->MessageProcessor    (&Event);
            Window->MessagePostProcessor(&Event);
			if (Message == WM_NCDESTROY)
				Window->Detach();
            return Event.Result;
        }
        return ::DefWindowProc(Handle, Message, WParam, LParam);
    }
}

#endif //!WL_WINDOW_EVENT_IMPL_H