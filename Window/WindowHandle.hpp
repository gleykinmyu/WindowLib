#ifndef WL_WINDOW_HANDLE_H
#define WL_WINDOW_HANDLE_H
#include <Windows.h>
#include <WinLib/Utility.hpp>

namespace Window
{
	class WL_NOVTABLE CWindowHandle
	{
	private:
		HWND m_Handle = NULL;

	public:
		CWindowHandle();
		CWindowHandle(HWND Handle);

		inline operator HWND();

        inline void Attach(HWND NewWnd);
        inline HWND Detach();

        LRESULT CallWindowProc(WNDPROC WndProc, UINT Message, WPARAM WParam, LPARAM LParam);
        LRESULT DefWindowProc(UINT Message, WPARAM WParam, LPARAM LParam);

        inline static CWindowHandle* getWndThis(HWND Handle);
        inline static void     setWndThis(HWND Handle, CWindowHandle* This);

        inline LONG_PTR  getStyle   () const;
        inline LONG_PTR  getExStyle () const;
        inline WNDPROC   getProc    () const;
        inline HINSTANCE getInstance() const;
        inline HWND      getParent  () const;
        inline LONG_PTR  getID      () const;
		 
        inline void setStyle   (LONG_PTR  Style);
        inline void setExStyle (LONG_PTR  ExStyle);
        inline void setProc    (WNDPROC   WndProc);
        inline void setInstance(HINSTANCE HInstance);
        inline void setParent  (HWND      newParent);
        inline void setID      (LONG_PTR  ID);

        inline bool setText(LPCTSTR Text) const;
        inline int  getText(LPTSTR  Text, int Quantity) const;
        inline int  getTextLength() const;

        inline bool Show     (int nCmdShow);
        inline bool ShowAsync(int nCmdShow);

        inline bool Animate   (DWORD dwTime, DWORD dwFlags);
        inline bool Flash     (bool bInvert);
        inline bool FlashEx   (UINT Size, DWORD Flags, UINT Count, DWORD Timeout);
        inline bool OpenIcon  ();
        inline bool Update    ();
        inline bool LockUpdate();
        inline bool Enable    (bool bEnable);
        inline bool setFocus  ();
        inline bool Redraw    (RECT *lprcUpdate, HRGN hrgnUpdate, UINT flags);

        inline bool Close();

		inline bool isChild  (CWindowHandle * Parent) const;
		inline bool isChild  (CWindowHandle & Parent) const;
        inline bool isHungApp() const;
        inline bool isVisible() const;
        inline bool isIconic () const;
        inline bool isZoomed () const;
        inline bool isUnicode() const;
        inline bool isEnabled() const;
		inline bool isWindow () const;
		inline bool isNull   () const;

        inline bool getRect      (LPRECT Rect) const;
        inline bool getUpdateRect(LPRECT Rect, bool Erase) const;
        inline bool getClientRect(LPRECT Rect) const;

        inline bool setPos(HWND WndInsertAfter, int Left, int Top, int Width, int Height, unsigned Flags);
        inline bool Move(int X, int Y, int Width, int Height, bool Repaint);

        inline bool InvalidateRect(const RECT *Rect, bool Erase = false);
        inline bool ValidateRect  (const RECT *Rect);


		//bool getPlacement(WINDOWPLACEMENT *lpwndpl);
		//bool setPlacement(WINDOWPLACEMENT *lpwndpl);
		//bool BringToTop();

		//bool getInfo(PWINDOWINFO pwi);

		///HMENU getMenu();
		//bool setMenu(HMENU hMenu);

		//int  getUpdateRgn (HRGN hRgn, BOOL bErase);
		//int  setRgn       (HRGN hRgn, BOOL bRedraw);
		//int  getRgn       (HRGN hRgn);
		//int  getRgnBox    (LPRECT lprc);
		//bool InvalidateRgn(HRGN hRgn, BOOL bErase);
		//bool ValidateRgn  (HRGN hRgn);

		//Properties
		///bool setPropA      (LPCSTR lpString, HANDLE hData);
		//HANDLE getPropA    (LPCSTR lpString);
		//HANDLE RemovePropA(LPCSTR lpString);
		//int EnumPropsExA  (PROPENUMPROCEXA lpEnumFunc, LPARAM lParam);
		//int	EnumPropsA    (PROPENUMPROCA lpEnumFunc);

		//bool setWindowContextHelpId(HWND, DWORD);
		//DWORD getWindowContextHelpId(HWND);

		//bool EnumChildWindows(HWND hWndParent, WNDENUMPROC lpEnumFunc, LPARAM lParam);			
	};

