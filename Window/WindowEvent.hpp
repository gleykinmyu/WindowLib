#ifndef WL_WINDOW_EVENT_H
#define WL_WINDOW_EVENT_H

#include <Windows.h>
#include <WinLib/Window/WindowHandle.hpp>
#include <WinLib/Window/WindowImpl.hpp>
#include <WinLib/Window/WindowMessages.hpp>
#include <WinLib/System.hpp>
#include <WinLib/Utility.hpp>

namespace Window
{
    class CWindowEvent : public CWindowImpl
    {
	public:
		bool Create(CWindowHandle Parent, LPCTSTR ClassName, WndInfo & Info);

    protected:
        virtual bool MessageProcessor             (System::CMessage * ) = 0;   // <- User must realise this function in his class

        virtual void MessagePreProcessor          (System::CMessage * ) {}     //<--\     Library calls PreProcessor before calling MessageProcessor
                                                                              //    |--- For developers 
        virtual void MessagePostProcessor         (System::CMessage * ) {}     //<--/     Library calls PostProcessor after calling MessageProcessor
        
		virtual void WindowParamsChangingProcessor(System::CMessage *) {};

                void DefaultMessageProcessor      (System::CMessage * Event);  // <- Library call this function, if user don't handle message

        //StartWindowProcedure - Catch first 5 window messages.  
        //When WM_NCCREATE message arrive, StartWindowProcedure do initializing work and call DefaultMessageProcessor.
        static LRESULT CALLBACK StartWindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);

        //WindowProcedure - Catch all Window Messages and call MessageProcessor.
        //If MessageProcessor don't handle message, WindowProcedure calls DefWindowProc.
        static LRESULT CALLBACK WindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);

		inline void setSuperProcedure(WNDPROC SuperProc);

    private:
        inline static CWindowEvent * getWndThis  (LPARAM LParam);
        inline static CWindowEvent * getWndThis  (HWND Handle);
		inline static bool           setWndThis  (HWND Handle, CWindowEvent * This);
		inline static bool           clearWndThis(HWND Handle);

		WNDPROC m_DefWindowProc = ::DefWindowProc;
    };

	inline void CWindowEvent::setSuperProcedure(WNDPROC SuperProc)
	{
		WL_ASSERT(SuperProc != NULL);
		m_DefWindowProc = SuperProc;
	}

	inline CWindowEvent* CWindowEvent::getWndThis(LPARAM LParam)
	{
		return (CWindowEvent*)((CREATESTRUCT*)LParam)->lpCreateParams;
	}

	inline CWindowEvent* CWindowEvent::getWndThis(HWND Handle)
	{
		return (CWindowEvent*)WindowMap.getWindowThis(Handle);
	}

	inline bool CWindowEvent::setWndThis(HWND Handle, CWindowEvent * This)
	{
		return WindowMap.AddWindow(Handle, This);
	}

	inline bool CWindowEvent::clearWndThis(HWND Handle)
	{
		return WindowMap.DeleteWindow(Handle);
	}

	inline bool CWindowEvent::Create(CWindowHandle Parent, LPCTSTR ClassName, WndInfo & Info)
	{
		return CWindowImpl::Create(Parent, ClassName, Info, this);
	}

	inline void CWindowEvent::DefaultMessageProcessor(System::CMessage * Event)
	{
		Event->Result = ::CallWindowProc(m_DefWindowProc, this->getHandle(), Event->Message, Event->WParam, Event->LParam);
	};
};
        
#endif //!WL_WINDOW_EVENT_H