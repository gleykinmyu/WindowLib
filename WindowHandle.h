#pragma once
#include <Windows.h>
#include <assert.h>

#define WINASSERT(expression) if(!(expression)) assert(!"Window id not exist!!!");
#define NULLHWND (HWND)0
#define NOFLAGS 0

namespace wl
{
	class CBaseWindowH
	{
	private:
		HWND m_Handle = NULL;
		bool m_Exist = false;
	public:
        inline bool Create(DWORD ExStyle, LPCTSTR ClassName, LPCTSTR WindowName, DWORD Style,
			int Left, int Top, int Width, int Height, CBaseWindowH* Parent, HMENU Menu, HINSTANCE Instance, LPVOID LParam);

        LRESULT CallWindowProcA(WNDPROC WndProc, UINT Message, WPARAM WParam, LPARAM LParam);
        LRESULT CallWindowProcW(WNDPROC WndProc, UINT Message, WPARAM WParam, LPARAM LParam);

        inline HWND GetHandle() const;
        inline void SetHandle(HWND Handle);

        inline static CBaseWindowH* GetWndThis(HWND Handle);
        inline static void          SetWndThis(HWND Handle, CBaseWindowH* This);

        inline LONG_PTR      GetStyle   () const;
        inline LONG_PTR      GetExStyle () const;
        inline WNDPROC       GetProc    () const;
        inline HINSTANCE     GetInstance() const;
        inline CBaseWindowH* GetParent  () const;
        inline LONG_PTR      GetID      () const;
		 
        inline void SetStyle   (LONG_PTR      Style);
        inline void SetExStyle (LONG_PTR      ExStyle);
        inline void SetProc    (WNDPROC       WndProc);
        inline void SetInstance(HINSTANCE     HInstance);
        inline void SetParent  (CBaseWindowH* newParent);
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
        inline bool IsChild        (CBaseWindowH* Parent);
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

	//CBaseWindowH - base class of WinLibrary

        inline bool CBaseWindowH::Create(DWORD ExStyle,
			LPCTSTR ClassName,
			LPCTSTR WindowName,
			DWORD Style,
			int Left, int Top, int Width, int Height,
            CBaseWindowH* Parent,
			HMENU Menu,
			HINSTANCE Instance,
			LPVOID LParam)
		{
			m_Handle = ::CreateWindowEx(ExStyle, ClassName, WindowName, Style, Left, Top, Width, Height, Parent->GetHandle(), Menu, Instance, LParam);
			m_Exist = (m_Handle != NULL);
			return m_Exist;
		}
        //=========================================================================================================================================
        inline LRESULT CBaseWindowH::CallWindowProcA(WNDPROC WndProc, UINT Message, WPARAM WParam, LPARAM LParam)
        {
            return ::CallWindowProcA(WndProc, m_Handle, Message, WParam, LParam);
        }

        inline LRESULT CBaseWindowH::CallWindowProcW(WNDPROC WndProc, UINT Message, WPARAM WParam, LPARAM LParam)
        {
            return ::CallWindowProcW(WndProc, m_Handle, Message, WParam, LParam);
        }

		//=========================================================================================================================================
        inline HWND CBaseWindowH::GetHandle() const
		{
			WINASSERT(m_Exist);
			return m_Handle;
		}

        inline void CBaseWindowH::SetHandle(HWND Handle)
		{
			if (IsWindow(Handle))
			{
				m_Exist = true;
				m_Handle = Handle;
			}
			else m_Exist = false;
		}
		//=========================================================================================================================================

        inline CBaseWindowH* CBaseWindowH::GetWndThis(HWND Handle)
		{
			WINASSERT(IsWindow(Handle));
			return (CBaseWindowH*)::GetWindowLongPtr(Handle, GWLP_USERDATA);
		}

        inline void CBaseWindowH::SetWndThis(HWND Handle, CBaseWindowH* This)
		{
			WINASSERT(IsWindow(Handle));
			::SetLastError(0);
			::SetWindowLong(Handle, GWLP_USERDATA, (LONG_PTR)This);
		}
		//=========================================================================================================================================
		
        inline LONG_PTR CBaseWindowH::GetStyle() const
		{
			WINASSERT(m_Exist);
			return ::GetWindowLongPtr(m_Handle, GWL_STYLE);
		}