	class WL_NOVTABLE CWindow : public CWindowHandle
	{
	public:
		CWindow() {WL_CTOR_TRACE;}
		inline bool Create(DWORD ExStyle, LPCTSTR ClassName, LPCTSTR WindowName, DWORD Style,
			int Left, int Top, int Width, int Height, CWindowHandle* Parent, HMENU Menu, HINSTANCE Instance, LPVOID LParam);

		inline bool Create(DWORD ExStyle, LPCTSTR ClassName, LPCTSTR WindowName, DWORD Style,
			int Left, int Top, int Width, int Height, CWindowHandle& Parent, HMENU Menu, HINSTANCE Instance, LPVOID LParam);

		bool Destroy();
	};

	//=============================================================================================

	inline CWindowHandle::CWindowHandle()
	{
		WL_CTOR_TRACE;
		m_Handle = NULL;
	}

	inline CWindowHandle::CWindowHandle(HWND Handle)
	{
		WL_ASSERT(Handle != NULL);
		m_Handle = Handle;
	}

	inline bool CWindowHandle::isNull() const
	{
		return m_Handle == NULL;
	}

    inline CWindowHandle::operator HWND()
    {
        return m_Handle;
    }

    inline void CWindowHandle::Attach(HWND NewWnd)
    {
        WL_ASSERT(m_Handle == NULL);
        WL_ASSERT(::IsWindow(NewWnd));
        m_Handle = NewWnd;
    }

    inline HWND CWindowHandle::Detach()
    {
        HWND RetHandle = m_Handle;
        m_Handle = NULL;
        return RetHandle;
    }

    //=========================================================================================================================================
    inline LRESULT CWindowHandle::CallWindowProc(WNDPROC WndProc, UINT Message, WPARAM WParam, LPARAM LParam)
    {
        return ::CallWindowProc(WndProc, m_Handle, Message, WParam, LParam);
    }

    inline LRESULT CWindowHandle::DefWindowProc(UINT Message, WPARAM WParam, LPARAM LParam)
    {
        return ::DefWindowProc(m_Handle, Message, WParam, LParam);
    }

    //=========================================================================================================================================

    inline CWindowHandle* CWindowHandle::getWndThis(HWND Handle)
    {
        WL_ASSERT(::IsWindow(Handle));
        return (CWindowHandle*)::GetWindowLongPtr(Handle, GWLP_USERDATA);
    }

    inline void CWindowHandle::setWndThis(HWND Handle, CWindowHandle* This)
    {
        WL_ASSERT(::IsWindow(Handle));
        ::SetLastError(0);
        ::SetWindowLong(Handle, GWLP_USERDATA, (LONG_PTR)This);
    }
    //=========================================================================================================================================

    inline LONG_PTR CWindowHandle::getStyle() const
    {
        WL_ASSERT(isWindow());
        return ::GetWindowLongPtr(m_Handle, GWL_STYLE);
    }

    inline LONG_PTR CWindowHandle::getExStyle() const
    {
        WL_ASSERT(isWindow());
        return ::GetWindowLongPtr(m_Handle, GWL_EXSTYLE);
    }

    inline WNDPROC CWindowHandle::getProc() const
    {
        WL_ASSERT(isWindow());
        return (WNDPROC)::GetWindowLongPtr(m_Handle, GWLP_WNDPROC);
    }

    inline HINSTANCE CWindowHandle::getInstance() const
    {
        WL_ASSERT(isWindow());
        return (HINSTANCE)::GetWindowLongPtr(m_Handle, GWLP_HINSTANCE);
    }

    inline HWND CWindowHandle::getParent() const
    {
        WL_ASSERT(isWindow());
        return (HWND)::GetWindowLongPtr(m_Handle, GWLP_HWNDPARENT);
    }

    inline LONG_PTR CWindowHandle::getID() const
    {
        WL_ASSERT(isWindow());
        return ::GetWindowLongPtr(m_Handle, GWLP_ID);
    }
    //=========================================================================================================================================

    inline void CWindowHandle::setStyle(LONG_PTR Style)
    {
        WL_ASSERT(isWindow());
        ::SetLastError(0);
        ::SetWindowLongPtr(m_Handle, GWL_STYLE, Style);
    }

    inline void CWindowHandle::setExStyle(LONG_PTR ExStyle)
    {
        WL_ASSERT(isWindow());
        ::SetLastError(0);
        ::SetWindowLong(m_Handle, GWL_EXSTYLE, ExStyle);
    }

