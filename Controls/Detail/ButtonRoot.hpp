#ifndef WL_BUTTON_ROOT_HPP
#define WL_BUTTON_ROOT_HPP

#include <Windows.h>
#include <WinLib/Window.hpp>
#include <WinLib/Controls/Detail/StdControlRoot.hpp>
#include <WinLib/Controls/ControlsEnums.hpp>
#include <WinLib/Utility.hpp>

namespace ControlsDetail
{
	typedef enum class bt : unsigned
	{
		PushBtn      = BS_PUSHBUTTON,
		DefPushBtn   = BS_DEFPUSHBUTTON,

		SplitBtn     = BS_SPLITBUTTON,
		DefSplitBtn  = BS_DEFSPLITBUTTON,

		CmdLink      = BS_COMMANDLINK,
		DefCmdLink   = BS_DEFCOMMANDLINK,

		CheckBox     = BS_CHECKBOX,
		AutoCheckBox = BS_AUTOCHECKBOX,

		TState       = BS_3STATE,
		Auto3State   = BS_AUTO3STATE,

		RadioBtn     = BS_RADIOBUTTON,
		AutoRadioBtn = BS_AUTORADIOBUTTON,

		GroupBox     = BS_GROUPBOX,

		UserBtn      = BS_USERBUTTON,
		PushBox      = BS_PUSHBOX
	} EButtonTypes;

	class CStdButtonRoot : public CStdControlRoot
	{
	public:
		DECLARE_WINDOW_SUPERCLASS(TEXT("WINBUTTON"), TEXT("BUTTON"))
		
		inline bool Create(Window::CWindowHandle Parent, EButtonTypes BtnType, Window::WndInfo & Info);
		inline bool isPushed();
		inline bool isFocus();
		inline void Click();
	};

	inline bool CStdButtonRoot::Create(Window::CWindowHandle Parent, EButtonTypes BtnType, Window::WndInfo & Info)
	{
		Info.WindowStruct.wiStyle.addValue((unsigned)BtnType);
		return CStdControlRoot::Create(Parent, Info);
	}

	inline bool CStdButtonRoot::isPushed()
	{
		return (BST_PUSHED & SendMessage(BM_GETSTATE, 0, 0)) && true;
	}

	inline bool CStdButtonRoot::isFocus()
	{
		return (BST_FOCUS & SendMessage(BM_GETSTATE, 0, 0)) && true;
	}

	inline void CStdButtonRoot::Click()
	{
		SendMessage(BM_CLICK, 0, 0);
	}

	class CStdCheckBoxRoot : public CStdButtonRoot
	{
	public:
		inline bool isChecked();

	};

	inline bool CStdCheckBoxRoot::isChecked()
	{
		return (BST_CHECKED & SendMessage(BM_GETSTATE, 0, 0)) && true;
	}

	class CStd3StateRoot : public CStdCheckBoxRoot
	{
	public:
		inline bool isNeutral();
	};

	inline bool CStd3StateRoot::isNeutral()
	{
		return (BST_INDETERMINATE & SendMessage(BM_GETSTATE, 0, 0)) && true;
	}
};

#endif //!WL_BUTTON_ROOT_HPP