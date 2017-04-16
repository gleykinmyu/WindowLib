#ifndef WL_STD_CONTROL_HPP
#define WL_STD_CONTROL_HPP

#include <Windows.h>
#include <WinLib/Window.hpp>
#include <WinLib/System.hpp>


namespace Cont
{
	//======================================Standart Windows controls =======================================
  
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
            inline bool Create(CWindow* Parent, WndInfo & Info)
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

#endif