    inline void CWindowHandle::setProc(WNDPROC WndProc)
    {
        WL_ASSERT(isWindow());
        ::SetLastError(0);
        ::SetWindowLong(m_Handle, GWLP_WNDPROC, (LONG_PTR)WndProc);
    }

    inline void CWindowHandle::setID(LONG_PTR ID)
    {
        WL_ASSERT(isWindow());
        ::SetLastError(0);
        ::SetWindowLong(m_Handle, GWLP_ID, ID);
    }

    inline void CWindowHandle::setInstance(HINSTANCE HInstance)
    {
        WL_ASSERT(isWindow());
        ::SetLastError(0);
        ::SetWindowLong(m_Handle, GWLP_WNDPROC, (LONG_PTR)HInstance);
    }

    inline void CWindowHandle::setParent(HWND Parent)
    {
        WL_ASSERT(isWindow());
        ::SetLastError(0);
        ::SetParent(m_Handle, Parent);
    }
    //=========================================================================================================================

    inline bool CWindowHandle::setText(LPCTSTR Text) const
    {
        WL_ASSERT(isWindow());
        if (::SetWindowText(m_Handle, Text)) return true;
        return false;
    }

    inline int CWindowHandle::getText(LPTSTR Text, int Quantity) const
    {
        WL_ASSERT(isWindow());
        return ::GetWindowText(m_Handle, Text, Quantity);
    }
    inline int CWindowHandle::getTextLength() const
    {
        WL_ASSERT(isWindow());
        return ::GetWindowTextLength(m_Handle);
    }

    inline bool CWindowHandle::Show(int nCmdShow)
    {
        WL_ASSERT(isWindow());
        return true && ::ShowWindow(m_Handle, nCmdShow);
    }

    inline bool CWindowHandle::ShowAsync(int nCmdShow)
    {
        WL_ASSERT(isWindow());
        return true && ::ShowWindowAsync(m_Handle, nCmdShow);
    }
    //=========================================================================================================================

    inline bool CWindowHandle::Animate(DWORD Time, DWORD Flags)
    {
        WL_ASSERT(isWindow());
        return true && ::AnimateWindow(m_Handle, Time, Flags);
    }

    inline bool CWindowHandle::Flash(bool Invert)
    {
        WL_ASSERT(isWindow());
        return true && ::FlashWindow(m_Handle, (BOOL)Invert);
    }

    inline bool CWindowHandle::FlashEx(UINT Size, DWORD Flags, UINT Count, DWORD TimeOut)
    {
        WL_ASSERT(isWindow());
        FLASHWINFO FlashStruct;
        FlashStruct.cbSize = Size;
        FlashStruct.dwFlags = Flags;
        FlashStruct.dwTimeout = TimeOut;
        FlashStruct.uCount = Count;
        FlashStruct.hwnd = m_Handle;
        return true && ::FlashWindowEx(&FlashStruct);
    }

    inline bool CWindowHandle::OpenIcon()
    {
        WL_ASSERT(isWindow());
        return true && ::OpenIcon(m_Handle);
    }

    inline bool CWindowHandle::Update()
    {
        WL_ASSERT(isWindow());
        return true && ::UpdateWindow(m_Handle);
    }

    inline bool CWindowHandle::LockUpdate()
    {
        WL_ASSERT(isWindow());
        return true && ::LockWindowUpdate(m_Handle);
    }

    inline bool CWindowHandle::Enable(bool Enable)
    {
        WL_ASSERT(isWindow());
        return true && ::EnableWindow(m_Handle, (BOOL)Enable);
    }

    inline bool CWindowHandle::setFocus()
    {
        WL_ASSERT(isWindow());
        return true && ::SetFocus(m_Handle);
    }

    inline bool CWindowHandle::Redraw(RECT* rUpdate, HRGN hUpdate, UINT Flags)
    {
        WL_ASSERT(isWindow());
        return true && ::RedrawWindow(m_Handle, rUpdate, hUpdate, Flags);
    }
    //===========================================================================================================================================

    inline bool CWindowHandle::Close()
    {
        WL_ASSERT(isWindow());
        return true && ::CloseWindow(m_Handle);
    }

    inline bool CWindowHandle::isHungApp() const
    {
        WL_ASSERT(isWindow());
        return true && ::IsHungAppWindow(m_Handle);
    }

    inline bool CWindowHandle::isChild(CWindowHandle * Parent) const
    {
		WL_ASSERT(Parent != NULL);
		WL_ASSERT(Parent->isWindow());
		WL_ASSERT(isWindow());
        return true && ::IsChild(*Parent, m_Handle);
    }