        inline LONG_PTR CBaseWindowH::GetExStyle() const
		{
			WINASSERT(m_Exist);
			return ::GetWindowLongPtr(m_Handle, GWL_EXSTYLE);
		}

        inline WNDPROC CBaseWindowH::GetProc() const
		{
			WINASSERT(m_Exist);
			return (WNDPROC)::GetWindowLongPtr(m_Handle, GWLP_WNDPROC);
		}

        inline HINSTANCE CBaseWindowH::GetInstance() const
		{
			WINASSERT(m_Exist);
			return (HINSTANCE)::GetWindowLongPtr(m_Handle, GWLP_HINSTANCE);
		}

        inline CBaseWindowH* CBaseWindowH::GetParent() const
		{
			WINASSERT(m_Exist);
			return GetWndThis((HWND)::GetWindowLongPtr(m_Handle, GWLP_HWNDPARENT));
		}

        inline LONG_PTR CBaseWindowH::GetID() const
		{
			WINASSERT(m_Exist);
			return ::GetWindowLongPtr(m_Handle, GWLP_ID);
		}
		//=========================================================================================================================================

        inline void CBaseWindowH::SetStyle(LONG_PTR Style)
		{
			WINASSERT(m_Exist);
			::SetLastError(0);
			::SetWindowLongPtr(m_Handle, GWL_STYLE, Style);
		}

        inline void CBaseWindowH::SetExStyle(LONG_PTR ExStyle)
		{
			WINASSERT(m_Exist);
			::SetLastError(0);
			::SetWindowLong(m_Handle, GWL_EXSTYLE, ExStyle);
		}

        inline void CBaseWindowH::SetProc(WNDPROC WndProc)
		{
			WINASSERT(m_Exist);
			::SetLastError(0);
			::SetWindowLong(m_Handle, GWLP_WNDPROC, (LONG_PTR)WndProc);
		}

        inline void CBaseWindowH::SetID(LONG_PTR ID)
		{
			WINASSERT(m_Exist);
			::SetLastError(0);
			::SetWindowLong(m_Handle, GWLP_ID, ID);
		}

        inline void CBaseWindowH::SetInstance(HINSTANCE HInstance)
		{
			WINASSERT(m_Exist);
			::SetLastError(0);
			::SetWindowLong(m_Handle, GWLP_WNDPROC, (LONG_PTR)HInstance);
		}

        inline void CBaseWindowH::SetParent(CBaseWindowH* Parent)
		{
			WINASSERT(m_Exist);
			::SetLastError(0);
			::SetParent(m_Handle, Parent->GetHandle());
		}
		//=========================================================================================================================

        inline bool CBaseWindowH::SetText(LPCTSTR Text)
		{
			WINASSERT(m_Exist);
			if (::SetWindowText(m_Handle, Text)) return true;
			return false;
		}

        inline int CBaseWindowH::GetText(LPTSTR Text, int Quantity) const
		{
			WINASSERT(m_Exist);
			return ::GetWindowText(m_Handle, Text, Quantity);
		}
        inline int CBaseWindowH::GetTextLength()
		{
			WINASSERT(m_Exist);
			return ::GetWindowTextLength(m_Handle);
		}

        inline bool CBaseWindowH::Show(int nCmdShow)
        {
            WINASSERT(m_Exist);
            return true && ::ShowWindow(m_Handle, nCmdShow);
        }
        inline bool CBaseWindowH::ShowAsync(int nCmdShow)
        {
            WINASSERT(m_Exist);
            return true && ::ShowWindowAsync(m_Handle, nCmdShow);
        }
		//=========================================================================================================================

        inline bool CBaseWindowH::Animate(DWORD Time, DWORD Flags)
        {
            WINASSERT(m_Exist);
            return true && ::AnimateWindow(m_Handle, Time, Flags);
        }

        inline bool CBaseWindowH::Flash(bool Invert)
        {
            WINASSERT(m_Exist);
            return true && ::FlashWindow(m_Handle, (BOOL)Invert);
        }

        inline bool CBaseWindowH::FlashEx(UINT Size, DWORD Flags, UINT Count, DWORD TimeOut)
        {
            WINASSERT(m_Exist);
            FLASHWINFO FlashStruct;
            FlashStruct.cbSize    = Size;
            FlashStruct.dwFlags   = Flags;
            FlashStruct.dwTimeout = TimeOut;
            FlashStruct.uCount    = Count;
            FlashStruct.hwnd      = m_Handle;
            return true && ::FlashWindowEx(&FlashStruct);
        }

