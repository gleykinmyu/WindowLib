#ifndef WL_EVENTS_H
#define WL_EVENTS_H
#include <Windows.h>

namespace System
{
    class CEvent
    {
    public:
        WPARAM  WParam;
        LPARAM  LParam;
        UINT    Message;
        LRESULT Result;
        CEvent(UINT _Message, WPARAM _WParam, LPARAM _LParam);
    };
}

#endif //!WL_EVENTS_H