	inline bool CWindowHandle::isChild(CWindowHandle & Parent) const
	{
		WL_ASSERT(Parent.isWindow());
		WL_ASSERT(isWindow());
		return true && ::IsChild(Parent, m_Handle);
	}

    inline bool CWindowHandle::isVisible() const
    {
        WL_ASSERT(isWindow());
        return true && ::IsWindowVisible(m_Handle);
    }

    inline bool CWindowHandle::isIconic() const
    {
        WL_ASSERT(isWindow());
        return true && ::IsIconic(m_Handle);
    }

    inline bool CWindowHandle::isZoomed() const
    {
        WL_ASSERT(isWindow());
        return true && ::IsZoomed(m_Handle);
    }

    inline bool CWindowHandle::isUnicode() const
    {
        WL_ASSERT(isWindow());
        return true && ::IsWindowUnicode(m_Handle);
    }

    inline bool CWindowHandle::isEnabled() const
    {
        WL_ASSERT(isWindow());
        return true && ::IsWindowEnabled(m_Handle);
    }

	inline bool CWindowHandle::isWindow() const
	{
		return true && ::IsWindow(m_Handle);
	}

    //=========================================================================================================================================

    inline bool CWindowHandle::getRect(LPRECT Rect) const
    {
        WL_ASSERT(isWindow());
        return true && ::GetWindowRect(m_Handle, Rect);
    }

    inline bool CWindowHandle::getUpdateRect(LPRECT Rect, bool Erase) const
    {
        WL_ASSERT(isWindow());
        return true && ::GetUpdateRect(m_Handle, Rect, (BOOL)Erase);
    }

    inline bool CWindowHandle::getClientRect(LPRECT Rect) const
    {
        WL_ASSERT(isWindow());
        return true && ::GetClientRect(m_Handle, Rect);
    }
    //=========================================================================================================================================

    inline bool CWindowHandle::setPos(HWND hWndInsertAfter, int Left, int Top, int Width, int Height, unsigned Flags)
    {
        WL_ASSERT(isWindow());
        return true && ::SetWindowPos(m_Handle, hWndInsertAfter, Left, Top, Width, Height, Flags);
    }
    inline bool CWindowHandle::Move(int Left, int Top, int Width, int Height, bool Repaint)
    {
        WL_ASSERT(isWindow());
        return true && ::MoveWindow(m_Handle, Left, Top, Width, Height, (BOOL)Repaint);
    }

    inline bool CWindowHandle::InvalidateRect(const RECT * Rect, bool Erase)
    {
        return true && ::InvalidateRect(m_Handle, Rect, Erase);
    }

    inline bool CWindowHandle::ValidateRect(const RECT * Rect)
    {
        return true && ::ValidateRect(m_Handle, Rect);
    }

	//=============================================================================================

	inline bool CWindow::Create(DWORD ExStyle,
		LPCTSTR ClassName,
		LPCTSTR WindowName,
		DWORD Style,
		int Left, int Top, int Width, int Height,
		CWindowHandle * Parent,
		HMENU Menu,
		HINSTANCE Instance,
		LPVOID LParam)
	{
		WL_ASSERT(Parent != NULL);
		WL_ASSERT(Parent->isWindow() == true);
		WL_ASSERT(isNull() == true);
		HWND NewHandle = ::CreateWindowEx(ExStyle, ClassName, WindowName, Style, Left, Top, Width, Height, *Parent, Menu, Instance, LParam);
		Detach();
		if (NewHandle != NULL)
			Attach(NewHandle);
		return NewHandle != NULL;
	}

	inline bool CWindow::Create(DWORD ExStyle,
		LPCTSTR ClassName,
		LPCTSTR WindowName,
		DWORD Style,
		int Left, int Top, int Width, int Height,
		CWindowHandle & Parent,
		HMENU Menu,
		HINSTANCE Instance,
		LPVOID LParam)
	{
		WL_ASSERT(isNull() == true);
		WL_ASSERT(Parent.isWindow() == true);
		HWND NewHandle = ::CreateWindowEx(ExStyle, ClassName, WindowName, Style, Left, Top, Width, Height, Parent, Menu, Instance, LParam);
		Detach();
		if (NewHandle != NULL)
			Attach(NewHandle);
		return NewHandle != NULL;
	}

	bool CWindow::Destroy()
	{
		WL_ASSERT(isWindow());
		HWND DestWnd = Detach();
		if (::DestroyWindow(DestWnd) == false)
		{
			Attach(DestWnd);
			return false;
		}
		return true;
	}
}
#endif //!WL_WINDOW_HANDLE_H