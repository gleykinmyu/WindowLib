#ifndef WL_TIMER_ROOT_HPP
#define WL_TIMER_ROOT_HPP
#include <Windows.h>

namespace SystemDetail
{
    class CTimerRoot
    {
    private:
        UINT_PTR m_TimerId = 0;

    public:
        inline bool setTimer(HWND Owner, UINT_PTR IdEvent, UINT Elapse, TIMERPROC TimerProcedure);
        inline bool killTimer(HWND Owner);
    };

    inline bool CTimerRoot::setTimer(HWND Owner, UINT_PTR IdEvent, UINT Elapse, TIMERPROC TimerProcedure)
    {
        UINT_PTR Result = ::SetTimer(Owner, IdEvent, Elapse, TimerProcedure);
        if (Result != 0)
        {
            if (IdEvent == 0)
                m_TimerId = Result;
            else
                m_TimerId = IdEvent;
        }
        return Result != 0;
    }

    inline bool CTimerRoot::killTimer(HWND Owner)
    {
        return true && ::KillTimer(Owner, m_TimerId);
    }
}

#endif //!WL_TIMER_ROOT_HPP