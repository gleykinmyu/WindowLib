#ifndef WL_WINDOW_MESSAGES_HPP
#define WL_WINDOW_MESSAGES_HPP

#include <Windows.h>
#include <Windowsx.h>


//==============================================Message map========================================

#define WL_BEGIN_MESSAGE_MAP \
    virtual void MessageProcessor(System::CEvent* Event) \
        { \
            switch(Event->Message) \
            {

// void OnMsg(System::CEvent* Event)
#define WL_MSG_HANDLER(Msg, func) \
            case Msg: func(Event); break; 

#define WL_COMMAND_MAP \
			case WM_COMMAND: CommandProcessor(Event); break;

#define WL_NOTIFY_MAP 

#define WL_END_MASSAGE_MAP \
            default: DefaultMessageProcessor(Event); break; \
            } \
        }

//==========================================Command map============================================

#define WL_BEGIN_COMMAND_MAP \
        void CommandProcessor(System::CEvent* Event) \
        {

// void CtrlHandler(UINT NotifyCode) 
#define CMD_CTRL_HANDLER(Ctrl, func) \
        if ((HWND)Event->LParam == Ctrl) \
		{ \
		func((UINT)HIWORD(wParam)); \
		Event->Result = 0; \
		return; \
		}

// void CtrlHandler(UINT NotifyCode) 
#define CMD_CTRL_ID_HANDLER(CtrlID, func) \
        if ((int)LOWORD(Event->WParam) == CtrlID) \
		{ \
		func((UINT)HIWORD(wParam)); \
		Event->Result = 0; \
		return; \
		}

// void OnAccel()
#define CMD_ACCEL_HANDLER(AccelID, func) \
		if ((int)LOWORD(Event->WParam) == AccelID && (int)HIWORD(Event->WParam) == 1 && Event->LParam == 0) \
		{ \
		func(); \
		Event->Result = 0; \
		return; \
		}

// void AccelProcessor(int AccelID);
#define CMD_ACCEL_PROCESSOR(func) \
		if ((int)HIWORD(Event->WParam) == 1 && Event->LParam == 0) \
		{ \
		func((int)LOWORD(wParam)); \
		Event->Result = 0; \
		return; \
		}

// void OnMenu()
#define CMD_MENU_HANDLER(AccelID, func) \
		if ((int)LOWORD(Event->WParam) == AccelID && (int)HIWORD(Event->WParam) == 0 && Event->LParam == 0) \
		{ \
		func(); \
		Event->Result = 0; \
		return; \
		}

// void MenuProcessor(int MenuID)
#define CMD_MENU_PROCESSOR(func) \
		if ((int)HIWORD(Event->WParam) == 0 && Event->LParam == 0) \
		{ \
		func((int)LOWORD(wParam)); \
		Event->Result = 0; \
		return; \
		}

#define WL_END_COMMAND_MAP \
        DefaultMessageProcessor(Event); \
        }

//=================================================================================================

// LRESULT OnCreate(CREATESTRUCT* CreateStruct)
#define WL_CREATE_HANDLER(func) \
case WM_CREATE: Event->Result = func((CREATESTRUCT*)Event->LParam); break;

// void OnDestroy()
#define WL_DESTROY_HANDLER(func) \
case WM_DESTROY: Event->Result = 0; func(); break;

// void OnMove(int Left, int Top)
#define WL_MOVE_HANDLER(func) \
case WM_MOVE: Event->Result = 0; func(GET_X_LPARAM(Event->LParam), GET_Y_LPARAM(Event->LParam)); break;

// void OnSize(UINT Type, int Width, int Height)
#define WL_SIZE_HANDLER(func) \
case WM_SIZE: Event->Result = 0; func((UINT)Event->WParam, GET_X_LPARAM(Event->LParam), GET_Y_LPARAM(Event->LParam)); break;

// void OnActivate(UINT State, bool Minimized, HWND Other)
#define WL_ACTIVATE_HANDLER(func) \
case WM_ACTIVATE: Event->Result = 0; func((UINT)LOWORD(Event->WParam), (bool)HIWORD(Event->WParam), (HWND)Event->LParam); break;

// void OnSetFocus(HWND OldWnd)
#define WL_SETFOCUS_HANDLER(func) \
case WM_SETFOCUS: Event->Result = 0; func((HWND)Event->WParam); break;

// void OnKillFocus(HWND FocusWnd)
#define WL_KILLFOCUS_HANDLER(func) \
case WM_KILLFOCUS: Event->Result = 0; func((HWND)Event->WParam); break;

// void OnEnable(bool Enabled)
#define WL_ENABLE_HANDLER(func) \
case WM_ENABLE: Event->Result = 0; func((bool)Event->WParam); break;

// void OnPaint()
#define WL_PAINT_HANDLER(func) \
case WM_PAINT: Event->Result = 0; func(); break;

// void OnClose()
#define WL_CLOSE_HANDLER(func) \
case WM_CLOSE: Event->Result = 0; func(); break;

// void OnTimer(UINT_PTR nIDEvent)
#define WL_TIMER_HANDLER(func) \
case WM_TIMER: Event->Result = 0; func((UINT_PTR)Event->WParam); break;

#endif // !WL_WINDOW_MESSAGES_HPP
