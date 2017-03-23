#pragma once
#include "WinLib.h"

class CControl : public CWindowChild
{
public:
	CControl(CWindowContainer* Parent, ClassInfo& ClsInfo) : CWindowChild(Parent, ClsInfo) {}
};

class CStdControls : public CControl
{
public:
	CStdControls(LPCTSTR WinControlName, LPCTSTR LibControlName, CWindowContainer* Parent) :
		CControl(Parent, m_WinClassInitialize(WinControlName, LibControlName, ClassInfo())) {}
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
	WNDCLASSEX WndStruct;
	GetClassInfoEx(_Application.hInstance, WinControlName, &WndStruct);

	m_ControlProcedure = WndStruct.lpfnWndProc;
	ClsInfo.ClassStruct.ClassName = LibControlName;
	return ClsInfo;
}

class CWinButton : public CStdControls
{
public:
	CWinButton(CWindowContainer* Parent) : CStdControls(L"BUTTON", L"WinButton", Parent) {}
	struct ClickInfo
	{
		UINT Flags;
		UINT Left;
		UINT Top;
	};
private:
	virtual void MessagePostProcessor(UINT Message, WPARAM WParam, LPARAM LParam)
	{
		if (Message == WM_LBUTTONDOWN)
			Parent->ChildProcessor(this, (UINT)WParam, (UINT)LOWORD(LParam), (UINT)HIWORD(LParam));
	}
#define GETARGS_BTN_CLICK(Struct) do { va_list ArgPtr; va_start(ArgPtr, Caller); \
									        Struct.Flags = va_arg(ArgPtr, UINT); \
                                             Struct.Left = va_arg(ArgPtr, UINT); \
                                              Struct.Top = va_arg(ArgPtr, UINT); } while(0)
};

/*
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
*/