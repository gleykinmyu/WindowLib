#pragma once
#include <windows.h>
#include "Window.h"
#include "WLDefines.h"

namespace wl
{
    class CEvent
    {
    public:
        WPARAM  WParam;
        LPARAM  LParam;
        UINT    Message;
        LRESULT Result;
        CEvent(UINT _Message,  WPARAM _WParam,  LPARAM _LParam) : 
            Message(_Message), WParam(_WParam), LParam(_LParam), Result(0) {}
    };

    //CWindowEvent : M - Map - this class add MessageMap in CWindow
    class CWindowEvent : public CWindow
    {
    protected:
        virtual bool MessageProcessor       (CEvent*) = 0;   // <- User must realise this function in his class

        virtual bool CommandProcessor       (CEvent*);       // <-Realise this function in your class, if you want to handle WM_COMMAND

        virtual void MessagePreProcessor    (CEvent*) {}     //<--\     Library calls PreProcessor before calling MessageProcessor
                                                             //    |--- For developers 
        virtual void MessagePostProcessor   (CEvent*) {}     //<--/     Library calls PostProcessor after calling MessageProcessor
        
        virtual void DefaultMessageProcessor(CEvent* Event); // <- Library call this function, if user don't handle message

        //StartWindowProcedure - Catch first 5 window messages.  
        //When WM_NCCREATE message arrive, StartWindowProcedure do initializing work and call DefaultMessageProcessor.
        static LRESULT CALLBACK StartWindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);

        //WindowProcedure - Catch all Window Messages and call MessageProcessor.
        //If MessageProcessor don't handle message, WindowProcedure calls DefWindowProc.
        static LRESULT CALLBACK WindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);

    private:
        inline static CWindowEvent* GetWndThis(LPARAM LParam);
        inline static CWindowEvent* GetWndThis(HWND Handle);
    };

    bool CWindowEvent::CommandProcessor(CEvent*)
    {
        return false;
    }

    void CWindowEvent::DefaultMessageProcessor(CEvent * Event)
    {
        Event->Result = DefWindowProc(GetHandle(), Event->Message, Event->WParam, Event->LParam);
    };

    LRESULT CALLBACK CWindowEvent::StartWindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
    {
        if (Message == WM_NCCREATE)
        {
            CWindowEvent* Window = GetWndThis(LParam);
            CWindow::SetWndThis(Handle, Window);
            Window->SetHandle(Handle);
            Window->SetProc(WindowProcedure);
            return WindowProcedure(Handle, Message, WParam, LParam);
        }
        return DefWindowProc(Handle, Message, WParam, LParam);
    }

    LRESULT CALLBACK CWindowEvent::WindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
    {
        CWindowEvent* Window = GetWndThis(Handle);
        CEvent          Event(Message, WParam, LParam);
        bool            Handled = false;

        if (Window != NULL)
        {
            Window->MessagePreProcessor(&Event);
            switch (Message)
            {
            case WM_COMMAND: 
                Handled = Window->CommandProcessor(&Event); 
                break;
            default:         
                Handled = Window->MessageProcessor(&Event); 
                break;
            }
            Window->MessagePostProcessor(&Event);

            if (Handled == false) 
                Window->DefaultMessageProcessor(&Event);
            return Event.Result;
        }
        return ::DefWindowProcA(Handle, Message, WParam, LParam);
    }

    inline CWindowEvent* CWindowEvent::GetWndThis(LPARAM LParam)
    {
        return (CWindowEvent*)LPCREATESTRUCT(LParam)->lpCreateParams;
    }

    inline CWindowEvent* CWindowEvent::GetWndThis(HWND Handle)
    {
        return (CWindowEvent*)CWindow::GetWndThis(Handle);
    }
};