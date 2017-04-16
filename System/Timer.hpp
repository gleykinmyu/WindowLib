#ifndef WL_TIMER_HPP
#define WL_TIMER_HPP

#include <Windows.h>
#include <WinLib/Window.hpp>
#include <WinLib/System/Detail/TimerRoot.hpp>

namespace System
{
    class CTimer : public SystemDetail::CTimerRoot
    {
    private:
        Window::CWindow* m_Owner;
        static void CALLBACK TimerProcedure(HWND Handle, UINT Message, UINT_PTR IdEvent, DWORD Time);

    public:

        bool Create(Window::CWindow* Owner, UINT Elapse);

        bool Destroy();
    };
}
#endif //!WL_TIMER_H