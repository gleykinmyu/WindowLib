#pragma once
#include "WinLib.h"

namespace wl
{
	class CStdControls : public CBaseWindow
	{
	public:
		CStdControls(LPCTSTR WinControlName, LPCTSTR LibControlName);
		inline void ControlProc(CEvent* Event);
        inline bool Create(CBaseWindow* Parent, WndInfo& Info);

	private:
		WNDPROC m_ControlProcedure;

		virtual bool MessageProcessor(CEvent* Event);
		ClassInfo& CStdControls::m_WinClassInitialize(LPCTSTR WinControlName, LPCTSTR LibControlName, ClassInfo& ClsInfo);

        inline UINT GetControlID();
	};

	CStdControls::CStdControls(LPCTSTR WinControlName, LPCTSTR LibControlName) :
		CBaseWindow(m_WinClassInitialize(WinControlName, LibControlName, ClassInfo()))
	{

	}

    inline void CStdControls::ControlProc(CEvent* Event)
	{
		Event->Result = CBaseWindowH::CallWindowProc(m_ControlProcedure, Event->Message, Event->WParam, Event->LParam);
	}

    inline bool CStdControls::Create(CBaseWindow* Parent, WndInfo& Info)
	{
		return CBaseWindow::Create(Parent, Info.Style(WS_CHILD).Menu((HMENU)GetControlID()));
	}

    bool CStdControls::MessageProcessor(CEvent* Event)
	{
		ControlProc(Event);
		return true;
	}

	ClassInfo& CStdControls::m_WinClassInitialize(LPCTSTR WinControlName, LPCTSTR LibControlName, ClassInfo& ClsInfo)
	{
		WNDCLASSEX WndStruct;

		::GetClassInfoEx(Module->Instance, WinControlName, &WndStruct);

		m_ControlProcedure = WndStruct.lpfnWndProc;
		ClsInfo.ClassStruct.ClassName = LibControlName;
		return ClsInfo;
	}

    inline UINT CStdControls::GetControlID()
    {
        static UINT m_ID = 0xFF;
        m_ID++;
        return m_ID;
    }

	//======================================Standart Windows constrols =======================================
	class CStdButton : public CStdControls
	{
	public:
		CStdButton() : CStdControls(TEXT("BUTTON"), TEXT("WinButton")) {}
	};

	class CStdEdit : public CStdControls
	{
	public:
		CStdEdit() : CStdControls(TEXT("EDIT"), TEXT("WinEdit")) {}
	};

	class CStdStatic : public CStdControls
	{
	public:
		CStdStatic() : CStdControls(TEXT("STATIC"), TEXT("WinStatic")) {}
	};

	class CStdComboBox : public CStdControls
	{
	public:
		CStdComboBox() : CStdControls(TEXT("COMBOBOX"), TEXT("WinComboBox")) {}
	};

	class CStdListBox : public CStdControls
	{
	public:
		CStdListBox() : CStdControls(TEXT("LISTBOX"), TEXT("WinListBox")) {}
	};

	class CStdScrollBar : public CStdControls
	{
	public:
		CStdScrollBar() : CStdControls(TEXT("SCROLLBAR"), TEXT("WinScrollBar")) {}
	};
}