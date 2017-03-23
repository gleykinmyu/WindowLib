#pragma once
#include <Windows.h>
#include <assert.h>
#include "CProperty.h"

#define NULLHWND (HWND)0
#define NOFLAGS 0

#define WINASSERT(expression) if(!(expression)) assert(!"Window id not exist!!!");


class CChild;
class CContainer;

class CContainer
{
public:
	CContainer() {}

	virtual bool ChildProcessor(CChild* Caller, ...) = 0;
};

class CChild
{

public:
	CChild(CContainer* _Parent) : Parent(_Parent) {}
	CContainer* Parent;
};

class CApplication : public CContainer
{
public:
	CApplication() { }
	HINSTANCE hInstance;
	virtual bool ChildProcessor(CChild* Caller, ...)
	{
		return false;
	}
};

CApplication _Application;

CApplication* Application = &_Application;


//CBaseWindow - base class of WinLibrary
class CBaseWindow
{
private:
	HWND m_Handle = NULL;
	bool m_Exist  = false;
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
	HWND GetHandle() const
	{ 
		WINASSERT(m_Exist);
		return m_Handle; 
	}

	LONG_PTR GetWndStyle() const
	{
		WINASSERT(m_Exist);
		return GetWindowLongPtr(m_Handle, GWL_STYLE);
	}

	LONG_PTR GetWndExStyle() const
	{
		WINASSERT(m_Exist);
		return GetWindowLongPtr(m_Handle, GWL_EXSTYLE);
	}

	WNDPROC GetWndProc() const
	{
		WINASSERT(m_Exist);
		return (WNDPROC)GetWindowLongPtr(m_Handle, GWLP_WNDPROC);
	}

	HINSTANCE GetWndInstance() const
	{
		WINASSERT(m_Exist);
		return (HINSTANCE)GetWindowLongPtr(m_Handle, GWLP_HINSTANCE);
	}

	HWND GetWndParentH() const
	{
		WINASSERT(m_Exist);
		return (HWND)GetWindowLongPtr(m_Handle, GWLP_HWNDPARENT);
	}

	static CBaseWindow* GetWndThis(HWND Handle)
	{
		WINASSERT(IsWindow(Handle));
		return (CBaseWindow*)GetWindowLongPtr(Handle, GWLP_USERDATA);
	}

	LONG_PTR GetWndID() const
	{
		WINASSERT(m_Exist);
		return GetWindowLongPtr(m_Handle, GWLP_ID);
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
	void SetWndParentH(HWND newParent)
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
		SetParent(m_Handle, newParent);
	}

//=========================================================================================================================================
	bool SetWndText(LPCTSTR Text)
	{
		WINASSERT(m_Exist);
		if ( SetWindowText(m_Handle, Text) ) return true;
		return false;
	}

	int GetWndText(LPTSTR Text, int Quantity) const
	{
		WINASSERT(m_Exist);
		return GetWindowText(m_Handle, Text, Quantity);
	}

//=========================================================================================================================================
	bool GetWndRect(LPRECT Rect) const
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
	struct CLASSINFOEX
	{
		UINT        Style;

		HICON       hIcon;
		HICON       hIconSm;
		HCURSOR     hCursor;
		HBRUSH      Background;

		LPCWSTR     MenuName;
		LPCWSTR     ClassName;
	};

	CLASSINFOEX ClassStruct;

	ClassInfo()
	{

		ClassStruct.Style = CS_HREDRAW | CS_VREDRAW;
		ClassStruct.hIcon = 0;
		ClassStruct.hCursor = LoadCursor(0, IDC_ARROW);
		ClassStruct.Background = HBRUSH(COLOR_WINDOW);
		ClassStruct.MenuName = 0;
		ClassStruct.ClassName = L"DefaultClass";
		ClassStruct.hIconSm = 0;
	}
	//====================================================================================================
	ClassInfo& NStyle    (UINT      _Style)     { ClassStruct.Style         = _Style;     return *this; }
	ClassInfo& Style     (UINT      _Style)     { ClassStruct.Style        |= _Style;     return *this; }
	//====================================================================================================
	ClassInfo& ClassName (LPCTSTR   _ClassName) { ClassStruct.ClassName     = _ClassName; return *this; }
	ClassInfo& Icon      (HICON     _Icon)      { ClassStruct.hIcon         = _Icon;      return *this; }
	ClassInfo& IconSm    (HICON     _IconSm)    { ClassStruct.hIconSm       = _IconSm;    return *this; }
	ClassInfo& Cursor    (HCURSOR   _Cursor)    { ClassStruct.hCursor       = _Cursor;    return *this; }
	ClassInfo& Background(HBRUSH    _Brush)     { ClassStruct.Background    = _Brush;     return *this; }
	ClassInfo& MenuName  (LPCTSTR   _MenuName)  { ClassStruct.MenuName      = _MenuName;  return *this; }
};

