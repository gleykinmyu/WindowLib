#pragma once
#include <Windows.h>
#include <assert.h>
#include "CProperty.h"

#define NULLHWND (HWND)0
#define NOFLAGS 0

#define WINASSERT(expression) if(!(expression)) assert(!"Window id not exist!!!");

class CApplication
{
public:
	CApplication() { }
	HINSTANCE hInstance;
};

CApplication Application;

//CBaseWindow - base class of WinLibrary
class CBaseWindow
{
public:
	CBaseWindow() : m_Handle(NULL), m_Exist(false) {}
	HWND GetHandle() const { return m_Handle; }
private:
	HWND m_Handle;
	bool m_Exist;
//==============================================================================================================================
public:

	bool Create(DWORD ExStyle, 
		      LPCTSTR ClassName, 
		      LPCTSTR WindowName, 
		        DWORD Style, 
		int Left, int Top, int Width, int Height, 
		         HWND Parent, 
		        HMENU Menu, 
		    HINSTANCE Instance,
		 LPVOID LParam)
	{
		m_Handle = CreateWindowEx(ExStyle, ClassName, WindowName, Style, Left, Top, Width, Height, Parent, Menu, Instance, LParam);
		m_Exist = (m_Handle != NULL);
		return m_Exist;
	}
//=========================================================================================================================================
	bool Close()
	{
		WINASSERT(m_Exist);
		if ( CloseWindow(m_Handle) ) return true;
		else return false;
	}

	bool Destroy()
	{
		WINASSERT(m_Exist);
		if (DestroyWindow(m_Handle) == FALSE)
			return false;
		m_Handle = NULL;
		return true;
	}
//=========================================================================================================================================
	HWND GetHandle() 
	{ 
		WINASSERT(m_Exist);
		return m_Handle; 
	}

	LONG_PTR GetWndStyle()
	{
		WINASSERT(m_Exist);
		return GetWindowLongPtr(m_Handle, GWL_STYLE);
	}

	LONG_PTR GetWndExStyle()
	{
		WINASSERT(m_Exist);
		return GetWindowLongPtr(m_Handle, GWL_EXSTYLE);
	}

	WNDPROC GetWndProc()
	{
		WINASSERT(m_Exist);
		return (WNDPROC)GetWindowLongPtr(m_Handle, GWLP_WNDPROC);
	}

	HINSTANCE GetWndInstance()
	{
		WINASSERT(m_Exist);
		return (HINSTANCE)GetWindowLongPtr(m_Handle, GWLP_HINSTANCE);
	}

	HWND GetWndParent()
	{
		WINASSERT(m_Exist);
		return (HWND)GetWindowLongPtr(m_Handle, GWLP_HWNDPARENT);
	}

	LONG_PTR GetWndID()
	{
		WINASSERT(m_Exist);
		return GetWindowLongPtr(m_Handle, GWLP_ID);
	}

	static CBaseWindow* GetWndThis(HWND Handle)
	{
		WINASSERT(IsWindow(Handle));
		return (CBaseWindow*)GetWindowLongPtr(Handle, GWLP_USERDATA);
	}
//=========================================================================================================================================
	void SetHandle(HWND Handle)
	{
		if (IsWindow(Handle))
		{
			m_Exist = true;
			m_Handle = Handle;
		}
		else m_Exist = false;
	}
	
	 void SetWndStyle(LONG_PTR Style)
	{
		WINASSERT(m_Exist);
		SetLastError(0);
		SetWindowLongPtr(m_Handle, GWL_STYLE, Style);
	}

	void SetWndExStyle(LONG_PTR ExStyle)
	{
		WINASSERT(m_Exist);
		SetLastError(0);
		SetWindowLong(m_Handle, GWL_EXSTYLE, ExStyle);
	}

	static void SetWndThis(HWND Handle, CBaseWindow* This)
	{
		WINASSERT(IsWindow(Handle));
		SetLastError(0);
		SetWindowLong(Handle, GWLP_USERDATA, (LONG_PTR)This);
	}