        inline bool CBaseWindowH::OpenIcon()
        {
            WINASSERT(m_Exist);
            return true && ::OpenIcon(m_Handle);
        }

        inline bool CBaseWindowH::Update()
        {
            WINASSERT(m_Exist);
            return true && ::UpdateWindow(m_Handle);
        }

        inline bool CBaseWindowH::LockUpdate()
        {
            WINASSERT(m_Exist);
            return true && ::LockWindowUpdate(m_Handle);
        }

        inline bool CBaseWindowH::Enable(bool Enable)
        {
            WINASSERT(m_Exist);
            return true && ::EnableWindow(m_Handle, (BOOL)Enable);
        }

        inline bool CBaseWindowH::SetFocus()
        {
            WINASSERT(m_Exist);
            return true && ::SetFocus(m_Handle);
        }

        inline bool CBaseWindowH::Redraw(RECT* rUpdate, HRGN hUpdate, UINT Flags)
        {
            WINASSERT(m_Exist);
            return true && ::RedrawWindow(m_Handle, rUpdate, hUpdate, Flags);
        }
        //===========================================================================================================================================

        inline bool CBaseWindowH::Close()
		{
			WINASSERT(m_Exist);
            return true && ::CloseWindow(m_Handle);
		}

        inline bool CBaseWindowH::Destroy()
		{
			WINASSERT(m_Exist);
			if (::DestroyWindow(m_Handle) == FALSE)
				return false;
			m_Handle = NULL;
            m_Exist  = false;
			return true;
		}
        inline bool CBaseWindowH::IsHungAppWindow()
        {
            WINASSERT(m_Exist);
            return true && ::IsHungAppWindow(m_Handle);
        }
        inline bool CBaseWindowH::IsChild(CBaseWindowH * Parent)
        {
            WINASSERT(m_Exist);
            return true && ::IsChild(Parent->GetHandle(), m_Handle);
        }
        inline bool CBaseWindowH::IsVisible()
        {
            WINASSERT(m_Exist);
            return true && ::IsWindowVisible(m_Handle);
        }
        inline bool CBaseWindowH::IsIconic()
        {
            WINASSERT(m_Exist);
            return true && ::IsIconic(m_Handle);
        }
        inline bool CBaseWindowH::IsZoomed()
        {
            WINASSERT(m_Exist);
            return true && ::IsZoomed(m_Handle);
        }
        inline bool CBaseWindowH::IsUnicode()
        {
            WINASSERT(m_Exist);
            return true && ::IsWindowUnicode(m_Handle);
        }
        inline bool CBaseWindowH::IsEnabled()
        {
            WINASSERT(m_Exist);
            return true && ::IsWindowEnabled(m_Handle);
        }
        inline bool CBaseWindowH::IsExist()
        {
            return m_Exist;
        }
		//=========================================================================================================================================

        inline bool CBaseWindowH::GetRect(LPRECT Rect) const
		{
			WINASSERT(m_Exist);
			return true && ::GetWindowRect(m_Handle, Rect);
		}

        inline bool CBaseWindowH::GetUpdateRect(LPRECT Rect, bool Erase)
        {
            WINASSERT(m_Exist);
            return true && ::GetUpdateRect(m_Handle, Rect, (BOOL)Erase);
        }

        inline bool CBaseWindowH::GetClientRect(LPRECT Rect)
        {
            WINASSERT(m_Exist);
            return true && ::GetClientRect(m_Handle, Rect);
        }
        //=========================================================================================================================================

        inline bool CBaseWindowH::SetPos(HWND hWndInsertAfter, int Left, int Top, int Width, int Height, unsigned Flags)
		{
			WINASSERT(m_Exist);
			return true && ::SetWindowPos(m_Handle, hWndInsertAfter, Left, Top, Width, Height, Flags);
		}
        inline bool CBaseWindowH::Move(int Left, int Top, int Width, int Height, bool Repaint)
        {
            WINASSERT(m_Exist);
            return true && ::MoveWindow(m_Handle, Left, Top, Width, Height, (BOOL)Repaint);
        }
}
