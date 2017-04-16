#ifndef WL_MODULE_HPP
#define WL_MODULE_HPP
#include <Windows.h>

namespace System
{
	class CModule
	{
	public:
		HINSTANCE Instance = GetModuleHandle(0);
	};

	const CModule m_Module;
	const CModule* Module = &m_Module;
}

#endif //!WL_MODULE_HPP

/*
WINUSERAPI
HWND
WINAPI
GetForegroundWindow(
	VOID);

WINUSERAPI
int
WINAPI
MapWindowPoints(
	_In_opt_ HWND hWndFrom,
	_In_opt_ HWND hWndTo,
	_Inout_updates_(cPoints) LPPOINT lpPoints,
	_In_ UINT cPoints);
WINUSERAPI
HWND
WINAPI
WindowFromPoint(
	_In_ POINT Point);

WINUSERAPI
HWND
WINAPI
WindowFromPhysicalPoint(
	_In_ POINT Point);
WINUSERAPI
HWND
WINAPI
FindWindowA(
	_In_opt_ LPCSTR lpClassName,
	_In_opt_ LPCSTR lpWindowName);
WINUSERAPI
HWND
WINAPI
FindWindowExA(
	_In_opt_ HWND hWndParent,
	_In_opt_ HWND hWndChildAfter,
	_In_opt_ LPCSTR lpszClass,
	_In_opt_ LPCSTR lpszWindow);

WINUSERAPI
HWND
WINAPI
GetShellWindow(
	VOID);
WORD
WINAPI
TileWindows(
	_In_opt_ HWND hwndParent,
	_In_ UINT wHow,
	_In_opt_ CONST RECT * lpRect,
	_In_ UINT cKids,
	_In_reads_opt_(cKids) const HWND FAR * lpKids);

WINUSERAPI
WORD
WINAPI CascadeWindows(
	_In_opt_ HWND hwndParent,
	_In_ UINT wHow,
	_In_opt_ CONST RECT * lpRect,
	_In_ UINT cKids,
	_In_reads_opt_(cKids) const HWND FAR * lpKids);
WINUSERAPI
BOOL
WINAPI
WinHelpA(
	_In_opt_ HWND hWndMain,
	_In_opt_ LPCSTR lpszHelp,
	_In_ UINT uCommand,
	_In_ ULONG_PTR dwData);

WINUSERAPI
HMONITOR
WINAPI
MonitorFromWindow(
	_In_ HWND hwnd,
	_In_ DWORD dwFlags);
WINUSERAPI
UINT
WINAPI
ArrangeIconicWindows(
	_In_ HWND hWnd);
WINUSERAPI
HWND
WINAPI
RealChildWindowFromPoint(
	_In_ HWND hwndParent,
	_In_ POINT ptParentClientCoords);
WINUSERAPI
UINT
WINAPI
RealGetWindowClassA(
	_In_ HWND hwnd,
	_Out_writes_to_(cchClassNameMax, return) LPSTR ptszClassName,
	_In_ UINT cchClassNameMax);

WINBASEAPI
HWND
APIENTRY
GetConsoleWindow(
	VOID
);
HWND
WINAPI
GetActiveWindow(
	VOID);

WINUSERAPI
HWND
WINAPI
GetFocus(
	VOID);
WINUSERAPI
HWND
WINAPI
GetCapture(
	VOID);
WINUSERAPI
HWND
WINAPI
SetCapture();
WINUSERAPI
HWND
WINAPI
ChildWindowFromPoint(
	_In_ HWND hWndParent,
	_In_ POINT Point);

WINUSERAPI
HWND
WINAPI
ChildWindowFromPointEx(
	_In_ HWND hwnd,
	_In_ POINT pt,
	_In_ UINT flags);
BOOL
WINAPI
SetForegroundWindow(
	_In_ HWND hWnd);
WINUSERAPI
BOOL
WINAPI
RegisterShellHookWindow(
	_In_ HWND hwnd);
WINUSERAPI
BOOL
WINAPI
DeregisterShellHookWindow(
	_In_ HWND hwnd);
HWND
WINAPI
GetTopWindow(HWND);
HWND GetAncestor(HWND, UINT gaFlags);
*/