	void SetWndProc(WNDPROC WndProc)
	{
		WINASSERT(m_Exist);
		SetLastError(0);
		SetWindowLong(m_Handle, GWLP_WNDPROC, (LONG_PTR)WndProc);
	}

	void SetWndID(LONG_PTR ID)
	{
		WINASSERT(m_Exist);
		SetLastError(0);
		SetWindowLong(m_Handle, GWLP_ID, ID);
	}

	void SetWndInstance(HINSTANCE HInstance)
	{
		WINASSERT(m_Exist);
		SetLastError(0);
		SetWindowLong(m_Handle, GWLP_WNDPROC, (LONG_PTR)HInstance);
	}

//=========================================================================================================================================
	HWND SetWndParent(HWND newParent)
	{
		WINASSERT(m_Exist);
		if (newParent == NULL)
		{
			SetWndStyle(GetWndStyle() & (~WS_CHILD));
		}
		else
		{
			DWORD Style = GetWndStyle();
			SetWndStyle(Style | WS_CHILD);
		}
		SetLastError(0);
		return SetParent(m_Handle, newParent);
	}

//=========================================================================================================================================
	bool SetWndText(LPCTSTR Text)
	{
		WINASSERT(m_Exist);
		if ( SetWindowText(m_Handle, Text) ) return true;
		return false;
	}

	int GetWndText(LPTSTR Text, int Quantity)
	{
		WINASSERT(m_Exist);
		return GetWindowText(m_Handle, Text, Quantity);
	}

//=========================================================================================================================================
	bool GetWndRect(LPRECT Rect)
	{
		WINASSERT(m_Exist);
		if ( GetWindowRect(m_Handle, Rect) ) return true;
		return false;
	}

	bool SetWndPos(HWND hWndInsertAfter, int Left, int Top, int Width, int Height, UINT Flags) 
	{
		WINASSERT(m_Exist);
		if ( SetWindowPos(m_Handle, hWndInsertAfter, Left, Top, Width, Height, Flags) ) return true;
		return false;
	}
//=========================================================================================================================================
};

//=========================================================================================================================================

//CBaseWindowM : M - Map - this class add MessageMap in CBaseWindow
class CBaseWindowM : public CBaseWindow
{
public:
	CBaseWindowM() {}
#define BEGIN_MESSAGE_MAP \
protected: \
	virtual bool MessageProcessor(LRESULT* Result, UINT Message, WPARAM WParam, LPARAM LParam) \
	{ \
		switch(Message) \
		{

#define ADD_MESSAGE_HANDLER(Msg, Handler) \
		case Msg : return Handler(Result, WParam, LParam);

#define END_MESSAGE_MAP \
		default: return false;\
		} \
	}
protected:
	virtual bool MessageProcessor(LRESULT*, UINT, WPARAM, LPARAM) = 0;
	virtual void MessagePreProcessor (UINT, WPARAM, LPARAM) { };
	virtual void MessagePostProcessor(UINT, WPARAM, LPARAM) { };

	static LRESULT CALLBACK WindowProcedure     (HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);
	static LRESULT CALLBACK StartWindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);
//============================================================================================================================
private: 
	inline static CBaseWindowM* GetWndThis(LPARAM LParam)
	{
		return (CBaseWindowM*)LPCREATESTRUCT(LParam)->lpCreateParams;
	}
	inline static CBaseWindowM* GetWndThis(HWND Handle)
	{
		return (CBaseWindowM*)CBaseWindow::GetWndThis(Handle);
	}
};

//StartWindowProcedure - Catch start window messages.  
//When WM_CREATE message arrive, StartWindowProcedure do initializing work and call WindowProcedure.
LRESULT CALLBACK CBaseWindowM::StartWindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
{
	if (Message == WM_NCCREATE)
	{
		CBaseWindowM* Window = GetWndThis(LParam);
		SetWndThis(Handle, Window);
		Window->SetHandle(Handle);
		Window->SetWndProc(WindowProcedure);
		return WindowProcedure(Handle, Message, WParam, LParam);
	}
	return DefWindowProc(Handle, Message, WParam, LParam);
}

