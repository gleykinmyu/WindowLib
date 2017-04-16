#ifndef WL_EVENTS_CPP
#define WL_EVENTS_CPP
#include <WinLib/System/Events.hpp>

namespace System
{
    CEvent::CEvent(UINT _Message, WPARAM _WParam, LPARAM _LParam) :
        Message(_Message), WParam(_WParam), LParam(_LParam), Result(0)
    {

    }
}

#endif //!WL_EVENTS_CPP