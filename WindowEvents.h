#pragma once
#include <windows.h>
#include "WindowHandle.h"

namespace wl
{
	class CEvent
	{
	public:
		WPARAM  WParam;
		LPARAM  LParam;
		UINT    Message;
		LRESULT Result;
	public:
		CEvent(UINT _Message, WPARAM _WParam, LPARAM _LParam) : Message(_Message), WParam(_WParam), LParam(_LParam) {}
	};

    //CBaseWindowM : M - Map - this class add MessageMap in CBaseWindowH
    class CBaseWindowM : public CBaseWindowH
    {
    protected:
        virtual bool MessageProcessor       (CEvent*) = 0;   // <- User must realise this function in his class

        virtual bool CommandProcessor       (CEvent*);       // <-Realise this function in your class, if you want to handle WM_COMMAND

        virtual void MessagePreProcessor    (CEvent*) {}     //<--\     Library calls PreProcessor before calling MessageProcessor
                                                             //    |--- For developers 
        virtual void MessagePostProcessor   (CEvent*) {}     //<--/     Library calls PostProcessor after calling MessageProcessor

        virtual void DefaultMessageProcessor(CEvent* Event); // <- Library call this function, if user don't handle message

        //StartWindowProcedure - Catch start window messages.  
        //When WM_CREATE message arrive, StartWindowProcedure do initializing work and call WindowProcedure.
        static LRESULT CALLBACK StartWindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);

        //WindowProcedure - Catch all Window Messages and call MessageProcessor.
        //If MessageProcessor don't handle message, WindowProcedure calls DefWindowProc.
        static LRESULT CALLBACK WindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);

    private:
        inline static CBaseWindowM* GetWndThis(LPARAM LParam);
        inline static CBaseWindowM* GetWndThis(HWND Handle);
    };

    bool CBaseWindowM::CommandProcessor(CEvent*)
    {
        return false;
    }

    void CBaseWindowM::DefaultMessageProcessor(CEvent * Event)
    {
        Event->Result = DefWindowProc(GetHandle(), Event->Message, Event->WParam, Event->LParam);
    };

    LRESULT CALLBACK CBaseWindowM::StartWindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
    {
        if (Message == WM_NCCREATE)
        {
            CBaseWindowM* Window = GetWndThis(LParam);
            SetWndThis(Handle, Window);
            Window->SetHandle(Handle);
            Window->SetProc(WindowProcedure);
            return WindowProcedure(Handle, Message, WParam, LParam);
        }
        return DefWindowProc(Handle, Message, WParam, LParam);
    }

    LRESULT CALLBACK CBaseWindowM::WindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
    {
        CBaseWindowM* Window = GetWndThis(Handle);
        CEvent        Event(Message, WParam, LParam);
        bool          Handled = false;

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
        }
        if (Handled == false) Window->DefaultMessageProcessor(&Event);
        return Event.Result;
    }

    inline CBaseWindowM * CBaseWindowM::GetWndThis(LPARAM LParam)
    {
        return (CBaseWindowM*)LPCREATESTRUCT(LParam)->lpCreateParams;
    }

    inline CBaseWindowM * CBaseWindowM::GetWndThis(HWND Handle)
    {
        return (CBaseWindowM*)CBaseWindowH::GetWndThis(Handle);
    }

    //=================================EVENT PROPERTY==========================================
    template<class OwnerType>
    class EventProperty
    {
    private:
        typedef bool (OwnerType::*Handler)(CEvent*);

        typedef void    (OwnerType::*SETTER)(Handler);
        typedef Handler(OwnerType::*GETTER)();

        SETTER Setter;
        GETTER Getter;
        OwnerType* Owner;
    public:
        void Init(OwnerType* _Owner, SETTER _Setter, GETTER _Getter)
        {
            Getter = _Getter;
            Setter = _Setter;
            Owner = _Owner;
        }

        template<class WindowType>
        void operator= (bool (WindowType::*EventHandler)(CEvent*))
        {
            (Owner->*Setter)(reinterpret_cast<bool (OwnerType::*)(CEvent*)>(EventHandler));
        }

        template<class WindowType>
        bool(WindowType::*operator() (CEvent*))
        {
            return (Owner->*Getter)(reinterpret_cast<bool (OwnerType::*)(CEvent*)>(EventHandler));
        }
    };

};