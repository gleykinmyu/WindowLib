#pragma once
#include "WinLib.h"

namespace wl
{
	class CStdControls : public CWindowRoot
	{
	public:
		CStdControls(LPCTSTR WinControlName, LPCTSTR LibControlName);
		inline void ControlProc(CEvent* Event);
        inline bool Create(CWindow* Parent, WndInfo& Info);

	private:
		WNDPROC m_ControlProcedure;
		virtual bool MessageProcessor(CEvent* Event);
	};

	CStdControls::CStdControls(LPCTSTR WinControlName, LPCTSTR LibControlName)
	{
        WNDCLASSEX WndStruct;
        ::GetClassInfoEx(Module->Instance, WinControlName, &WndStruct);
        m_ControlProcedure = WndStruct.lpfnWndProc;
        ClassInfo.ClassName(LibControlName);
	}

    inline void CStdControls::ControlProc(CEvent* Event)
	{
		Event->Result = CWindow::CallWindowProcA(m_ControlProcedure, Event->Message, Event->WParam, Event->LParam);
	}

    inline bool CStdControls::Create(CWindow* Parent, WndInfo& Info)
	{
		return CWindowRoot::Create(Parent, Info.Style(WS_CHILD));
	}

    bool CStdControls::MessageProcessor(CEvent* Event)
	{
		ControlProc(Event);
		return true;
	}
	//======================================Standart Windows constrols =======================================
  
	class CStdButtonRoot : public CStdControls
	{
	public:
		CStdButtonRoot() : CStdControls(TEXT("BUTTON"), TEXT("WinButton")) {}
	};

    namespace StdCtrl
    {
        class CCheckBox : public CStdButtonRoot
        {
        public:
            inline bool Create(CWindow* Parent, WndInfo& Info)
            {
                return CStdControls::Create(Parent, Info.Style(BS_AUTOCHECKBOX));
            }
        };

        class CRadioButton : public CStdButtonRoot
        {
        public:
            inline bool Create(CWindow* Parent, WndInfo& Info)
            {
                return CStdControls::Create(Parent, Info.Style(BS_AUTORADIOBUTTON));
            }
        };

        class CButton : public CStdButtonRoot {};

        class CEdit : public CStdControls
        {
        public:
            CEdit() : CStdControls(TEXT("EDIT"), TEXT("WinEdit")) {}
        };

        class CStatic : public CStdControls
        {
        public:
            CStatic() : CStdControls(TEXT("STATIC"), TEXT("WinStatic")) {}
        };

        class CComboBox : public CStdControls
        {
        public:
            CComboBox() : CStdControls(TEXT("COMBOBOX"), TEXT("WinComboBox")) {}
        };

        class CListBox : public CStdControls
        {
        public:
            CListBox() : CStdControls(TEXT("LISTBOX"), TEXT("WinListBox")) {}
        };

        class CScrollBar : public CStdControls
        {
        public:
            CScrollBar() : CStdControls(TEXT("SCROLLBAR"), TEXT("WinScrollBar")) {}
        };
    }
//============================================================================================================================

}