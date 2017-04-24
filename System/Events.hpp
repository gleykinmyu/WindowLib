#ifndef WL_EVENTS_H
#define WL_EVENTS_H
#include <Windows.h>

namespace System
{
    class CMessage
    {
    public:
        WPARAM  WParam;
        LPARAM  LParam;
        UINT    Message;
        LRESULT Result;
        inline CMessage(UINT _Message, WPARAM _WParam, LPARAM _LParam);
    };

	inline CMessage::CMessage(UINT _Message, WPARAM _WParam, LPARAM _LParam) :
		Message(_Message), WParam(_WParam), LParam(_LParam), Result(0)
	{

	}
}

#endif //!WL_EVENTS_H