//CBaseWindowR : R - Register - this class add Registering in CBaseWindow
class  CBaseWindowR : public CBaseWindowM
{
public:
	CBaseWindowR(ClassInfo& ClsInfo, WNDPROC WndProc)
	{
		WNDCLASSEX WindowStruct = {};

		WndProc ? WindowStruct.lpfnWndProc = WndProc : WindowStruct.lpfnWndProc = StartWindowProcedure;
		
		WindowStruct.style         = ClsInfo.ClassStruct.Style;

		WindowStruct.lpszClassName = ClsInfo.ClassStruct.ClassName;
		ClassName                  = ClsInfo.ClassStruct.ClassName;

		WindowStruct.hIcon         = ClsInfo.ClassStruct.hIcon;
		WindowStruct.hIconSm       = ClsInfo.ClassStruct.hIconSm;
		
		WindowStruct.hCursor       = ClsInfo.ClassStruct.hCursor;
		WindowStruct.hbrBackground = ClsInfo.ClassStruct.Background;
		WindowStruct.lpszMenuName  = ClsInfo.ClassStruct.MenuName;
		WindowStruct.hInstance     = _Application.hInstance;

		WindowStruct.cbSize        = sizeof(WNDCLASSEX);

		WindowStruct.cbWndExtra    = sizeof(this);
		WindowStruct.cbClsExtra    = 0;

		ClassAtom = RegisterClassEx(&(WindowStruct));
	}
	inline ATOM    GetWndAtom()      const { return ClassAtom; }
	inline LPCTSTR GetWndClassName() const { return ClassName; }
//=================================================================================================
private:
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
public:
	struct WNDINFOEX
	{
		DWORD        Style;
		DWORD        ExStyle;
		LPCTSTR      WindowName;
		int          Top;
		int          Left;
		int          Width;
		int          Height;
		HMENU        Menu;
	};
	
	WNDINFOEX WindowStruct;

	WndInfo()
	{
		WindowStruct.Style      = WS_CLIPCHILDREN | WS_VISIBLE;
		WindowStruct.ExStyle    = 0;

		WindowStruct.WindowName = L"Default Window Name";

		WindowStruct.Top      = 20;
		WindowStruct.Left     = 20;
		WindowStruct.Width    = 50;
		WindowStruct.Height   = 50;

		WindowStruct.Menu     = 0;
	}
	//============================================================================================================
	WndInfo& NStyle  (DWORD _Style)             { WindowStruct.Style      = _Style;              return *this; }
	WndInfo& NExStyle(DWORD _ExStyle)           { WindowStruct.ExStyle    = _ExStyle;            return *this; }
	//============================================================================================================
	WndInfo& Style   (DWORD _Style)             { WindowStruct.Style     |= _Style;              return *this; }
	WndInfo& ExStyle (DWORD _ExStyle)           { WindowStruct.ExStyle   |= _ExStyle;            return *this; }
	//============================================================================================================
	WndInfo& WindowName(LPCTSTR _WindowName)    { WindowStruct.WindowName = _WindowName;         return *this; }
	//============================================================================================================
	WndInfo& Top   (int _Top)                   { WindowStruct.Top        = _Top;                return *this; }
	WndInfo& Left  (int _Left)                  { WindowStruct.Left       = _Left;               return *this; }
	WndInfo& Pos   (int _Top, int _Left)        { WindowStruct.Top        = _Top;                
	                                              WindowStruct.Left       = _Left;               return *this; }
	//============================================================================================================
	WndInfo& Width (int _Width)                 { WindowStruct.Width      = _Width;              return *this; }
	WndInfo& Height(int _Height)                { WindowStruct.Height     = _Height;             return *this; }
	WndInfo& Size(int _Width, int _Height)      { WindowStruct.Width      = _Width;
		                                          WindowStruct.Height     = _Height;             return *this; }
	//============================================================================================================
	WndInfo& Menu(HMENU _Menu)                  { WindowStruct.Menu       = _Menu;               return *this; }
};


