#pragma once
#include "WinLib.h"

namespace wsl
{
	class CStdControls : public CWindow
	{
	public:
		CStdControls(LPCTSTR WinControlName, LPCTSTR LibControlName) :	
			CWindow(m_WinClassInitialize(WinControlName, LibControlName, ClassInfo())) {}

		LRESULT ControlProc(UINT Message, WPARAM WParam, LPARAM LParam)
		{
			return (*m_ControlProcedure)(GetHandle(), Message, WParam, LParam);
		}

		bool Create(CWindow* Parent, WndInfo& Info) { return CWindow::Create(Parent, Info.Style(WS_CHILD)); }

	private:
		WNDPROC m_ControlProcedure;

		virtual bool MessageProcessor(LRESULT* Result, UINT Message, WPARAM WParam, LPARAM LParam);
		ClassInfo& CStdControls::m_WinClassInitialize(LPCTSTR WinControlName, LPCTSTR LibControlName, ClassInfo& ClsInfo);
	};

	bool CStdControls::MessageProcessor(LRESULT* Result, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		*Result = ::CallWindowProc(m_ControlProcedure, GetHandle(), Message, WParam, LParam);
		return true;
	}

	ClassInfo& CStdControls::m_WinClassInitialize(LPCTSTR WinControlName, LPCTSTR LibControlName, ClassInfo& ClsInfo)
	{
		WNDCLASSEX WndStruct;
		::GetClassInfoEx(Application->hInstance, WinControlName, &WndStruct);

		m_ControlProcedure = WndStruct.lpfnWndProc;
		ClsInfo.ClassStruct.ClassName = LibControlName;
		return ClsInfo;
	}

	//======================================Standart Windows constrols =======================================

	class CStdButton : public CStdControls
	{
	public:	
		CStdButton() : CStdControls(L"BUTTON", L"WinButton") {}
	};

	class CStdEdit : public CStdControls
	{
	public:
		CStdEdit() : CStdControls(L"EDIT", L"WinEdit") {}
	};

	class CStdStatic : public CStdControls
	{
	public:
		CStdStatic() : CStdControls(L"STATIC", L"WinStatic") {}
	};

	class CStdComboBox : public CStdControls
	{
	public:
		CStdComboBox() : CStdControls(L"COMBOBOX", L"WinComboBox") {}
	};

	class CStdListBox : public CStdControls
	{
	public:
		CStdListBox() : CStdControls(L"LISTBOX", L"WinListBox") {}
	};

	class CStdScrollBar : public CStdControls
	{
	public:
		CStdScrollBar() : CStdControls(L"SCROLLBAR", L"WinScrollBar") {}
	};
}

