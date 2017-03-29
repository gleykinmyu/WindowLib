#pragma once
#include <Windows.h>
#include <assert.h>
#include "WLDefines.h"


namespace wl
{
	class CWindow
	{
	private:
		HWND m_Handle = NULL;
		bool m_Exist  = false;
	public:
        inline bool Create(DWORD ExStyle, LPCTSTR ClassName, LPCTSTR WindowName, DWORD Style,
			int Left, int Top, int Width, int Height, CWindow* Parent, HMENU Menu, HINSTANCE Instance, LPVOID LParam);

        LRESULT CallWindowProcA(WNDPROC WndProc, UINT Message, WPARAM WParam, LPARAM LParam);
        LRESULT CallWindowProcW(WNDPROC WndProc, UINT Message, WPARAM WParam, LPARAM LParam);

        inline HWND GetHandle() const;
        inline void SetHandle(HWND Handle);

        inline static CWindow* GetWndThis(HWND Handle);
        inline static void          SetWndThis(HWND Handle, CWindow* This);

        inline LONG_PTR  GetStyle   () const;
        inline LONG_PTR  GetExStyle () const;
        inline WNDPROC   GetProc    () const;
        inline HINSTANCE GetInstance() const;
        inline CWindow*  GetParent  () const;
        inline LONG_PTR  GetID      () const;
		 
        inline void SetStyle   (LONG_PTR      Style);
        inline void SetExStyle (LONG_PTR      ExStyle);
        inline void SetProc    (WNDPROC       WndProc);
        inline void SetInstance(HINSTANCE     HInstance);
        inline void SetParent  (CWindow* newParent);
        inline void SetID      (LONG_PTR      ID);

        inline bool SetText(LPCTSTR Text);
        inline int  GetText(LPTSTR  Text, int Quantity) const;
        inline int  GetTextLength();

        inline bool Show     (int nCmdShow);
        inline bool ShowAsync(int nCmdShow);

        inline bool Animate   (DWORD dwTime, DWORD dwFlags);
        inline bool Flash     (bool bInvert);
        inline bool FlashEx   (UINT Size, DWORD Flags, UINT Count, DWORD Timeout);
        inline bool OpenIcon  ();
        inline bool Update    ();
        inline bool LockUpdate();
        inline bool Enable    (bool bEnable);
        inline bool SetFocus  ();
        inline bool Redraw    (RECT *lprcUpdate, HRGN hrgnUpdate, UINT flags);

        inline bool Close     ();
        inline bool Destroy   ();

        inline bool IsHungAppWindow();
        inline bool IsChild        (CWindow* Parent);
        inline bool IsVisible      ();
        inline bool IsIconic       ();
        inline bool IsZoomed       ();
        inline bool IsUnicode      ();
        inline bool IsEnabled      ();
        inline bool IsExist        ();

        inline bool GetRect      (LPRECT Rect) const;
        inline bool GetUpdateRect(LPRECT Rect, bool Erase);
        inline bool GetClientRect(LPRECT Rect);

        inline bool SetPos(HWND hWndInsertAfter, int Left, int Top, int Width, int Height, unsigned Flags);
        inline bool Move(int X, int Y, int nWidth, int nHeight, bool bRepaint);

		//bool GetPlacement(WINDOWPLACEMENT *lpwndpl);
		//bool SetPlacement(WINDOWPLACEMENT *lpwndpl);
		//bool BringToTop();

		//bool GetInfo(PWINDOWINFO pwi);

		///HMENU GetMenu();
		//bool SetMenu(HMENU hMenu);

		//int  GetUpdateRgn (HRGN hRgn, BOOL bErase);
		//int  SetRgn       (HRGN hRgn, BOOL bRedraw);
		//int  GetRgn       (HRGN hRgn);
		//int  GetRgnBox    (LPRECT lprc);
		//bool InvalidateRgn(HRGN hRgn, BOOL bErase);
		//bool ValidateRgn  (HRGN hRgn);

		//bool InvalidateRect(const RECT *lpRect, BOOL bErase);
		//bool ValidateRect  (const RECT *lpRect);

		//Properties
		///bool SetPropA      (LPCSTR lpString, HANDLE hData);
		//HANDLE GetPropA    (LPCSTR lpString);
		//HANDLE RemovePropA(LPCSTR lpString);
		//int EnumPropsExA  (PROPENUMPROCEXA lpEnumFunc, LPARAM lParam);
		//int	EnumPropsA    (PROPENUMPROCA lpEnumFunc);

		//bool SetWindowContextHelpId(HWND, DWORD);
		//DWORD GetWindowContextHelpId(HWND);

		//bool EnumChildWindows(HWND hWndParent, WNDENUMPROC lpEnumFunc, LPARAM lParam);			
	};

