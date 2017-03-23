#pragma once
#include "WinLib.h"

class CControl : public CBaseWindowC
{
public:
	CControl(CBaseWindow& Parent, ClassInfo& ClsInfo) : CBaseWindowC(ClsInfo) {}
};

class CStdControls : public CBaseWindowC
{
public:
	CStdControls(LPCTSTR WinControlName, LPCTSTR LibControlName) :
		CBaseWindowC(m_WinClassInitialize(WinControlName, LibControlName, ClassInfo())) {}
private:
	WNDPROC m_ControlProcedure;

	virtual bool MessageProcessor(LRESULT* Result, UINT Message, WPARAM WParam, LPARAM LParam);
	ClassInfo& CStdControls::m_WinClassInitialize(LPCTSTR WinControlName, LPCTSTR LibControlName, ClassInfo& ClsInfo);
};

bool CStdControls::MessageProcessor(LRESULT* Result, UINT Message, WPARAM WParam, LPARAM LParam)
{
	*Result = CallWindowProc(m_ControlProcedure, GetHandle(), Message, WParam, LParam);
	return true;
}

ClassInfo& CStdControls::m_WinClassInitialize(LPCTSTR WinControlName, LPCTSTR LibControlName, ClassInfo& ClsInfo)
{
	int er = GetClassInfoEx(Application.hInstance, WinControlName, &ClsInfo.WindowStruct);

	m_ControlProcedure = ClsInfo.WindowStruct.lpfnWndProc;

	ClsInfo.WindowStruct.cbSize = sizeof(ClsInfo.WindowStruct);
	ClsInfo.WindowStruct.lpfnWndProc = StartWindowProcedure;
	ClsInfo.WindowStruct.lpszClassName = LibControlName;

	return ClsInfo;
}

class CWinButton : public CStdControls
{
public:
	CWinButton() : CStdControls(L"BUTTON", L"WinButton") {}
};

class CWinEdit : public CStdControls
{
public:
	CWinEdit() : CStdControls(L"EDIT", L"WinEdit") {}
};

class CWinStatic : public CStdControls
{
public:
	CWinStatic() : CStdControls(L"STATIC", L"WinStatic") {}
};

class CWinComboBox : public CStdControls
{
public:
	CWinComboBox() : CStdControls(L"COMBOBOX", L"WinComboBox") {}
};

class CWinListBox : public CStdControls
{
public:
	CWinListBox() : CStdControls(L"LISTBOX", L"WinListBox") {}
};

class CWinScrollBar : public CStdControls
{
public:
	CWinScrollBar() : CStdControls(L"SCROLLBAR", L"WinScrollBar") {}
};