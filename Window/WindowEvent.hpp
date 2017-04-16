#ifndef WL_WINDOW_EVENT_H
#define WL_WINDOW_EVENT_H

#include <windows.h>
#include <WinLib/Window/WindowHandle.hpp>
#include <WinLib/Window/WindowImpl.hpp>
#include <WinLib/Window/WindowMessages.hpp>
#include <WinLib/System.hpp>
#include <WinLib/Utility.hpp>

namespace Window
{
    class WL_NOVTABLE CWindowEvent : public CWindowImpl
    {
	public:
		CWindowEvent() {WL_CTOR_TRACE;}
    protected:
        virtual void MessageProcessor       (System::CEvent*) = 0;   // <- User must realise this function in his class

        virtual void MessagePreProcessor    (System::CEvent*) {}     //<--\     Library calls PreProcessor before calling MessageProcessor
                                                                     //    |--- For developers 
        virtual void MessagePostProcessor   (System::CEvent*) {}     //<--/     Library calls PostProcessor after calling MessageProcessor
        
                void DefaultMessageProcessor(System::CEvent* Event); // <- Library call this function, if user don't handle message

        //StartWindowProcedure - Catch first 5 window messages.  
        //When WM_NCCREATE message arrive, StartWindowProcedure do initializing work and call DefaultMessageProcessor.
        static LRESULT CALLBACK StartWindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);

        //WindowProcedure - Catch all Window Messages and call MessageProcessor.
        //If MessageProcessor don't handle message, WindowProcedure calls DefWindowProc.
        static LRESULT CALLBACK WindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);

    private:
        inline static CWindowEvent* getWndThis(LPARAM LParam);
        inline static CWindowEvent* getWndThis(HWND Handle);

		WNDPROC m_DefWindowProc = ::DefWindowProc;
    };
};
        
#endif //!WL_WINDOW_EVENT_H