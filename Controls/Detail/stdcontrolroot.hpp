#ifndef WL_STD_CONTROL_ROOT
#define WL_STD_CONTROL_ROOT

#include <WinLib/Window.hpp>
#include <WinLib/Utility.hpp>

namespace ControlsDetail
{
    class CtrlInfo : public Window::WndInfo
    {

    };

    class CStdControlRoot : public Window::CWindowProperty<Window::CWindowImpl>
    {
    public:
        CStdControlRoot(LPCTSTR WinControlName);
        inline bool Create(Window::CWindowHandle * Parent, Window::WndInfo & Info);
		inline bool Create(Window::CWindowHandle & Parent, Window::WndInfo & Info);

    private:
		LPCTSTR m_ClassName = NULL;
		static LRESULT CALLBACK ControlProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);
        WNDPROC m_OwnControlProcedure;
    };
}

#endif //!WL_STD_CONTROL_ROOT