        inline bool CWindow::Create(DWORD ExStyle,
			LPCTSTR ClassName,
			LPCTSTR WindowName,
			DWORD Style,
			int Left, int Top, int Width, int Height,
            CWindow* Parent,
			HMENU Menu,
			HINSTANCE Instance,
			LPVOID LParam)
		{
			m_Handle = ::CreateWindowEx(ExStyle, ClassName, WindowName, Style, Left, Top, Width, Height, Parent->GetHandle(), Menu, Instance, LParam);
			m_Exist = (m_Handle != NULL);
			return m_Exist;
		}
        //=========================================================================================================================================
        inline LRESULT CWindow::CallWindowProcA(WNDPROC WndProc, UINT Message, WPARAM WParam, LPARAM LParam)
        {
            return ::CallWindowProcA(WndProc, m_Handle, Message, WParam, LParam);
        }

        inline LRESULT CWindow::CallWindowProcW(WNDPROC WndProc, UINT Message, WPARAM WParam, LPARAM LParam)
        {
            return ::CallWindowProcW(WndProc, m_Handle, Message, WParam, LParam);
        }

		//=========================================================================================================================================
        inline HWND CWindow::GetHandle() const
		{
			WL_ASSERT(m_Exist);
			return m_Handle;
		}

        inline void CWindow::SetHandle(HWND Handle)
		{
			if (IsWindow(Handle))
			{
				m_Exist = true;
				m_Handle = Handle;
			}
			else m_Exist = false;
		}
		//=========================================================================================================================================

        inline CWindow* CWindow::GetWndThis(HWND Handle)
		{
			WL_ASSERT(IsWindow(Handle));
			return (CWindow*)::GetWindowLongPtr(Handle, GWLP_USERDATA);
		}

        inline void CWindow::SetWndThis(HWND Handle, CWindow* This)
		{
			WL_ASSERT(IsWindow(Handle));
			::SetLastError(0);
			::SetWindowLong(Handle, GWLP_USERDATA, (LONG_PTR)This);
		}
		//=========================================================================================================================================
		
        inline LONG_PTR CWindow::GetStyle() const
		{
			WL_ASSERT(m_Exist);
			return ::GetWindowLongPtr(m_Handle, GWL_STYLE);
		}

        inline LONG_PTR CWindow::GetExStyle() const
		{
			WL_ASSERT(m_Exist);
			return ::GetWindowLongPtr(m_Handle, GWL_EXSTYLE);
		}

        inline WNDPROC CWindow::GetProc() const
		{
			WL_ASSERT(m_Exist);
			return (WNDPROC)::GetWindowLongPtr(m_Handle, GWLP_WNDPROC);
		}

        inline HINSTANCE CWindow::GetInstance() const
		{
			WL_ASSERT(m_Exist);
			return (HINSTANCE)::GetWindowLongPtr(m_Handle, GWLP_HINSTANCE);
		}

        inline CWindow* CWindow::GetParent() const
		{
			WL_ASSERT(m_Exist);
			return GetWndThis((HWND)::GetWindowLongPtr(m_Handle, GWLP_HWNDPARENT));
		}

        inline LONG_PTR CWindow::GetID() const
		{
			WL_ASSERT(m_Exist);
			return ::GetWindowLongPtr(m_Handle, GWLP_ID);
		}
		//=========================================================================================================================================

        inline void CWindow::SetStyle(LONG_PTR Style)
		{
			WL_ASSERT(m_Exist);
			::SetLastError(0);
			::SetWindowLongPtr(m_Handle, GWL_STYLE, Style);
		}

        inline void CWindow::SetExStyle(LONG_PTR ExStyle)
		{
			WL_ASSERT(m_Exist);
			::SetLastError(0);
			::SetWindowLong(m_Handle, GWL_EXSTYLE, ExStyle);
		}

        inline void CWindow::SetProc(WNDPROC WndProc)
		{
			WL_ASSERT(m_Exist);
			::SetLastError(0);
			::SetWindowLong(m_Handle, GWLP_WNDPROC, (LONG_PTR)WndProc);
		}

        inline void CWindow::SetID(LONG_PTR ID)
		{
			WL_ASSERT(m_Exist);
			::SetLastError(0);
			::SetWindowLong(m_Handle, GWLP_ID, ID);
		}

        inline void CWindow::SetInstance(HINSTANCE HInstance)
		{
			WL_ASSERT(m_Exist);
			::SetLastError(0);
			::SetWindowLong(m_Handle, GWLP_WNDPROC, (LONG_PTR)HInstance);
		}

        inline void CWindow::SetParent(CWindow* Parent)
		{
			WL_ASSERT(m_Exist);
			::SetLastError(0);
			::SetParent(m_Handle, Parent->GetHandle());
		}
		//=========================================================================================================================

        inline bool CWindow::SetText(LPCTSTR Text)
		{
			WL_ASSERT(m_Exist);
			if (::SetWindowText(m_Handle, Text)) return true;
			return false;
		}

        inline int CWindow::GetText(LPTSTR Text, int Quantity) const
		{
			WL_ASSERT(m_Exist);
			return ::GetWindowText(m_Handle, Text, Quantity);
		}
        inline int CWindow::GetTextLength()
		{
			WL_ASSERT(m_Exist);
			return ::GetWindowTextLength(m_Handle);
		}

