#ifndef WL_TIMER_CPP
#define WL_TIMER_CPP

#include <WinLib/System/Timer.hpp>
namespace System
{
    void CTimer::TimerProcedure(HWND Handle, UINT Message, UINT_PTR IdEvent, DWORD Time)
    {

    }

    bool CTimer::Create(Window::CWindow * Owner, UINT Elapse)
    {
        WL_ASSERT(Owner);
        return CTimerRoot::setTimer(*Owner, (UINT_PTR)this, Elapse, 0);
    }

    bool CTimer::Destroy()
    {
        return CTimerRoot::killTimer(*m_Owner);
    }
}
#endif //!WL_TIMER_CPP