//WindowProcedure - Catch all Window Messages and call MessageProcessor.
//If MessageProcessor don't handle message, WindowProcedure calls DefWindowProc.
LRESULT CALLBACK CBaseWindowM::WindowProcedure(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
{
	CBaseWindowM* Window = GetWndThis(Handle);
	LRESULT Result = 0;

	if (Window != NULL)
	{
		Window->MessagePreProcessor(Message, WParam, LParam);
		bool Handled = Window->MessageProcessor(&Result, Message, WParam, LParam);
		Window->MessagePostProcessor(Message, WParam, LParam);
		if (Handled == false)
		{
			//TODO:
			Result = DefWindowProc(Handle, Message, WParam, LParam);
		}
		return Result;
	}
	return DefWindowProc(Handle, Message, WParam, LParam);
}


/*========================================================================================================================================
ClassInfo - Help you to change some window class parmeters instead changing all parmeters in once.

USING: foo(ClassInfo&) - foo(ClassInfo().ClassName(L"BlaBla").Style(0). ... )
                                                                          /\ 
                                                                          ||
                                                            Enter here setters, you need. 

============================================================================================================

ADVICE: If you create new window class - inherited from CBaseWindowR, use next syntax in your constructors:
class CYourClass : public CBaseClass
{
CYourClass(ClassInfo& ClassInfo) : CBaseClass(ClassInfo.ClassName(L"CYourClass")) {...}
                                                                     /\
                                                                     ||
                                   Write here name of your class. Windows needs it, to create your Window.
============================================================================================================
*/
class ClassInfo
{
public:
	WNDCLASSEX WindowStruct;
	ClassInfo()
	{
		WindowStruct.cbSize = sizeof(WNDCLASSEX);

		WindowStruct.style = CS_HREDRAW | CS_VREDRAW;
		WindowStruct.lpfnWndProc = NULL;

		WindowStruct.cbClsExtra = 0;
		WindowStruct.cbWndExtra = sizeof(this);

		WindowStruct.hInstance = Application.hInstance;

		WindowStruct.hIcon = 0;
		WindowStruct.hCursor = LoadCursor(0, IDC_ARROW);
		WindowStruct.hbrBackground = HBRUSH(COLOR_WINDOW);
		WindowStruct.lpszMenuName = 0;
		WindowStruct.lpszClassName = L"DefaultClass";
		WindowStruct.hIconSm = 0;
	}
	//====================================================================================================
	ClassInfo& NStyle    (UINT      _Style)     { WindowStruct.style         = _Style;     return *this; }
	ClassInfo& Style     (UINT      _Style)     { WindowStruct.style        |= _Style;     return *this; }
	//====================================================================================================
	ClassInfo& ClassName (LPCTSTR   _ClassName) { WindowStruct.lpszClassName = _ClassName; return *this; }
	ClassInfo& Instance  (HINSTANCE _Instance)  { WindowStruct.hInstance     = _Instance;  return *this; }
	ClassInfo& Icon      (HICON     _Icon)      { WindowStruct.hIcon         = _Icon;      return *this; }
	ClassInfo& Cursor    (HCURSOR   _Cursor)    { WindowStruct.hCursor       = _Cursor;    return *this; }
	ClassInfo& Background(HBRUSH    _Brush)     { WindowStruct.hbrBackground = _Brush;     return *this; }
	ClassInfo& MenuName  (LPCTSTR   _MenuName)  { WindowStruct.lpszMenuName  = _MenuName;  return *this; }
	ClassInfo& IconSm    (HICON     _Icon)      { WindowStruct.hIcon         = _Icon;      return *this; }
	ClassInfo& WndProc   (WNDPROC   _WndProc)   { WindowStruct.lpfnWndProc   = _WndProc;   return *this; }
	//====================================================================================================
	ClassInfo& WndStruct (WNDCLASSEX _WndClass) { WindowStruct               = _WndClass;  return *this; }
};

//CBaseWindowR : R - Register - this class add Registering in CBaseWindow
class  CBaseWindowR : public CBaseWindowM
{
public:
	CBaseWindowR(ClassInfo& ClassInfo) : ClassAtom(0), ClassName(ClassInfo.WindowStruct.lpszClassName)
	{
		if (ClassInfo.WindowStruct.lpfnWndProc == NULL)
		{
			ClassInfo.WindowStruct.lpfnWndProc = StartWindowProcedure;
		}

		ClassAtom = RegisterClassEx(&(ClassInfo.WindowStruct));
	}

protected:
	ATOM    ClassAtom;
	LPCTSTR ClassName;
};

//=========================================================================================================================================

//WndInfo - Help you to change some window parmeters instead changing all parmeters in once.
//USING: foo(WndInfo&) - foo(WndInfo().Top(10).Left(112). .... )
//                                                           /\ 
//                                                           ||
//                                                       Enter here setters, you need. 
class WndInfo
{
	struct WNDINFOEX
	{
		DWORD        i_Style;
		DWORD        i_ExStyle;
		LPCTSTR      i_WindowName;
		int          i_Top;
		int          i_Left;
		int          i_Width;
		int          i_Height;
		HMENU        i_Menu;
		HWND         i_Parent;
		HINSTANCE    i_Instance;
	};
public:
	WNDINFOEX WindowStruct;
	WndInfo()
	{
		WindowStruct.i_Style      = WS_CLIPCHILDREN | WS_VISIBLE;
		WindowStruct.i_ExStyle    = 0;

		WindowStruct.i_WindowName = L"Default Window Name";

		WindowStruct.i_Top      = 20;
		WindowStruct.i_Left     = 20;
		WindowStruct.i_Width    = 50;
		WindowStruct.i_Height   = 50;

		WindowStruct.i_Parent   = NULL;
		WindowStruct.i_Menu     = 0;
		WindowStruct.i_Instance = 0;
	}
	//============================================================================================================
	WndInfo& NStyle  (DWORD _Style)             { WindowStruct.i_Style      = _Style;              return *this; }
	WndInfo& NExStyle(DWORD _ExStyle)           { WindowStruct.i_ExStyle    = _ExStyle;            return *this; }
	//============================================================================================================
	WndInfo& Style   (DWORD _Style)             { WindowStruct.i_Style     |= _Style;              return *this; }
	WndInfo& ExStyle (DWORD _ExStyle)           { WindowStruct.i_ExStyle   |= _ExStyle;            return *this; }
	//============================================================================================================
	WndInfo& WindowName(LPCTSTR _WindowName)    { WindowStruct.i_WindowName = _WindowName;         return *this; }
	//============================================================================================================
	WndInfo& Top   (int _Top)                   { WindowStruct.i_Top        = _Top;                return *this; }
	WndInfo& Left  (int _Left)                  { WindowStruct.i_Left       = _Left;               return *this; }
	WndInfo& Pos   (int _Top, int _Left)        { WindowStruct.i_Top        = _Top;                
	                                              WindowStruct.i_Left       = _Left;               return *this; }
	//============================================================================================================
	WndInfo& Width (int _Width)                 { WindowStruct.i_Width      = _Width;              return *this; }
	WndInfo& Height(int _Height)                { WindowStruct.i_Height     = _Height;             return *this; }
	WndInfo& Size(int _Width, int _Height)      { WindowStruct.i_Width      = _Width;
		                                          WindowStruct.i_Height     = _Height;             return *this; }
	//============================================================================================================
	WndInfo& Menu(HMENU _Menu)                  { WindowStruct.i_Menu       = _Menu;               return *this; }
	WndInfo& Parent(HWND _Parent)               { WindowStruct.i_Parent     = _Parent;             return *this; }
	WndInfo& Instance(HINSTANCE _Instance)      { WindowStruct.i_Instance   = _Instance;           return *this; }
};

//CBaseWindowC : C - Createing - this class add Create function in CBaseWindow
class CBaseWindowC : public CBaseWindowR
{
public:
	CBaseWindowC(ClassInfo& ClassInfo) : CBaseWindowR(ClassInfo) {}
	bool Create(WndInfo& WndInfo)
	{
		return CBaseWindow::Create(
			WndInfo.WindowStruct.i_ExStyle,
			ClassName, 
			WndInfo.WindowStruct.i_WindowName,
			WndInfo.WindowStruct.i_Style,
			WndInfo.WindowStruct.i_Left,
			WndInfo.WindowStruct.i_Top,
			WndInfo.WindowStruct.i_Width,
			WndInfo.WindowStruct.i_Height,
			WndInfo.WindowStruct.i_Parent,
			WndInfo.WindowStruct.i_Menu,
			WndInfo.WindowStruct.i_Instance,
			this);
	}
};

//=========================================================================================================================================

//CBaseWindowP: P - Property - Add to CBaseWindow properties
class CBaseWindowP : public CBaseWindowC
{
public:
	typedef CProperty<RW, int,      CBaseWindowP> rwINT;
	typedef CProperty<RO, HWND,     CBaseWindowP> roHWND;
	typedef CProperty<RW, LONG_PTR, CBaseWindowP> rwLONG_PTR;
	typedef CProperty<RW, WCHAR,    CBaseWindowP> rwWCHAR;
//=========================================================================================================================================
	rwINT pTop;
	rwINT pLeft;
	rwINT pHeight;
	rwINT pWidth;

	roHWND     pHandle;
	rwWCHAR    pClassName;
	rwLONG_PTR pStyle;
	rwLONG_PTR pExStyle;
//=========================================================================================================================================
	CBaseWindowP(ClassInfo& ClassInfo) : CBaseWindowC(ClassInfo)
	{
		pHandle. ROInit(&CBaseWindowP::GetHandle);
		pStyle.  RWInit(&CBaseWindowP::GetWndStyle,     &CBaseWindowP::SetWndStyle);
		pExStyle.RWInit(&CBaseWindowP::GetWndExStyle,   &CBaseWindowP::SetWndExStyle);
		pTop.    RWInit(&CBaseWindowP::GetWndTop,       &CBaseWindowP::SetWndTop);
		pLeft.   RWInit(&CBaseWindowP::GetWndLeft,      &CBaseWindowP::SetWndLeft);
		pHeight. RWInit(&CBaseWindowP::GetWndHeight,    &CBaseWindowP::SetWndHeight);
		pWidth.  RWInit(&CBaseWindowP::GetWndWidth,     &CBaseWindowP::SetWndWidth);
	}
//============GETTERS======================================================================================================================
private:
	void SetWndTop(int Top)
	{
		SetWndPos(NULL, GetWndLeft(), Top, 0, 0, SWP_NOSIZE);
	}
	void SetWndLeft(int Left)
	{
		SetWndPos(NULL, Left, GetWndTop(), 0, 0, SWP_NOSIZE);
	}
	int GetWndTop()
	{
		RECT Rect = {};
		GetWndRect(&Rect);
		return Rect.top;
	}
	int GetWndLeft()
	{
		RECT Rect = {};
		GetWndRect(&Rect);
		return Rect.left;
	}
//===========SETTERS======================================================================================================================
	void SetWndWidth(int Width)
	{
		SetWndPos(NULL, 0, 0, Width, GetWndHeight(), SWP_NOMOVE);
	}
	void SetWndHeight(int Height)
	{
		SetWndPos(NULL, 0, 0, GetWndWidth(), Height, SWP_NOMOVE);
	}
	int GetWndWidth()
	{
		RECT Rect = {};
		GetWndRect(&Rect);
		return Rect.right - Rect.left;
	}
	int GetWndHeight()
	{
		RECT Rect = {};
		GetWndRect(&Rect);
		return Rect.bottom - Rect.top;
	}
};

//=========================================================================================================================================



class CMessageLoop
{
public:
	void Run()
	{
		MSG msg;
		while (GetMessage(&msg, 0, 0, 0) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
};