        inline bool CWindow::Show(int nCmdShow)
        {
            WL_ASSERT(m_Exist);
            return true && ::ShowWindow(m_Handle, nCmdShow);
        }
        inline bool CWindow::ShowAsync(int nCmdShow)
        {
            WL_ASSERT(m_Exist);
            return true && ::ShowWindowAsync(m_Handle, nCmdShow);
        }
		//=========================================================================================================================

        inline bool CWindow::Animate(DWORD Time, DWORD Flags)
        {
            WL_ASSERT(m_Exist);
            return true && ::AnimateWindow(m_Handle, Time, Flags);
        }

        inline bool CWindow::Flash(bool Invert)
        {
            WL_ASSERT(m_Exist);
            return true && ::FlashWindow(m_Handle, (BOOL)Invert);
        }

        inline bool CWindow::FlashEx(UINT Size, DWORD Flags, UINT Count, DWORD TimeOut)
        {
            WL_ASSERT(m_Exist);
            FLASHWINFO FlashStruct;
            FlashStruct.cbSize    = Size;
            FlashStruct.dwFlags   = Flags;
            FlashStruct.dwTimeout = TimeOut;
            FlashStruct.uCount    = Count;
            FlashStruct.hwnd      = m_Handle;
            return true && ::FlashWindowEx(&FlashStruct);
        }

        inline bool CWindow::OpenIcon()
        {
            WL_ASSERT(m_Exist);
            return true && ::OpenIcon(m_Handle);
        }

        inline bool CWindow::Update()
        {
            WL_ASSERT(m_Exist);
            return true && ::UpdateWindow(m_Handle);
        }

        inline bool CWindow::LockUpdate()
        {
            WL_ASSERT(m_Exist);
            return true && ::LockWindowUpdate(m_Handle);
        }

        inline bool CWindow::Enable(bool Enable)
        {
            WL_ASSERT(m_Exist);
            return true && ::EnableWindow(m_Handle, (BOOL)Enable);
        }

        inline bool CWindow::SetFocus()
        {
            WL_ASSERT(m_Exist);
            return true && ::SetFocus(m_Handle);
        }

        inline bool CWindow::Redraw(RECT* rUpdate, HRGN hUpdate, UINT Flags)
        {
            WL_ASSERT(m_Exist);
            return true && ::RedrawWindow(m_Handle, rUpdate, hUpdate, Flags);
        }
        //===========================================================================================================================================

        inline bool CWindow::Close()
		{
			WL_ASSERT(m_Exist);
            return true && ::CloseWindow(m_Handle);
		}

        inline bool CWindow::Destroy()
		{
			WL_ASSERT(m_Exist);
			if (::DestroyWindow(m_Handle) == FALSE)
				return false;
			m_Handle = NULL;
            m_Exist  = false;
			return true;
		}
        inline bool CWindow::IsHungAppWindow()
        {
            WL_ASSERT(m_Exist);
            return true && ::IsHungAppWindow(m_Handle);
        }
        inline bool CWindow::IsChild(CWindow * Parent)
        {
            WL_ASSERT(m_Exist);
            return true && ::IsChild(Parent->GetHandle(), m_Handle);
        }
        inline bool CWindow::IsVisible()
        {
            WL_ASSERT(m_Exist);
            return true && ::IsWindowVisible(m_Handle);
        }
        inline bool CWindow::IsIconic()
        {
            WL_ASSERT(m_Exist);
            return true && ::IsIconic(m_Handle);
        }
        inline bool CWindow::IsZoomed()
        {
            WL_ASSERT(m_Exist);
            return true && ::IsZoomed(m_Handle);
        }
        inline bool CWindow::IsUnicode()
        {
            WL_ASSERT(m_Exist);
            return true && ::IsWindowUnicode(m_Handle);
        }
        inline bool CWindow::IsEnabled()
        {
            WL_ASSERT(m_Exist);
            return true && ::IsWindowEnabled(m_Handle);
        }
        inline bool CWindow::IsExist()
        {
            return m_Exist;
        }
		//=========================================================================================================================================

        inline bool CWindow::GetRect(LPRECT Rect) const
		{
			WL_ASSERT(m_Exist);
			return true && ::GetWindowRect(m_Handle, Rect);
		}

        inline bool CWindow::GetUpdateRect(LPRECT Rect, bool Erase)
        {
            WL_ASSERT(m_Exist);
            return true && ::GetUpdateRect(m_Handle, Rect, (BOOL)Erase);
        }

        inline bool CWindow::GetClientRect(LPRECT Rect)
        {
            WL_ASSERT(m_Exist);
            return true && ::GetClientRect(m_Handle, Rect);
        }
        //=========================================================================================================================================

        inline bool CWindow::SetPos(HWND hWndInsertAfter, int Left, int Top, int Width, int Height, unsigned Flags)
		{
			WL_ASSERT(m_Exist);
			return true && ::SetWindowPos(m_Handle, hWndInsertAfter, Left, Top, Width, Height, Flags);
		}
        inline bool CWindow::Move(int Left, int Top, int Width, int Height, bool Repaint)
        {
            WL_ASSERT(m_Exist);
            return true && ::MoveWindow(m_Handle, Left, Top, Width, Height, (BOOL)Repaint);
        }
}