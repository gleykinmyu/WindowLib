#ifndef WL_MESSAGE_LOOP_CPP
#define WL_MESSAGE_LOOP_CPP

#include <WinLib/System/MessageLoop.hpp>

namespace System
{
	void CMessageLoop::Run()
	{
		MSG msg;
		while (GetMessage(&msg, 0, 0, 0) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}	
}
#endif //!WL_MESSAGE_LOOP_CPP