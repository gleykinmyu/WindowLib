#ifndef WL_STD_BUTTON_HPP
#define WL_STD_BUTTON_HPP

#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <WinLib/Utility.hpp>
#include <WinLib/Controls/Detail/ButtonRoot.hpp>

namespace Controls
{
	template<ControlsDetail::EButtonTypes BtnType>
	class  CStdButtonT : public ControlsDetail::CStdButtonRoot
	{
		static_assert(BtnType == ControlsDetail::bt::PushBtn || 
					  BtnType == ControlsDetail::bt::CmdLink || 
					  BtnType == ControlsDetail::bt::SplitBtn, TEXT("YOU CHOUSE WRONG BUTTON TYPE"));

		typedef Utility::CProperty<Utility::RW, bool, CStdButtonT> rwBOOL;

	public:
		inline CStdButtonT()
		{
			DefOption.Init(this, &CStdButtonT::getDefault, &CStdButtonT::setDefault);
		}

		inline bool Create(Window::CWindowHandle Parent, Window::WndInfo & Info)
		{
			return CStdButtonRoot::Create(Parent, BtnType, Info);
		}

		rwBOOL DefOption;

	private:
		inline void setDefault(bool Flag)
		{
			bool PrevState = getDefault();

			if (Flag && !PrevState)
			{
				Window::WNDSTYLE BitStyle = Style;
				BitStyle = (BitStyle & ~0xF) | ((unsigned)BtnType + 1);
				Style.addValue((unsigned)BitStyle);
				return;
			}
				
			if (!Flag && PrevState)
			{
				Window::WNDSTYLE BitStyle = Style;
				BitStyle = (BitStyle & ~0xF) | (unsigned)BtnType;
				Style.addValue((unsigned)BitStyle);
				return;
			}
		}

		inline bool getDefault() const
		{
			Window::WNDSTYLE BitStyle = Style;
			return (BitStyle & 0xF) == ((unsigned)BtnType + 1);
		}
	};

	typedef CStdButtonT<ControlsDetail::EButtonTypes::PushBtn>  CButton;
	typedef CStdButtonT<ControlsDetail::EButtonTypes::SplitBtn> CSplitButton;
	typedef CStdButtonT<ControlsDetail::EButtonTypes::CmdLink>  CCmdLink;
}

#endif //!WL_STD_BUTTON_HPP