//CBaseWindowC : C - Createing - this class add Create function in CBaseWindow
class CBaseWindowC : public CBaseWindowR
{
public:
	CBaseWindowC(ClassInfo& ClassInfo, WNDPROC WndProc) 
		: CBaseWindowR(ClassInfo, WndProc) {}

	bool Create(WndInfo& WndInfo, HWND Parent)
	{
		return CBaseWindow::Create(
			WndInfo.WindowStruct.ExStyle,
			GetWndClassName(), 
			WndInfo.WindowStruct.WindowName,
			WndInfo.WindowStruct.Style,
			WndInfo.WindowStruct.Left,
			WndInfo.WindowStruct.Top,
			WndInfo.WindowStruct.Width,
			WndInfo.WindowStruct.Height,
			Parent,
			WndInfo.WindowStruct.Menu,
			_Application.hInstance,
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
	CBaseWindowP(ClassInfo& ClassInfo) : CBaseWindowC(ClassInfo, NULL)
	{
		pHandle. Init(this, &CBaseWindowP::GetHandle);
		pStyle.  Init(this, &CBaseWindowP::GetWndStyle,     &CBaseWindowP::SetWndStyle);
		pExStyle.Init(this, &CBaseWindowP::GetWndExStyle,   &CBaseWindowP::SetWndExStyle);
		pTop.    Init(this, &CBaseWindowP::GetWndTop,       &CBaseWindowP::SetWndTop);
		pLeft.   Init(this, &CBaseWindowP::GetWndLeft,      &CBaseWindowP::SetWndLeft);
		pHeight. Init(this, &CBaseWindowP::GetWndHeight,    &CBaseWindowP::SetWndHeight);
		pWidth.  Init(this, &CBaseWindowP::GetWndWidth,     &CBaseWindowP::SetWndWidth);
	}
//============GETTERS======================================================================================================================
private:
	void SetWndTop(const int Top)
	{
		SetWndPos(NULL, GetWndLeft(), Top, 0, 0, SWP_NOSIZE);
	}
	void SetWndLeft(const int Left)
	{
		SetWndPos(NULL, Left, GetWndTop(), 0, 0, SWP_NOSIZE);
	}
	int GetWndTop() const
	{
		RECT Rect = {};
		GetWndRect(&Rect);
		return Rect.top;
	}
	int GetWndLeft() const
	{
		RECT Rect = {};
		GetWndRect(&Rect);
		return Rect.left;
	}
//===========SETTERS======================================================================================================================
	void SetWndWidth(const int Width)
	{
		SetWndPos(NULL, 0, 0, Width, GetWndHeight(), SWP_NOMOVE);
	}
	void SetWndHeight(const int Height)
	{
		SetWndPos(NULL, 0, 0, GetWndWidth(), Height, SWP_NOMOVE);
	}
	int GetWndWidth() const
	{
		RECT Rect = {};
		GetWndRect(&Rect);
		return Rect.right - Rect.left;
	}
	int GetWndHeight() const
	{
		RECT Rect = {};
		GetWndRect(&Rect);
		return Rect.bottom - Rect.top;
	}
};

//=========================================================================================================================================


class CWindowContainer : public CBaseWindowC, public CContainer
{
public:
	CWindowContainer(CContainer* Parent, ClassInfo& ClsInfo) : CBaseWindowC(ClsInfo, 0), CContainer() {};
};

class CWindowChild : public CChild, public CBaseWindowC
{
public:
	CWindowChild(CWindowContainer* Parent, ClassInfo& ClsInfo) : CChild((CContainer*)Parent), CBaseWindowC(ClsInfo, NULL) { }
	bool Create(WndInfo& Info) { return CBaseWindowC::Create(Info, ((CWindowContainer*)Parent)->GetHandle()); }
};





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